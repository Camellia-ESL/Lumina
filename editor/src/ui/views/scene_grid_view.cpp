#include "scene_grid_view.h"

#include "ui/ui_shared_vars.h"

#include "ImGui/imgui.h"
#include "ImGuizmo/ImGuizmo.h"
#include "scene/editor_camera.h"

namespace lumina_editor
{
	void scene_grid_view::on_create()
	{
		// Scale the matrix to a default size
		grid_matrix_ = glm::scale(grid_matrix_, { 1.0f , 1.0f , 1.0f });
	}

	void scene_grid_view::on_render()
	{
		if (!ui_shared_vars::IS_SCENE_GRID_ENABLED)
			return;

		ImGuizmo::DrawGrid(
			(const float*)&editor_camera::get_singleton().get_camera()->get_view_matrix(),
			(const float*)&editor_camera::get_singleton().get_camera()->get_projection_matrix(),
			(float*)&grid_matrix_,
			grid_size_
		);
	}
}