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

		// Joins the main application loop
		while (is_running_)
		{
			on_update();
			on_render();
		}
	}

	void application_player::exit()
	{
		spdlog::info("Exiting application player...");
		is_running_ = false;
	}
}