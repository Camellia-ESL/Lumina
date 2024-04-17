#include "camera_component.h"

#include "application/app.h"

namespace lumina
{
    camera_component::camera_component()
    {
        calculate_all();
    }

    void camera_component::set_position(glm::vec3 position)
    {
        position_ = position;
    }

    void camera_component::set_fov(float fov)
    {
        fov_ = fov;
    }

    void camera_component::move_position(move_directions_e direction, float velocity)
    {
        if (direction == move_directions_e::FORWARD)
            position_ += front_ * velocity;
        
        if (direction == move_directions_e::BACKWARD)
            position_ -= front_ * velocity;
        
        if (direction == move_directions_e::LEFT)
            position_ -= glm::normalize(glm::cross(front_, up_)) * velocity;
        
        if (direction == move_directions_e::RIGHT)
            position_ += glm::normalize(glm::cross(front_, up_)) * velocity;
    }

    void camera_component::set_rotation(float yaw, float pitch)
    {
        this->yaw_ = yaw;
       
        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (pitch >= 89.0f)
        {
            this->pitch_ = 89.0f;
            return;
        }
        if (pitch <= -89.0f)
        {
            this->pitch_ = -89.0f;
            return;
        }

        this->pitch_ = pitch;
    }

    void camera_component::rotate(float yaw, float pitch)
    {
        this->yaw_ += yaw;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if ((this->pitch_ + pitch) >= 89.0f)
        {
            this->pitch_ = 89.0f;
            return;
        }
        if ((this->pitch_ + pitch) <= -89.0f)
        {
            this->pitch_ = -89.0f;
            return;
        }

        this->pitch_ += pitch;
    }

    void camera_component::calculate_vectors()
    {
        // Calculate the new Front vector
        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
        direction.y = sin(glm::radians(pitch_));
        direction.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));

        front_ = glm::normalize(direction);

        // Calculate the Right and Up vector
        // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        right_ = glm::normalize(glm::cross(front_, world_up_));
        up_ = glm::normalize(glm::cross(right_, front_));
    }

    void camera_component::calculate_view_matrix()
    {
        view_ = glm::lookAt(position_, position_ + front_, up_);
    }

    void camera_component::calculate_projection_matrix()
    {
        glm::vec2 surface_dimensions = application_player::get_singleton().get_surface().get_dimensions();
        projection_ = glm::perspective(fov_, surface_dimensions.x / surface_dimensions.y, near_view_, far_view_);
    }

    void camera_component::calculate_all()
    {
        calculate_vectors();
        calculate_view_matrix();
        calculate_projection_matrix();
    }
}