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

		// Copies every component attached to the source entity in the destination entity
		src_entity.copy_component<transform_component>(entity_copy_buffer);
		src_entity.copy_component<sprite_component>(entity_copy_buffer);
		src_entity.copy_component<camera_component>(entity_copy_buffer);
		
		return entity_copy_buffer;
	}

	void scene::destroy_entity(entt::entity entity)
	{
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
}