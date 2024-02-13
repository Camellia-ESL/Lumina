#pragma once

#include "glm/glm.hpp"
#include "yaml-cpp/yaml.h"

namespace lumina
{
	class types_serializer
	{
	public:

		static void serialize_yaml_vec3(const glm::vec3& vec, YAML::Emitter& yaml_stream_emitter);
		static void serialize_yaml_vec4(const glm::vec4& vec, YAML::Emitter& yaml_stream_emitter);

		static glm::vec3 deserialize_yaml_vec3(YAML::Node& vec_node);
		static glm::vec4 deserialize_yaml_vec4(YAML::Node& vec_node);

	};
}