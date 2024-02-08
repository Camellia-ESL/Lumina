#include "app.h"

#include "ui/ui_render.h"
#include "ui/view_register.h"

namespace lumina_editor
{
	void editor_app_player::on_init()
	{
		// Inits UI Rendering
		ui_render_s::on_init();
	}

	void editor_app_player::on_update()
	{
		
	}

	void editor_app_player::on_render()
	{
		// Renders Scene
		lumina::scenes_system::get_singleton().render();

		// Renders UI
		ui_render_s::on_render();
	}
}