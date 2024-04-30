#include "scene.h"

namespace lumina
{
	scene::scene(const std::string& name) 
		: name_{ name } 
	{
	}

	entity scene::create_entity()
	{
		entity entity_buffer{ &registry_, registry_.create() };
		entity_buffer.add_component<identity_component>();
		entity_buffer.add_component<entity_hierarchy_component>();
		return entity_buffer;
	}

	entity scene::duplicate_entity(entity src_entity)
	{
		// Creates the entity
		entity entity_copy_buffer = create_entity();

		// Copies the entity name
		entity_copy_buffer.get_component<identity_component>().name = src_entity.get_component<identity_component>().name;
		entity_hierarchy_component& src_entity_hierarchy = src_entity.get_component<entity_hierarchy_component>();

		// Copies every component attached to the source entity in the destination entity
		src_entity.copy_component<transform_component>(entity_copy_buffer);
		src_entity.copy_component<sprite_component>(entity_copy_buffer);
		src_entity.copy_component<camera_component>(entity_copy_buffer);
		src_entity.copy_component<physics_collider_2d_component>(entity_copy_buffer);
		
		// Copies every sub entity if has some
		if (src_entity_hierarchy.has_childs())
			for (auto& child : src_entity_hierarchy.get_childs())
				entity_copy_buffer.get_component<entity_hierarchy_component>().attach_child(
					duplicate_entity(child)
				);

		return entity_copy_buffer;
	}

	void scene::destroy_entity(entt::entity entity)
	{
		for (auto& child : lumina::entity(&registry_, entity).get_component<entity_hierarchy_component>().get_childs())
			destroy_entity(entity);

		registry_.destroy(entity);
	}

	entity scene::get_entity_by_id(const std::string& id)
	{
		for (auto ent_ith : registry_.view<identity_component>())
		{
			entity ent{ &registry_, ent_ith };
			if (ent.get_component<identity_component>().id == id)
				return ent;
		}

		return entity{};
	}

	void scene::on_create()
	{

	}

	void scene::on_destroy()
	{
		// Destroy's the physics simulation
		physics_2d_sim_.destroy_simulation();
	}

	void scene::on_activate()
	{
		// Resume the physics simulation
		physics_2d_sim_.play();
	}

	void scene::on_deactivate()
	{
		// Stop the physics simulation
		physics_2d_sim_.pause();
	}

	void scene::on_load()
	{
		// Create's the physics simulation
		physics_2d_sim_.init_simulation(this);
	}
}