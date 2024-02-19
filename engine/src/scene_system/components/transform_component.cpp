#include "transform_component.h"

namespace lumina
{
	const glm::mat4& transform_component::get_model_matrix()
	{
		glm::mat4 rotation_matrix = glm::rotate(glm::mat4(1.0f), rotation.x, { 1.0f, 0.0f, 0.0f });
		rotation_matrix = glm::rotate(rotation_matrix, rotation.y, { 0.0f, 1.0f, 0.0f });
		rotation_matrix = glm::rotate(rotation_matrix, rotation.z, { 0.0f, 0.0f, 1.0f });

		model_matrix_ =
			glm::translate(glm::mat4(1.0), position) *
			rotation_matrix *
			glm::scale(glm::mat4(1.0), scale);

		return model_matrix_;
	}
}