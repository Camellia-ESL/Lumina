#pragma once

#include "mono_script.h"

#include "core/lumina_singleton.h"

#include "mono/jit/jit.h"
#include "mono/metadata/assembly.h"

#include <vector>

namespace lumina
{
	class LUMINA_SINGLETON_CLASS(script_engine)
	{
	public:

		script_engine();
		~script_engine();

		mono_script* load_script(const std::string& file_path);

		MonoDomain* get_root_domain() { return root_domain_; }
		MonoDomain* get_app_domain() { return app_domain_; }

	private:

		MonoDomain* root_domain_ = nullptr;
		MonoDomain* app_domain_ = nullptr;
		std::vector<mono_script> scripts_loaded_{};

		// Init's the script engine
		void init();

		// Destroy's the script engine
		void destroy();
	};
}