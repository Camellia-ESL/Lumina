#include "surface.h"

#include "spdlog/spdlog.h"
#include "GLFW/glfw3.h"

#include "event_system/event_system.h"
#include "scene_system/scenes_system.h"
#include "assets_system/asset_atlas.h"
#include "script_engine/script_engine.h"

#include "graphics/graphics_driver.h"
#include "graphics/d3d11_api/d3d11_renderer.h"

namespace lumina
{
	void app_surface::init(float surface_width, float surface_height, const std::string& surface_name)
	{
        spdlog::warn("Creating Surface...");

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

        spdlog::info("Surface Created.");

        // Init Graphics API
        graphics_driver_.on_init();

        // Install events callbacks
        spdlog::warn("Installing event callbacks...");
        install_events_handler();
        spdlog::info("Event callbacks installed.");

        // Init the asset atlas
        LUMINA_SINGLETON_INIT_INSTANCE(asset_atlas);

        // Init the scene system
        spdlog::warn("Instancing the scene system...");
        LUMINA_SINGLETON_INIT_INSTANCE(scenes_system);
        spdlog::info("Scene system created.");

        // Init the script engine
        spdlog::warn("Instancing scripting engine...");
        LUMINA_SINGLETON_INIT_INSTANCE(script_engine);

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
        graphics_driver_.clear_screen();
    }

    void app_surface::present()
    {
        graphics_driver_.present();
    }

    void app_surface::install_events_handler()
    {
        // Init the event system
        LUMINA_SINGLETON_INIT_INSTANCE(event_dispatcher);
        event_dispatcher_instance->init();

        LUMINA_SINGLETON_INIT_INSTANCE(event_listener);
        
        // Register a callback to handle surface resize
        event_listener_instance->submit_event_callback(
            [&](const window_resize_event_t& resize_event) -> void 
            {
                graphics_driver_.resize(resize_event.app_width, resize_event.app_height);
            }
        );
    }

    void app_surface::on_destroy()
    {
        // Destroy script engine
        LUMINA_SINGLETON_DESTROY_INSTANCE(script_engine);

        // Destroy asset atlas
        LUMINA_SINGLETON_DESTROY_INSTANCE(asset_atlas);

        // Destroy scene system
        LUMINA_SINGLETON_DESTROY_INSTANCE(scenes_system);

        // Destroy event system
        LUMINA_SINGLETON_DESTROY_INSTANCE(event_dispatcher);
        LUMINA_SINGLETON_DESTROY_INSTANCE(event_listener);

        // Destroy graphics 
        graphics_driver_.on_destroy();
    }
}