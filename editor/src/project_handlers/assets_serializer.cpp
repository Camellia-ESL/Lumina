#include "assets_serializer.h"

namespace lumina_editor
{
	void assets_serializer::serialize_assets_bundle(const lumina::assets_registry::asset_registry_t& assets, const std::string& file_path_out)
	{
		YAML::Emitter yaml_stream_emitter;
		yaml_stream_emitter << YAML::BeginMap;
		yaml_stream_emitter << YAML::Key << "Assets Metadata";
		yaml_stream_emitter << YAML::Value << YAML::BeginSeq;

		// Loop all the assets and serialize them in a sequence of maps (each map is an asset metadata map)
		for (auto& [asset_id, asset] : assets)
		{
			yaml_stream_emitter << YAML::BeginMap;

			// The Asset UUID
			yaml_stream_emitter << YAML::Key << "Id";
			yaml_stream_emitter << YAML::Value << asset->get_asset_id();

			// The Asset file path (the file location of the asset)
			yaml_stream_emitter << YAML::Key << "File Path";
			yaml_stream_emitter << YAML::Value << asset->get_file_path();

			// The Asset type 
			yaml_stream_emitter << YAML::Key << "Type";
			yaml_stream_emitter << YAML::Value << (uint32_t)asset->get_type();

			// The Asset name
			yaml_stream_emitter << YAML::Key << "Name";
			yaml_stream_emitter << YAML::Value << asset->get_asset_name();

			yaml_stream_emitter << YAML::EndMap;
		}

		yaml_stream_emitter << YAML::EndSeq;

		

		yaml_stream_emitter << YAML::EndMap;

		// Save everything in the bundle file
		std::ofstream out_stream{ file_path_out };
		out_stream << yaml_stream_emitter.c_str();
	}

	void assets_serializer::deserialize_assets_bundle(lumina::assets_registry& registry_to_load, const std::string& file_path)
	{
		// Tries to load the file
		YAML::Node assets_bundle_yaml;

		try
		{
			assets_bundle_yaml = YAML::LoadFile(file_path);
		}
		catch (const std::exception&)
		{
			return;
		}

		// Check if the file is good
		if (!assets_bundle_yaml || !assets_bundle_yaml["Assets Metadata"])
			return;

		// Load the assets in the registry
		for (auto asset_yaml : assets_bundle_yaml["Assets Metadata"])
		{
			const lumina::asset::resource_types_e asset_type = (lumina::asset::resource_types_e)asset_yaml["Type"].as<uint32_t>();

			// Based on the type tries to load the different asset
			if (asset_type == lumina::asset::resource_types_e::TEXTURE)
			{
				lumina::texture* texture = new lumina::texture{};
				bool result = texture->load_from_file(asset_yaml["File Path"].as<std::string>());

				// If loaded correctly, loads the asset in the registry
				if (result)
					registry_to_load.create_asset(texture, asset_yaml["File Path"].as<std::string>(), asset_yaml["Id"].as<std::string>());
			}
		}
	}
}