#pragma once

#include "entt/entt.hpp"

namespace lumina
{
	// a wrapper class used to abstract and simplify ENTT entities to avoid miss usage
	// or miss understanding about the code used written using entt, represent a entt entity
	class entity
	{
	public:

		entity() {}
		entity(entt::registry* entity_registry, entt::entity entity) : entity_registry_{ entity_registry }, entity_{ entity } {}
		entity(const entity& copy_entity) : entity_registry_{ copy_entity.entity_registry_ }, entity_{ copy_entity.entity_ } {}

		// Gets a single component inside the entity
		template<typename component_type>
		component_type& get_component()
		{
			return entity_registry_->get<component_type>(entity_);
		}

		// Gets multiple components inside the entity
		template<typename... components_type>
		decltype(auto) get_components() 
		{
			return entity_registry_->get<components_type...>(entity_);
		}

		// Check wheter if the entity contains a given component 
		template<typename component_type>
		bool has_component() const
		{
			return entity_registry_->any_of<component_type>(entity_);
		}

		// Add a component inside the entity
		template<typename component_type, typename... args>
		component_type& add_component(args&&... arguments)
		{
			return entity_registry_->emplace<component_type>(entity_, std::forward<args>(arguments)...);
		}

		// Copies a component in another entity
		template<typename component_type>
		component_type* copy_component(entity dst_entity)
		{
			component_type generic_component{};

			// Check if src entity has the component to copy or if the dst doesn't already have it
			if (!entity_registry_->all_of<component_type>(entity_) || entity_registry_->all_of<component_type>(dst_entity.get_entity()))
				return nullptr;

			// Copies the src component in the dst entity calling the copy constructor of the given component
			return &entity_registry_->emplace<component_type>(
				dst_entity.get_entity(),
				entity_registry_->get<component_type>(entity_)
			);
		}

		const bool has_entity() const { return entity_ != entt::null; }
		const entt::entity get_entity() const { return entity_; }
		entt::registry* get_registry() const { return entity_registry_; }

	private:

		entt::entity entity_ = entt::null;
		entt::registry* entity_registry_;

	};
}