#pragma once

#include "component.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace lumina
{
	struct transform_component : public component
	{

		const glm::mat4& get_model_matrix() { return model_matrix_; }
		 
	private:

		glm::mat4 model_matrix_{ 1.0f };
	
	};
}
