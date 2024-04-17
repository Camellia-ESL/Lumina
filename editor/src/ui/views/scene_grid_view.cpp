#include "scene_grid_view.h"

#include "ui/ui_shared_vars.h"

#include "ImGui/imgui.h"
#include "ImGuizmo/ImGuizmo.h"
#include "scene/editor_camera.h"

namespace lumina_editor
{
	void scene_grid_view::on_render()
	{
		if (!ui_shared_vars::IS_SCENE_GRID_ENABLED)
			return;

		// Does a single render pass to draw the grid
		lumina::renderer_2d_s::begin_render_pass(editor_camera::get_singleton().get_camera());
		
		lumina::renderer_2d_s::draw_grid(grid_transform_.get_model_matrix(), grid_color_, grid_size_);

		lumina::renderer_2d_s::end_render_pass();
	}
}