#include "top_window_toolbar_view.h"

#include "ui/ui_objects_lib/lumina_ui_input_text.h"
#include "app/projects.h"

#include "core/lumina_file_system.h"

#include "ImGui/imgui.h"

namespace lumina_editor
{
	void top_window_toolbar_view::on_render()
	{
		bool open_popup = false;

		// Menu
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Projects"))
			{
				if (ImGui::MenuItem("New Project", "Ctrl + N"))
					open_popup = true;

				if (ImGui::MenuItem("Save Project", "Ctrl + S"))
					open_popup = !on_project_save();

				if (ImGui::MenuItem("Load Project", "Ctrl + L"))
					on_project_load();

				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		// Render eventual opened popus
		render_new_project_popup(open_popup);
	}

	bool top_window_toolbar_view::on_project_save()
	{
		if (!project_handler::get_singleton().has_opened_project())
			return false;

		project_handler::get_singleton().save_project();

		return true;
	}

	void top_window_toolbar_view::on_project_load()
	{
		lumina::lumina_file_system_s::in_file_dialog_t project_directory = 
			lumina::lumina_file_system_s::open_input_file_dialog();

		project_handler::get_singleton().load_project(project_directory.path);
	}

	void top_window_toolbar_view::render_new_project_popup(bool open_popup)
	{
		if(open_popup)
			ImGui::OpenPopup("Create Project");

		if (ImGui::BeginPopupModal("Create Project"))
		{
			// Define helper variables and lambdas for the project creation
			static bool first_opening = true;
			static std::string project_name{""};
			static lumina_ui_input_text project_name_input_text{};
			static std::string project_path{ "" };
			static lumina_ui_input_text project_path_input_text{};

			if (first_opening)
			{
				project_name_input_text.bind_text_buffer(&project_name);
				project_path_input_text.bind_text_buffer(&project_path);
			}

			first_opening = false;

			auto close_popup = [&]() -> void
				{
					project_name_input_text.clear_buffer();
					project_path_input_text.clear_buffer();
					ImGui::CloseCurrentPopup();
				};

			// Render UI
			project_name_input_text.render("Name");
			project_path_input_text.render("Path");

			if (ImGui::SmallButton("Create") && !project_path.empty() && !project_name.empty())
			{
				project_handler::get_singleton().create_project(project_path, project_name);

				close_popup();
			}

			ImGui::SameLine();

			if (ImGui::SmallButton("Select Folder"))
				project_path_input_text.update_buffer(
					lumina::lumina_file_system_s::open_input_folder_dialog().path
				);

			ImGui::SameLine();

			if (ImGui::SmallButton("Close"))
				close_popup();

			ImGui::EndPopup();
		}
	}
}