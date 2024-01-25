#include "graphics_initializer.h"

#include "application/app.h"

#include "graphics/d3d11_api/d3d11_api.h"

#include "spdlog/spdlog.h"
#include "GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"

namespace lumina
{
	void graphics_initializer_s::on_init()
	{
        spdlog::info("Initializing graphics...");
		d3d11_renderer* renderer_instance = new d3d11_renderer();
		renderer_instance->init(glfwGetWin32Window(application_player::get_singleton().get_surface().get_desktop_handler()));
	}
}