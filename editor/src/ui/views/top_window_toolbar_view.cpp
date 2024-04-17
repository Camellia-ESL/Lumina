#include "top_window_toolbar_view.h"

#include "ui/ui_objects_lib/lumina_ui_input_text.h"
#include "ui/ui_shared_vars.h"
#include "project_handlers/projects.h"

#include "core/lumina_file_system.h"

#include "ImGui/imgui.h"

namespace lumina_editor
{
	void top_window_toolbar_view::on_create()
	{
		// Install the shortcuts callbacks
		lumina::event_listener::get_singleton().submit_event_callback(
			[&](const lumina::keyboard_event_t& event) -> void
			{
				if (
					event.key == lumina::keyboard_keys_types_e::KEY_N &&
					event.is_keyboard_mod_pressed(lumina::keyboard_key_mods_types_e::KEY_MOD_CONTROL) &&
					event.action_type == lumina::input_action_types_e::ACTION_PRESS)
					is_new_project_keybind_pressed_ = true;

				if (
					event.key == lumina::keyboard_keys_types_e::KEY_L &&
					event.is_keyboard_mod_pressed(lumina::keyboard_key_mods_types_e::KEY_MOD_CONTROL) &&
					event.action_type == lumina::input_action_types_e::ACTION_PRESS)
					is_load_project_keybind_pressed_ = true;

				if (
					event.key == lumina::keyboard_keys_types_e::KEY_S &&
					event.is_keyboard_mod_pressed(lumina::keyboard_key_mods_types_e::KEY_MOD_CONTROL) &&
					event.action_type == lumina::input_action_types_e::ACTION_PRESS)
					is_save_project_keybind_pressed_ = true;
			}
		);
	}

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

			if (ImGui::BeginMenu("View"))
			{ 
				ImGui::SeparatorText("Views");
				ImGui::PushStyleColor(ImGuiCol_Separator, { 0.35f, 0.35f, 0.35f, 1.0f });
				ImGui::Separator();
				ImGui::PopStyleColor();
				
				ImGui::Checkbox("Show Profiler", &ui_shared_vars::IS_PROFILER_VIEW_OPEN);
				ImGui::Checkbox("Show Content Browser", &ui_shared_vars::IS_CONTENT_BROWSER_VIEW_OPEN);
				ImGui::Checkbox("Show Assets Browser", &ui_shared_vars::IS_ASSETS_BROWSER_VIEW_OPEN);
				
				ImGui::SeparatorText("Scene");
				ImGui::PushStyleColor(ImGuiCol_Separator, { 0.35f, 0.35f, 0.35f, 1.0f });
				ImGui::Separator();
				ImGui::PopStyleColor();
				ImGui::Checkbox("Show Grid", &ui_shared_vars::IS_SCENE_GRID_ENABLED);

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::MenuItem("Edit Project Settings"))
					is_build_settings_editor_open_ = true;

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Settings"))
			{
				ImGui::SeparatorText("Graphics");
				ImGui::PushStyleColor(ImGuiCol_Separator, { 0.35f, 0.35f, 0.35f, 1.0f });
				ImGui::Separator();
				ImGui::PopStyleColor();

				ImGui::Checkbox("Editor Vsync", &ui_shared_vars::IS_VSYNC_ENABLED);
				lumina::application_player::get_singleton().get_surface().get_graphics_driver().set_vsync(ui_shared_vars::IS_VSYNC_ENABLED);

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Build"))
			{
				if (ImGui::MenuItem("Build Project"))
					project_handler::get_singleton().build_project();

				if (ImGui::MenuItem("Build And Run"))
					if (project_handler::get_singleton().build_project())
						project_handler::get_singleton().launch_runtime_player();

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		// Check for shortcuts for being pressed
		if (is_new_project_keybind_pressed_)
		{
			open_popup = true;
			is_new_project_keybind_pressed_ = false;
		}

		if (is_save_project_keybind_pressed_)
		{
			open_popup = !on_project_save();
			is_save_project_keybind_pressed_ = false;
		}

		if (is_load_project_keybind_pressed_)
		{
			on_project_load();
			is_load_project_keybind_pressed_ = false;
		}

		// Render eventual opened popus
		render_new_project_popup(open_popup);

		// Render eventual opened editor windows
		render_build_settings_editor();
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

		// Tries to load the project, if the project loads successfully logs it
		if (project_handler::get_singleton().load_project(project_directory.path))
			LUMINA_LOG_INFO("Project -> " + project_handler::get_singleton().get_project().name + " successfully loaded!");
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

	void top_window_toolbar_view::render_build_settings_editor()
	{
		static bool first_opening = true;
		if (!is_build_settings_editor_open_ || !project_handler::get_singleton().has_opened_project())
		{
			// Prevent crash for changing to a different project
			first_opening = true;
			// Prevent the window being instantly opened on project load if the button to open the editor was previously clicked
			is_build_settings_editor_open_ = false;
			return;
		}

		ImGui::Begin("Build Settings", &is_build_settings_editor_open_);

		static lumina_ui_input_text build_production_name_input_text{};
		static lumina_ui_input_text runtime_player_name_input_text{};
		static lumina_ui_input_text runtime_player_process_name_input_text{};
		static lumina_ui_input_text runtime_player_window_name_input_text{};

		if (first_opening)
		{
			project& project = project_handler::get_singleton().get_project();
			build_production_name_input_text.bind_text_buffer(&project.build_info.build_production_name);
			runtime_player_name_input_text.bind_text_buffer(&project.build_info.runtime_player_name);
			runtime_player_process_name_input_text.bind_text_buffer(&project.build_info.runtime_player_process_name);
			runtime_player_window_name_input_text.bind_text_buffer(&project.build_info.runtime_player_window_name);
			first_opening = false;
		}

		// Render the input texts
		build_production_name_input_text.render("Build Production Name");
		runtime_player_name_input_text.render("Runtime Player Name");
		runtime_player_process_name_input_text.render("Runtime Player Process Name");
		runtime_player_window_name_input_text.render("Runtime Player Window Name");

		ImGui::End();
	}
}