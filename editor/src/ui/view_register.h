#pragma once

#include "view.h"

#include <vector>
#include <memory>

namespace lumina_editor
{
	// The view register contains all the views created to render every frame
	// using this to allocate views it's the preferable way
	class view_register_s
	{
	public:

		// Register a new view in the register 
		static std::shared_ptr<view> register_view(std::shared_ptr<view> panel_ptr);
		
		// Wheter if a view is contained or not in the view register
		static bool contains_view(std::shared_ptr<view> panel_ptr);

		// Destroy's a view in the register and erase it
		static void destroy_view(std::shared_ptr<view> panel_ptr);

		// Destroy's all the views that match the given tag
		static void destroy_views(const std::string& tag);

	private:

		// Render every view
		static void render_views();

	private:

		friend class ui_render_s;

	};
}