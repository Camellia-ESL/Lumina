#include "scene_serializer.h"

#include "scene_system/scenes_system.h"
#include "types_serializer.h"

#include "spdlog/spdlog.h"
#include "yaml-cpp/yaml.h"

#include <fstream>

namespace lumina
{
	// Serialization

	static void serialize_identity_component(identity_component& identifier, YAML::Emitter& yaml_stream_emitter)
	{
		yaml_stream_emitter << YAML::Key << "Identity Component";
		
		// Create's the component map
		yaml_stream_emitter << YAML::Value << YAML::BeginMap;

		yaml_stream_emitter << YAML::Key << "Entity Name";
		yaml_stream_emitter << YAML::Value << identifier.name;
		yaml_stream_emitter << YAML::Key << "Entity UUID";
		yaml_stream_emitter << YAML::Value << identifier.id;

		// End the
		yaml_stream_emitter << YAML::EndMap;
	}

	static void serialize_transform_component(transform_component& transform, YAML::Emitter& yaml_stream_emitter)
	{
		yaml_stream_emitter << YAML::Key << "Transform Component";

		// Create's the component map
		yaml_stream_emitter << YAML::Value << YAML::BeginMap;

		yaml_stream_emitter << YAML::Key << "Position";
		yaml_stream_emitter << YAML::Value;
		types_serializer::serialize_yaml_vec3(transform.position, yaml_stream_emitter);

		yaml_stream_emitter << YAML::Key << "Rotation";
		yaml_stream_emitter << YAML::Value;
		types_serializer::serialize_yaml_vec3(transform.rotation, yaml_stream_emitter);

		yaml_stream_emitter << YAML::Key << "Scale";
		yaml_stream_emitter << YAML::Value;
		types_serializer::serialize_yaml_vec3(transform.scale, yaml_stream_emitter);
		
		// End the
		yaml_stream_emitter << YAML::EndMap;
	}

	static void serialize_sprite_component(sprite_component& sprite, YAML::Emitter& yaml_stream_emitter)
	{
		yaml_stream_emitter << YAML::Key << "Sprite Component";

		// Create's the component map
		yaml_stream_emitter << YAML::Value << YAML::BeginMap;

		yaml_stream_emitter << YAML::Key << "Shape";
		yaml_stream_emitter << YAML::Value << (uint32_t)sprite.shape;

		yaml_stream_emitter << YAML::Key << "Color";
		yaml_stream_emitter << YAML::Value;
		types_serializer::serialize_yaml_vec4(sprite.color, yaml_stream_emitter);

		// End the
		yaml_stream_emitter << YAML::EndMap;
	}

	void scene_serializer::serialize_yaml(scene& scene, const std::string& file_path)
	{
		// Log the save msg
		spdlog::info("Saving scene: " + scene.get_name() + "...");

		// Start's Serializing the scene
		YAML::Emitter yaml_stream_emitter;
		yaml_stream_emitter << YAML::BeginMap;
		yaml_stream_emitter << YAML::Key << "Scene Name";
		yaml_stream_emitter << YAML::Value << scene.get_name();
		
		// Serialize entities with their components
		yaml_stream_emitter << YAML::Key << "Entities";
		yaml_stream_emitter << YAML::Value << YAML::BeginSeq;

		auto entities_view = scene.get_entity_registry().view<identity_component>();

		for (entt::entity ent : entities_view)
		{
			entity entity{ &scene.get_entity_registry(), ent };

			// Create's the entity map
			yaml_stream_emitter << YAML::BeginMap;

			// Serialize identity_component
			serialize_identity_component(entity.get_component<identity_component>(), yaml_stream_emitter);
			
			// Serialize transform_component
			if(entity.has_component<transform_component>())
				serialize_transform_component(entity.get_component<transform_component>(), yaml_stream_emitter);

			// Serialize sprite_component
			if (entity.has_component<sprite_component>())
				serialize_sprite_component(entity.get_component<sprite_component>(), yaml_stream_emitter);

			// Save the entity map
			yaml_stream_emitter << YAML::EndMap;
		}

		yaml_stream_emitter << YAML::EndSeq;

		// End the scene serializing
		yaml_stream_emitter << YAML::EndMap;

		// Save everything in the file 
		std::ofstream out_stream{ file_path };
		out_stream << yaml_stream_emitter.c_str();
	}

	// Deserialization

	static void deserialize_identity_component(entity& entity, YAML::detail::iterator_value& yaml_entity)
	{
		auto yaml_identity_component = yaml_entity["Identity Component"];
		identity_component& ent_identity_component = entity.get_component<identity_component>();

		// Deserialize the component
		ent_identity_component.name = yaml_identity_component["Entity Name"].as<std::string>();
		ent_identity_component.id = yaml_identity_component["Entity UUID"].as<std::string>();
	}

	static void deserialize_transform_component(entity& entity, YAML::detail::iterator_value& yaml_entity)
	{
		auto yaml_component = yaml_entity["Transform Component"];
		
		// Check if the component doesn't exist
		if (!yaml_component)
			return;

		transform_component& ent_component = entity.add_component<transform_component>();

		auto position_node = yaml_component["Position"];
		auto rotation_node = yaml_component["Rotation"];
		auto scale_node = yaml_component["Scale"];
	
		// Deserialize the component
		ent_component.position = types_serializer::deserialize_yaml_vec3(position_node);
		ent_component.rotation = types_serializer::deserialize_yaml_vec3(rotation_node);
		ent_component.scale = types_serializer::deserialize_yaml_vec3(scale_node);
	}

	static void deserialize_sprite_component(entity& entity, YAML::detail::iterator_value& yaml_entity)
	{
		auto yaml_component = yaml_entity["Sprite Component"];

		// Check if the component doesn't exist
		if (!yaml_component)
			return;

		sprite_component& ent_component = entity.add_component<sprite_component>();

		// Deserialize the component
		ent_component.shape = (lumina::sprite_component::shapes)yaml_component["Shape"].as<uint32_t>();

		auto color_node = yaml_component["Color"];
		ent_component.color = types_serializer::deserialize_yaml_vec4(color_node);
	}

	void scene_serializer::deserialize_yaml(scene& scene, const std::string& file_path)
	{
		// Log the save msg
		spdlog::info("Importing scene: " + scene.get_name() + "...");

		// Tries to load the file
		YAML::Node scene_yaml;

		try
		{
			scene_yaml = YAML::LoadFile(file_path);
		}
		catch (const std::exception&)
		{
			return;
		}

		// Check if the file is good
		if (!scene_yaml || !scene_yaml["Scene Name"] || !scene_yaml["Entities"])
			return;
		
		// Load scene name
		scenes_system::get_singleton().change_name(scene.get_name(), scene_yaml["Scene Name"].as<std::string>());

		for (auto ent : scene_yaml["Entities"])
		{
			entity new_entity = scene.create_entity();

			// Deserialize identity_component
			deserialize_identity_component(new_entity, ent);

			// Deserialize transform_component
			deserialize_transform_component(new_entity, ent);

			// Deserialize transform_component
			deserialize_sprite_component(new_entity, ent);
		}
	}
}