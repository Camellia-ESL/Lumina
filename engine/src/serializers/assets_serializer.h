#pragma once

#include "assets_system/asset_registry.h"

namespace lumina
{
	// Asset serializer used to save and store assets for projects
	class assets_serializer
	{
	public:

		/*
		* Bundles format serialization's, bundles contain a list of all the assets with their relative file path and more asset metadata.
		* They are saved in a yaml format.
		*/

		// Create's an asset bundle file with all the metadata about all the loaded assets
		static void serialize_assets_bundle(const assets_registry::asset_registry_t& assets, const std::string& file_path_out);

		// Load all the assets of a given bundle (note that it doesn't clear the asset registry before doing it)
		static void deserialize_assets_bundle(assets_registry& registry_to_load, const std::string& file_path);

		/*
		* Packages format serialization's, packages contain all the assets packed in a single file.
		*/

		// Create's an asset package file with all the assets serialized 
		static void serialize_assets_package(const assets_registry::asset_registry_t& assets, const std::string& file_path_out);

		// Load all the assets of a given package (note that it doesn't clear the asset registry before doing it)
		static void deserialize_assets_package(assets_registry& registry_to_load, const std::string& file_path);
	};
}