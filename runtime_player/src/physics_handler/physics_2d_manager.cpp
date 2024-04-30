#include "physics_2d_manager.h"

#include "scene_system/scenes_system.h"

namespace lumina_runtime_player
{
	void physics_2d_manager_s::on_update()
	{
		// Update's the physics for the active scene
		lumina::scenes_system::get_singleton().get_active_scene()->get_physics_simulator_2d().update(
			lumina::scenes_system::get_singleton().get_active_scene()
		);
	}
}