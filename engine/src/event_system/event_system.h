#pragma once

/*
	This header contains the whole function of the event system of Lumina Engine
	made by https://github.com/VanityEmptiness 
*/

#include "mouse_event.h"
#include "keyboard_event.h"
#include "window_resize_event.h"

#include <functional>

namespace lumina
{
	// Dispatcher encharged to dispatch events to the listener (singleton)
	class event_dispatcher
	{
	public:

		event_dispatcher() { instance_ = this; }
		
		static event_dispatcher& get_singleton() { return *instance_; }

		void dispatch_mouse_events(const mouse_event_t& mouse_event);
		void dispatch_keyboard_events(const keyboard_event_t& keyboard_event);
		void dispatch_window_resize(const window_resize_event_t& window_resize_event);

		// Mouse callbacks

		void on_mouse_cursor_move(double x_pos, double y_pos);
		void on_mouse_cursor_enter_leave_window_area(int entered);
		void on_mouse_button_click(int button, int action, int mods);
		void on_mouse_wheel_scroll(double xoffset, double yoffset);

		// Keyboard callbacks

		void on_key_input(int key, int scancode, int action, int mods);

		// Window resize callbacks
		
		void on_window_resize(int width, int height);


	private:

		static event_dispatcher* instance_;
	
	private:

		void init();

	private:

		friend class app_surface;

	};

	// Event listener that handles the updates of binded event callbacks (singleton)
	class event_listener
	{
	public:

		event_listener() { instance_ = this; }
		
		static event_listener& get_singleton() { return *instance_; }

		void submit_event_callback(std::function<void(const mouse_event_t&)> mouse_event_callback);
		void submit_event_callback(std::function<void(const keyboard_event_t&)> keyboard_event_callback);
		void submit_event_callback(std::function<void(const window_resize_event_t&)> window_resize_event_callback);


	private:

		static event_listener* instance_;

	private:

		std::vector<std::function<void(const mouse_event_t&)>> mouse_event_callbacks_;
		std::vector<std::function<void(const keyboard_event_t&)>> keyboard_event_callbacks;
		std::vector<std::function<void(const window_resize_event_t&)>> window_resize_event_callbacks_;

	private:

		friend class event_dispatcher;

	};

	// This class can be used alternatively to event_listener callbacks to pull directly the input state for this render frame of some input type
	class event_state_handler_s
	{
	public:
		
		// Gets the buffered state of a given key (for the current frame)
		static input_action_types_e get_key_state(keyboard_keys_types_e key);

		// Check if a given key is in pressed status
		static bool is_key_pressed(keyboard_keys_types_e key);

		// Check if a given key is in released status
		static bool is_key_released(keyboard_keys_types_e key);
		
		// Check if a given key is in held status (the held status counts the interval_delay of your keyboard as if u are writing text)
		static bool is_key_held(keyboard_keys_types_e key);

	private:

	};
}