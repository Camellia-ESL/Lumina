#pragma once

#include "ui/view.h"

#include "lumina.h"

namespace lumina_editor
{
	class scene_toolbar_view : public view
	{
	public:

		void on_render() override;

	};
}