#pragma once

#include <string>

namespace lumina_editor
{
	// Represent a basic window surface of the editor 
	class view
	{
	public:

		// An assignable tag identifier (can be everything)
		std::string tag{ "" };

		// Called when the view get's instanced
		virtual void on_create() {}

		// Called every frame on render
		virtual void on_render() {}

		// Called when the view get's destroyed
		virtual void on_destroy() {}
	};
}