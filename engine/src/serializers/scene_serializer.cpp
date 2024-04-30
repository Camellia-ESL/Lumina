#include "scene_serializer.h"

#include "scene_system/scenes_system.h"
#include "types_serializer.h"
#include "assets_system/asset_atlas.h"

#include "spdlog/spdlog.h"
#include "ImGui/imgui.h"
#include "ImGuizmo/ImGuizmo.h"

#include <fstream>

namespace lumina
{
	// Serialization

	template<>
	static void scene_serializer::serialize_component_yaml<identity_component>(identity_component& component, YAML::Emitter& yaml_stream_emitter, scene* scene)
	{
		yaml_stream_emitter << YAML::Key << "Identity Component";
		
		// Create's the component map
		yaml_stream_emitter << YAML::Value << YAML::BeginMap;

		yaml_stream_emitter << YAML::Key << "Entity Name";
		yaml_stream_emitter << YAML::Value << component.name;
		yaml_stream_emitter << YAML::Key << "Entity UUID";
		yaml_stream_emitter << YAML::Value << component.id;

		// End the component map
		yaml_stream_emitter << YAML::EndMap;
	}

	template<>
	static void scene_serializer::serialize_component_yaml<transform_component>(transform_component& component, YAML::Emitter& yaml_stream_emitter, scene* scene)
	{
		yaml_stream_emitter << YAML::Key << "Transform Component";

		// Create's the component map
		yaml_stream_emitter << YAML::Value << YAML::BeginMap;

		glm::vec3 position_ptr;
		glm::vec3 rotation_ptr;
		glm::vec3 scale_ptr;

		ImGuizmo::DecomposeMatrixToComponents(
			(const l_float32*)&component.get_model_matrix(),
			(l_float32*)&position_ptr,
			(l_float32*)&rotation_ptr,
			(l_float32*)&scale_ptr
			);

		yaml_stream_emitter << YAML::Key << "Position";
		yaml_stream_emitter << YAML::Value;
		types_serializer::serialize_yaml_vec3(position_ptr, yaml_stream_emitter);

		yaml_stream_emitter << YAML::Key << "Rotation";
		yaml_stream_emitter << YAML::Value;
		types_serializer::serialize_yaml_vec3(rotation_ptr, yaml_stream_emitter);

		yaml_stream_emitter << YAML::Key << "Scale";
		yaml_stream_emitter << YAML::Value;
		types_serializer::serialize_yaml_vec3(scale_ptr, yaml_stream_emitter);
		
		ImGuizmo::RecomposeMatrixFromComponents(
			(const l_float32*)&position_ptr,
			(const l_float32*)&rotation_ptr,
			(const l_float32*)&scale_ptr,
			(l_float32*)&component.get_model_matrix()
		);

		// End the component map
		yaml_stream_emitter << YAML::EndMap;
	}

	template<>
	static void scene_serializer::serialize_component_yaml<sprite_component>(sprite_component& component, YAML::Emitter& yaml_stream_emitter, scene* scene)
	{
		yaml_stream_emitter << YAML::Key << "Sprite Component";

		// Create's the component map
		yaml_stream_emitter << YAML::Value << YAML::BeginMap;

		yaml_stream_emitter << YAML::Key << "Shape";
		yaml_stream_emitter << YAML::Value << (uint32_t)component.shape;

		yaml_stream_emitter << YAML::Key << "TextureAssetId";
		yaml_stream_emitter << YAML::Value << component.get_texture_asset_id();

		yaml_stream_emitter << YAML::Key << "Color";
		yaml_stream_emitter << YAML::Value;
		types_serializer::serialize_yaml_vec4(component.color, yaml_stream_emitter);

		// End the component map
		yaml_stream_emitter << YAML::EndMap;
	}

	template<>
	static void scene_serializer::serialize_component_yaml<camera_component>(camera_component& component, YAML::Emitter& yaml_stream_emitter, scene* scene)
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

		// End the component map
		yaml_stream_emitter << YAML::EndMap;
	}

	template<>
	static void scene_serializer::serialize_component_yaml<entity_hierarchy_component>(entity_hierarchy_component& component, YAML::Emitter& yaml_stream_emitter, scene* scene)
	{
		yaml_stream_emitter << YAML::Key << "Hierarchy Component";

		// Create's the component map
		yaml_stream_emitter << YAML::Value << YAML::BeginMap;

		yaml_stream_emitter << YAML::Key << "Childs";
		yaml_stream_emitter << YAML::Value << YAML::BeginSeq;
		for (auto& child : component.get_childs())
		{
			yaml_stream_emitter << child.get_component<identity_component>().id;
		}
		yaml_stream_emitter << YAML::Value << YAML::EndSeq;

		yaml_stream_emitter << YAML::Key << "Parent";
		yaml_stream_emitter << YAML::Value << (component.get_parent().has_entity() ? component.get_parent().get_component<identity_component>().id : "not_parented");

		// End the
		yaml_stream_emitter << YAML::EndMap;
	}

	template<>
	static void scene_serializer::serialize_component_yaml<physics_collider_2d_component>(physics_collider_2d_component& component, YAML::Emitter& yaml_stream_emitter, scene* scene)
	{
		yaml_stream_emitter << YAML::Key << "PhysicsCollider2D Component";

		// Create's the component map
		yaml_stream_emitter << YAML::Value << YAML::BeginMap;

		yaml_stream_emitter << YAML::Key << "Body Type";
		yaml_stream_emitter << YAML::Value << (l_uint32)component.body_type;

		yaml_stream_emitter << YAML::Key << "Shape Type";
		yaml_stream_emitter << YAML::Value << (l_uint32)component.shape_type;

		yaml_stream_emitter << YAML::Key << "Is Rotation Fixed";
		yaml_stream_emitter << YAML::Value << component.is_rotation_fixed;

		yaml_stream_emitter << YAML::Key << "Density";
		yaml_stream_emitter << YAML::Value << component.density;

		yaml_stream_emitter << YAML::Key << "Friction";
		yaml_stream_emitter << YAML::Value << component.friction;

		yaml_stream_emitter << YAML::Key << "Restitution";
		yaml_stream_emitter << YAML::Value << component.restitution;

		yaml_stream_emitter << YAML::Key << "Restitution Threshold";
		yaml_stream_emitter << YAML::Value << component.restitution_threshold;

		yaml_stream_emitter << YAML::Key << "Fixture Size";
		yaml_stream_emitter << YAML::Value;
		types_serializer::serialize_yaml_vec2(component.get_fixture_size(), yaml_stream_emitter);

		// End the component map
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

			serialize_component_yaml(entity.get_component<identity_component>(), yaml_stream_emitter, scene);
			
			serialize_component_yaml(entity.get_component<entity_hierarchy_component>(), yaml_stream_emitter, scene);

			if(entity.has_component<transform_component>())
				serialize_component_yaml(entity.get_component<transform_component>(), yaml_stream_emitter, scene);

			if (entity.has_component<sprite_component>())
				serialize_component_yaml(entity.get_component<sprite_component>(), yaml_stream_emitter, scene);

			if (entity.has_component<camera_component>())
				serialize_component_yaml(entity.get_component<camera_component>(), yaml_stream_emitter, scene);

			if (entity.has_component<physics_collider_2d_component>())
				serialize_component_yaml(entity.get_component<physics_collider_2d_component>(), yaml_stream_emitter, scene);

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
	static void scene_serializer::deserialize_component_yaml<identity_component>(entity& entity, YAML::detail::iterator_value& yaml_entity, scene* scene)
	{
		auto yaml_identity_component = yaml_entity["Identity Component"];
		identity_component& ent_identity_component = entity.get_component<identity_component>();

		// Deserialize the component
		ent_identity_component.name = yaml_identity_component["Entity Name"].as<std::string>();
		ent_identity_component.id = yaml_identity_component["Entity UUID"].as<std::string>();
	}

	template<>
	static void scene_serializer::deserialize_component_yaml<transform_component>(entity& entity, YAML::detail::iterator_value& yaml_entity, scene* scene)
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
		glm::vec3 position = types_serializer::deserialize_yaml_vec3(position_node);
		glm::vec3 rotation = types_serializer::deserialize_yaml_vec3(rotation_node);
		glm::vec3 scale = types_serializer::deserialize_yaml_vec3(scale_node);

		glm::vec3 position_ptr;
		glm::vec3 rotation_ptr;
		glm::vec3 scale_ptr;

		ImGuizmo::DecomposeMatrixToComponents(
			(const l_float32*)&ent_component.get_model_matrix(),
			(l_float32*)&position_ptr,
			(l_float32*)&rotation_ptr,
			(l_float32*)&scale_ptr
		);

		position_ptr = position;
		rotation_ptr = rotation;
		scale_ptr = scale;

		ImGuizmo::RecomposeMatrixFromComponents(
			(const l_float32*)&position_ptr,
			(const l_float32*)&rotation_ptr,
			(const l_float32*)&scale_ptr,
			(l_float32*)&ent_component.get_model_matrix()
		);
	}

	template<>
	static void scene_serializer::deserialize_component_yaml<sprite_component>(entity& entity, YAML::detail::iterator_value& yaml_entity, scene* scene)
	{
		auto yaml_component = yaml_entity["Sprite Component"];

		// Check if the component doesn't exist
		if (!yaml_component)
			return;

		sprite_component& ent_component = entity.add_component<sprite_component>();

		// Deserialize the component
		ent_component.shape = (lumina::sprite_component::shapes)yaml_component["Shape"].as<uint32_t>();

		// When deserializing the texture, it tries to search inside the asset atlas an asset that matches TextureAssetId of the sprite 
		// if found loads it.
		const std::string texture_asset_id = yaml_component["TextureAssetId"].as<std::string>();

		if (asset_atlas::get_singleton().get_registry().has_asset(texture_asset_id))
			ent_component.bind_texture(asset_atlas::get_singleton().get_registry().get_asset(texture_asset_id));
		
		auto color_node = yaml_component["Color"];
		ent_component.color = types_serializer::deserialize_yaml_vec4(color_node);
	}

	template<>
	static void scene_serializer::deserialize_component_yaml<camera_component>(entity& entity, YAML::detail::iterator_value& yaml_entity, scene* scene)
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

		ent_component.fov_ = yaml_component["Fov"].as<l_float32>();
		ent_component.far_view_ = yaml_component["Far View"].as<l_float32>();
		ent_component.near_view_ = yaml_component["Near View"].as<l_float32>();
		ent_component.yaw_ = yaml_component["Yaw"].as<l_float32>();
		ent_component.pitch_ = yaml_component["Pitch"].as<l_float32>();
		ent_component.position_ = types_serializer::deserialize_yaml_vec3(position_node);
		ent_component.front_ = types_serializer::deserialize_yaml_vec3(front_node);
		ent_component.up_ = types_serializer::deserialize_yaml_vec3(up_node);
		ent_component.right_ = types_serializer::deserialize_yaml_vec3(right_node);
		ent_component.world_up_ = types_serializer::deserialize_yaml_vec3(world_up_node);
	}

	template<>
	static void scene_serializer::deserialize_component_yaml<entity_hierarchy_component>(entity& null_ent, YAML::detail::iterator_value& yaml_entity, scene* scene)
	{
		// Note that by default here entity is always null
		auto yaml_identity_component = yaml_entity["Identity Component"];
		auto yaml_hierarchy_component = yaml_entity["Hierarchy Component"];
		entity entity = scene->get_entity_by_id(yaml_identity_component["Entity UUID"].as<std::string>());
		entity_hierarchy_component& ent_hierarchy_component = entity.get_component<entity_hierarchy_component>();
		
		// Deserialize the component
		const std::string parent = yaml_hierarchy_component["Parent"].as<std::string>();
		if(parent != "not_parented")
			ent_hierarchy_component.set_parent(scene->get_entity_by_id(parent));

		for (auto child : yaml_hierarchy_component["Childs"])
			ent_hierarchy_component.attach_child(
				scene->get_entity_by_id(child.as<std::string>())
			);
	}

	template<>
	static void scene_serializer::deserialize_component_yaml<physics_collider_2d_component>(entity& entity, YAML::detail::iterator_value& yaml_entity, scene* scene)
	{
		auto yaml_component = yaml_entity["PhysicsCollider2D Component"];

		// Check if the component doesn't exist
		if (!yaml_component)
			return;

		physics_collider_2d_component& ent_component = entity.add_component<physics_collider_2d_component>();

		auto fixture_size_node = yaml_component["Fixture Size"];

		// Deserialize the component
		ent_component.body_type = (physics_collider_2d_component::body_type_e)yaml_component["Body Type"].as<l_uint32>();
		ent_component.shape_type = (physics_collider_2d_component::shape_type_e)yaml_component["Shape Type"].as<l_uint32>();
		ent_component.is_rotation_fixed = yaml_component["Is Rotation Fixed"].as<bool>();
		ent_component.density = yaml_component["Density"].as<l_float32>();
		ent_component.friction = yaml_component["Friction"].as<l_float32>();
		ent_component.restitution = yaml_component["Restitution"].as<l_float32>();
		ent_component.restitution_threshold = yaml_component["Restitution Threshold"].as<l_float32>();
		ent_component.set_fixture_size(types_serializer::deserialize_yaml_vec2(fixture_size_node));
	}

	bool scene_serializer::deserialize_yaml(scene* scene, const std::string& file_path)
	{
		// Check if the scene is null
		if (scene == nullptr)
			return false;

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

		// Deserializes all the entities with their components
		for (auto ent : scene_yaml["Entities"])
		{
			entity new_entity = scene->create_entity();

			deserialize_component_yaml<identity_component>(new_entity, ent, scene);

			deserialize_component_yaml<transform_component>(new_entity, ent, scene);

			deserialize_component_yaml<sprite_component>(new_entity, ent, scene);

			deserialize_component_yaml<camera_component>(new_entity, ent, scene);

			deserialize_component_yaml<physics_collider_2d_component>(new_entity, ent, scene);
		}

		// Executes a special deserialization for the entity hierarchies
		for (auto ent : scene_yaml["Entities"])
		{
			entity null_entity{};

			deserialize_component_yaml<entity_hierarchy_component>(null_entity, ent, scene);
		}

		// Calls the scene on load
		scene->on_load();

		return true;
	}
}