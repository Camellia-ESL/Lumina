#pragma once

#include "lumina.h"

namespace lumina_runtime_player
{
	class LUMINA_SINGLETON_CLASS(runtime_script_manager)
	{
	public:

		runtime_script_manager();

		// Calls the on_start function for the application and every potential object that get's started
		void call_on_start();

		// Calls the on_update function for the application and every potential object that must be updated
		void call_on_update();

	private:

		lumina::mono_script* core_script_;
		lumina::mono_script* runtime_script_;
		MonoObject* rs_app_class_obj_;
		MonoMethod* rs_app_class_on_start_mtd_;
		MonoMethod* rs_app_class_on_update_mtd_;

		void init();

	};
}