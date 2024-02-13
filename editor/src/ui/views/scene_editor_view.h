#pragma once

#include "ui/view.h"
#include "ui/ui_objects_lib/lumina_ui_input_text.h"

#include "lumina.h"

namespace lumina_editor
{
	class scene_editor_view : public view
	{
	public:

		scene_editor_view(lumina::scene* scene);

		void on_create() override;
		void on_render() override;

	private:

		// The selected scene
		lumina::scene* scene_;

		// The data holded by this instance of the view purely used for containing
		// ui objects instanced 
		struct view_instance_data
		{
			lumina_ui_input_text scene_name_input_text;
			std::string scene_name_input_text_buffer;
		}view_instance_data_;

	};
}