#pragma once

#include "project_content_browser.h"

#include "lumina.h"

namespace lumina_editor
{
	struct project
	{
		// The name of the project
		std::string name{ "" };

		// The project directory path
		std::string project_dir_path{ "" };

		// The scenes directory path
		std::string scenes_dir_path{ "" };
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

		// Wheter if there is an opened project or not
		bool has_opened_project() { return loaded_project_ != nullptr; }

		// Get's the content browser
		project_content_browser& get_content_browser() { return content_browser_; }

	private:

		std::shared_ptr<project> loaded_project_ = nullptr;
		project_content_browser content_browser_{};

		// Saves project settins
		void save_project_settings();

		// Saves scenes 
		void save_scenes();

		// Saves assets
		void save_assets();

		// Load scenes
		void load_scenes();

		// Load assets
		void load_assets();

		// Cleanup the scene context in a safe way
		void destroy_scenes_context();

		// Cleanp the assets 
		void destroy_assets();
	};
}