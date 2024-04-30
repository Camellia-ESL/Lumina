#pragma once

#include "component.h"

#include "scene_system/entity.h"

#include <functional>
#include <vector>

namespace lumina
{
	struct entity_hierarchy_component : public component
	{
	public:

		// Wheter if the entity given is attached or not (it does not recursevily check, use has_child for this purpose)
		const bool has_attached(const entity& child) const;

		// Wheter if the entity has a parent or not
		const bool has_parent() const { return parent_.has_entity(); }

		// Wheter if has childs or not
		const bool has_childs() const { return !childs_.empty(); }

		// Wheter if the given entity is a child attached (note it also recursevily checks all the subchilds)
		const bool has_child(const entity& child) const;

		// Get's the childs
		std::vector<entity>& get_childs() { return childs_; }

		// Get's the parent
		entity& get_parent() { return parent_; }

		// Adds a new child 
		void attach_child(const entity& child);

		// Removes a child
		void remove_child(const entity& child);

		// Set the entity parent
		void set_parent(const entity& parent);

		// Dispatch a function that executes for every child and subchild recursively
		void dispatch_func_to_childs(std::function<void(entity&)> callback);

		// Attach a child to a new parent and handles the switch automatically (note it does not let you assign a parent to a child that contains the parent)
		static void switch_child_attachment(entity& parent, entity& child);

	private:
		
		std::vector<entity> childs_;
		entity parent_;
	
	};
}