#include "surface.h"

#include "spdlog/spdlog.h"
#include "GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"

#include "event_system/event_system.h"
#include "graphics/d3d11_api/d3d11_instance.h"

namespace lumina
{
	void app_surface::init(float surface_width, float surface_height, const std::string& surface_name)
	{
        spdlog::info("Creating Surface...");

        if (!glfwInit())
        {
            spdlog::error("Unable to initialize surface\n");
            return;
        }

        GLFWmonitor* primary_monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* video_mode = glfwGetVideoMode(primary_monitor);

        glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_FALSE);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        window_ = glfwCreateWindow(
            surface_width,
            surface_height,
            surface_name.c_str(),
            nullptr,
            nullptr
        );
        
        if (window_ == nullptr)
        {
            spdlog::error("Unable to create window surface\n");
            glfwTerminate();
            return;
        }

        // Init Graphics API
        spdlog::info("Initializing graphics...");
        d3d11_instance* instance = new d3d11_instance();

        if (!d3d11_instance::get_singleton().create_device(glfwGetWin32Window(window_)))
        {
            spdlog::error("Error creating D3D Device!");
            return;
        }

        // Install events callbacks
        spdlog::info("Installing event callbacks...");
        install_events_handler();

        glfwSetWindowPos(
            window_,
            video_mode->width / 2 - surface_width / 2,
            video_mode->height / 2 - surface_height / 2
        );
	}

    void app_surface::update_events()
    {
        glfwPollEvents();
    }

    void app_surface::destroy()
    {
        glfwDestroyWindow(window_);
        glfwTerminate();
    }

    void app_surface::clear_screen()
    {
        constexpr const float clear_color_with_alpha[4] = { 0.12f, 0.12f, 0.12f, 1.0f };
        ID3D11RenderTargetView* render_target = d3d11_instance::get_singleton().get_main_render_target_view();
        d3d11_instance::get_singleton().get_device_context()->OMSetRenderTargets(
            1, 
            &render_target,
            nullptr
        );

        d3d11_instance::get_singleton().get_device_context()->ClearRenderTargetView(render_target, clear_color_with_alpha);
    }

    void app_surface::present()
    {
        d3d11_instance::get_singleton().get_swap_chain()->Present(TRUE, 0);
    }

    void app_surface::install_events_handler()
    {
        // Init the event system
        event_dispatcher* event_dispatcher_instance = new event_dispatcher();
        event_dispatcher_instance->init();

        event_listener* event_listener_instance = new event_listener();

        // Register a callback to handle surface resize
        event_listener_instance->submit_event_callback(
            [](const window_resize_event_t& resize_event) -> void 
            {
                d3d11_instance::get_singleton().cleanup_render_target();
                d3d11_instance::get_singleton().get_swap_chain()->ResizeBuffers(0, resize_event.app_width, resize_event.app_height, DXGI_FORMAT_UNKNOWN, 0);
                d3d11_instance::get_singleton().create_rendere_target();
            }
        );
    }
}