#pragma once

#include "ImGui/imgui.h"

namespace lumina_editor
{
	struct editor_ui_colors
	{
		static constexpr const ImVec4 RED = { 1.0f, 0.0f, 0.0f, 1.0f };
		static constexpr const ImVec4 GREEN = { 0.0f, 1.0f, 0.0f, 1.0f };
		static constexpr const ImVec4 BLUE = { 0.0f, 0.0f, 1.0f, 1.0f };
	};
}