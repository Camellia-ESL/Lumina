#include "console_view.h"

#include "ui/colors.h"

#include "application/logger.h"

#include "ImGui/imgui.h"

namespace lumina_editor
{
	void console_view::on_render()
	{
		ImGui::Begin("Console");

		// Display all the logs 
		lumina::lumina_logger& logger = lumina::lumina_logger::get_singleton();
		static l_uint64 logs_precedent_size = logger.get_logs().size();

		const auto get_log_header_color =
			[&](lumina::lumina_logger::log_types_e type) -> editor_ui_color
			{
				return
					type == lumina::lumina_logger::log_types_e::INFO_LOG ? editor_ui_colors::GREEN :
					type == lumina::lumina_logger::log_types_e::WARNING_LOG ? editor_ui_colors::YELLOW :
					type == lumina::lumina_logger::log_types_e::ERROR_LOG ? editor_ui_colors::RED : ImVec4{ 1.0f, 1.0f, 1.0f, 1.0f };
			};

		const auto get_log_header_prefix =
			[&](lumina::lumina_logger::log_types_e type) -> const std::string
			{
				return
					type == lumina::lumina_logger::log_types_e::INFO_LOG ? "[Info]" :
					type == lumina::lumina_logger::log_types_e::WARNING_LOG ? "[Warning]" :
					type == lumina::lumina_logger::log_types_e::ERROR_LOG ? "[Error]" : "[Info]";
			};

		for (const auto& log : logger.get_logs())
		{
			ImGui::TextColored(
				get_log_header_color(log.type),
				(get_log_header_prefix(log.type) + log.date + " ").c_str()
			);

			ImGui::SameLine();

			ImGui::Text(log.msg.c_str());
		}

		if (logger.get_logs().size() > logs_precedent_size)
		{
			logs_precedent_size = logger.get_logs().size();
			ImGui::SetScrollHereY(1.0f);
		}

		ImGui::End();
	}
}