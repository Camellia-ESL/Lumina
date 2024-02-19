#include "event_system.h"

#include "application/app.h"

#include "GLFW/glfw3.h"

lumina::event_dispatcher* lumina::event_dispatcher::singleton_instance_ = nullptr;
lumina::event_listener* lumina::event_listener::singleton_instance_ = nullptr;

namespace lumina
{
	// Glfw Callbacks handlers functions

	// --MOUSE--

	// Called whenever the mouse moves
	static void mouse_cursor_callback(GLFWwindow* window, double x_pos, double y_pos)
	{
		event_dispatcher::get_singleton().on_mouse_cursor_move(x_pos, y_pos);
	}

	// Called whenever the mouse enter or leave window area
	static void mouse_cursor_enter_callback(GLFWwindow* window, int entered)
	{
		event_dispatcher::get_singleton().on_mouse_cursor_enter_leave_window_area(entered);
	}

	// Called whenever a mouse button gets clicked (either called if pressed or released)
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		event_dispatcher::get_singleton().on_mouse_button_click(button, action, mods);
	}

	// Called whenever the mouse wheel gets scrolled up or down
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		event_dispatcher::get_singleton().on_mouse_wheel_scroll(xoffset, yoffset);
	}

	// --KEYBOARD--

	static void keyboard_input_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		event_dispatcher::get_singleton().on_key_input(key, scancode, action, mods);
	}

	// --WINDOW RESIZE--
	static void window_resize_callback(GLFWwindow* window, int width, int height)
	{
		event_dispatcher::get_singleton().on_window_resize(width, height);
	}

	// Event dispatcher functions

	void event_dispatcher::init()
	{
		// Mouse callbacks
		glfwSetCursorPosCallback(application_player::get_singleton().get_surface().get_desktop_handler(), mouse_cursor_callback);
		glfwSetCursorEnterCallback(application_player::get_singleton().get_surface().get_desktop_handler(), mouse_cursor_enter_callback);
		glfwSetMouseButtonCallback(application_player::get_singleton().get_surface().get_desktop_handler(), mouse_button_callback);
		glfwSetScrollCallback(application_player::get_singleton().get_surface().get_desktop_handler(), scroll_callback);

		// Keyboard callbacks
		glfwSetKeyCallback(application_player::get_singleton().get_surface().get_desktop_handler(), keyboard_input_callback);

		// Window resize callbacks
		glfwSetWindowSizeCallback(application_player::get_singleton().get_surface().get_desktop_handler(), window_resize_callback);
	}

	void event_dispatcher::dispatch_mouse_events(const mouse_event_t& mouse_event)
	{
		for (size_t i = 0; i < event_listener::get_singleton().mouse_event_callbacks_.size(); i++)
			event_listener::get_singleton().mouse_event_callbacks_[i](mouse_event);
	}

	void event_dispatcher::dispatch_keyboard_events(const keyboard_event_t& keyboard_event)
	{
		for (size_t i = 0; i < event_listener::get_singleton().keyboard_event_callbacks.size(); i++)
			event_listener::get_singleton().keyboard_event_callbacks[i](keyboard_event);
	}

	void event_dispatcher::dispatch_window_resize(const window_resize_event_t& window_resize_event)
	{
		for (size_t i = 0; i < event_listener::get_singleton().window_resize_event_callbacks_.size(); i++)
			event_listener::get_singleton().window_resize_event_callbacks_[i](window_resize_event);
	}

	// Event dispatcher callbacks related to the glfw callbacks (MOUSE)
	
	void event_dispatcher::on_mouse_cursor_move(double x_pos, double y_pos)
	{
		mouse_event_t mouse_event{};
		mouse_event.event_type = event_types_e::MOUSE_EVENT_;
		mouse_event.mouse_event_subtype = mouse_event_types_e::MOUSE_CURSOR_MOVE;
		mouse_event.cursor_pos_x = x_pos;
		mouse_event.cursor_pos_y = y_pos;

		dispatch_mouse_events(mouse_event);
	}

	void event_dispatcher::on_mouse_cursor_enter_leave_window_area(int entered)
	{
		mouse_event_t mouse_event{};
		mouse_event.event_type = event_types_e::MOUSE_EVENT_;
		mouse_event.mouse_event_subtype = entered ? mouse_event_types_e::MOUSE_JOINED_WINDOW_AREA : mouse_event_types_e::MOUSE_LEFT_WINDOW_AREA;

		dispatch_mouse_events(mouse_event);
	}

	void event_dispatcher::on_mouse_button_click(int button, int action, int mods)
	{
		mouse_event_t mouse_event{};
		mouse_event.event_type = event_types_e::MOUSE_EVENT_;
		mouse_event.mouse_event_subtype = mouse_event_types_e::MOUSE_BUTTON_CLICK;
		mouse_event.action_type = (input_action_types_e)action;
		mouse_event.mouse_button = (mouse_button_types_e)button;

		dispatch_mouse_events(mouse_event);
	}

	void event_dispatcher::on_mouse_wheel_scroll(double xoffset, double yoffset)
	{
		mouse_event_t mouse_event{};
		mouse_event.event_type = event_types_e::MOUSE_EVENT_;
		mouse_event.mouse_event_subtype = mouse_event_types_e::MOUSE_WHEEL_SCROLL;
		mouse_event.mouse_wheel_x = xoffset;
		mouse_event.mouse_wheel_y = yoffset;

		dispatch_mouse_events(mouse_event);
	}

	// Event dispatcher callbacks related to the glfw callbacks (KEYBOARD)

	void event_dispatcher::on_key_input(int key, int scancode, int action, int mods)
	{
		keyboard_event_t keyboard_event{};
		keyboard_event.event_type = event_types_e::KEYBOARD_EVENT_;
		keyboard_event.action_type = (input_action_types_e)action;
		keyboard_event.key = (keyboard_keys_types_e)key;
		keyboard_event.key_mod = (keyboard_key_mods_types_e)mods;

		dispatch_keyboard_events(keyboard_event);
	}

	// Event dispatcher callbacks related to the glfw callbacks (WINDOW RESIZE)

	void event_dispatcher::on_window_resize(int width, int height)
	{
		window_resize_event_t window_resize_event{};
		window_resize_event.app_width = width;
		window_resize_event.app_height = height;

		dispatch_window_resize(window_resize_event);
	}

	// Event listener helper functions

	void event_listener::submit_event_callback(std::function<void(const mouse_event_t&)> mouse_event_callback)
	{
		mouse_event_callbacks_.push_back(mouse_event_callback);
	}

	void event_listener::submit_event_callback(std::function<void(const keyboard_event_t&)> keyboard_event_callback)
	{
		keyboard_event_callbacks.push_back(keyboard_event_callback);
	}

	void event_listener::submit_event_callback(std::function<void(const window_resize_event_t&)> window_resize_event_callback)
	{
		window_resize_event_callbacks_.push_back(window_resize_event_callback);
	}

	// Event State Handler

	input_action_types_e event_state_handler_s::get_key_state(keyboard_keys_types_e key)
	{
		return (input_action_types_e)glfwGetKey(application_player::get_singleton().get_surface().get_desktop_handler(), (int)key);
	}

	bool event_state_handler_s::is_key_pressed(keyboard_keys_types_e key)
	{
		return get_key_state(key) == input_action_types_e::ACTION_PRESS;
	}

	bool event_state_handler_s::is_key_released(keyboard_keys_types_e key)
	{
		return get_key_state(key) == input_action_types_e::ACTION_RELEASE;
	}

	bool event_state_handler_s::is_key_held(keyboard_keys_types_e key)
	{
		return get_key_state(key) == input_action_types_e::ACTION_REPEAT;
	}
}