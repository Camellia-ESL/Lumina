#include "editor_camera.h"

lumina_editor::editor_camera* lumina_editor::editor_camera::singleton_instance_ = nullptr;

namespace lumina_editor
{
	void editor_camera::init()
	{
		// Create's the camera
		camera_ = std::make_shared<lumina::camera_component>();
	}
}