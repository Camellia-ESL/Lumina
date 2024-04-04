#include "project_content_browser.h"

#include "spdlog/spdlog.h"

namespace lumina_editor
{
	void project_content_browser::reload_content()
	{
		free_loaded_content();
		fetch_directory_content(content_directory_, loaded_directory_content_.get_root_node());
	}

	void project_content_browser::fetch_directory_content(const std::string& dir_path, directory_t& directory)
	{
		// Get's all the files and directories inside the current given path
		const auto content = lumina::lumina_file_system_s::get_files_in_directory(dir_path);

		for (auto& path : content)
		{
			try
			{
				// Parse string in a file system path
				const std::filesystem::path fs_path{ path };

				// Check and save if the current path iterated is a subdirectory or file
				// @enhancement-[project_content_browser]: Implement a better check not based on the extension to verify if the path is a dir or a file
				const bool is_dir = fs_path.extension().empty();

				if (is_dir)
					fetch_directory_content(
						path,
						loaded_directory_content_.add_node(directory, fs_path.filename().string())
					);
				else
					directory.node_elements.push_back({
						path,
						std::filesystem::path(path).filename().string(),
						cb_resource_types_e::FILE
						});
			}
			catch (const std::exception&) {}
		}
	}

	void project_content_browser::free_loaded_content()
	{
		loaded_directory_content_.clear();
	}
}