#include "transform_component.h"

#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

	glm::mat4 transform_component::compute_models_difference(const glm::mat4& mat1, const glm::mat4& mat2)
	{
		// Decompose the matrices into translation, rotation, and scale components
		glm::vec3 translation1, translation2;
		glm::quat rotation1, rotation2;
		glm::vec3 scale1, scale2;
		glm::vec3 skew1, skew2; // Ignored
		glm::vec4 perspective1, perspective2; // Ignored

		glm::decompose(mat1, scale1, rotation1, translation1, skew1, perspective1);
		glm::decompose(mat2, scale2, rotation2, translation2, skew2, perspective2);

		// Compute the differences
		glm::vec3 translate_dif = translation2 - translation1;
		glm::quat rot_dif = glm::inverse(rotation1) * rotation2;
		glm::vec3 scale_dif = scale2 - scale1;

		// Return the constructed difference matrix
		return
			glm::translate(glm::mat4(1.0f), translate_dif) *
			glm::toMat4(rot_dif) *
			glm::scale(glm::mat4(1.0f), glm::vec3(1.0f) + scale_dif);
	}
}