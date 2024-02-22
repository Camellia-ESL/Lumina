#include "scene_serializer.h"

#include "scene_system/scenes_system.h"
#include "types_serializer.h"

#include "spdlog/spdlog.h"

#include <fstream>

namespace lumina
{
	// Serialization

	template<>
	static void scene_serializer::serialize_component<identity_component>(identity_component& component, YAML::Emitter& yaml_stream_emitter, scene* scene)
	{
		yaml_stream_emitter << YAML::Key << "Identity Component";
		
		// Create's the component map
		yaml_stream_emitter << YAML::Value << YAML::BeginMap;

		yaml_stream_emitter << YAML::Key << "Entity Name";
		yaml_stream_emitter << YAML::Value << component.name;
		yaml_stream_emitter << YAML::Key << "Entity UUID";
		yaml_stream_emitter << YAML::Value << component.id;

		// End the
		yaml_stream_emitter << YAML::EndMap;
	}

	template<>
	static void scene_serializer::serialize_component<transform_component>(transform_component& component, YAML::Emitter& yaml_stream_emitter, scene* scene)
	{
		yaml_stream_emitter << YAML::Key << "Transform Component";

		// Create's the component map
		yaml_stream_emitter << YAML::Value << YAML::BeginMap;

		yaml_stream_emitter << YAML::Key << "Position";
		yaml_stream_emitter << YAML::Value;
		types_serializer::serialize_yaml_vec3(component.position, yaml_stream_emitter);

		yaml_stream_emitter << YAML::Key << "Rotation";
		yaml_stream_emitter << YAML::Value;
		types_serializer::serialize_yaml_vec3(component.rotation, yaml_stream_emitter);

		yaml_stream_emitter << YAML::Key << "Scale";
		yaml_stream_emitter << YAML::Value;
		types_serializer::serialize_yaml_vec3(component.scale, yaml_stream_emitter);
		
		// End the
		yaml_stream_emitter << YAML::EndMap;
	}

	template<>
	static void scene_serializer::serialize_component<sprite_component>(sprite_component& component, YAML::Emitter& yaml_stream_emitter, scene* scene)
	{
		yaml_stream_emitter << YAML::Key << "Sprite Component";

		// Create's the component map
		yaml_stream_emitter << YAML::Value << YAML::BeginMap;

		yaml_stream_emitter << YAML::Key << "Shape";
		yaml_stream_emitter << YAML::Value << (uint32_t)component.shape;

		yaml_stream_emitter << YAML::Key << "Color";
		yaml_stream_emitter << YAML::Value;
		types_serializer::serialize_yaml_vec4(component.color, yaml_stream_emitter);

		// End the
		yaml_stream_emitter << YAML::EndMap;
	}

	template<>
	static void scene_serializer::serialize_component<camera_component>(camera_component& component, YAML::Emitter& yaml_stream_emitter, scene* scene)
	{
		yaml_stream_emitter << YAML::Key << "Camera Component";

		// Create's the component map
		yaml_stream_emitter << YAML::Value << YAML::BeginMap;

		yaml_stream_emitter << YAML::Key << "Is Active";
		yaml_stream_emitter << YAML::Value << scene->is_active_camera(&component);

		yaml_stream_emitter << YAML::Key << "Fov";
		yaml_stream_emitter << YAML::Value << component.fov_;

		yaml_stream_emitter << YAML::Key << "Far View";
		yaml_stream_emitter << YAML::Value << component.far_view_;

		yaml_stream_emitter << YAML::Key << "Near View";
		yaml_stream_emitter << YAML::Value << component.near_view_;

		yaml_stream_emitter << YAML::Key << "Yaw";
		yaml_stream_emitter << YAML::Value << component.yaw_;

		yaml_stream_emitter << YAML::Key << "Pitch";
		yaml_stream_emitter << YAML::Value << component.pitch_;

		yaml_stream_emitter << YAML::Key << "Position";
		yaml_stream_emitter << YAML::Value;
		types_serializer::serialize_yaml_vec3(component.position_, yaml_stream_emitter);

		yaml_stream_emitter << YAML::Key << "Front";
		yaml_stream_emitter << YAML::Value;
		types_serializer::serialize_yaml_vec3(component.front_, yaml_stream_emitter);

		yaml_stream_emitter << YAML::Key << "Up";
		yaml_stream_emitter << YAML::Value;
		types_serializer::serialize_yaml_vec3(component.up_, yaml_stream_emitter);

		yaml_stream_emitter << YAML::Key << "Right";
		yaml_stream_emitter << YAML::Value;
		types_serializer::serialize_yaml_vec3(component.right_, yaml_stream_emitter);

		yaml_stream_emitter << YAML::Key << "World Up";
		yaml_stream_emitter << YAML::Value;
		types_serializer::serialize_yaml_vec3(component.world_up_, yaml_stream_emitter);

		// End the
		yaml_stream_emitter << YAML::EndMap;
	}

	void scene_serializer::serialize_yaml(scene* scene, const std::string& file_path)
	{
		// Check if the scene is null
		if (scene == nullptr)
			return;
		
		// Log the save msg
		spdlog::info("Saving scene: " + scene->get_name() + "...");

		// Start's Serializing the scene
		YAML::Emitter yaml_stream_emitter;
		yaml_stream_emitter << YAML::BeginMap;
		yaml_stream_emitter << YAML::Key << "Scene Name";
		yaml_stream_emitter << YAML::Value << scene->get_name();

		yaml_stream_emitter << YAML::Key << "Is Active Scene";
		yaml_stream_emitter << YAML::Value << scenes_system::get_singleton().is_active_scene(scene);
		
		// Serialize entities with their components
		yaml_stream_emitter << YAML::Key << "Entities";
		yaml_stream_emitter << YAML::Value << YAML::BeginSeq;

		auto entities_view = scene->get_entity_registry().view<identity_component>();

		for (entt::entity ent : entities_view)
		{
			entity entity{ &scene->get_entity_registry(), ent };

			// Create's the entity map
			yaml_stream_emitter << YAML::BeginMap;

			serialize_component(entity.get_component<identity_component>(), yaml_stream_emitter, scene);
			
			if(entity.has_component<transform_component>())
				serialize_component(entity.get_component<transform_component>(), yaml_stream_emitter, scene);

			if (entity.has_component<sprite_component>())
				serialize_component(entity.get_component<sprite_component>(), yaml_stream_emitter, scene);

			if (entity.has_component<camera_component>())
				serialize_component(entity.get_component<camera_component>(), yaml_stream_emitter, scene);

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

	template<>
	static void scene_serializer::deserialize_component<identity_component>(entity& entity, YAML::detail::iterator_value& yaml_entity, scene* scene)
	{
		auto yaml_identity_component = yaml_entity["Identity Component"];
		identity_component& ent_identity_component = entity.get_component<identity_component>();

		// Deserialize the component
		ent_identity_component.name = yaml_identity_component["Entity Name"].as<std::string>();
		ent_identity_component.id = yaml_identity_component["Entity UUID"].as<std::string>();
	}

	template<>
	static void scene_serializer::deserialize_component<transform_component>(entity& entity, YAML::detail::iterator_value& yaml_entity, scene* scene)
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

	template<>
	static void scene_serializer::deserialize_component<sprite_component>(entity& entity, YAML::detail::iterator_value& yaml_entity, scene* scene)
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

	template<>
	static void scene_serializer::deserialize_component<camera_component>(entity& entity, YAML::detail::iterator_value& yaml_entity, scene* scene)
	{
		auto yaml_component = yaml_entity["Camera Component"];

		// Check if the component doesn't exist
		if (!yaml_component)
			return;

		camera_component& ent_component = entity.add_component<camera_component>();

		auto position_node = yaml_component["Position"];
		auto front_node = yaml_component["Front"];
		auto up_node = yaml_component["Up"];
		auto right_node = yaml_component["Right"];
		auto world_up_node = yaml_component["World Up"];

		// Deserialize the component
		if (yaml_component["Is Active"].as<bool>())
			scene->set_camera(&ent_component);

		ent_component.fov_ = yaml_component["Fov"].as<float>();
		ent_component.far_view_ = yaml_component["Far View"].as<float>();
		ent_component.near_view_ = yaml_component["Near View"].as<float>();
		ent_component.yaw_ = yaml_component["Yaw"].as<float>();
		ent_component.pitch_ = yaml_component["Pitch"].as<float>();
		ent_component.position_ = types_serializer::deserialize_yaml_vec3(position_node);
		ent_component.front_ = types_serializer::deserialize_yaml_vec3(front_node);
		ent_component.up_ = types_serializer::deserialize_yaml_vec3(up_node);
		ent_component.right_ = types_serializer::deserialize_yaml_vec3(right_node);
		ent_component.world_up_ = types_serializer::deserialize_yaml_vec3(world_up_node);
	}

	bool scene_serializer::deserialize_yaml(scene* scene, const std::string& file_path)
	{
		// Check if the scene is null
		if (scene == nullptr)
			return false;

		// Log the save msg
		spdlog::info("Importing scene: " + scene->get_name() + "...");

		// Tries to load the file
		YAML::Node scene_yaml;

		try
		{
			scene_yaml = YAML::LoadFile(file_path);
		}
		catch (const std::exception&)
		{
			return false;
		}

		// Check if the file is good
		if (!scene_yaml || !scene_yaml["Scene Name"] || !scene_yaml["Entities"])
			return false;
		
		// Load scene name
		scenes_system::get_singleton().change_name(scene->get_name(), scene_yaml["Scene Name"].as<std::string>()); 
		if (scene_yaml["Is Active Scene"] && scene_yaml["Is Active Scene"].as<bool>())
			scenes_system::get_singleton().activate_scene(scene->get_name());

		for (auto ent : scene_yaml["Entities"])
		{
			entity new_entity = scene->create_entity();

			deserialize_component<identity_component>(new_entity, ent, scene);

			deserialize_component<transform_component>(new_entity, ent, scene);

			deserialize_component<sprite_component>(new_entity, ent, scene);

			deserialize_component<camera_component>(new_entity, ent, scene);
		}

		return true;
	}
}