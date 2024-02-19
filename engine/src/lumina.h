#pragma once

/*
  This header contains the includes of every accessible file of Lumina Engine,
  and some compilation settings.

  Lumina Engine made by https://github.com/VanityEmptiness/
*/

#include "application/app.h"
#include "application/surface.h"
#include "graphics/d3d11_api/d3d11_api.h"
#include "graphics/renderer_2d.h"
#include "scene_system/scenes_system.h"
#include "scene_system/components/components.h"
#include "core/lumina_memory.h"
#include "core/lumina_strings.h"
#include "core/lumina_singleton.h"
#include "serializers/scene_serializer.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Lumina is the namespace containing the lumina engine
namespace lumina
{
	constexpr const char* VERSION = "0.0.67";
}