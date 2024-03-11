#include "asset_registry.h"

lumina::asset_registry* lumina::asset_registry::singleton_instance_ = nullptr;

#include "graphics/texture.h"

namespace lumina
{
	template<>
	asset& asset_registry::create_asset<texture>(texture* resource_ptr)
	{
		return push_asset(resource_ptr, asset::resource_types_e::TEXTURE);
	}

	bool asset_registry::destroy_asset(const std::string& asset_id)
	{
		return free_asset(asset_id);
	}

	bool asset_registry::destroy_asset(asset& asset)
	{
		return free_asset(asset.get_asset_id());
	}

	asset& asset_registry::push_asset(void* resource_ptr, asset::resource_types_e type)
	{
		// Create the new asset
		asset new_asset{};
		new_asset.set_resource(resource_ptr, type);

		// Push it into the registry
		registry_[new_asset.get_asset_id()] = new_asset;

		return registry_[new_asset.get_asset_id()];
	}

	bool asset_registry::free_asset(const std::string& asset_id)
	{
		if (!has_asset(asset_id))
			return false;

		// Erase the asset
		registry_.erase(asset_id);

		return true;
	}
}