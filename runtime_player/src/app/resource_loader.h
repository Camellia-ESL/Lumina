#pragma once

#include "core/lumina_singleton.h"

namespace lumina_runtime_player
{
	// The resource loader used to load assets, scenes and more
	class resource_loader
	{
	public:

		static void load_assets();
		static void load_scenes();

	};
}