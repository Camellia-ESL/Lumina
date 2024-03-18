#include "assets_browser_view.h"

#include "ui/ui_shared_vars.h"
#include "ui/ui_objects_lib/lumina_ui_input_text.h"
#include "ui/ui_objects_lib/lumina_ui_buttons.h"

#include "lumina.h"

#include "ImGui/imgui.h"
#include "spdlog/spdlog.h"

namespace lumina_editor
{
	void assets_browser_view::render_import_asset_popup()
	{
		if (ImGui::BeginPopupModal("Import Asset"))
		{
			// Define helper variables and lambdas for the project creation
			static bool first_opening = true;
			static int selected_asset_type = 0;
			static std::string asset_name{ "" };
			static lumina_ui_input_text asset_name_input_text{};

			// NOTE: This array must contain the names of the asset types in the same order as they are in the enum that contains all the asset types
			// for more info watch inside resource_types_e -> asset.h inside lumina engine.
			int asset_type_names_count = 1;
			const char* const asset_type_names[] =
			{
				"TEXTURE"
			};

			// Register the buffer in the text input label
			if (first_opening)
			{
				asset_name_input_text.bind_text_buffer(&asset_name);
				first_opening = false;
			}

			// Close the popup and clear buffers
			auto close_popup = 
				[&]() -> void
				{
					asset_name_input_text.clear_buffer();
					dragged_file_path_.clear();
					ImGui::CloseCurrentPopup();
				};

			// Render UI
			asset_name_input_text.render("Name");

			ImGui::Combo("Asset Type", &selected_asset_type, asset_type_names, asset_type_names_count);

			if (ImGui::SmallButton("Import") && !asset_name.empty())
			{
				// We need to sum 1 to the selected asset type because we don't consider NULL_ASSET_TYPE as a valid asset type so we start from 1

				// Tries to import as a texture
				if ((lumina::asset::resource_types_e)(selected_asset_type + 1) == lumina::asset::resource_types_e::TEXTURE)
				{
					//@enhancement-[assets_browser_view]: Add an error check and display the error if something goes wrong.
					lumina::texture* texture_buffer = new lumina::texture();
					bool load_result = texture_buffer->load_from_file(dragged_file_path_);

					// If import succeded load texture in the asset atlas
					if (load_result)
					{
						lumina::asset& asset_loaded = lumina::asset_atlas::get_singleton().get_registry().create_asset(texture_buffer, dragged_file_path_);
						asset_loaded.set_name(asset_name);
						close_popup();
					}
				}
			}

			ImGui::SameLine();

			if (ImGui::SmallButton("Close"))
				close_popup();

			ImGui::EndPopup();
		}
	}

	void assets_browser_view::render_assets()
	{
		auto& asset_registry = lumina::asset_atlas::get_singleton().get_registry().get_registry();

		for (auto& [asset_id, asset] : asset_registry)
		{
			// If the type is texture simply shows it as a image button with the description
			if (asset->get_type() == lumina::asset::resource_types_e::TEXTURE)
			{
				lumina_ui_buttons::img_txt_button(
					asset->get_asset_name(),
					asset_id,
					*asset->get_resource<lumina::texture>()
				);

				// Create's the drag and drop source
				ImGuiDragDropFlags src_flags = 0;
				src_flags |= ImGuiDragDropFlags_SourceNoDisableHover;     // Keep the source displayed as hovered
				src_flags |= ImGuiDragDropFlags_SourceAllowNullID;		  // Fix item not having a unique id

				if (ImGui::BeginDragDropSource(src_flags))
				{
					// Drag transport tooltip
					if (ImGui::BeginTooltip())
					{
						ImGui::Image(
							asset->get_resource<lumina::texture>()->get_native_resource_buffer(),
							{ 50.0f , 50.0f }
						);
						ImGui::EndTooltip();
					}

					// Set's the drag and drop payload data
					ImGui::SetDragDropPayload(
						ui_shared_vars::TEXTURE_DAD_ID,
						&asset,
						sizeof(std::shared_ptr<lumina::asset>),
						ImGuiCond_Once
					);

					ImGui::EndDragDropSource();
				}
			}
		}
	}

	void assets_browser_view::on_render()
	{
		ImGui::Begin("Assets");

		// Render a child to accept the drag and drop of files to load (IMPORTANT: everything inside the asset browser goes inside this child)
		ImGui::BeginChild("drag_and_drop_accepter");

		// Render all the imported assets 
		render_assets();

		ImGui::EndChild();

		// Start accepting drag and drops
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* file_drag_and_drop_payload = ImGui::AcceptDragDropPayload(ui_shared_vars::FILE_TO_LOAD_DAD_ID))
			{
				// Allocates memory to handle the drop response and copy data inside it
				char* path_parsed = (char*)malloc(file_drag_and_drop_payload->DataSize + l_byte8_size);
				memcpy(path_parsed, file_drag_and_drop_payload->Data, file_drag_and_drop_payload->DataSize);
				memcpy(path_parsed + file_drag_and_drop_payload->DataSize, "\0", l_byte8_size);

				// Copy data in a string 
				dragged_file_path_ = path_parsed;

				// Free the memory previously allocated
				free(path_parsed);

				ImGui::OpenPopup("Import Asset");
			}
			ImGui::EndDragDropTarget();
		}

		// Render the import asset popup if opened (for example when dragging a file in the window)
		render_import_asset_popup();

		ImGui::End();
	}
}