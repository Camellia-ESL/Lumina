#include "editor_camera.h"

#include "app/app.h"

#include "ImGui/imgui.h"

lumina_editor::editor_camera* lumina_editor::editor_camera::singleton_instance_ = nullptr;

namespace lumina_editor
{
	void editor_camera::init()
	{
		// Create's the camera
		camera_ = std::make_shared<lumina::camera_component>();

		// Replace the camera position and rotation
		camera_->set_position({ 0.0f, 2.0f , 1.0f });
		camera_->rotate(0.0f, -45.0f);

		// Install the event callbacks
		install_event_callbacks();
	}

	void editor_camera::install_event_callbacks()
	{
		// Register keyboard events
		lumina::event_listener::get_singleton().submit_event_callback(
			[&](const lumina::keyboard_event_t& event) -> void 
			{
				on_key_pressed(event);
			}
		);

		// Register mouse events
		lumina::event_listener::get_singleton().submit_event_callback(
			[&](const lumina::mouse_event_t& event) -> void
			{
				on_mouse_move(event);
			}
		);

		// Register resize events
		lumina::event_listener::get_singleton().submit_event_callback(
			[&](const lumina::window_resize_event_t& event) -> void
			{
				on_resize(event);
			}
		);
	}

	void editor_camera::on_key_pressed(const lumina::keyboard_event_t& event)
	{
		// Handles camera mod activation (spectator mode)
		if (
			event.key == lumina::keyboard_keys_types_e::KEY_M &&
			event.is_keyboard_mod_pressed(lumina::keyboard_key_mods_types_e::KEY_MOD_CONTROL) &&
			event.action_type == lumina::input_action_types_e::ACTION_PRESS)
		{
			is_camera_active_ = !is_camera_active_;
			editor_app_player::get_singleton().get_surface().enable_cursor(!is_camera_active_);
		}
	}

	void editor_camera::on_mouse_move(const lumina::mouse_event_t& event)
	{
		// If the engine isn't in spectator mode skip
		if (!is_camera_active_)
			return;

		// If the event isn't a mouse cursor movement skip
		if (event.mouse_event_subtype != lumina::mouse_event_types_e::MOUSE_CURSOR_MOVE)
			return;

		static float last_x = 400;
		static float last_y = 300;
		static bool is_first_time = false;

		float cursor_x = static_cast<float>(event.cursor_pos_x);
		float cursor_y = static_cast<float>(event.cursor_pos_y);

		if (is_first_time)
		{
			last_x = cursor_x;
			last_y = cursor_y;
			is_first_time = false;
		}

		float xoffset = (cursor_x - last_x) * camera_sensitivity;
		float yoffset = (last_y - cursor_y) * camera_sensitivity; // reversed since y-coordinates go from bottom to top

		last_x = cursor_x;
		last_y = cursor_y;

		camera_->rotate(xoffset, yoffset);
	}

	void editor_camera::on_update()
	{
		// If the engine isn't in spectator mode skip
		if (!is_camera_active_)
			return;

		const float movement_velocity = camera_movement_speed_ * editor_app_player::get_singleton().get_delta_time();

		if (lumina::event_state_handler_s::is_key_pressed(lumina::keyboard_keys_types_e::KEY_W))
			camera_->move_position(lumina::camera_component::move_directions_e::FORWARD, movement_velocity);

		if (lumina::event_state_handler_s::is_key_pressed(lumina::keyboard_keys_types_e::KEY_S))
			camera_->move_position(lumina::camera_component::move_directions_e::BACKWARD, movement_velocity);

		if (lumina::event_state_handler_s::is_key_pressed(lumina::keyboard_keys_types_e::KEY_A))
			camera_->move_position(lumina::camera_component::move_directions_e::LEFT, movement_velocity);

		if (lumina::event_state_handler_s::is_key_pressed(lumina::keyboard_keys_types_e::KEY_D))
			camera_->move_position(lumina::camera_component::move_directions_e::RIGHT, movement_velocity);
	}

	void editor_camera::on_resize(const lumina::window_resize_event_t& event)
	{
		// Check that sizes aren't null
		if (event.app_width <= 0 || event.app_height <= 0)
			return;

		camera_->recalculate_all_matricies();
	}
}