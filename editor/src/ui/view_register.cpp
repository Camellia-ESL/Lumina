#include "view_register.h"

namespace lumina_editor
{
	std::vector<std::shared_ptr<view>> views;

	std::shared_ptr<view> view_register_s::register_view(std::shared_ptr<view> panel_ptr)
	{
		// Check if the same view already exist
		if (contains_view(panel_ptr))
			return nullptr;

		panel_ptr->on_create();

		views.push_back(panel_ptr);

		return panel_ptr;
	}

	bool view_register_s::contains_view(std::shared_ptr<view> panel_ptr)
	{
		// Check if the view exist
		for (auto& panel_obj : views)
			if (panel_obj.get() == panel_ptr.get())
				return true;

		return false;
	}

	void view_register_s::destroy_view(std::shared_ptr<view> panel_ptr)
	{
		// Check if the view doesn't exist
		if (!contains_view(panel_ptr))
			return;

		panel_ptr->on_destroy();

		// Creates an itherator to iterate the list safely
		std::vector<std::shared_ptr<view>>::iterator panels_it = views.begin();

		// Search for missing items and delete them
		while (panels_it != views.end())
		{
			if (panels_it._Ptr->get() == panel_ptr.get())
				panels_it = views.erase(panels_it);
			else
				panels_it++;
		}
	}

	void view_register_s::destroy_views(const std::string& tag)
	{
		for (auto& view : views)
			if (view != nullptr && view->tag == tag)
				view_register_s::destroy_view(view);
	}

	void view_register_s::render_views()
	{
		// Render views
		for (size_t i = 0; i < views.size(); i++)
			views[i]->on_render();
	}
}