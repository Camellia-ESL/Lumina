#include "asset_registry.h"

#include "graphics/texture.h"

namespace lumina
{
	asset& assets_registry::get_asset_by_name(const std::string& asset_name)
	{
		for (auto& [id, asset] : registry_)
			if (asset->get_asset_name() == asset_name)
				return *registry_[id];

		return *registry_[0];
	}

	template<>
	asset& assets_registry::create_asset<texture>(texture* resource_ptr, const std::string& file_path)
	{
		return push_asset(resource_ptr, asset::resource_types_e::TEXTURE, file_path);
	}

	template<>
	asset& assets_registry::create_asset<texture>(texture* resource_ptr, const std::string& file_path, const std::string& uuid)
	{
		return push_asset(resource_ptr, asset::resource_types_e::TEXTURE, file_path, uuid);
	}

	bool assets_registry::destroy_asset(const std::string& asset_id)
	{
		return free_asset(asset_id);
	}

	bool assets_registry::destroy_asset(asset& asset)
	{
		return free_asset(asset.get_asset_id());
	}

	asset& assets_registry::push_asset(void* resource_ptr, asset::resource_types_e type, const std::string& file_path, const std::string& uuid)
	{
		// Create the new asset
		std::shared_ptr<asset> new_asset = std::make_shared<asset>();
		new_asset->set_resource(resource_ptr, type, file_path);
		
		if (!uuid.empty())
			new_asset->set_uuid(uuid);

		// Push it into the registry
		registry_.insert({ new_asset->get_asset_id(), new_asset });
		
		return *registry_.at(new_asset->get_asset_id());
	}

	bool assets_registry::free_asset(const std::string& asset_id)
	{
		if (!has_asset(asset_id))
			return false;

		// Erase the asset
		registry_.erase(asset_id);

		return true;
	}
}