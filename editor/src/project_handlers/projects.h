#pragma once

#include "project_content_browser.h"

#include "lumina.h"

namespace lumina_editor
{
	struct project_build_info
	{
		// The name that will be used for the directory that will contain the build
		std::string build_production_name{ "Build Package" };

		// The name that will be used for the runtime player executable
		std::string runtime_player_name{ "lumina_runtime_player" };

		// The name that will be used for the runtime player process when running
		std::string runtime_player_process_name{ "lumina_runtime_player" };

		// The name that will be used for the runtime player window when running
		std::string runtime_player_window_name{ "lumina_runtime_player" };
	};

	struct project
	{
		// The name of the project
		std::string name{ "" };

		// The project directory path
		std::string project_dir_path{ "" };

		// The scenes directory path
		std::string scenes_dir_path{ "" };

		// The build informations about this project
		project_build_info build_info{};
	};

	class LUMINA_SINGLETON_CLASS(project_handler)
	{
	public:

		// Create's a fresh project
		void create_project(const std::string& directory_path, const std::string& project_name);
		
		// Save the opened project
		void save_project();

		// Load an existing project
		bool load_project(const std::string& project_file);

		// Unload a project
		void unload_project();

		// Pack and builds the project for distribution inside a temp_build dir
		bool build_project();

		// Start the runtime player from the build folder
		void launch_runtime_player();

		// Wheter if there is an opened project or not
		bool has_opened_project() { return loaded_project_ != nullptr; }

		// Get's the content browser
		project_content_browser& get_content_browser() { return content_browser_; }

		// Get's opened project
		project& get_project() { return *loaded_project_; }

	private:

		std::shared_ptr<project> loaded_project_ = nullptr;
		project_content_browser content_browser_{};

		// Saves project settings
		void save_project_settings();

		// Saves scenes 
		void save_scenes();

		// Saves assets
		void save_assets();

		// Load the project settings
		void load_project_settings(const YAML::Node& project_node_yaml, const std::string& project_file);

		// Load scenes
		void load_scenes();

		// Load assets
		void load_assets();

		// Cleanup the scene context in a safe way
		void destroy_scenes_context();

		// Cleanp the assets 
		void destroy_assets();

		// Generates scripting project
		void generate_scripting_proj();

		// Opens the editor to edit scripts
		void open_script_editor();
	};
}