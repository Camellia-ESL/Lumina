#include "entity_editor_view.h"

#include "ui/colors.h"
#include "ui/ui_objects_lib/lumina_ui_drag_objects.h"

#include "ImGui/imgui.h"

namespace lumina_editor
{
	entity_editor_view::entity_editor_view(lumina::entity entity, lumina::scene* scene)
		: entity_{ entity }, scene_ { scene }
	{}

	void entity_editor_view::on_create()
	{
		// Bind the entity name to a text input buffer
		view_instance_data_.entity_name_input_text.bind_text_buffer(
			&entity_.get_component<lumina::identity_component>().name
		);
	}

	void entity_editor_view::on_render()
	{
		ImGui::Begin("Entity Editor");

		// Render the popup menu
		render_entity_popup_menu();

		// Render components if needed (IN ORDER)
		render_identifier_component();
		render_transform_component();
		render_sprite_component();
		render_camera_component();

		ImGui::End();
	}

	void entity_editor_view::render_entity_popup_menu()
	{
		// Edit Scene popup menu (opened on right mouse button click
		if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
			ImGui::OpenPopup("entity_edit_menu_popup");

		if (ImGui::BeginPopupContextWindow("entity_edit_menu_popup"))
		{
			if (ImGui::SmallButton("Add Transform"))
			{
				entity_.add_component<lumina::transform_component>();
				ImGui::CloseCurrentPopup();
			}

			if (ImGui::SmallButton("Add Sprite"))
			{
				entity_.add_component<lumina::sprite_component>();
				ImGui::CloseCurrentPopup();
			}

			if (ImGui::SmallButton("Add Camera"))
			{
				entity_.add_component<lumina::camera_component>();
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
	}

	void entity_editor_view::render_identifier_component()
	{
		ImGui::SeparatorText("Identifier");
		ImGui::PushStyleColor(ImGuiCol_Separator, { 0.35f, 0.35f, 0.35f, 1.0f });
		ImGui::Separator();
		ImGui::PopStyleColor();

		view_instance_data_.entity_name_input_text.render("Name");
	}

	void entity_editor_view::render_transform_component()
	{
		// Check if the entity has not the component, to avoid rendering or crashing
		if (!entity_.has_component<lumina::transform_component>())
			return;

		ImGui::SeparatorText("Transform");
		ImGui::PushStyleColor(ImGuiCol_Separator, { 0.35f, 0.35f, 0.35f, 1.0f });
		ImGui::Separator();
		ImGui::PopStyleColor();

		glm::vec3* position_ptr = &entity_.get_component<lumina::transform_component>().position;
		glm::vec3* rotation_ptr = &entity_.get_component<lumina::transform_component>().rotation;
		glm::vec3* scale_ptr = &entity_.get_component<lumina::transform_component>().scale;

		// Position 
		lumina_ui_drag_objects::drag_float_3_multi_text_colored(
			"Position",
			editor_ui_colors::red,
			editor_ui_colors::green,
			editor_ui_colors::blue,
			(float*)position_ptr
		);

		// Rotation 
		lumina_ui_drag_objects::drag_float_3_multi_text_colored(
			"Rotation",
			editor_ui_colors::red,
			editor_ui_colors::green,
			editor_ui_colors::blue,
			(float*)rotation_ptr
		);

		// Scale 
		lumina_ui_drag_objects::drag_float_3_multi_text_colored(
			"Scale",
			editor_ui_colors::red,
			editor_ui_colors::green,
			editor_ui_colors::blue,
			(float*)scale_ptr
		);
	}

	void entity_editor_view::render_sprite_component()
	{
		// Check if the entity has not the component, to avoid rendering or crashing
		if (!entity_.has_component<lumina::sprite_component>())
			return;

		ImGui::SeparatorText("Sprite");
		ImGui::PushStyleColor(ImGuiCol_Separator, { 0.35f, 0.35f, 0.35f, 1.0f });
		ImGui::Separator();
		ImGui::PopStyleColor();

		// Color edit 
		ImGui::ColorEdit4("Color", (float*)&entity_.get_component<lumina::sprite_component>().color);
	}

	void entity_editor_view::render_camera_component()
	{
		// Check if the entity has not the component, to avoid rendering or crashing
		if (!entity_.has_component<lumina::camera_component>())
			return;

		ImGui::SeparatorText("Camera");
		ImGui::PushStyleColor(ImGuiCol_Separator, { 0.35f, 0.35f, 0.35f, 1.0f });
		ImGui::Separator();
		ImGui::PopStyleColor();

		lumina::camera_component& camera = entity_.get_component<lumina::camera_component>();

		if(ImGui::Checkbox("Active Camera", &view_instance_data_.is_active_camera))
		{
			scene_->set_camera(&camera);
		}
	}
}