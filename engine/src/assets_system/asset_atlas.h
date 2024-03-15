#pragma once

#include "asset_registry.h"
#include "core/lumina_singleton.h"

namespace lumina
{
	// The main asset atlas provided by the engine that should contain every asset that belongs to the scenes
	class LUMINA_SINGLETON_CLASS(asset_atlas)
	{
	public:

		// Get the registry to access the assets
		assets_registry& get_registry() { return registry_; };

	private:

		assets_registry registry_{};

	};
}