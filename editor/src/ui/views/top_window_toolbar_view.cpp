#include "top_window_toolbar_view.h"

#include "ImGui/imgui.h"

namespace lumina_editor
{
	void top_window_toolbar_view::on_render()
	{
		// Menu
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Projects"))
			{
				if (ImGui::MenuItem("New Project", "Ctrl + N"))
				{

				}

				if (ImGui::MenuItem("Save Project", "Ctrl + S"))
				{

				}

				if (ImGui::MenuItem("Load Project", "Ctrl + L"))
				{

				}

				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
	}
}