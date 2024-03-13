#pragma once

#include "lumina.h"

namespace lumina_editor
{
	// File system abstraction of the project directory, contains all the content of each subfolder and files 
	class project_content_browser final
	{
	public:

		enum class cb_resource_types_e
		{
			FILE
		};

		// A file system resource abstraction, can be wheter a file or a directory
		struct cb_resource_t
		{
			std::string path;
			std::string name;
			cb_resource_types_e type;
		};

	public:

		using content_t = lumina::lumina_tree<cb_resource_t>;
		using directory_t = content_t::tree_node_t;

		void reload_content();

		lumina::lumina_tree<cb_resource_t>& get_content() { return loaded_directory_content_; }

	private:

		std::string content_directory_{""};
		content_t loaded_directory_content_;

		void set_content_directory(const std::string& dir) { content_directory_ = dir; }
		void fetch_directory_content(const std::string& dir_path, directory_t& directory);
		void free_loaded_content();

	private:

		friend class project_handler;

	};
}