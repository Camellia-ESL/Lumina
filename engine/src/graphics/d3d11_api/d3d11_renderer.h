#pragma once

#include "d3d11_instance.h"	
#include "core/lumina_singleton.h"

namespace lumina
{
	// Abastracted D3D11 Renderer (singleton)
	class LUMINA_SINGLETON_CLASS(d3d11_renderer)
	{
	public:

		// Handles the resize of the renderer surface
		void handle_resize(const float width, const float height);

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