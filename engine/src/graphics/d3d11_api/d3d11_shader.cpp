#include "d3d11_shader.h"

#include "core/lumina_strings.h"

#include "spdlog/spdlog.h"

#include <d3dcompiler.h>

namespace lumina
{
	bool d3d11_shader::load_from_file(const d3d11_shader_load_info_t& load_info)
	{
		ID3DBlob* error_msg_blob = nullptr;

		// Tries to compile shader and display eventual errors while compiling if there are
		if (FAILED(
			D3DCompileFromFile(
				lumina_strings_s::str_to_wstr(load_info.file_path_name).c_str(),
				nullptr,
				nullptr,
				load_info.shader_func_name.c_str(),
				load_info.shader_profile.c_str(),
				0,
				0,
				&shader_memory_blob_,
				&error_msg_blob
			)
		))
		{
			spdlog::error("Error compiling shader from file.");

			if (error_msg_blob != nullptr) 
				spdlog::error((char*)error_msg_blob->GetBufferPointer());
			
			return false;
		}

		if (shader_memory_blob_ == nullptr)
		{
			spdlog::error("Error compiling shader from file, unknown error occured!");
			return false;
		}

		return allocate_shader();
	}
}