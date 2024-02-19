#pragma once

#include "component.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace lumina
{
	struct transform_component : public component
	{
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale{ 1.0f, 1.0f, 0.0f };

		const glm::mat4& get_model_matrix();
	
	private:

		glm::mat4 model_matrix_ = glm::mat4(1.0f);
		
	};
}
