#include "texture.h"

#include "application/app.h"
#include "d3d11_api/d3d11_api.h"

namespace lumina
{
	texture::~texture()
	{
		destroy();
	}

	bool texture::load_from_file(const std::string& file_path)
	{
		graphics_api_e running_graphics_api = application_player::get_singleton().get_surface().get_graphics_driver().get_graphics_api_running();

		if (running_graphics_api == graphics_api_e::D3D11_API && !is_allocated())
		{
			texture_native_resource_handle_ = new d3d11_texture();
			return ((d3d11_texture*)texture_native_resource_handle_)->load_from_file(file_path);
		}

		return false;
	}

	void texture::destroy()
	{
		graphics_api_e running_graphics_api = application_player::get_singleton().get_surface().get_graphics_driver().get_graphics_api_running();

		if (running_graphics_api == graphics_api_e::D3D11_API && is_allocated())
			delete reinterpret_cast<d3d11_texture*>(texture_native_resource_handle_);
	}
}