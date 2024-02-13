#include "graphics_driver.h"

#include "application/app.h"

#include "graphics/d3d11_api/d3d11_api.h"

#include "spdlog/spdlog.h"
#include "GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"

namespace lumina
{
	void graphics_driver::on_init()
	{
        spdlog::warn("Initializing graphics...");

		// Init DirectX11 Api
		if (graphics_api_running_ == graphics_api_e::D3D11_API)
		{
			spdlog::info("Selected graphics API --> D3D11");

			d3d11_renderer* renderer_instance = new d3d11_renderer();
			renderer_instance->init(
				glfwGetWin32Window(application_player::get_singleton().get_surface().get_desktop_handler())
			);

			int window_width, window_height;
			glfwGetWindowSize(application_player::get_singleton().get_surface().get_desktop_handler(), &window_width, &window_height);
			
			// Calls a first resize to fix the window resolution not matching the api resolution
			resize(window_width, window_height);
		}
	}

	void graphics_driver::on_destroy()
	{
		if (graphics_api_running_ == graphics_api_e::D3D11_API)
			delete& d3d11_renderer::get_singleton();
	}

	void graphics_driver::resize(float surface_width, float surface_height)
	{
		if (graphics_api_running_ == graphics_api_e::D3D11_API)
			d3d11_renderer::get_singleton().handle_resize(surface_width, surface_height);
	}

	void graphics_driver::clear_screen()
	{
		if (graphics_api_running_ == graphics_api_e::D3D11_API)
			d3d11_renderer::get_singleton().clear_screen();
	}

	void graphics_driver::present()
	{
		if (graphics_api_running_ == graphics_api_e::D3D11_API)
			d3d11_renderer::get_singleton().present();
	}
}