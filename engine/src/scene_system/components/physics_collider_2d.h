#pragma once

#include "component.h"
#include "core/lumina_types.h"

#include "box2d/box2d.h"
#include "glm/glm.hpp"

namespace lumina
{
	struct physics_collider_2d_component : public component
	{
	public:

		// The type of body with which will be consider in the physics world the collider
		enum class body_type_e
		{
			// The body will stay static no matter what
			STATIC = 0,
			// A kinematic interactable body
			KINEMATIC,
			// A dynamic body type
			DYNAMIC
		};

		// The type of the shape of the fixture
		enum class shape_type_e
		{
			// The shape of a box/quad
			QUAD = 0
		};

	public:

		// Represents the default unit conversion scale factor for scaling transforms positions and dimensions (Look at box2D wiki for more info)
		static constexpr const l_float32 UNIT_SCALE_FACTOR_ = 1.0f;

		// The type of the body (default to DYNAMIC)
		body_type_e body_type = body_type_e::DYNAMIC;

		// The shape of the fixture (default to QUAD)
		shape_type_e shape_type = shape_type_e::QUAD;

		// Even if the body rotates or not
		bool is_rotation_fixed = false;

		// The density of the fixture
		l_float32 density = 1.0f;
		
		// The friction of the fixture
		l_float32 friction = 0.5f;

		// The restitution of the fixture
		l_float32 restitution = 0.0f;

		// The restitution_threshold of the fixture
		l_float32 restitution_threshold = 0.5f;

		// Get's the native underlying structure of the 2d physics body abstraction
		b2Body* get_native_body() { return body_; }

		// Set's the native underlying structure of the 2d physics body abstraction
		void set_native_body(b2Body* body_ptr) { body_ = body_ptr; }
		
		// Get's the native underlying structure of the 2d physics body fixture abstraction
		b2Fixture* get_native_fixture() { return fixture_; }

		// Returns the size computed ready for transform use (normally when being holded by the physics collider the size is reduced)
		const glm::vec2 get_fixture_size() const;
		
		// Returns the raw size contained
		const glm::vec2& get_fixture_raw_size() const { return fixture_size_; }

		// Set's the native underlying structure of the 2d physics body fixture abstraction
		void set_native_fixture(b2Fixture* fixture_ptr) { fixture_ = fixture_ptr; }

		// Set's the size of the fixture (it get's automatically computed by the function)
		void set_fixture_size(const glm::vec2& size);

		// Set's the raw size of the fixture (note: it get's not computed for that purpose use set_fixture_size)
		void set_fixture_raw_size(const glm::vec2& size) { fixture_size_ = size; }

		// Converts the engine unit to a box2d unit
		static l_float32 engine_unit_to_box2_unit(const l_float32 transform_unit) { return transform_unit / UNIT_SCALE_FACTOR_; }
		
		// Converts the box2d unit to a engine unit 
		static l_float32 box2_unit_to_engine_unit(const l_float32 box2d_unit) { return box2d_unit * UNIT_SCALE_FACTOR_; }

	private:

		// The fixture size (it is privately stored because it needs to be computed in order to be used)
		glm::vec2 fixture_size_ = { 1.0f, 1.0f };

		// The fixture pointer to the fixture class of the body (the shape) (instanced at runtime)
		b2Fixture* fixture_ = nullptr;

		// The pointer to the body instance of box2D body class (instanced at runtime)
		b2Body* body_ = nullptr;
	};
}