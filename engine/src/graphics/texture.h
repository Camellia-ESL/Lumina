#pragma once

#include "core/lumina_types.h"

#include <string>

namespace lumina
{
	// Texture abstraction, should be instantly pushed as an asset in the asset registry when created
	class texture
	{
	public:

		~texture();

		// Load a texture from file
		bool load_from_file(const std::string& file_path);

		// Load a texture from memory
		bool load_from_memory(void* img_data, l_uint32 data_size);

		// Destroy and free the texture holded
		void destroy();

		// Wheter if the texture is loaded or not
		const bool is_allocated() const { return texture_native_resource_handle_ != nullptr; }

		// Get's the native resource handle to the abstracted gapis that could be a (d3d11_texture, vk_texture or other gapis texture resource)
		const void* get_native_resource() const { return texture_native_resource_handle_; }

		// Get's the native resource buffer that contains the ptr to the native gapi resource (ID3D11ShaderResourceView, vk_texture or opengl texture)
		void* get_native_resource_buffer() const;

	private:

		// The native resource that contains the texture (d3d11_texture, vk_texture or other gapis texture resource)
		void* texture_native_resource_handle_ = nullptr;

	};
}