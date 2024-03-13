#pragma once

#include "asset.h"
#include "core/lumina_singleton.h"

#include <unordered_map>
#include <string>
#include <memory>

namespace lumina
{
	// A generic asset registry, can contains any type of asset resource (check which resource is considered asset before using it)
	class assets_registry
	{
	public:

		using asset_registry_t = std::unordered_map<std::string, std::shared_ptr<asset>>;

		// Gets an asset by is a id (unique), NOTE you must check if it exist before with has_asset
		asset& get_asset(const std::string& asset_id) { return *registry_[asset_id]; }
		
		// Gets an asset by a given asset name (not that there may be more assets with the same name in that case it returns the first one)
		// NOTE you must check if it exist before with has_asset
		asset& get_asset_by_name(const std::string& asset_name);
		
		// Wheter if it contains a certain asset or not
		bool has_asset(const std::string& asset_id) { return registry_.contains(asset_id); }

		// Add an asset to the registry by giving a resource type that an asset can handle
		template<typename asset_resource_type>
		asset& create_asset(asset_resource_type* resource_ptr);

		// Destroy's an asset
		bool destroy_asset(const std::string& asset_id);
		bool destroy_asset(asset& asset);

		// Get's the whole registry
		const asset_registry_t& get_registry() const { return registry_; }

	private:

		asset_registry_t registry_;

		asset& push_asset(void* resource_ptr, asset::resource_types_e type);
		bool free_asset(const std::string& asset_id);

	};
}