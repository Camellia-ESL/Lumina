#include "scene_editor_view.h"

#include "../editor_compile_configs.h"
#include "ui/colors.h"

#include "ImGui/imgui.h"

namespace lumina_editor
{
	scene_editor_view::scene_editor_view(lumina::scene* scene)
		: scene_{ scene }
	{
	}

	void scene_editor_view::on_create()
	{
		view_instance_data_.scene_name_input_text.bind_text_buffer(
			&view_instance_data_.scene_name_input_text_buffer
		);
	}

	void scene_editor_view::on_render()
	{
		ImGui::Begin("Scene Editor");

		// Input Text to handle scene name modification
		view_instance_data_.scene_name_input_text.render("Name");
		ImGui::SameLine();
		if (ImGui::SmallButton("Change"))
		{
			if (lumina::scenes_system::get_singleton().change_name(
				scene_->get_name(),
				view_instance_data_.scene_name_input_text_buffer
			))
				view_instance_data_.scene_name_input_text.clear_buffer();
		}

		// Set Active scene button
		if (lumina::scenes_system::get_singleton().is_active_scene(scene_))
			ImGui::TextColored(editor_ui_colors::GREEN, "Active");
		else if (ImGui::SmallButton("Set Active"))
			lumina::scenes_system::get_singleton().activate_scene(scene_->get_name());

		ImGui::End();
	}
}