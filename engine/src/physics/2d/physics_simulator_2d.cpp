#include "physics_simulator_2d.h"

#include "scene_system/scene.h"
#include "scene_system/components/components.h"
#include "application/app.h"

#include "spdlog/spdlog.h"


#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace lumina
{
	void physics_simulator_2d::play()
	{
		is_playing_ = true;
	}

	void physics_simulator_2d::pause()
	{
		is_playing_ = false;
	}

	void physics_simulator_2d::update(scene* scene_ptr)
	{
		// If the simulation isn't created yet it returns
		if (!is_created())
			return;

		// If the simulation isn't playing return 
		if (!is_playing_)
			return;

		// Updates the world through various iterations
		constexpr const l_int32 velocity_iterations = 6;
		constexpr const l_int32 position_iterations = 2;
		physics_world_->Step(
			application_player::get_singleton().get_delta_time(), 
			velocity_iterations,
			position_iterations
		);
		
		// Fetches the updates and applies them for the rendering
		auto physics_collider_2d_view = 
			scene_ptr->get_entity_registry().view<transform_component, physics_collider_2d_component, entity_hierarchy_component>();
		
		for (auto entity : physics_collider_2d_view)
		{
			auto [transform, physics_collider_2d, entity_hierarchy] =
				physics_collider_2d_view.get<transform_component, physics_collider_2d_component, entity_hierarchy_component>(entity);
			auto& obj_pos_in_physics_world = 
				physics_collider_2d.get_native_body()->GetPosition();
			auto transform_rotation = transform.get_euler_angles();
			transform_component transform_pre_physics = transform;

			transform.set_position({
				physics_collider_2d_component::box2_unit_to_engine_unit(obj_pos_in_physics_world.x),
				physics_collider_2d_component::box2_unit_to_engine_unit(obj_pos_in_physics_world.y),
				transform.get_position().z
				});
			
			transform.set_rotation({
				glm::radians(transform_rotation.x),
				glm::radians(transform_rotation.y),
				physics_collider_2d.get_native_body()->GetTransform().q.GetAngle()
				});

			entity_hierarchy.dispatch_func_to_childs(
				[&](lumina::entity& ent_iterated) -> void
				{
					if (!ent_iterated.has_component<lumina::transform_component>())
						return;
				
					lumina::transform_component::adjust_transforms_diffs_2d(
						transform_pre_physics, 
						transform, 
						ent_iterated.get_component<lumina::transform_component>()
					);
				}
			);
		}
	}

	void physics_simulator_2d::init_simulation(scene* scene_ptr)
	{
		// Create's the world
		physics_world_ = new b2World({ 0.0f, GRAVITY });

		auto physics_collider_2d_view = scene_ptr->get_entity_registry().view<transform_component, physics_collider_2d_component>();

		for (auto entity : physics_collider_2d_view)
		{
			auto [transform, physics_collider_2d] = physics_collider_2d_view.get<transform_component, physics_collider_2d_component>(entity);

			// Creates a body definition
			b2BodyDef rigidbody_box2d_body_definition;
			
			// Body type
			rigidbody_box2d_body_definition.type = (b2BodyType)physics_collider_2d.body_type;
			
			// Body position
			const glm::vec3 position = transform.get_position();
			rigidbody_box2d_body_definition.position.Set(
				physics_collider_2d_component::engine_unit_to_box2_unit(position.x),
				physics_collider_2d_component::engine_unit_to_box2_unit(position.y)
			);

			// Body rotation
			rigidbody_box2d_body_definition.angle = glm::radians(transform.get_euler_angles().z);

			// Fixed rotation
			rigidbody_box2d_body_definition.fixedRotation = physics_collider_2d.is_rotation_fixed;

			// Uses the body definition to create a Box2D physic body
			b2Body* rigidbody_box2d_body = physics_world_->CreateBody(&rigidbody_box2d_body_definition);

			// Assign the body handler of box2D to the physics_collider_2d component
			physics_collider_2d.set_native_body(rigidbody_box2d_body);

			// Creates the fixture
			b2PolygonShape box_collider_shape;
			box_collider_shape.SetAsBox(
				physics_collider_2d.get_fixture_raw_size().x, 
				physics_collider_2d.get_fixture_raw_size().y
			);

			// Creates the shape fixture and assigns it to the boxcollider
			b2FixtureDef box_collider_box2D_fixture_def;
			box_collider_box2D_fixture_def.shape = &box_collider_shape;
			box_collider_box2D_fixture_def.density = physics_collider_2d.density;
			box_collider_box2D_fixture_def.friction = physics_collider_2d.friction;
			box_collider_box2D_fixture_def.restitution = physics_collider_2d.restitution;
			box_collider_box2D_fixture_def.restitutionThreshold = physics_collider_2d.restitution_threshold;
			physics_collider_2d.set_native_fixture(rigidbody_box2d_body->CreateFixture(&box_collider_box2D_fixture_def));
		}
	}

	void physics_simulator_2d::destroy_simulation()
	{
		if (!is_created())
			return;

		if (is_playing_)
			pause();

		// Destroys the physics world and free the memory
		delete physics_world_;
		physics_world_ = nullptr;
	}
}