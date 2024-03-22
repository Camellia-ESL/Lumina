#pragma once

#include "core/lumina_types.h"

#include <d3d11.h>
#include <string>

namespace lumina
{
	class d3d11_texture
	{
	public:

		// Load a texture from file (BMP, JPEG, PNG, TIFF, GIF are supported)
		bool load_from_file(const std::string& file_path);

		// Load a texture from memory (BMP, JPEG, PNG, TIFF, GIF are supported)
		bool load_from_memory(void* img_data, l_uint32 data_size);

		// Enable the texture for the current render pass
		bool enable(const uint32_t slot) const;

		// Wheter if a texture is loaded or not
		const bool is_allocated() const { return texture_ != nullptr; }
		
		// Get the d3d11 resource that holds the texture
		ID3D11ShaderResourceView* get_texture_resource() { return texture_; }

	private:

		ID3D11ShaderResourceView* texture_ = nullptr;

	};
}