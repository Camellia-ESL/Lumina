#pragma once

#include "d3d11_instance.h"	

namespace lumina
{
	// Abastracted D3D11 Renderer (singleton)
	class d3d11_renderer
	{
	public:

		d3d11_renderer() { instance_ = this; }

		static d3d11_renderer& get_singleton() { return *instance_; }

		// Handles the resize of the renderer surface
		void handle_resize(const float width, const float height);

	private:

		static d3d11_renderer* instance_;

	private:

		// Initialize the renderer 
		void init(HWND window);

		// Clears the screen from previous rendering
		void clear_screen();

		// Present everything rendered on screen
		void present();


	private:

		friend class app_surface;
		friend class graphics_driver;

	};
}