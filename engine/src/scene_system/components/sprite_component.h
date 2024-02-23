#pragma once

#include "component.h"
#include "graphics/texture.h"

#include "glm/glm.hpp"

namespace lumina
{
	struct sprite_component : public component
	{
		enum class shapes
		{
			QUAD
		}shape{ shapes::QUAD };

		// Note that this will not be used if there already is a texture
		glm::vec4 color{ 1.0f, 1.0f, 0.0f, 1.0f };
		texture* texture = nullptr;
	};
}