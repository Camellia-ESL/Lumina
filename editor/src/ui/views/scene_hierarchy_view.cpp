#include "scene_hierarchy_view.h"

#include "ui/view_register.h"
#include "ui/colors.h"
#include "ui/ui_shared_vars.h"

#include "ImGui/imgui.h"

#include <functional>

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
		// Fetch the registry and all the entities
		entt::registry& scene_registry = scene_->get_entity_registry();
		auto entities = scene_registry.view<lumina::identity_component>();

		// Lambda to handle entity operations
		const auto handle_entity_op =
			[&](lumina::entity& entity) -> void
			{
				lumina::entity_hierarchy_component& entity_hierarchy_c = entity.get_component<lumina::entity_hierarchy_component>();

				// Create's the drag and drop source
				ImGuiDragDropFlags src_flags = 0;
				src_flags |= ImGuiDragDropFlags_SourceNoDisableHover;

				if (ImGui::BeginDragDropSource(src_flags))
				{
					// Set's the drag and drop payload data
					ImGui::SetDragDropPayload(
						ui_shared_vars::ENTITY_DAD_ID,
						&entity,
						sizeof(lumina::entity),
						ImGuiCond_Once
					);

					ImGui::EndDragDropSource();
				}

				// Start accepting drag and drops
				if (ImGui::BeginDragDropTarget())
				{
					if (const ImGuiPayload* entity_drag_and_drop_payload = ImGui::AcceptDragDropPayload(ui_shared_vars::ENTITY_DAD_ID))
						lumina::entity_hierarchy_component::switch_child_attachment(
							entity,
							*(lumina::entity*)entity_drag_and_drop_payload->Data
						);

					ImGui::EndDragDropTarget();
				}

				// Handles entity right click
				if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
				{
					right_clicked_entity_ = entity;
					ImGui::OpenPopup("entity_action_menu_popup");
				}
			};

		// Lambda to handle entity selection
		const auto handle_entity_selection =
			[&](lumina::entity& entity) -> void
			{
				// Destroy if exist the previous entity editor view
				destroy_selected_entity_context();

				// Set the selected entity
				selected_entity_ = entity;

				// Create's a new entity editor view for the new entity
				entity_editor_view_ = std::make_shared<entity_editor_view>(entity, scene_);
				entity_editor_view_->tag = "scene_view_type";
				view_register_s::register_view(entity_editor_view_);
			};

		// Lamdda to render a single entity
		const auto render_entity =
			[&](lumina::entity& entity, bool has_childs) -> bool
			{
				lumina::identity_component& entity_identifier_c = entity.get_component<lumina::identity_component>();
				bool result = false;

				if (has_childs)
				{
					result = ImGui::TreeNodeEx((entity_identifier_c.name + "##" + entity_identifier_c.id).c_str(), ImGuiTreeNodeFlags_Selected);
					if (ImGui::IsItemClicked())
						handle_entity_selection(entity);
				}
				else
				{
					if (ImGui::Selectable(
						(entity_identifier_c.name + "##" + entity_identifier_c.id).c_str(),
						selected_entity_.has_entity() && selected_entity_.get_component<lumina::identity_component>().id == entity_identifier_c.id
					))
						handle_entity_selection(entity);
				}
				
				// Handle all the eventually operations on the entity
				handle_entity_op(entity);

				return result;
			};

		// Lambda to render entity childs
		std::function<void(lumina::entity&)> render_entity_childs =
			[&](lumina::entity& entity) -> void
			{
				lumina::identity_component& entity_identifier_c = entity.get_component<lumina::identity_component>();
				lumina::entity_hierarchy_component& entity_hierarchy_c = entity.get_component<lumina::entity_hierarchy_component>();

				// Render the parent
				if (render_entity(entity, true))
				{
					// Render the childs
					for (auto& child_ent : entity_hierarchy_c.get_childs())
					{
						lumina::entity_hierarchy_component& child_entity_hierarchy_c = child_ent.get_component<lumina::entity_hierarchy_component>();

						if (child_entity_hierarchy_c.has_childs())
							render_entity_childs(child_ent);
						else
							render_entity(child_ent, false);
					}

					ImGui::TreePop();
				}
			};

		// Loop all the entities and display a selectable to choose the entity to edit
		for (auto entity_unpacked : entities)
		{
			lumina::entity entity{ &scene_registry , entity_unpacked };

			lumina::identity_component& entity_identifier_c = entity.get_component<lumina::identity_component>();
			lumina::entity_hierarchy_component& entity_hierarchy_c = entity.get_component<lumina::entity_hierarchy_component>();
			
			// Avoid rendering 
			if (entity_hierarchy_c.has_parent())
				continue;

			if (!entity_hierarchy_c.has_childs())
			{
				ImGui::Indent();
				render_entity(entity, false);
				ImGui::Unindent();
			}
			else
				render_entity_childs(entity);
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
		ImGui::Text("Scene: ");
		ImGui::SameLine();
		ImGui::PushStyleColor(
			ImGuiCol_Text, 
			lumina::scenes_system::get_singleton().is_active_scene(scene_) ? 
			editor_ui_colors::GREEN : editor_ui_colors::YELLOW
		);
		ImGui::Text(scene_->get_name().c_str());
		ImGui::PopStyleColor();

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