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
		return entity_buffer;
	}

	void scene::destroy_entity(entt::entity entity)
	{
		registry_.destroy(entity);
	}
}