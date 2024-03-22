#include "lumina_file_system.h"

#ifdef LUMINA_WIN32_PLATFORM
#include <Windows.h>
#include <ShlObj.h>
#endif 

namespace lumina
{
	lumina_file_system_s::in_file_dialog_t lumina_file_system_s::open_input_folder_dialog()
	{
#ifdef LUMINA_WIN32_PLATFORM
		CoInitialize(NULL);

		IFileDialog* file_dialog;
		HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&file_dialog));
		in_file_dialog_t file_dialog_buffer{};

		if (!SUCCEEDED(hr))
			return file_dialog_buffer;

		DWORD dialog_options;
		file_dialog->GetOptions(&dialog_options);
		file_dialog->SetOptions(dialog_options | FOS_PICKFOLDERS);

		hr = file_dialog->Show(NULL);

		if (!SUCCEEDED(hr))
			return file_dialog_buffer;

		IShellItem* dialog_fetched_item;
		hr = file_dialog->GetResult(&dialog_fetched_item);

		if (!SUCCEEDED(hr))
			return file_dialog_buffer;

		LPWSTR folder_path;
		hr = dialog_fetched_item->GetDisplayName(SIGDN_FILESYSPATH, &folder_path);

		if (!SUCCEEDED(hr))
			return file_dialog_buffer;

		file_dialog_buffer.path = lumina_strings_s::wstr_to_str(folder_path);

		dialog_fetched_item->Release();
		file_dialog->Release();

		CoUninitialize();

		return file_dialog_buffer;
#endif 
	}

	lumina_file_system_s::in_file_dialog_t lumina_file_system_s::open_input_file_dialog()
	{
#ifdef LUMINA_WIN32_PLATFORM

		OPENFILENAME open_file_name{};
		char dir_file_name[MAX_PATH] = "";

		ZeroMemory(&open_file_name, sizeof(open_file_name));

		open_file_name.lStructSize = sizeof(open_file_name);
		open_file_name.hwndOwner = NULL;
		open_file_name.lpstrFilter = "All Files (*.*)\0*.*\0";
		open_file_name.lpstrFile = dir_file_name;
		open_file_name.nMaxFile = MAX_PATH;
		open_file_name.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

		GetOpenFileName(&open_file_name);

		in_file_dialog_t file_dialog_buffer{};
		file_dialog_buffer.path = open_file_name.lpstrFile;

		return file_dialog_buffer;
#endif 
	}

	lumina_file_system_s::out_file_dialog_t lumina_file_system_s::open_output_file_dialog(std::string file_name)
	{
#ifdef LUMINA_WIN32_PLATFORM
		OPENFILENAME open_file_name{};
		char dir_file_name[MAX_PATH] = "";
		strcpy(dir_file_name, file_name.c_str());

		ZeroMemory(&open_file_name, sizeof(open_file_name));

		open_file_name.lStructSize = sizeof(open_file_name);
		open_file_name.hwndOwner = NULL;
		open_file_name.lpstrFilter = "All Files (*.*)\0*.*\0";
		open_file_name.lpstrFile = dir_file_name;
		open_file_name.nMaxFile = MAX_PATH;
		open_file_name.Flags = OFN_EXPLORER | OFN_HIDEREADONLY;

		GetOpenFileName(&open_file_name);

		out_file_dialog_t file_dialog_buffer{};
		file_dialog_buffer.path = open_file_name.lpstrFile;

		return file_dialog_buffer;
#endif 
	}

	bool lumina_file_system_s::create_folder(const std::string& path)
	{
		return std::filesystem::create_directory(path);
	}

	std::string lumina_file_system_s::get_file_directory(const std::string& file_path)
	{
		const size_t last_slash_idx = file_path.rfind('\\');
		if (std::string::npos == last_slash_idx)
			return "";

		return file_path.substr(0, last_slash_idx);
	}

	std::string lumina_file_system_s::get_process_directory()
	{
		char path_buffer[256];
		
#ifdef LUMINA_WIN32_PLATFORM
		int bytes_read = GetModuleFileName(NULL, path_buffer, sizeof(path_buffer));
#endif 

		return get_file_directory(path_buffer);
	}

	std::vector<std::string> lumina_file_system_s::get_files_in_directory(const std::string& dir_path)
	{
		std::vector<std::string> result_buffer{};
		
		// Check if the directory does not exist
		if (!std::filesystem::exists(dir_path))
			return result_buffer;

		// Iterate the directory
		auto directory_iterator = std::filesystem::directory_iterator(dir_path);
		for (const auto& entry : directory_iterator)
			result_buffer.push_back(entry.path().string());

		return result_buffer;
	}

	void lumina_file_system_s::execute_process(const std::string& exe_path, const std::string& starting_dir)
	{
#ifdef LUMINA_WIN32_PLATFORM
		// additional information
		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		// set the size of the structures
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		// start the program up
		CreateProcess(exe_path.c_str(),								// The path to the exe
			(char*)"",												// Command line
			NULL,													// Process handle not inheritable
			NULL,													// Thread handle not inheritable
			TRUE,													// Set handle inheritance to FALSE
			CREATE_NEW_CONSOLE,										// Flags
			NULL,													// Use parent's environment block
			!starting_dir.empty() ? starting_dir.c_str() : nullptr, // Use parent's starting directory 
			&si,													// Pointer to STARTUPINFO structure
			&pi														// Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
		);
		// Close process and thread handles. 
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
#endif 
	}
}