#pragma once

#include <string>

namespace lumina
{
	struct app_info_t
	{
		// The application name (not the surface name)
		std::string app_name{ "Untitled App" };
		
		// The surface name 
		std::string surface_name{ "Untitled Surface" };
		
		// Surface start width size
		float surface_width{ 1280 };

		// Surface start height size 
		float surface_height{ 1024 };
	};

	// Application player abstraction, create, run and holds an application
	class application_player
	{
	public:

		application_player() { instance_ = this; }

		static application_player& get_singleton() { return *instance_; }

		// Should be called only once, starts the application
		void run(const app_info_t& app_info);

		// Should be called only once, terminate the application
		void exit();

		// Called every frame before rendering
		virtual void on_update() {}

		// Called every frame on rendering
		virtual void on_render() {}

		// Wheter if the app is running or not
		const bool is_running() const { return is_running_; }

	protected:

		static application_player* instance_;

	protected:

		bool is_running_ = false;

	};
}