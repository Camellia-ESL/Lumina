#include "runtime_script_manager.h"

#include "../runtime_player_compile_configs.h"

#include "script_engine/script_binder.h"

#include "spdlog/spdlog.h"

LUMINA_SINGLETON_DECL_INSTANCE(lumina_runtime_player::runtime_script_manager);

namespace lumina_runtime_player
{
	runtime_script_manager::runtime_script_manager()
	{
		init();
	}

	void runtime_script_manager::call_on_start()
	{
		// Call the C# method App::OnStart on the objectInstance instance, and get any potential exceptions
		MonoObject* exception = nullptr;
		mono_runtime_invoke(rs_app_class_on_start_mtd_, rs_app_class_obj_, nullptr, &exception);
	}

	void runtime_script_manager::call_on_update()
	{
		// Call the C# method App::OnUpdate on the objectInstance instance, and get any potential exceptions
		MonoObject* exception = nullptr;
		mono_runtime_invoke(rs_app_class_on_update_mtd_, rs_app_class_obj_, nullptr, &exception);
	}

	void runtime_script_manager::init()
	{
		core_script_ = lumina::script_engine::get_singleton().load_script(
			LUMINA_RUNTIME_PLAYER_ASSEMBLIES_DIR LUMINA_RUNTIME_PLAYER_SCRIPT_CORE_NAME
		);

		// Loads lumina script core dll
		if (core_script_ == nullptr)
		{
			spdlog::error("Error loading lumina script core.");
			return;
		}

		runtime_script_ = lumina::script_engine::get_singleton().load_script(
			LUMINA_RUNTIME_PLAYER_ASSEMBLIES_DIR LUMINA_RUNTIME_PLAYER_SCRIPT_BUILD_NAME
		);

		// Loads assembled template dll
		if (runtime_script_ == nullptr)
		{
			spdlog::error("Error loading lumina runtime assembly.");
			return;
		}

		// Binds all the script functions, methods, properties, classes, etc..
		lumina::script_binder::bind_all(core_script_);

		// Get's a handle to the App class, create's a instance of it an run it's methods
		MonoClass* rs_app_class_def = runtime_script_->get_class("App");
		rs_app_class_obj_ = runtime_script_->create_class_obj(rs_app_class_def);

		// Get a reference to the OnStart and OnUpdate methods in the App class
		rs_app_class_on_start_mtd_ = mono_class_get_method_from_name(rs_app_class_def, "OnStart", 0);

		if (rs_app_class_on_start_mtd_ == nullptr)
		{
			spdlog::error("Error binding runtime app class, no OnStart method was found in App class.");
			return;
		}

		rs_app_class_on_update_mtd_ = mono_class_get_method_from_name(rs_app_class_def, "OnUpdate", 0);

		if (rs_app_class_on_update_mtd_ == nullptr)
		{
			spdlog::error("Error binding runtime app class, no OnUpdate method was found in App class.");
			return;
		}
	}
}