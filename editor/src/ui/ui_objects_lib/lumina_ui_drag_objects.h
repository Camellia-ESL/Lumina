#pragma once

#include "ImGui/imgui.h"

#include <string>

namespace lumina_editor
{
	class lumina_ui_drag_objects
	{
	public:

		static bool drag_float_3_multi_text(
			const std::string& label, 
			float* buffer,
			float speed = 1.0f,
			float items_width = 0.0f,
			const std::string& x_label = "X",
			const std::string& y_label = "Y",
			const std::string& z_label = "Z"
		);

		static bool drag_float_3_multi_text_colored(
			const std::string& label,
			const ImVec4& x_color,
			const ImVec4& y_color,
			const ImVec4& z_color,
			float* buffer,
			float speed = 1.0f,
			float items_width = 0.0f,
			const std::string & x_label = "X",
			const std::string& y_label = "Y",
			const std::string& z_label = "Z"
		);

		static bool drag_float_4_multi_text(
			const std::string& label,
			float* buffer,
			float speed = 1.0f,
			float items_width = 0.0f,
			const std::string& x_label = "X",
			const std::string& y_label = "Y",
			const std::string& z_label = "Z",
			const std::string& w_label = "W"
		);

		static bool drag_float_4_multi_text_colored(
			const std::string& label,
			const ImVec4& x_color,
			const ImVec4& y_color,
			const ImVec4& z_color,
			const ImVec4& w_color,
			float* buffer,
			float speed = 1.0f,
			float items_width = 0.0f,
			const std::string& x_label = "X",
			const std::string& y_label = "Y",
			const std::string& z_label = "Z",
			const std::string& w_label = "W"
		);

	};
}