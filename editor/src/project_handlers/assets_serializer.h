#pragma once

#include "lumina.h"

namespace lumina_editor
{
	// Asset serializer used to save and store assets for projects
	class assets_serializer
	{
	public:

		// Create's an asset bundle file with all the metadata about all the loaded assets
		static void serialize_assets_bundle(const lumina::assets_registry::asset_registry_t& assets, const std::string& file_path_out);

		// Load all the assets of a given bundle (note that it doesn't clear the asset registry before doing it)
		static void deserialize_assets_bundle(lumina::assets_registry& registry_to_load, const std::string& file_path);

	};
}