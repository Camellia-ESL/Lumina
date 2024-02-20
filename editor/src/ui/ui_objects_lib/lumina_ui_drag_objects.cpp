#include "lumina_ui_drag_objects.h"

namespace lumina_editor
{
	bool lumina_ui_drag_objects::drag_float_3_multi_text(
		const std::string& label,
		float* buffer,
		float speed,
		float items_width,
		const std::string& x_label,
		const std::string& y_label,
		const std::string& z_label
	)
	{
		bool result_x_drag = false;
		bool result_y_drag = false;
		bool result_z_drag = false;

		items_width = items_width == 0.0f ? ImGui::GetWindowWidth() / 5.0f : items_width;

		ImGui::Text(label.c_str());

		// Render Drag X
		ImGui::PushItemWidth(items_width);
		result_x_drag = ImGui::DragFloat(("##" + label + "drag_x").c_str(), &buffer[0], speed);
		ImGui::SameLine();
		ImGui::Text(x_label.c_str());

		ImGui::SameLine();

		// Render Drag Y
		result_y_drag = ImGui::DragFloat(("##" + label + "drag_y").c_str(), &buffer[1], speed);
		ImGui::SameLine();
		ImGui::Text(y_label.c_str());

		ImGui::SameLine();

		// Render Drag Z
		result_z_drag = ImGui::DragFloat(("##" + label + "drag_z").c_str(), &buffer[2], speed);
		ImGui::SameLine();
		ImGui::Text(z_label.c_str());
		ImGui::PopItemWidth();

		return result_x_drag || result_y_drag || result_z_drag;
	}

	bool lumina_ui_drag_objects::drag_float_3_multi_text_colored(
		const std::string& label,
		const ImVec4& x_color,
		const ImVec4& y_color,
		const ImVec4& z_color,
		float* buffer,
		float speed,
		float items_width,
		const std::string& x_label,
		const std::string& y_label,
		const std::string& z_label
	)
	{
		bool result_x_drag = false;
		bool result_y_drag = false;
		bool result_z_drag = false;

		items_width = items_width == 0.0f ? ImGui::GetWindowWidth() / 5.0f : items_width;

		ImGui::Text(label.c_str());

		// Render Drag X
		ImGui::PushItemWidth(items_width);
		result_x_drag = ImGui::DragFloat(("##" + label + "drag_x").c_str(), &buffer[0], speed);
		ImGui::PushStyleColor(ImGuiCol_Text, x_color);
		ImGui::SameLine();
		ImGui::Text(x_label.c_str());
		ImGui::PopStyleColor();

		ImGui::SameLine();

		// Render Drag Y
		result_y_drag = ImGui::DragFloat(("##" + label + "drag_y").c_str(), &buffer[1], speed);
		ImGui::PushStyleColor(ImGuiCol_Text, y_color);
		ImGui::SameLine();
		ImGui::Text(y_label.c_str());
		ImGui::PopStyleColor();

		ImGui::SameLine();

		// Render Drag Z
		result_z_drag = ImGui::DragFloat(("##" + label + "drag_z").c_str(), &buffer[2], speed);
		ImGui::PushStyleColor(ImGuiCol_Text, z_color);
		ImGui::SameLine();
		ImGui::Text(z_label.c_str());
		ImGui::PopStyleColor();
		ImGui::PopItemWidth();

		return result_x_drag || result_y_drag || result_z_drag;
	}

	bool lumina_ui_drag_objects::drag_float_4_multi_text(
		const std::string& label,
		float* buffer,
		float speed,
		float items_width,
		const std::string& x_label,
		const std::string& y_label,
		const std::string& z_label,
		const std::string& w_label
	)
	{
		bool result_x_drag = false;
		bool result_y_drag = false;
		bool result_z_drag = false;
		bool result_w_drag = false;

		items_width = items_width == 0.0f ? ImGui::GetWindowWidth() / 5.0f : items_width;

		ImGui::Text(label.c_str());

		// Render Drag X
		ImGui::PushItemWidth(items_width);
		result_x_drag = ImGui::DragFloat(("##" + label + "drag_x").c_str(), &buffer[0], speed);
		ImGui::SameLine();
		ImGui::Text(x_label.c_str());

		ImGui::SameLine();

		// Render Drag Y
		result_y_drag = ImGui::DragFloat(("##" + label + "drag_y").c_str(), &buffer[1], speed);
		ImGui::SameLine();
		ImGui::Text(y_label.c_str());

		ImGui::SameLine();

		// Render Drag Z
		result_z_drag = ImGui::DragFloat(("##" + label + "drag_z").c_str(), &buffer[2], speed);
		ImGui::SameLine();
		ImGui::Text(z_label.c_str());

		ImGui::SameLine();

		// Render Drag W
		result_w_drag = ImGui::DragFloat(("##" + label + "drag_w").c_str(), &buffer[3], speed);
		ImGui::SameLine();
		ImGui::Text(w_label.c_str());
		ImGui::PopItemWidth();

		return result_x_drag || result_y_drag || result_z_drag;
	}

	bool lumina_ui_drag_objects::drag_float_4_multi_text_colored(
		const std::string& label,
		const ImVec4& x_color,
		const ImVec4& y_color,
		const ImVec4& z_color,
		const ImVec4& w_color,
		float* buffer,
		float speed,
		float items_width,
		const std::string& x_label,
		const std::string& y_label,
		const std::string& z_label,
		const std::string& w_label
	)
	{
		bool result_x_drag = false;
		bool result_y_drag = false;
		bool result_z_drag = false;
		bool result_w_drag = false;

		items_width = items_width == 0.0f ? ImGui::GetWindowWidth() / 5.0f : items_width;

		ImGui::Text(label.c_str());

		// Render Drag X
		ImGui::PushItemWidth(items_width);
		result_x_drag = ImGui::DragFloat(("##" + label + "drag_x").c_str(), &buffer[0], speed);
		ImGui::PushStyleColor(ImGuiCol_Text, x_color);
		ImGui::SameLine();
		ImGui::Text(x_label.c_str());
		ImGui::PopStyleColor();

		ImGui::SameLine();

		// Render Drag Y
		result_y_drag = ImGui::DragFloat(("##" + label + "drag_y").c_str(), &buffer[1], speed);
		ImGui::PushStyleColor(ImGuiCol_Text, y_color);
		ImGui::SameLine();
		ImGui::Text(y_label.c_str());
		ImGui::PopStyleColor();

		ImGui::SameLine();

		// Render Drag Z
		result_z_drag = ImGui::DragFloat(("##" + label + "drag_z").c_str(), &buffer[2], speed);
		ImGui::PushStyleColor(ImGuiCol_Text, z_color);
		ImGui::SameLine();
		ImGui::Text(z_label.c_str());
		ImGui::PopStyleColor();

		ImGui::SameLine();

		// Render Drag W
		result_z_drag = ImGui::DragFloat(("##" + label + "drag_w").c_str(), &buffer[3], speed);
		ImGui::PushStyleColor(ImGuiCol_Text, w_color);
		ImGui::SameLine();
		ImGui::Text(w_label.c_str());
		ImGui::PopStyleColor();
		ImGui::PopItemWidth();

		return result_x_drag || result_y_drag || result_z_drag;
	}
}