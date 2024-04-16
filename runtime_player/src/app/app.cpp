#include "app.h"

#include "resource_loader.h"
#include "script_assemblies/runtime_script_manager.h"

namespace lumina_runtime_player
{
	void runtime_player_app_player::on_init()
	{
		// Loads the application configs
		resource_loader::load_configs();

		// Load assets **NOTE** -> assets must be loaded BEFORE loading scenes or any other type of resource
		resource_loader::load_assets();

		// Load scenes
		resource_loader::load_scenes();

		// Load assemblies
		resource_loader::load_assemblies();
	}

	void runtime_player_app_player::on_update()
	{
		// Calls the on update for the scripting manager
		runtime_script_manager::get_singleton().call_on_update();
	}

	void runtime_player_app_player::on_render()
	{
		// Renders Scene
		lumina::scenes_system::get_singleton().render();
	}
}