#include "profiler_view.h"

#include "lumina.h"
#include "ImGui/imgui.h"

namespace lumina_editor
{
	void profiler_view::on_render() 
	{
		ImGui::Begin("Profiler");
		ImGui::Text("Memory Usage: %d mb", lumina::lumina_memory_s::get_virtual_memory_usage() / lumina::lumina_memory_s::MEGA_BYTE_SIZE);
		ImGui::Text("Latency: %.4f ms", lumina::application_player::get_singleton().get_delta_time());
		ImGui::Text("Fps: %.2f", lumina::application_player::get_singleton().get_fps());
		ImGui::End();
	}
}