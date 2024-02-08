#include "lumina_ui_input_text.h"

#include "ImGui/imgui.h"

namespace lumina_editor
{
	void lumina_ui_input_text::bind_text_buffer(std::string* text_buffer)
	{
		text_buffer_ = text_buffer;
		strcpy(input_holder_buffer_, text_buffer->c_str());
	}

	void lumina_ui_input_text::render(const std::string& label)
	{
		if (text_buffer_ == nullptr) 
			return;

		ImGui::InputText(label.c_str(), input_holder_buffer_, sizeof(input_holder_buffer_));
		*text_buffer_ = input_holder_buffer_;
	}
}