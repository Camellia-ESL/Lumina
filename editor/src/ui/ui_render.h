#pragma once

namespace lumina_editor
{
	// Main UI render class
	class ui_render_s
	{
	public:

		// Called the first time the UI is initialized
		static void on_init();

		// Called every frame of the UI
		static void on_render();

	};
}