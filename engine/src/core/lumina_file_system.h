#pragma once

#include "lumina_strings.h"

#include <fstream>
#include <filesystem>

namespace lumina
{
	// A file system abstraction platform independent
	class lumina_file_system_s
	{
	public:

		// Holds all the informations about a opened file dialog
		struct in_file_dialog_t
		{
			std::string path{ "" };
		};

		// Holds all the informations about a opened file dialog
		struct out_file_dialog_t
		{
			std::string path{ "" };
		};

	public:

		static in_file_dialog_t open_input_folder_dialog();
		static in_file_dialog_t open_input_file_dialog();
		static out_file_dialog_t open_output_file_dialog(std::string file_name);
		static bool create_folder(const std::string& path);
		static std::string get_file_directory(const std::string& file_path);
		static std::string get_process_directory();
		static std::vector<std::string> get_files_in_directory(const std::string& dir_path);
		static void execute_process(const std::string& exe_path, const std::string& starting_dir = "");

	};
}