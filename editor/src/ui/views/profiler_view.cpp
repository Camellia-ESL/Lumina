#include "profiler_view.h"

#include "ui/ui_shared_vars.h"

#include "lumina.h"
#include "ImGui/imgui.h"

namespace lumina_editor
{
	void profiler_view::on_render() 
	{
		if (!ui_shared_vars::IS_PROFILER_VIEW_OPEN)
			return;

		ImGui::Begin("Profiler");
		ImGui::Text("Memory Usage: %d mb", lumina::lumina_memory_s::get_virtual_memory_usage() / lumina::lumina_memory_s::MEGA_BYTE_SIZE);
		ImGui::Text("Latency: %.4f ms", lumina::application_player::get_singleton().get_delta_time());
		ImGui::Text("Fps: %.2f", lumina::application_player::get_singleton().get_fps());
		ImGui::End();
	}
}