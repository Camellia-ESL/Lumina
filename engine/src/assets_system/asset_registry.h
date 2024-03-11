#pragma once

#include "asset.h"
#include "core/lumina_singleton.h"

#include <unordered_map>
#include <string>

namespace lumina
{
	class LUMINA_SINGLETON_CLASS(asset_registry)
	{
	public:

		asset& get_asset(const std::string& asset_id) { return registry_[asset_id]; }
		bool has_asset(const std::string& asset_id) { return registry_.contains(asset_id); }

		// Add an asset to the registry by giving a resource type that an asset can handle
		template<typename asset_resource_type>
		asset& create_asset(asset_resource_type* resource_ptr);

		// Destroy's an asset
		bool destroy_asset(const std::string& asset_id);
		bool destroy_asset(asset& asset);

		// Get's the whole registry
		const std::unordered_map<std::string, asset>& get_registry() const { return registry_; }

	private:

		std::unordered_map<std::string, asset> registry_;

		asset& push_asset(void* resource_ptr, asset::resource_types_e type);
		bool free_asset(const std::string& asset_id);

	};
}