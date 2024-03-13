#pragma once

#include "ui/view.h"

#include "project_handlers/projects.h"

namespace lumina_editor
{
	class content_browser_view : public view
	{

		void on_create() override;
		void on_render() override;

	private:

		std::string selected_directory_id_;

	};
}