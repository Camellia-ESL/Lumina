#pragma once

// Define to run the playe in a development environment **NOTE MUST BE DISABLED FOR PRODUCTION**
//#define LUMINA_RUNTIME_PLAYER_DEVELOPMENT 

#ifdef LUMINA_RUNTIME_PLAYER_DEVELOPMENT

// The relative path to directory where the player will take resource files for testing
#define LUMINA_RUNTIME_PLAYER_PROJ_EXECUTED_DIR "test_bed/"

#else

#define LUMINA_RUNTIME_PLAYER_PROJ_EXECUTED_DIR

#endif

#define LUMINA_RUNTIME_PLAYER_CONTENT_DIR LUMINA_RUNTIME_PLAYER_PROJ_EXECUTED_DIR "content"
#define LUMINA_RUNTIME_PLAYER_ASSETS_DIR LUMINA_RUNTIME_PLAYER_CONTENT_DIR "/"
#define LUMINA_RUNTIME_PLAYER_SCENES_DIR LUMINA_RUNTIME_PLAYER_CONTENT_DIR "/"

#define LUMINA_RUNTIME_PLAYER_ASSET_PACKAGE_NAME "compiled_resources.package"

namespace lumina_editor_configs
{
	constexpr const char* RUNTIME_PLAYER_VERSION = "0.0.1";
	constexpr const char* RUNTIME_PLAYER_NAME = "Lumina RuntimePlayer";
	constexpr const char* RUNTIME_PLAYER_WINDOW_NAME = "Lumina RuntimePlayer";
	constexpr float RUNTIME_PLAYER_DEFAULT_WIDTH = 1280;
	constexpr float RUNTIME_PLAYER_DEFAULT_HEIGHT = 1024;
}