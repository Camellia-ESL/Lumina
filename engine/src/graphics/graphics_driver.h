#pragma once

namespace lumina
{
	// Available surface graphics api
	enum class graphics_api_e
	{
		// DirectX11 Api
		D3D11_API
	};

	// A generic abstraction layer for the application graphics rendering 
	// it handles the generic graphics functions that are contained in every
	// GraphicAPI (DirectX11, Vulkan, OpenGL, ...) such as the api choice
	// screen clear, presentation, window resize and more...
	class graphics_driver
	{
	public:

		// Resize the graphics api
		void resize(float surface_width, float surface_height);

		// Set the graphics api used to render
		void set_graphics_api(graphics_api_e api) { graphics_api_running_ = api; }

		// Get's the graphics api used for rendering
		const graphics_api_e get_graphics_api_running() const { return graphics_api_running_; }

		// Wheter if the vsync is enabled or not
		const bool is_vsync_enabled() const { return vsync_; }

	private:

		// Called when the graphic get's initialized
		void on_init();

		// Called when the graphic get's destroyed
		void on_destroy();

		// Clears the screen
		void clear_screen();

		// Present everything on screen
		void present();

	private:

		// Which graphics api the application is currently using 
		graphics_api_e graphics_api_running_;

		// Wheter if the vsync is enabled or not
		bool vsync_ = true;

		friend class app_surface;
	};
}