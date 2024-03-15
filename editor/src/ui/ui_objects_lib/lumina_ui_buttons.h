#pragma once

#include "lumina.h"

#include "ImGui/imgui.h"

#include <string>

namespace lumina_editor
{
	class lumina_ui_buttons
	{
	public:

		// Display an image button with a text description below  
		static bool img_txt_button(
			const std::string& str, 
			const std::string& id,
			const lumina::texture& texture, 
			const float txt_offset = -1.0f, 
			const ImVec2 size = { 50.0f, 50.0f }
		);

	};
}