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
			// The parent node id
			std::string parent_id;
			// The vector that contains value_types n elements on this node 
			std::vector<elements_value_type> node_elements;
			// The next nodes of the tree
			std::vector<tree_node_t> next_nodes;
			
			// Add a node in the root node
			constexpr tree_node_t& add_node()
			{
				return add_node(DEFAULT_NODE_NAME_);
			}

			// Add a node in the root node with a custom name
			constexpr tree_node_t& add_node(const std::string& node_name)
			{
				// Push the new node
				this->next_nodes.push_back(
					tree_node_t(
						lumina_strings_s::generate_uuidv4(),
						node_name,
						this->id
					)
				);

				// Return the last item (the one added now)
				return this->next_nodes[this->next_nodes.size() - 1];
			}
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
				{
					lumina_strings_s::generate_uuidv4(),
					node_name,
					node.id
				}
			);

			// Return the last item (the one added now)
			return node.next_nodes[node.next_nodes.size() - 1];
		}

		// Get the parent node of a given node
		constexpr tree_node_t* get_parent(tree_node_t& child)
		{
			return get_parent(root_node_, child.parent_id);
		}

		// Get the parent node of a given node
		constexpr tree_node_t* get_parent(const std::string& parent_id)
		{
			if (parent_id == root_node_.id)
				return &root_node_;

			return get_node_(root_node_, [&](tree_node_t& node) -> bool { return node.id == parent_id; });
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

		// Get the first node that has the given id (name must be null to search with only id)
		constexpr tree_node_t* get_node(const std::string& node_name, const std::string& node_id)
		{
			return get_node_(root_node_, [&](tree_node_t& node) -> bool { return node_name.empty() ? node.id == node_id : node.name == node_name && node.id == node_id; });
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

		// Erase all the nodes and items from the tree and free every resoure holded (be careful to manually free memory if the elements_value_type is a pointer heap allocated)
		constexpr void clear() { root_node_.next_nodes.clear(); root_node_.node_elements.clear(); }

		// Iterate all the tree and execute a given expression for every sub node
		constexpr void iterate_nodes(std::function<void(tree_node_t&)> expression) { iterate_nodes_(root_node_, expression); }

		// Iterate all the tree from a given starting node and execute a given expression for every sub node
		constexpr void iterate_nodes(tree_node_t& node, std::function<void(tree_node_t&)> expression) { iterate_nodes_(node, expression); }

		// Iterate all the tree and execute a given expression for every sub node with a push expression to manually insert to iterate subnode
		// at any given point of the execution decided by the user (if the push expression is not called by the user somewhere in the main expression subnodes will not be iterated)
		constexpr void iterate_nodes_push_expr(std::function<void(tree_node_t&, std::function<void()>)> expression) { iterate_nodes_with_push_expression_(root_node_, expression); }

		// Iterate all the tree from a given starting node and execute a given expression for every sub node with a push expression to manually insert to iterate subnode
		// at any given point of the execution decided by the user (if the push expression is not called by the user somewhere in the main expression subnodes will not be iterated)
		constexpr void iterate_nodes_push_expr(tree_node_t& node, std::function<void(tree_node_t&, std::function<void()>)> expression) { iterate_nodes_with_push_expression_(node, expression); }

		// Iterate all the tree and execute a given expression for every node and sub node with a starting and ending function for parent nodes
		constexpr void iterate_nodes_close_expr(std::function<bool(tree_node_t&)> expression) { iterate_nodes_(root_node_, expression); }

		// Iterate all the tree from a given starting node and execute a given expression for every node and sub node with a starting and ending function for parent nodes
		constexpr void iterate_nodes_close_expr(tree_node_t& node, std::function<bool(tree_node_t&)> expression) { iterate_nodes_(node, expression); }

		// Iterate all the tree and execute a given expression for every item
		constexpr void iterate_node_items(std::function<bool(tree_node_t&)> expression) { iterate_node_items_(root_node_, expression); }

		// Iterate all the tree from a given starting node and execute a given expression for every item
		constexpr void iterate_node_items(tree_node_t& node, std::function<bool(tree_node_t&)> expression) { iterate_node_items_(node, expression); }

		// Get the root node
		constexpr tree_node_t& get_root_node() { return root_node_; }

	private:

		static constexpr const char* DEFAULT_NODE_NAME_ = "default_node_name";
		tree_node_t root_node_{ lumina_strings_s::generate_uuidv4() };

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
		constexpr void iterate_nodes_(
			// The node in which to start iterating
			tree_node_t& parent_node,
			// The expression to execute
			std::function<void(tree_node_t&)> execute_expression
		)
		{
			// Iterate subnodes
			for (tree_node_t& node : parent_node.next_nodes)
			{
				execute_expression(node);
				iterate_nodes_(node, execute_expression);
			}
		}

		// Recursevely iterate all the tree from a given starting node and execute a given expression for every sub node with a push expression to manually insert to iterate subnode
		// at any given point of the execution decided by the user (if the push expression is not called by the user somewhere in the main expression subnodes will not be iterated)
		constexpr void iterate_nodes_with_push_expression_(
			// The node in which to start iterating
			tree_node_t& parent_node,
			// The expression to execute (the node iterating, the push expression to call to iterate subnodes)
			std::function<void(tree_node_t&, std::function<void()>)> execute_expression
		)
		{
			// Iterate nodes
			for (tree_node_t& node : parent_node.next_nodes)
				execute_expression(node, 
					[&]() -> void 
					{
						iterate_nodes_with_push_expression_(node, execute_expression);
					}
				);
		}

		// Recursevely iterate all the tree from a given starting node and execute a given expression for every node and sub node with a starting and ending function for parent nodes
		constexpr void iterate_nodes_with_iteration_passages_(
			// The node in which to start iterating
			tree_node_t& parent_node,
			// The expression to execute when a node start iterating sub nodes (works also for every sub node)
			std::function<void(tree_node_t&)> begin_pass_execute_expression,
			// The expression to execute when a node end iterating sub nodes (works also for every sub node)
			std::function<void(tree_node_t&)> end_pass_execute_expression
		)
		{
			// Iterate subnodes
			for (tree_node_t& node : parent_node.next_nodes)
			{
				begin_pass_execute_expression(node);
				iterate_nodes_with_iteration_passages_(node, begin_pass_execute_expression, end_pass_execute_expression);
				end_pass_execute_expression(node);
			}
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