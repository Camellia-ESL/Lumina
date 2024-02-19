#pragma once

#include "lumina.h"

namespace lumina_editor
{
	class LUMINA_SINGLETON_CLASS(editor_camera)
	{
	public:

		lumina::camera_component* get_camera() const { return camera_.get(); }

	private:

		std::shared_ptr<lumina::camera_component> camera_;

		// Init the editor camera
		void init();

	private:

		friend class editor_app_player;

	};
}