#include "scene_toolbar_view.h"

#include "ui/ui_shared_vars.h"
#include "editor_assets/editor_asset_manager.h"
#include "project_handlers/projects.h"

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
		
		ImGui::SameLine();

		ImVec2 window_dim = ImGui::GetWindowSize();
		const ImVec2 img_buttons_size = { window_dim.y * 0.5f , window_dim.y * 0.5f };

		ImGui::SetCursorPosX((ImGui::GetWindowContentRegionMax().x / 2.0f) - (img_buttons_size.x / 2.0f));
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.0f , 0.0f , 0.0f , 0.0f });

		if (ImGui::ImageButton(
			"play_button",
			LUMINA_EDITOR_GET_ASSET(editor_asset_manager::textures::play_button, lumina::texture)->get_native_resource_buffer(),
			img_buttons_size
		))
		{
			if (project_handler::get_singleton().build_project())
				project_handler::get_singleton().launch_runtime_player();
		}

		ImGui::PopStyleColor();

		ImGui::End();
	}
}