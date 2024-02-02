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
		// Must be specified to load a shader from file
		std::string file_path_name{ "" };

		// Must be specified to load a shader from string
		std::string src_code{ "" };

		// Must be specified in every case
		std::string shader_func_name{ "" };
		
		// Must be specified in every case
		std::string shader_profile{ "" };
	};

	class d3d11_shader
	{
	public:

		~d3d11_shader() { shader_memory_blob_->Release(); shader_memory_blob_ = nullptr; }

		ID3DBlob* get_blob() { return shader_memory_blob_; }

		// Load a shader from file
		bool load_from_file(const d3d11_shader_load_info_t& load_info);

		// Load a shader from a code string
		bool load_from_string(const d3d11_shader_load_info_t& load_info);

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

	class d3d11_vertex_shader : public d3d11_shader
	{
	public:

		~d3d11_vertex_shader() { vertex_shader_->Release(); vertex_shader_ = nullptr; }

		// Enables the shader for the current render pass
		void enable() override;

		// Wheter if the shader is loaded and usable or not
		bool is_loaded() override { return vertex_shader_ != nullptr; }

		// Gets the pointer to the contained shader
		void* get_shader() override { return vertex_shader_; }

	private:

		ID3D11VertexShader* vertex_shader_ = nullptr; 

		// Allocates the shader and encapsulate it
		bool allocate_shader() override;

	};

	class d3d11_pixel_shader : public d3d11_shader
	{
	public:

		~d3d11_pixel_shader() { pixel_shader_->Release(); pixel_shader_ = nullptr; }

		// Enables the shader for the current render pass
		void enable() override;

		// Wheter if the shader is loaded and usable or not
		bool is_loaded() override { return pixel_shader_ != nullptr; }

		// Gets the pointer to the contained shader
		void* get_shader() override { return pixel_shader_; }

	private:

		ID3D11PixelShader* pixel_shader_ = nullptr; 

		// Allocates the shader and encapsulate it
		bool allocate_shader() override;

	};
}