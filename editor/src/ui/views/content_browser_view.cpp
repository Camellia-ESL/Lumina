#include "content_browser_view.h"

#include "editor_assets/editor_asset_manager.h"
#include "ui/ui_objects_lib/lumina_ui_buttons.h"

#include "ui/ui_shared_vars.h"

#include "ImGui/imgui.h"

namespace lumina_editor
{
	void content_browser_view::on_create()
	{
		// Store the root node as selected directory
		selected_directory_id_ = project_handler::get_singleton().get_content_browser().get_content().get_root_node().id;
	}

	void content_browser_view::on_render()
	{
		if (!ui_shared_vars::IS_CONTENT_BROWSER_VIEW_OPEN)
			return;

		ImGui::Begin("Content Browser");

		// Get's an handle to the content browser
		project_content_browser& content_browser_handle = project_handler::get_singleton().get_content_browser();
		project_content_browser::content_t& content = content_browser_handle.get_content();

		// Refresh the content of the project file system
		if (ImGui::ImageButton(
			"Refresh", 
			LUMINA_EDITOR_GET_ASSET(editor_asset_manager::textures::refresh, lumina::texture)->get_native_resource_buffer(), 
			{12 , 12}
		))
		{
			content_browser_handle.reload_content();
			selected_directory_id_ = content.get_root_node().id;
		}

		// Check if there is not a selected directory
		if (selected_directory_id_ == "")
			return;
		
		bool is_root_node = selected_directory_id_ == content_browser_handle.get_content().get_root_node().id;
		project_content_browser::directory_t& selected_dir_content = 
			is_root_node ? content.get_root_node() : *content.get_node("", selected_directory_id_);

		// Set the refresh and back button on the sameline
		ImGui::SameLine();

		// Display a back button
		if (ImGui::ArrowButton("back_button", ImGuiDir_Left) && !is_root_node)
			selected_directory_id_ = content.get_parent(selected_dir_content.parent_id)->id;

		// The image buttons size
		const float img_button_size = 50.0f;
		const float img_margin_size = img_button_size * 0.20f;
		uint32_t drawn_elements_new_line = 0;

		// Automatically calculate if the next item to render will fit the window or not and goes to new line accordingly
		const auto eval_next_item_line_pos =
			[&]() -> void
			{
				// Check wheter if the available content region is exceed and goes to new line
				if ((uint32_t)(ImGui::GetWindowSize().x / (img_button_size + (img_margin_size * 2))) == drawn_elements_new_line)
					drawn_elements_new_line = 0;
				else
					ImGui::SameLine();
			};

		// @bug-[content_browser_view]: Fix item names colliding if being too long.
		// Display the directories inside the selected directory
		for (uint32_t i = 0; i < selected_dir_content.next_nodes.size(); i++)
		{
			// Get's the directory iterated
			project_content_browser::directory_t& directory = selected_dir_content.next_nodes[i];

			// Display the folder button
			if (lumina_ui_buttons::img_txt_button(
				directory.name,
				directory.id,
				*LUMINA_EDITOR_GET_ASSET(editor_asset_manager::textures::folder, lumina::texture),
				-1.0f,
				{ img_button_size , img_button_size }
			))
				selected_directory_id_ = directory.id;

			eval_next_item_line_pos();

			drawn_elements_new_line++;
		}

		// Display the resources inside the selected directory
		for (uint32_t i = 0; i < selected_dir_content.node_elements.size(); i++)
		{
			project_content_browser::cb_resource_t& resource = selected_dir_content.node_elements[i];

			// Display the resource button
			lumina_ui_buttons::img_txt_button(
				resource.name,
				resource.path,
				*LUMINA_EDITOR_GET_ASSET(editor_asset_manager::textures::document, lumina::texture),
				-1.0f,
				{ img_button_size , img_button_size }
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
						LUMINA_EDITOR_GET_ASSET(editor_asset_manager::textures::document, lumina::texture)->get_native_resource_buffer(), 
						{ img_button_size , img_button_size }
					);
					ImGui::EndTooltip();
				}

				// Set's the drag and drop payload data
				ImGui::SetDragDropPayload(
					ui_shared_vars::FILE_TO_LOAD_DAD_ID,
					resource.path.c_str(),
					resource.path.size(),
					ImGuiCond_Once
				);

				ImGui::EndDragDropSource();
			}

			eval_next_item_line_pos();

			drawn_elements_new_line++;
		}

		ImGui::End();
	}
}