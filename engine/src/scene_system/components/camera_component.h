#pragma once

#include "component.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace lumina
{
	// A camera object used to perform operations on the view matrix easily
	// Note: this cannot be globally constructed it needs functions only executable after the surface got initialized.
	struct camera_component : public component
	{
	public:

		enum class move_directions_e
		{
			FORWARD,
			LEFT,
			RIGHT,
			BACKWARD
		};

		camera_component();

		// Set the camera position
		void set_position(glm::vec3 position);

		// Set the camera view angle's rotation
		void set_rotation(float yaw, float pitch);
		
		// Set the camera field of view
		void set_fov(float fov);

		// Move the camera position 
		void move_position(move_directions_e direction, float velocity);

		// Rotate the camera view angle's by a certain offset 
		void rotate(float yaw, float pitch);

		// Get's the view matrix of the camera
		const glm::mat4& get_view_matrix() { calculate_vectors(); calculate_view_matrix(); return view_; }

		// Get's the projection used by this camera (should be multiplied with the view matrix)
		const glm::mat4& get_projection_matrix() const { return projection_; }

	private:

		// The camera position in the world
		glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 1.0f);

		// The camera FOV
		float fov_ = 90.0f;

		// The closest distance the camera can see
		float near_view_ = 0.1f;

		// The farest distance the camera can see
		float far_view_ = 100.0f;

		// The up target vector 
		glm::vec3 up_ = glm::vec3(0.0f, 1.0f, 0.0f);

		// The right target vector 
		glm::vec3 right_ = glm::vec3(0.0f, 0.0f, 0.0f);

		// The front target vector 
		glm::vec3 front_ = glm::vec3(0.0f, 0.0f, -1.0f);

		// The world up vector used to recalculate with precision the view matrix 
		glm::vec3 world_up_ = glm::vec3(0.0f, 1.0f, 0.0f);

		// The yaw angle of the camera 
		float yaw_ = -90.0f;

		// The pitch angle of the camera 
		float pitch_ = 0.0f;

		glm::mat4 projection_{ glm::mat4(1.0f) };
		glm::mat4 view_{ glm::mat4(1.0f) };

		void calculate_vectors();
		void calculate_view_matrix();
		void calculate_projection_matrix();
		void calculate_all();

	private:

		friend class scene_serializer;

	};
}