#pragma once

#include "entt/entt.hpp"

namespace lumina
{
	// a wrapper class used to abstract and simplify ENTT entities to avoid miss usage
	// or miss understanding about the code used written using entt, represent a entt entity
	class entity
	{
	public:

		entity(entt::registry& entity_registry, entt::entity entity) : entity_registry_{ entity_registry }, entity_{ entity } {}
		entity(const entity& copy_entity) : entity_registry_{ copy_entity.entity_registry_ }, entity_{ copy_entity.entity_ } {}

		template<typename component_type>
		component_type& get_component()
		{
			return entity_registry_.get<component_type>(entity_);
		}

		template<typename component_type, typename... args>
		component_type& add_component(args&&... arguments)
		{
			return entity_registry_.emplace<component_type>(entity_, std::forward<args>(arguments)...);
		}

	private:

		entt::entity entity_;
		entt::registry& entity_registry_;

	};
}