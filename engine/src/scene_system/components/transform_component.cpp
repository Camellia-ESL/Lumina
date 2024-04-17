#include "transform_component.h"

#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace lumina
{
	transform_component& transform_component::set_position(const glm::vec3& position)
	{
		model_matrix_[3] = glm::vec4(position, 1.0f);
		return *this;
	}

	transform_component& transform_component::set_scale(const glm::vec3& scale)
	{
		model_matrix_[0][0] = scale.x; 
		model_matrix_[1][1] = scale.y; 
		model_matrix_[2][2] = scale.z;
		return *this;
	}

	transform_component& transform_component::translate(const glm::vec3& translation)
	{
		model_matrix_ = glm::translate(model_matrix_, translation);
		return *this;
	}

	transform_component& transform_component::rotate(const glm::vec3& rotation_axis_multiplier, float angle)
	{
		model_matrix_ = glm::rotate(model_matrix_, angle, rotation_axis_multiplier);
		return *this;
	}

	transform_component& transform_component::scale(const glm::vec3& scale)
	{
		model_matrix_ = glm::scale(model_matrix_, scale);
		return *this;
	}

	const glm::vec3 transform_component::get_position() const
	{
		return glm::vec3(model_matrix_[3]);
	}

	const glm::vec3 transform_component::get_euler_angles() const
	{
		return glm::degrees(
			glm::eulerAngles(
				glm::toQuat(glm::mat3(model_matrix_))
			)
		);
	}

	const glm::vec3 transform_component::get_scale() const
	{
		return glm::vec3(
			glm::length(glm::vec3(model_matrix_[0])),
			glm::length(glm::vec3(model_matrix_[1])),
			glm::length(glm::vec3(model_matrix_[2]))
		); 
	}
}