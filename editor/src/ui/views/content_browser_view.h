#pragma once

#include "ui/view.h"

#include "project_handlers/projects.h"

namespace lumina_editor
{
	class content_browser_view : public view
	{
	public:

		void on_create() override;
		void on_render() override;

		void set_selected_directory_id(const std::string& id) { selected_directory_id_ = id; }

	private:

		std::string selected_directory_id_;

	};
}