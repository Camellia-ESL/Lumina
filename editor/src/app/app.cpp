#include "app.h"

#include "ui/ui_render.h"
#include "ui/view_register.h"

#include "scene/editor_camera.h"
#include "project_handlers/projects.h"
#include "editor_assets/editor_asset_manager.h"

#include "../editor_compile_configs.h"

namespace lumina_editor
{
	void editor_app_player::on_init()
	{
		// Inits the project handler
		project_handler* project_handler_instance = new project_handler();

		// Inits the editor camera
		editor_camera* editor_camera_instance = new editor_camera();
		editor_camera_instance->init();

		// Inits the asset manager 
		editor_asset_manager* editor_asset_manager_instance = new editor_asset_manager();

		// Inits UI Rendering
		ui_render_s::on_init();
	}

	void editor_app_player::on_update()
	{
		// Update the editor camera
		editor_camera::get_singleton().on_update();
	}
	
	void editor_app_player::on_render()
	{
		// Renders Scene
		lumina::scenes_system::get_singleton().render(editor_camera::get_singleton().get_camera());

		// Renders UI
		ui_render_s::on_render();
	}
}