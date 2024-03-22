#pragma once

#include "scene_system/scene.h"

#include "yaml-cpp/yaml.h"

namespace lumina
{
	class scene_serializer
	{
	public:
		
		// Serialize a scene in a yaml file
		static void serialize_yaml(scene* scene, const std::string& file_path);
		
		// Deserialize a scene from a yaml file
		static bool deserialize_yaml(scene* scene, const std::string& file_path);

	private:

		template<typename component_type>
		static void serialize_component_yaml(component_type& component, YAML::Emitter& yaml_stream_emitter, scene* scene);

		template<typename component_type>
		static void deserialize_component_yaml(entity& entity, YAML::detail::iterator_value& yaml_entity, scene* scene);

	};
}