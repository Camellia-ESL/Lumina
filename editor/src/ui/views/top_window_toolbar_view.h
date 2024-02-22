#pragma once

#include "ui/view.h"
#include "ui/ui_objects_lib/lumina_ui_input_text.h"

#include "lumina.h"

namespace lumina_editor
{
	class top_window_toolbar_view : public view
	{
	public:

		void on_render() override;

	private:

		bool on_project_save();
		void on_project_load();

		void render_new_project_popup(bool open_popup);

	};
}