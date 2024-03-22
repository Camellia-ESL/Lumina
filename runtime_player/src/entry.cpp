#include "app/app.h"

#include "../runtime_player_compile_configs.h"

#include "spdlog/spdlog.h"

int main()
{
	// Set app player options
	lumina::app_info_t app_player_config{};
	app_player_config.app_name = lumina_editor_configs::RUNTIME_PLAYER_NAME;
	app_player_config.surface_name = lumina_editor_configs::RUNTIME_PLAYER_WINDOW_NAME;
	app_player_config.surface_width = lumina_editor_configs::RUNTIME_PLAYER_DEFAULT_WIDTH;
	app_player_config.surface_height = lumina_editor_configs::RUNTIME_PLAYER_DEFAULT_HEIGHT;

	// Instance and run the application player
	lumina_runtime_player::runtime_player_app_player* app_player = new lumina_runtime_player::runtime_player_app_player{};

	try
	{
		lumina_runtime_player::runtime_player_app_player::get_singleton().run(app_player_config);
	}
	catch (const std::exception& error) { spdlog::info(error.what()); return 0; }

	lumina_runtime_player::runtime_player_app_player::get_singleton().exit();

	return 0;
}