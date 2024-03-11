#pragma once

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

		// Destroy and free the texture holded
		void destroy();

		// Wheter if the texture is loaded or not
		const bool is_allocated() const { return texture_native_resource_handle_ != nullptr; }

		// Get's the native resource handle that could be a (d3d11_texture, vk_texture or other gapis texture resource)
		const void* get_native_resource() const { return texture_native_resource_handle_; }

	private:

		// The native resource that contains the texture (d3d11_texture, vk_texture or other gapis texture resource)
		void* texture_native_resource_handle_ = nullptr;

	};
}