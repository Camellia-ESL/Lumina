#include "script_engine.h"

#include "spdlog/spdlog.h"

LUMINA_SINGLETON_DECL_INSTANCE(lumina::script_engine);

namespace lumina
{
	script_engine::script_engine()
	{
		init();
	}

	script_engine::~script_engine()
	{
		destroy();
	}

	mono_script* script_engine::load_script(const std::string& file_path)
	{
		// Push the new script instance and get's a reference to operate on it
		scripts_loaded_.push_back(mono_script{});
		mono_script* script_instance = &scripts_loaded_[scripts_loaded_.size() - 1];

		// Tries to load the assembly
		script_instance->load_from_file(file_path);
		
		// If the loading fails removes the script instance added and return nullptr
		if (!script_instance->is_loaded())
		{
			scripts_loaded_.pop_back();
			return nullptr;
		}

		return script_instance;
	}

	void script_engine::init()
	{
		mono_set_dirs("mono_res/lib", "mono_res/etc");

		root_domain_ = mono_jit_init("ScriptRuntime");
		if (root_domain_ == nullptr)
		{
			spdlog::error("Error initializing the scripting engine!");
			return;
		}

		// Create an App Domain
		app_domain_ = mono_domain_create_appdomain((char*)"ScriptAppDomain", nullptr);
		mono_domain_set(app_domain_, true);

		spdlog::info("Scripting engine initialized.");
	}

	void script_engine::destroy()
	{
		mono_domain_free(app_domain_, true);
		mono_domain_free(root_domain_, true);
	}
}