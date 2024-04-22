#pragma once

#include "component.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace lumina
{
	struct transform_component : public component
	{
		transform_component() {}
		transform_component(const glm::mat4& transform_matrix) : model_matrix_{ transform_matrix } {}

		// Set the model of the transform directly
		transform_component& set_model(const glm::mat4& matrix) { model_matrix_ = matrix; return *this; }

		// Set the position of the transform
		transform_component& set_position(const glm::vec3& position);
		
		// Set the scale of the transform
		transform_component& set_scale(const glm::vec3& scale);

		// Translate the transform
		transform_component& translate(const glm::vec3& translation);

		// Rotate the transform by a given angle (in radians)
		transform_component& rotate(const glm::vec3& rotation_axis_multiplier, float angle);

		// Scale the transform
		transform_component& scale(const glm::vec3& scale);

		// Get the position of the transform
		const glm::vec3 get_position() const;

		// Get's the euler angles for each axis of the transform
		const glm::vec3 get_euler_angles() const;

		// Get's the scale of the transform
		const glm::vec3 get_scale() const;

		// Get the model matrix of the transform
		const glm::mat4& get_model_matrix() { return model_matrix_; }
		 
		// Compute the difference about 2 transforms model matricies and return the matrix holding the difference
		// note: the function involves several decomposition and calculations it may be slow
		static glm::mat4 compute_models_difference(const glm::mat4& mat1, const glm::mat4& mat2);

	private:

		glm::mat4 model_matrix_{ 1.0f };
	
	};
}
