#pragma once

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

	private:

		std::shared_ptr<project> loaded_project_ = nullptr;

		// Saves project settins
		void save_project_settings();

		// Saves scenes 
		void save_scenes();
	};
}