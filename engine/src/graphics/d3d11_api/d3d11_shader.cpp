#include "d3d11_shader.h"

#include "graphics/d3d11_api/d3d11_api.h"
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
				spdlog::error("D3D11 Shader Compiler -> " + (std::string)((char*)error_msg_blob->GetBufferPointer()));
			
			return false;
		}

		if (shader_memory_blob_ == nullptr)
		{
			spdlog::error("Error compiling shader from file, unknown error occured!");
			return false;
		}

		return allocate_shader();
	}

	bool d3d11_vertex_shader::allocate_shader()
	{
		if (shader_memory_blob_ == nullptr)
			return false;

		d3d11_instance::get_singleton().get_device()->CreateVertexShader(
			shader_memory_blob_->GetBufferPointer(), 
			shader_memory_blob_->GetBufferSize(), 
			nullptr, 
			&vertex_shader_
		);

		return is_loaded();
	}

	void d3d11_vertex_shader::enable()
	{
		if (!is_loaded())
			return;

		d3d11_instance::get_singleton().get_device_context()->VSSetShader(vertex_shader_, 0, 0);
	}

	bool d3d11_pixel_shader::allocate_shader()
	{
		if (shader_memory_blob_ == nullptr)
			return false;

		d3d11_instance::get_singleton().get_device()->CreatePixelShader(
			shader_memory_blob_->GetBufferPointer(), 
			shader_memory_blob_->GetBufferSize(), 
			nullptr, 
			&pixel_shader_
		);

		return is_loaded();
	}

	void d3d11_pixel_shader::enable()
	{
		if (!is_loaded())
			return;

		d3d11_instance::get_singleton().get_device_context()->PSSetShader(pixel_shader_, 0, 0);
	}
}