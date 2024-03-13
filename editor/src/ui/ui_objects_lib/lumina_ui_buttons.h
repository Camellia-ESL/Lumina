#pragma once

#include "lumina.h"

#include "ImGui/imgui.h"

#include <string>

namespace lumina_editor
{
	class lumina_ui_buttons
	{
	public:

		// Display an image button with a text description below (str must be a unique str or the button is not going to handle input properly) 
		static bool img_txt_button(
			const std::string& str, 
			const lumina::texture& texture, 
			const float txt_offset = -1.0f, 
			const ImVec2 size = { 50.0f, 50.0f }
		);

	};
}