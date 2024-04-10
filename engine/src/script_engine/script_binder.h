#pragma once

#include "mono_script.h"

namespace lumina
{
	// Mono util class to provide an easy way to bind c++ functions to the MONO ICL functions
	class script_binder
	{
	public:

		static void bind_all(mono_script* script_to_forward_binds);
		static void bind_application(mono_script* script_to_forward_binds);
		static void bind_scene_manager(mono_script* script_to_forward_binds);
		static void bind_scene(mono_script* script_to_forward_binds);
		static void bind_entity(mono_script* script_to_forward_binds);
		static void bind_transform(mono_script* script_to_forward_binds);
		static void bind_sprite(mono_script* script_to_forward_binds);
		static void bind_logger(mono_script* script_to_forward_binds);

	private:

	};
}