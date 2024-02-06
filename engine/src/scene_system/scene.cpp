#include "scene.h"

namespace lumina
{
	entity scene::create_entity()
	{
		return entity{ registry_, registry_.create() };
	}

	void scene::destroy_entity(entt::entity entity)
	{
		registry_.destroy(entity);
	}

}