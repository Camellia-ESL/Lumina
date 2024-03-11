#include "scene_toolbar_view.h"

#include "ui/ui_shared_vars.h"

#include "ImGui/imgui.h"
#include "ImGuizmo/ImGuizmo.h"

namespace lumina_editor
{
	void scene_toolbar_view::on_render()
	{
		ImGui::Begin("##scene_toolbar_view");

		ImGui::BeginDisabled(ui_shared_vars::GIZMO_OPERATION_TYPE == ImGuizmo::OPERATION::TRANSLATE);
		if (ImGui::SmallButton("Translate")) 
			ui_shared_vars::GIZMO_OPERATION_TYPE = ImGuizmo::OPERATION::TRANSLATE;
		ImGui::EndDisabled();

		ImGui::SameLine();

		ImGui::BeginDisabled(ui_shared_vars::GIZMO_OPERATION_TYPE == ImGuizmo::OPERATION::ROTATE);
		if (ImGui::SmallButton("Rotation"))
			ui_shared_vars::GIZMO_OPERATION_TYPE = ImGuizmo::OPERATION::ROTATE;
		ImGui::EndDisabled();

		ImGui::SameLine();

		ImGui::BeginDisabled(ui_shared_vars::GIZMO_OPERATION_TYPE == ImGuizmo::OPERATION::SCALE);
		if (ImGui::SmallButton("Scale"))
			ui_shared_vars::GIZMO_OPERATION_TYPE = ImGuizmo::OPERATION::SCALE;
		ImGui::EndDisabled();

		ImGui::End();
	}
}