#include "content_browser_view.h"

#include "editor_assets/editor_asset_manager.h"
#include "ui/ui_objects_lib/lumina_ui_buttons.h"

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
		ImGui::Begin("Content Browser");

		// Get's an handle to the content browser
		project_content_browser& content_browser_handle = project_handler::get_singleton().get_content_browser();
		project_content_browser::content_t& content = content_browser_handle.get_content();

		// Refresh the content of the project file system
		if (ImGui::SmallButton("Refresh"))
		{
			content_browser_handle.reload_content();
			selected_directory_id_ = content.get_root_node().id;
		}

		// Check if there is not a selected directory
		if (selected_directory_id_ == "")
			return;
		
		bool is_root_node = selected_directory_id_ == content_browser_handle.get_content().get_root_node().id;
		project_content_browser::directory_t& selected_dir_content = is_root_node ? content.get_root_node() : *content.get_node("", selected_directory_id_);

		// Display a back button
		if (ImGui::SmallButton("Back") && !is_root_node)
			selected_directory_id_ = content.get_parent(selected_dir_content.parent_id)->id;

		// The image buttons size
		const float img_button_size = 50.0f;

		// Display the directories inside the selected directory
		for (uint32_t i = 0; i < selected_dir_content.next_nodes.size(); i++)
		{
			// Get's the directory iterated
			project_content_browser::directory_t& directory = selected_dir_content.next_nodes[i];

			// Display the folder button
			if (lumina_ui_buttons::img_txt_button(
				directory.name,
				*LUMINA_EDITOR_GET_ASSET(editor_asset_manager::textures::folder, lumina::texture)
			))
				selected_directory_id_ = directory.id;

			ImGui::SameLine();
		}

		// Display the resources inside the selected directory
		for (project_content_browser::cb_resource_t& resource : selected_dir_content.node_elements)
		{
			// Display the resource button
			lumina_ui_buttons::img_txt_button(
				resource.name,
				*LUMINA_EDITOR_GET_ASSET(editor_asset_manager::textures::document, lumina::texture)
			);

			ImGui::SameLine();
		}

		ImGui::End();
	}
}