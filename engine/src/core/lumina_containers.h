#pragma once

#include "lumina_strings.h"

#include <vector>
#include <string>
#include <functional>

namespace lumina
{
	// A tree structure container, note that for a better use items contained in nodes should be uniques 
	template<class elements_value_type>
	class lumina_tree
	{
	public:

		// A single node of the tree
		struct tree_node_t
		{
			// The node id (should not be assigned outside of the tree)
			std::string id;
			// The node name (optional)
			std::string name;
			// The vector that contains value_types n elements on this node 
			std::vector<elements_value_type> node_elements;
			// The next nodes of the tree
			std::vector<tree_node_t> next_nodes;
		};

	public:
		
		constexpr lumina_tree() {}

		// Add a node in the root node
		constexpr tree_node_t& add_node()
		{
			return add_node(root_node_, DEFAULT_NODE_NAME_);
		}

		// Add a node in the root node with a custom name
		constexpr tree_node_t& add_node(const std::string& node_name)
		{
			return add_node(root_node_, node_name);
		}

		// Add a node in another node
		constexpr tree_node_t& add_node(tree_node_t& node)
		{
			return add_node(node, DEFAULT_NODE_NAME_);
		}

		// Add a node in another with a custom name
		constexpr tree_node_t& add_node(tree_node_t& node, const std::string& node_name)
		{
			// Push the new node
			node.next_nodes.push_back(
				tree_node_t(
					lumina_strings_s::generate_uuidv4(),
					node_name
				)
			);

			// Return the last item (the one added now)
			return node.next_nodes[node.next_nodes.size() - 1];
		}

		// Get the first node that match the given expression
		constexpr tree_node_t* get_node(std::function<bool(tree_node_t&)> search_expression)
		{
			return get_node_(root_node_, search_expression);
		}

		// Get the first node that has the given name
		constexpr tree_node_t* get_node(const std::string& node_name)
		{
			return get_node_(root_node_, [&](tree_node_t& node) -> bool { return node.name == node_name; });
		}

		// Get the first node that contains the given item
		constexpr tree_node_t* get_node(const elements_value_type& item_value)
		{
			return get_node_(root_node_, 
				[&](tree_node_t& node) -> bool { 
					for (auto& element : node.node_elements)
						if (element == item_value)
							return true;

					return false;
				}
			);
		}

		// Get the first node that contains the given item pointer
		constexpr tree_node_t* get_node(const elements_value_type* item_ptr)
		{
			return get_node_(root_node_,
				[&](tree_node_t& node) -> bool {
					for (auto& element : node.node_elements)
						if (&element == item_ptr)
							return true;

					return false;
				}
			);
		}

		// Iterate all the tree and execute a given expression for every sub node
		constexpr void iterate_node(std::function<bool(tree_node_t&)> expression) { iterate_node_(root_node_, expression); }

		// Iterate all the tree from a given starting node and execute a given expression for every sub node
		constexpr void iterate_node(tree_node_t& node, std::function<bool(tree_node_t&)> expression) { iterate_node_(node, expression); }

		// Iterate all the tree and execute a given expression for every item
		constexpr void iterate_node_items(std::function<bool(tree_node_t&)> expression) { iterate_node_items_(root_node_, expression); }

		// Iterate all the tree from a given starting node and execute a given expression for every item
		constexpr void iterate_node_items(tree_node_t& node, std::function<bool(tree_node_t&)> expression) { iterate_node_items_(node, expression); }

		// Get the root node
		constexpr const tree_node_t& get_root_node() const { return root_node_; }

	private:

		static constexpr const char* DEFAULT_NODE_NAME_ = "default_node_name";
		tree_node_t root_node_;

		// Recursevely iterate the tree to find the node with the given name
		constexpr tree_node_t* get_node_(
			// The node in which to start the search
			tree_node_t& parent_node, 
			// The expression that should match the node to search (es. node.node_name == "Example Node")
			std::function<bool(tree_node_t&)> search_expression
		)
		{
			// Tries to search the node in the child nodes
			for (tree_node_t& node : parent_node.next_nodes)
				if (search_expression(node))
					return &node;

			// If no node could be found tries to search in childs childrens
			for (tree_node_t& node : parent_node.next_nodes)
			{
				// Search in sub nodes
				tree_node_t* sub_node_ith_search_result = get_node_(node, search_expression);
				
				// If a node where found matching the given expression return it's pointer
				if (sub_node_ith_search_result != nullptr)
					return sub_node_ith_search_result;
			}

			return nullptr; 
		}

		// Recursevely iterate all the tree from a given starting node and execute a given expression for every sub node
		constexpr void iterate_node_(
			// The node in which to start iterating
			tree_node_t& parent_node,
			// The expression to execute
			std::function<void(tree_node_t&)> execute_expression
		)
		{
			// Execute expression for all the given next_nodes
			for (tree_node_t& node : parent_node.next_nodes)
				execute_expression(node);

			// Iterate subnodes
			for (tree_node_t& node : parent_node.next_nodes)
				iterate_node_(node, execute_expression);
		}

		// Iterate all the node items and execute a given expression for every item iteration
		constexpr void iterate_node_items_(
			// The node that contains the items to iterate
			tree_node_t& node,
			// The expression to execute
			std::function<void(elements_value_type&)> execute_expression
		)
		{
			// Execute expression for all the given next_nodes
			for (auto& element : node.node_elements)
				execute_expression(element);
		}
	};
}