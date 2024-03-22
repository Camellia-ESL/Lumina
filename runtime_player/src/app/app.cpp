#include "app.h"

#include "resource_loader.h"

namespace lumina_runtime_player
{
	void runtime_player_app_player::on_init()
	{
		// Load assets **NOTE** -> assets must be loaded BEFORE loading scenes or any other type of resource
		resource_loader::load_assets();

		// Load scenes
		resource_loader::load_scenes();
	}

	void runtime_player_app_player::on_update()
	{
		
	}

	void runtime_player_app_player::on_render()
	{
		// Renders Scene
		lumina::scenes_system::get_singleton().render();
	}
}