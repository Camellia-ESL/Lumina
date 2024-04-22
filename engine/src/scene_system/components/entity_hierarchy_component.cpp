#include "entity_hierarchy_component.h"

namespace lumina
{
	const bool entity_hierarchy_component::has_attached(const entity& child) const
	{
		for (auto& ent : childs_)
			if (ent.get_entity() == child.get_entity())
				return true;

		return false;
	}

	const bool entity_hierarchy_component::has_child(const entity& child) const
	{
		for (auto& child_ent : childs_)
		{
			// Check if is child
			if (child_ent.get_entity() == child.get_entity())
				return true;

			entity_hierarchy_component& child_ent_hierarchy = const_cast<entity&>(child_ent).get_component<entity_hierarchy_component>();

			if (child_ent_hierarchy.has_childs() && child_ent_hierarchy.has_child(child))
				return true;
		}

		return false;
	}

	void entity_hierarchy_component::attach_child(const entity& child)
	{
		// Check if a entity is already attached
		if (has_attached(child))
			return;

		childs_.push_back(child);
	}

	void entity_hierarchy_component::remove_child(const entity& child)
	{
		// Creates an itherator to iterate the list safely
		std::vector<entity>::iterator childs_it = childs_.begin();

		// Search for items to delete and erase it
		while (childs_it != childs_.end())
		{
			if (childs_it->get_entity() == child.get_entity())
				childs_it = childs_.erase(childs_it);
			else
				childs_it++;
		}
	}

	void entity_hierarchy_component::set_parent(const entity& parent)
	{
		parent_ = parent;
	}

	static void dispatch_func_to_childs_impl(std::function<void(entity&)> callback, std::vector<entity>& entities)
	{
		for (auto& child_ent : entities)
		{
			callback(child_ent);

			entity_hierarchy_component& child_ent_hierarchy = const_cast<entity&>(child_ent).get_component<entity_hierarchy_component>();

			if (child_ent_hierarchy.has_childs())
				dispatch_func_to_childs_impl(callback, child_ent_hierarchy.get_childs());
		}
	}

	void entity_hierarchy_component::dispatch_func_to_childs(std::function<void(entity&)> callback)
	{
		dispatch_func_to_childs_impl(callback, childs_);
	}

	void entity_hierarchy_component::switch_child_attachment(entity& parent, entity& child)
	{
		lumina::entity_hierarchy_component& child_hierarchy =
			child.get_component<lumina::entity_hierarchy_component>();

		// It first check if the new parent is a child of child to avoid undefined behaviours
		if (child.get_component<lumina::entity_hierarchy_component>().has_child(parent))
			return;

		// Remove the child from the old parent childs list
		if (child_hierarchy.has_parent())
			child_hierarchy.get_parent().get_component<lumina::entity_hierarchy_component>().remove_child(child);

		// Set the new parent entity of the dragged entity
		child_hierarchy.set_parent(parent);

		// Submit the entity in the hierarchy as a child
		parent.get_component<lumina::entity_hierarchy_component>().attach_child(child);
	}
}