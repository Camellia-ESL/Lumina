#pragma once

#include "ImGui/imgui.h"

namespace lumina_editor
{
	struct editor_ui_colors
	{
		static constexpr const ImVec4 red = { 1.0f, 0.0f, 0.0f, 1.0f };
		static constexpr const ImVec4 green = { 0.0f, 1.0f, 0.0f, 1.0f };
		static constexpr const ImVec4 blue = { 0.0f, 0.0f, 1.0f, 1.0f };
	};
}