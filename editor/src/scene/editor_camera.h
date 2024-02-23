#pragma once

#include "lumina.h"

namespace lumina_editor
{
	class LUMINA_SINGLETON_CLASS(editor_camera)
	{
	public:

		lumina::camera_component* get_camera() const { return camera_.get(); }

	private:

		// The camera handle
		std::shared_ptr<lumina::camera_component> camera_;
		
		// Wheter if the camera behaviours are active or not
		bool is_camera_active_ = false;

		// The camera movement speed 
		float camera_movement_speed_ = 2.5;

		// The camera mouse sensitivity
		float camera_sensitivity = 0.05f;

		// Init the editor camera
		void init();

		// Install the camera events callbacks
		void install_event_callbacks();

		// Called on keyboard event
		void on_key_pressed(const lumina::keyboard_event_t& event);

		// Called on mouse event
		void on_mouse_move(const lumina::mouse_event_t& event);

		// Called when the window resizes
		void on_resize(const lumina::window_resize_event_t& event);
		
		// Called on update
		void on_update();


	private:

		friend class editor_app_player;

	};
}