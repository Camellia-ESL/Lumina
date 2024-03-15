#pragma once

#include "ui/view.h"

namespace lumina_editor
{
	class assets_browser_view : public view
	{

		void on_render() override;
	
	private:

		// The file path of the file that were dragged in the window
		std::string dragged_file_path_ = "";

		void render_import_asset_popup();
		void render_assets();

	};
}