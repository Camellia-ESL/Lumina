#include "resource_loader.h"

#include "../runtime_player_compile_configs.h"

#include "script_assemblies/runtime_script_manager.h"

#include "lumina.h"

#include "spdlog/spdlog.h"

namespace lumina_runtime_player
{
	void resource_loader::load_assets()
	{
		spdlog::warn("Loading assets...");

		// Load all the assets contained in the compiled package
		lumina::assets_serializer::deserialize_assets_package(
			lumina::asset_atlas::get_singleton().get_registry(),
			LUMINA_RUNTIME_PLAYER_ASSETS_DIR LUMINA_RUNTIME_PLAYER_ASSET_PACKAGE_NAME
		);
		
		spdlog::info("Assets loaded.");
	}

	void resource_loader::load_scenes()
	{
		std::vector<std::string> scene_files_path =
			lumina::lumina_file_system_s::get_files_in_directory(
				LUMINA_RUNTIME_PLAYER_SCENES_DIR
			);

		spdlog::warn("Loading scenes...");

		// Loop thru all the scene files and load them
		for (auto& path : scene_files_path)
		{
			lumina::scenes_system::get_singleton().create_scene("__importing_scene__");
			bool scene_load_result = lumina::scene_serializer::deserialize_yaml(
				lumina::scenes_system::get_singleton().get_scene("__importing_scene__"),
				path
			);

			if (!scene_load_result)
				lumina::scenes_system::get_singleton().destroy_scene("__importing_scene__");
		}

		spdlog::info("Scenes loaded.");
	}

	void resource_loader::load_assemblies()
	{
		LUMINA_SINGLETON_INIT_INSTANCE(runtime_script_manager);
		runtime_script_manager_instance->call_on_start();
	}
}