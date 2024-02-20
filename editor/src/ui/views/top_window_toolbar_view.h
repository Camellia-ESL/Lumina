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

	};
}