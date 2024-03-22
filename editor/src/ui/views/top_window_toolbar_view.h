#pragma once

#include "ui/view.h"
#include "ui/ui_objects_lib/lumina_ui_input_text.h"

#include "lumina.h"

namespace lumina_editor
{
	class top_window_toolbar_view : public view
	{
	public:

		void on_create() override;
		void on_render() override;

	private:

		bool is_new_project_keybind_pressed_ = false;
		bool is_load_project_keybind_pressed_ = false;
		bool is_save_project_keybind_pressed_ = false;
		bool is_build_settings_editor_open_ = false;

		bool on_project_save();
		void on_project_load();

		void render_new_project_popup(bool open_popup);
		void render_build_settings_editor();

	};
}