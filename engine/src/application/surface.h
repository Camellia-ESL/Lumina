#pragma once

#include "GLFW/glfw3.h"

#include <string>

namespace lumina
{
	// Available surface graphics api
	enum class graphics_api_e
	{
		D3D11_API
	};

	class app_surface
	{
	public:

		// Get's the surface handle class when app is running on a Desktop device
		GLFWwindow* get_desktop_handler() const { return window_; }

		// Wheter if the surface is opened or it's been closed (on desktop devices for example closed by cliking exit button)
		const bool is_surface_opened() const { return !glfwWindowShouldClose(window_); }

		// Get's the current graphics api that the application is using to render
		const graphics_api_e get_graphics_api_running() const { return graphics_api_running_; }

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

		// Called on surface destruction
		void on_destroy();

	private:

		// Which graphics api the application is currently using 
		graphics_api_e graphics_api_running_;

		// Holds Glfw Window that represent the surface on desktop devices
		GLFWwindow* window_ = nullptr;

	private:
		
		friend class application_player;
	
	};
}