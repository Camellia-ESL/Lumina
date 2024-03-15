#include "lumina_ui_buttons.h"

namespace lumina_editor
{
	bool lumina_ui_buttons::img_txt_button(const std::string& str, const std::string& id, const lumina::texture& texture, const float txt_offset, const ImVec2 size)
	{
		bool is_clicked = false;

		ImGui::BeginGroup();

		// Display the button image
		if (ImGui::ImageButton(
			id.c_str(),
			texture.get_native_resource_buffer(),
			size
		))
			is_clicked = true;

		const ImVec2 str_pixel_size = ImGui::CalcTextSize(str.c_str());

		// Display the button text (if not txt_offset is provided [txt_offset == -1.0f] it place the text 20% of the size coordinates on the right)
		ImGui::SetCursorPosX(
			txt_offset == -1.0f ? 
			ImGui::GetCursorPosX() + (size.x / 2.0f) - (str_pixel_size.x / 2.0f) : 
			ImGui::GetCursorPosX() + txt_offset
		);

		ImGui::Text(str.c_str());

		ImGui::EndGroup();

		return is_clicked;
	}
}