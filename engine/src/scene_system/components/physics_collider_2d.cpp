#include "physics_collider_2d.h"

namespace lumina
{
	const glm::vec2 physics_collider_2d_component::get_fixture_size() const
	{ 
		return { 
			box2_unit_to_engine_unit(fixture_size_.x) * 2.5f,
			box2_unit_to_engine_unit(fixture_size_.y) * 2.5f
		}; 
	}

	void physics_collider_2d_component::set_fixture_size(const glm::vec2& size)
	{
		fixture_size_ = { 
			engine_unit_to_box2_unit(size.x) / 2.5f,
			engine_unit_to_box2_unit(size.y) / 2.5f,
		};
	}
}