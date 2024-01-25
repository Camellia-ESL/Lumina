#pragma once

#include <d3d11.h>
#include <string>

namespace lumina
{
	struct d3d11_shader_profiles
	{
		static constexpr const char* VERTEX_SHADER_PROFILE_V5 = "vs_5_0";
		static constexpr const char* PIXEL_SHADER_PROFILE_V5 = "ps_5_0";
	};

	struct d3d11_shader_load_info_t
	{
		std::string file_path_name{ "" };
		std::string shader_func_name{ "" };
		std::string shader_profile{ "" };
	};

	class d3d11_shader
	{
	public:

		ID3DBlob* get_blob() { return shader_memory_blob_; }

		// Load a shader from file
		bool load_from_file(const d3d11_shader_load_info_t& load_info);

		// Enables the shader for the current render pass
		virtual void enable() {}

		// Wheter if the shader is loaded and usable or not
		virtual bool is_loaded() { return false; }

		// Gets the pointer to the contained shader
		virtual void* get_shader() { return nullptr; }

	protected:

		ID3DBlob* shader_memory_blob_ = nullptr;
		
		// Allocates the shader and encapsulate it
		virtual bool allocate_shader() { return true; };
	};

}