#include "types_serializer.h"

namespace lumina
{
	void types_serializer::serialize_yaml_vec2(const glm::vec2& vec, YAML::Emitter& yaml_stream_emitter)
	{
		yaml_stream_emitter << YAML::BeginSeq;
		yaml_stream_emitter << vec.x << vec.y;
		yaml_stream_emitter << YAML::EndSeq;
	}

	void types_serializer::serialize_yaml_vec3(const glm::vec3& vec, YAML::Emitter& yaml_stream_emitter)
	{
		yaml_stream_emitter << YAML::BeginSeq;
		yaml_stream_emitter << vec.x << vec.y << vec.z;
		yaml_stream_emitter << YAML::EndSeq;
	}

	void types_serializer::serialize_yaml_vec4(const glm::vec4& vec, YAML::Emitter& yaml_stream_emitter)
	{
		yaml_stream_emitter << YAML::BeginSeq;
		yaml_stream_emitter << vec.x << vec.y << vec.z << vec.w;
		yaml_stream_emitter << YAML::EndSeq;
	}

	glm::vec2 types_serializer::deserialize_yaml_vec2(YAML::Node& vec_node)
	{
		// Check if the node isn't a vec3
		if (!vec_node.IsSequence() || vec_node.size() != 2) {
			return glm::vec2();
		}

		return glm::vec2{
			vec_node[0].as<float>(),
			vec_node[1].as<float>()
		};
	}

	glm::vec3 types_serializer::deserialize_yaml_vec3(YAML::Node& vec_node)
	{
		// Check if the node isn't a vec3
		if (!vec_node.IsSequence() || vec_node.size() != 3) {
			return glm::vec3();
		}

		return glm::vec3{
			vec_node[0].as<float>(),
			vec_node[1].as<float>(),
			vec_node[2].as<float>()
		};
	}

	glm::vec4 types_serializer::deserialize_yaml_vec4(YAML::Node& vec_node)
	{
		// Check if the node isn't a vec3
		if (!vec_node.IsSequence() || vec_node.size() != 4) {
			return glm::vec4();
		}

		return glm::vec4{
			vec_node[0].as<float>(),
			vec_node[1].as<float>(),
			vec_node[2].as<float>(),
			vec_node[3].as<float>()
		};
	}
}