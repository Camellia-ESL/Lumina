#pragma once

#include "scene_system/scene.h"

namespace lumina
{
	class scene_serializer
	{
	public:
		
		// Serialize a scene in a yaml file
		static void serialize_yaml(scene& scene, const std::string& file_path);
		
		// Deserialize a scene from a yaml file
		static void deserialize_yaml(scene& scene, const std::string& file_path);

	};
}