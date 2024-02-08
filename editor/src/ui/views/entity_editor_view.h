#pragma once

#include "ui/view.h"
#include "ui/ui_objects_lib/lumina_ui_input_text.h"

#include "lumina.h"

namespace lumina_editor
{
	class entity_editor_view : public view
	{
	public:

		entity_editor_view(lumina::entity entity, lumina::scene* scene);

		void on_create() override;
		void on_render() override;

	private:

		lumina::entity entity_;
		lumina::scene* scene_;

		// The data holded by this instance of the view purely used for containing
		// ui objects instanced 
		struct view_instance_data
		{
			lumina_ui_input_text entity_name_input_text;
			bool is_active_camera;
		}view_instance_data_;

		// Render the popup menu of the entity
		void render_entity_popup_menu();

		// Render Components Functions
		void render_identifier_component();
		void render_transform_component();
		void render_sprite_component();
		void render_camera_component();
	};
}