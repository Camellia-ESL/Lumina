#pragma once

#include "ImGui/imgui.h"

namespace lumina_editor
{
	typedef ImVec4 editor_ui_color;

	struct editor_ui_colors
	{
		static constexpr const editor_ui_color RED = { 1.0f, 0.0f, 0.0f, 1.0f };
		static constexpr const editor_ui_color GREEN = { 0.0f, 1.0f, 0.0f, 1.0f };
		static constexpr const editor_ui_color BLUE = { 0.0f, 0.0f, 1.0f, 1.0f };
		static constexpr const editor_ui_color YELLOW = { 1.0f, 0.9f, 0.0f, 1.0f };
	};
}