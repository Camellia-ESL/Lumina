#include "assets_serializer.h"

#include "yaml-cpp/yaml.h"
#include "core/lumina_file_system.h"

#include "core/lumina_types.h"

// Asset types imports
#include "graphics/texture.h"

namespace lumina
{
	void assets_serializer::serialize_assets_bundle(const assets_registry::asset_registry_t& assets, const std::string& file_path_out)
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

	void assets_serializer::deserialize_assets_bundle(assets_registry& registry_to_load, const std::string& file_path)
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
			const asset::resource_types_e asset_type = (asset::resource_types_e)asset_yaml["Type"].as<uint32_t>();

			// Based on the type tries to load the different asset
			if (asset_type == asset::resource_types_e::TEXTURE)
			{
				texture* texture = new lumina::texture{};
				bool result = texture->load_from_file(asset_yaml["File Path"].as<std::string>());

				// If loaded correctly, loads the asset in the registry
				if (result)
				{
					asset& asset_loaded = 
						registry_to_load.create_asset(
							texture, 
							asset_yaml["File Path"].as<std::string>(), 
							asset_yaml["Id"].as<std::string>()
						);
					
					asset_loaded.set_name(asset_yaml["Name"].as<std::string>());
				}
			}
		}
	}

	static constexpr const l_uint32 ASSET_METADATA_BIN_MASK_SIZE = l_kbyte8_size;

	/*
	* NOTE -> This should be updated everytime assets metadata indentation structure changes when serializing and deserializing binary
	* 
	*	file -> 
	*		4 bytes (assets count)
	*			assets array ->
	*						{
	*							4 bytes (name size)
	*							? bytes (name const char*)
	*							4 bytes (id size)
	*							? bytes (id const char*)
	*							4 bytes (asset type size)
	*							4 bytes (asset type)
	*						}
	*/

	void assets_serializer::serialize_assets_package(const assets_registry::asset_registry_t& assets, const std::string& file_path_out)
	{
		// Before opening the file tries to delete it if exist
		std::filesystem::remove(file_path_out);

		// Opens the file
		std::ofstream asset_package_file(file_path_out, std::ios::out | std::ios::binary | std::ios::app);

		l_uint32 mask_usage_size = 0;

		auto serialize_resource = 
			[&](void* resource, l_uint32 resource_size, bool is_metadata = true) -> void 
			{
				asset_package_file.write(reinterpret_cast<const char*>(&resource_size), sizeof(l_uint32));
				asset_package_file.write(reinterpret_cast<const char*>(resource), resource_size);

				if(is_metadata)
					mask_usage_size += sizeof(l_uint32) + resource_size;
			};

		// Write the number of assets that the package will contains
		l_uint32 assets_count = assets.size();
		asset_package_file.write(reinterpret_cast<const char*>(&assets_count), sizeof(l_uint32));

		// Loop all the assets and serialize them in a sequence of maps (each map is an asset metadata map)
		for (auto& [asset_id, asset] : assets)
		{
			// Serialize assets metadatas (add's one byte to strings for the null character)
			serialize_resource((void*)asset->get_asset_name().c_str(), asset->get_asset_name().size() + l_byte8_size);
			serialize_resource((void*)asset->get_asset_id().c_str(), asset->get_asset_id().size() + l_byte8_size);
			lumina::asset::resource_types_e asset_type = asset->get_type();
			serialize_resource((void*)&asset_type, sizeof(lumina::asset::resource_types_e));

			// Fills the empty metadata mask memory
			char* empty_mask_buffer = new char[ASSET_METADATA_BIN_MASK_SIZE - mask_usage_size]();
			asset_package_file.write(empty_mask_buffer, ASSET_METADATA_BIN_MASK_SIZE - mask_usage_size);

			// Reset the mask usage and free the empty mask buffer
			mask_usage_size = 0;
			delete[] empty_mask_buffer;

			// Load the asset file and fills the memory with its data
			std::ifstream asset_res_file{ asset->get_file_path(), std::ios::binary };
			
			// Get asset file size using buffer's members
			l_uint64 asset_data_size = std::filesystem::file_size(asset->get_file_path());

			// Allocate memory to contain asset file data
			l_byte8* asset_data_buffer = new l_byte8[asset_data_size];

			// Get asset file data
			asset_res_file.read((l_char8*)asset_data_buffer, asset_data_size);

			// Serialize asset file data in the package
			serialize_resource(asset_data_buffer, asset_data_size, false);
			asset_res_file.close();

			// Free the asset data buffer
			delete[] asset_data_buffer;
		}
		
		asset_package_file.close();
	}

	void assets_serializer::deserialize_assets_package(assets_registry& registry_to_load, const std::string& file_path)
	{
		// Load the asset package file
		std::ifstream assets_package_file{ file_path, std::ios::binary };

		// Read the assets count
		l_uint32 assets_count = 0;
		l_uint32 mask_usage_size = 0;
		assets_package_file.read(reinterpret_cast<char*>(&assets_count), l_uint32_size);

		// Contains as first argument the pointer to the deserialized resource and as second parameter the size of the resource
		typedef std::pair<void*, l_uint32> deserialized_resource;

		// Return's a pointer to the buffer holding the next read resource, BE SURE TO FREE THE MEMORY after using it
		auto deserialize_next_resource =
			[&](bool is_metadata = true) -> deserialized_resource
			{
				// Get's the resoure size and then read the resource
				l_uint32 resource_size = 0;
				assets_package_file.read(reinterpret_cast<char*>(&resource_size), sizeof(l_uint32));

				// Check if the size is good
				if (resource_size == 0)
					return std::pair{ nullptr, 0 };

				char* resource = new char[resource_size]();

				// Read the resource
				assets_package_file.read(resource, resource_size);

				// If metadata resource eval the new size
				if (is_metadata)
					mask_usage_size += sizeof(l_uint32) + resource_size;

				return std::pair{ resource, resource_size };
			};

		// Get's the string from a deserialized resource, NOTE that also free the memory of the resource after
		auto get_string_from_deserialized_res = 
			[&](deserialized_resource res) -> std::string
			{
				// Copies the string
				std::string res_copied_buf = (char*)res.first;

				// Free the resource buffer
				delete[] res.first;

				return res_copied_buf;
			};

		auto get_uint_from_deserialized_res =
			[&](deserialized_resource res) -> l_uint32
			{
				// Copies the string
				l_uint32 res_copied_buf = *((l_uint32*)res.first);

				// Free the resource buffer
				delete[] res.first;

				return res_copied_buf;
			};

		for (l_uint32 i = 0; i < assets_count; i++)
		{
			std::string asset_name_buffer = get_string_from_deserialized_res(deserialize_next_resource());
			std::string asset_name_id = get_string_from_deserialized_res(deserialize_next_resource());
			asset::resource_types_e asset_type = (asset::resource_types_e)get_uint_from_deserialized_res(deserialize_next_resource());

			// Skip all the rest of the unused metadata bytes
			char* unused_bytes = new char[ASSET_METADATA_BIN_MASK_SIZE - mask_usage_size]();
			assets_package_file.read(unused_bytes, ASSET_METADATA_BIN_MASK_SIZE - mask_usage_size);
			delete[] unused_bytes;

			// Reset the mask usage size
			mask_usage_size = 0;

			deserialized_resource asset_resource_buffer = deserialize_next_resource(false);

			// Load the asset based on the different type
			if (asset_type == asset::resource_types_e::TEXTURE)
			{
				texture* texture_to_load = new lumina::texture{};
				bool tex_load_result = texture_to_load->load_from_memory(asset_resource_buffer.first, asset_resource_buffer.second);

				// Texture was loaded correctly, loads the texture inside and assets and loads the asset in the atlas
				if (tex_load_result)
				{
					asset& asset_loaded = registry_to_load.create_asset(texture_to_load, file_path, asset_name_id);
					asset_loaded.set_name(asset_name_buffer);
				}
			}

			// Free the asset resource buffer
			delete[] asset_resource_buffer.first;
		}
	}
}