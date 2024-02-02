#pragma once

#include "component.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace lumina
{
	struct camera_component : public component
	{
		const glm::mat4& get_view_matrix() const { return view_; }
		const glm::mat4& get_projection_matrix() const { return projection_; }

	private:

		glm::mat4 projection_{ glm::mat4(1.0f) };
		glm::mat4 view_{ glm::mat4(1.0f) };

	};
}