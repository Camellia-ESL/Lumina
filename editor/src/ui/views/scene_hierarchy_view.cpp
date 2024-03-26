#include "scene_hierarchy_view.h"

#include "ui/view_register.h"

#include "ImGui/imgui.h"

namespace lumina_editor
{
	void scene_hierarchy_view::render_properties_popup()
	{
		// Check wether the right click was on a selected entity or not
		if (right_clicked_entity_.has_entity())
			return;

		// Edit Scene popup menu (opened on right mouse button click
		if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
			ImGui::OpenPopup("scene_edit_menu_popup");

		if (ImGui::BeginPopupContextWindow("scene_edit_menu_popup"))
		{
			if (ImGui::SmallButton("Add Entity"))
			{
				scene_->create_entity();
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
	}

	void scene_hierarchy_view::render_entities()
	{
		entt::registry& scene_registry = scene_->get_entity_registry();

		auto entities = scene_registry.view<lumina::identity_component>();

		// Loop all the entities and display a selectable to choose the entity to edit
		for (auto entity_unpacked : entities)
		{
			lumina::entity entity{ &scene_registry , entity_unpacked };

			lumina::identity_component& entity_identifier_c = entity.get_component<lumina::identity_component>();
			
			if (ImGui::Selectable(
				(entity_identifier_c.name + "##" + entity_identifier_c.id).c_str(), 
				selected_entity_.has_entity() && selected_entity_.get_component<lumina::identity_component>().id == entity_identifier_c.id
			))
			{
				// Destroy if exist the previous entity editor view
				destroy_selected_entity_context();

				// Set the selected entity
				selected_entity_ = entity;

				// Create's a new entity editor view for the new entity
				entity_editor_view_ = std::make_shared<entity_editor_view>(entity, scene_);
				entity_editor_view_->tag = "scene_view_type";
				view_register_s::register_view(entity_editor_view_);
			}
			
			// Handles entity right click
			if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
			{
				right_clicked_entity_ = entity;
				ImGui::OpenPopup("entity_action_menu_popup");
			}
		}

	}

	void scene_hierarchy_view::render_entity_actions_popup()
	{
		if (right_clicked_entity_.has_entity() && ImGui::BeginPopupContextItem("entity_action_menu_popup"))
		{
			entt::registry& scene_registry = scene_->get_entity_registry();

			if (ImGui::SmallButton("Delete"))
			{
				// Destroy if exist the previous entity editor view
				destroy_selected_entity_context();
				scene_registry.destroy(right_clicked_entity_.get_entity());
				right_clicked_entity_ = lumina::entity{};
			}

			if (ImGui::SmallButton("Duplicate"))
			{
				scene_->duplicate_entity(right_clicked_entity_);
				right_clicked_entity_ = lumina::entity{};
			}

			ImGui::EndPopup();
		}
		else
			right_clicked_entity_ = lumina::entity{};
	}

	void scene_hierarchy_view::on_render()
	{
		ImGui::Begin("Scene Hierarchy");

		// Display the scene name
		ImGui::Text(scene_->get_name().c_str());

		// Renders all the entities
		render_entities();

		// Renders the properties popup if scene is right clicked
		render_properties_popup();

		// Renders the entity actions popup (the popup menu to delete, duplicate... entity)
		render_entity_actions_popup();

		ImGui::End();
	}

	void scene_hierarchy_view::on_destroy()
	{
		// Destroy if exist the previous entity editor view
		destroy_selected_entity_context();
	}

	void scene_hierarchy_view::destroy_selected_entity_context()
	{
		if (entity_editor_view_ != nullptr)
			view_register_s::destroy_view(entity_editor_view_);
	}
}