#pragma once

#include "GLFW/glfw3.h"

#include <string>

namespace lumina
{
	class app_surface
	{
	public:

		// Get's the surface handle class when app is running on a Desktop device
		GLFWwindow* get_desktop_handler() const { return window_; }

		// Wheter if the surface is opened or it's been closed (on desktop devices for example closed by cliking exit button)
		const bool is_surface_opened() const { return !glfwWindowShouldClose(window_); }

	private:

		// Creates the surface
		void init(float surface_width, float surface_height, const std::string& surface_name);

		// Poll and updates surface events
		void update_events();

		// Destroys the surface
		void destroy();

		// Install the event handler and register all the surface callbacks
		void install_events_handler();

		// Clear the surface screen
		void clear_screen();

		// Present all the render data to the surface screen
		void present();

		// Function executed when the surface get's resized
		static void on_resize(GLFWwindow* window, int width, int height);

	private:

		// Holds Glfw Window that represent the surface on desktop devices
		GLFWwindow* window_ = nullptr;

	private:
		
		friend class application_player;
	
	};
}