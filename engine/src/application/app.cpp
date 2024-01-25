#include "app.h"

#include "spdlog/spdlog.h"

#include "lumina.h"

namespace lumina
{
	application_player* application_player::instance_ = nullptr;

	void application_player::run(const app_info_t& app_info)
	{
		spdlog::info("App Starting...");
		spdlog::info("Please wait while initializing.");
		spdlog::info("Built against Lumina Engine ver. --> " + (std::string)lumina::VERSION);

		// Set the app in running status
		is_running_ = true;

		// Init surface
		surface_.graphics_api_running_ = app_info.graphics_api;
		surface_.init(app_info.surface_width, app_info.surface_height, app_info.surface_name);

		// Calls On Init
        on_init();

		// Join main application loop
        while (surface_.is_surface_opened() && is_running_)
        {
			surface_.update_events();
            on_update();
			surface_.clear_screen();
            on_render();
			surface_.present();
        }

		// Cleanup the surface
		surface_.on_destroy();
		surface_.destroy();
	}

	void application_player::exit()
	{
		spdlog::info("Exiting application player...");
		is_running_ = false;
	}
}