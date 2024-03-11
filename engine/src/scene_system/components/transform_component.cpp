#include "transform_component.h"

namespace lumina
{
	transform_component& transform_component::set_position(const glm::vec3& position)
	{
		model_matrix_ = glm::translate(model_matrix_, position);
		return *this;
	}

	transform_component& transform_component::rotate(const glm::vec3& rotation_axis_multiplier, float angle)
	{
		model_matrix_ = glm::rotate(model_matrix_, angle, rotation_axis_multiplier);
		return *this;
	}

	transform_component& transform_component::set_scale(const glm::vec3& scale)
	{
		model_matrix_ = glm::scale(model_matrix_, scale);
		return *this;
	}
}