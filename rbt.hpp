/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:16:46 by mbarut            #+#    #+#             */
/*   Updated: 2022/02/15 15:26:09 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RBT_HPP
# define FT_RBT_HPP

#include "iterator.hpp"
#include "utility.hpp"
#include <cstddef>
#include <memory>
#include <iostream>
#include "debug.hpp"

namespace ft 
{

	enum __RBT_Node_color {	_S_black = false, _S_red = true };

	template <typename _T>
	class __RBT_Node
	{

	public:

		typedef _T						value_type;
		typedef __RBT_Node<value_type>	node_type;

		value_type						__value;
		__RBT_Node*						__parent;
		__RBT_Node*						__left;
		__RBT_Node*						__right;
		__RBT_Node_color				__color;

		__RBT_Node () : __value(), __parent(u_nullptr), __left(u_nullptr), __right(u_nullptr), __color(_S_red) {}

		__RBT_Node(node_type* nil, const value_type& __value)
		: __value(__value), __parent(nil), __left(nil), __right(nil), __color(_S_red) {}

		__RBT_Node (const __RBT_Node& node)
		: __value(node.__value), __parent(node.__parent), __left(node.__left), __right(node.__right), __color(node.__color) {}

		__RBT_Node (__RBT_Node* __parent, __RBT_Node* __left, __RBT_Node* __right, __RBT_Node_color __color = _S_red) : __value(), __parent(__parent), __left(__left), __right(__right), __color(__color) {}
		__RBT_Node (const value_type& __value, __RBT_Node* __parent = u_nullptr, __RBT_Node* __left = u_nullptr, __RBT_Node* __right = u_nullptr, __RBT_Node_color __color = _S_red) : __value(__value), __parent(__parent), __left(__left), __right(__right), __color(__color) {}
		~__RBT_Node() {}

		__RBT_Node& operator= (const __RBT_Node& rhs)
		{
			if (rhs == *this)
				return *this;
			this->__value = rhs.__value;
			this->__parent = rhs.__parent;
			this->__left = rhs.__left;
			this->__right = rhs.__right;
			this->__color = rhs.__color;
			return *this;
		}

		bool operator==(const __RBT_Node& rhs)
		{
			if (__value == rhs.__value)
				return (true);
			return (false);
		}

		template <typename node_pointer> 
		static node_pointer _get_min(node_pointer node, const __RBT_Node* nil)
		{
			for (; node != nil && node->__left != nil; node = node->__left) {}
				return node;
		}

		template <typename node_pointer> 
		static node_pointer _get_max(node_pointer node, const __RBT_Node* nil)
		{
			for (; node != nil && node->__right != nil; node = node->__right) {}
				return node;
		}

		template <typename node_pointer>
		static void	_increment(node_pointer& node, const __RBT_Node* nil)
		{
			if (node->__right != nil)
				node = _get_min(node->__right, nil);
			else if (node == nil || nil->__left == node)
				node = node->__right;
			else
			{
				for (; node->__parent != nil && node == node->__parent->__right; node = node->__parent) {}
				node = node->__parent;
			}
		}

		template <typename node_pointer>
		static void	_decrement(node_pointer& node, const __RBT_Node* nil)
		{
			if (node->__left != nil)
				node = _get_max(node->__left, nil);
			else if (node == nil || nil->__right == node)
				node = node->__left;
			else
			{
				for (; node->__parent != nil && node == node->__parent->__left; node = node->__parent) {}
				node = node->__parent;
			}
		}
	};

	template <
		class T, class Key = T,
		class Compare = std::less<T>,
		class Node = ft::__RBT_Node<T>,
		class Allocator_T = std::allocator<T>,
		class Allocator_Node = std::allocator<Node>
	>
	class	_RBT
	{

		#ifndef _PARENT_IS_LEFT_CHILD
		# define _PARENT_IS_LEFT_CHILD							node->__parent == node->__parent->__parent->__left
		#endif

		#ifndef _IS_LEFT_CHILD
		# define _IS_LEFT_CHILD									node == node->__parent->__left
		#endif

		#ifndef _IS_RIGHT_CHILD
		# define _IS_RIGHT_CHILD								node == node->__parent->__right
		#endif

		#ifndef _MIN_NODE
		# define _MIN_NODE										_nil->__right
		#endif

		#ifndef _MAX_NODE
		# define _MAX_NODE										_nil->__left
		#endif

	public:

		typedef _RBT											self_type;
		typedef _RBT&											self_type_reference;
		typedef T												value_type;
		typedef Node											node_type;
		typedef Node*											node_pointer;
		typedef Allocator_T										allocator_type;
		typedef Allocator_Node									node_allocator;
		typedef ft::_RBT_iterator<Node>							iterator;
		typedef ft::_RBT_const_iterator<Node>					const_iterator;
		typedef size_t											size_type;
		typedef Compare											compare_type;
		typedef Key												key_type;

		size_t													_n;
		node_pointer											_nil;
		node_pointer											_root;
		node_allocator											_nalloc;
		compare_type											_compare;

		_RBT(const node_allocator& custom = node_allocator()) : _nalloc(custom)
		{
			_nil = _nalloc.allocate(1);
			_nalloc.construct(_nil, node_type(_nil, _nil, _nil, _S_black));
			_root = _nil;
			_n = 0;
		}

		~_RBT()
		{
			_nalloc.destroy(_nil);
			_nalloc.deallocate(_nil, 1);	
		}

		node_pointer	_create_node(const value_type& __value)
		{
			node_type*		node = _nalloc.allocate(1);
			node->__color = _S_red;
			node->__parent = _nil;
			node->__right = _nil;
			node->__left = _nil;
			allocator_type().construct(&(node->__value), __value);
			return node;
		}

		void			_destroy_node(node_pointer node)
		{
			#ifdef __DEBUG
				std::cout << "[debug] Destroying a node with key, value pair: ( " << node->__value.first << ", " << node->__value.second << " )" << std::endl;
			#endif
			_nalloc.destroy(node);
			_nalloc.deallocate(node, 1);
		}

		node_pointer	_clone_node(const node_pointer& node)
		{
			node_type*	clone = _create_node(node->__value);
			clone->__color = node->__color;
			clone->__left = _nil;
			clone->__right = _nil;
			return clone;
		}

		void			_lrotate_node(node_pointer node)
		{
			if (node == _nil || node->__right == _nil)
				return ;
			node_pointer	ptr = node->__right;
			if ((node->__right = ptr->__left) != _nil)
				node->__right->__parent = node;
			if ((ptr->__parent = node->__parent) == _nil)
				_root = ptr;
			else if (ptr->__parent->__left == node)
				ptr->__parent->__left = ptr;
			else
				ptr->__parent->__right = ptr;
			ptr->__left = node;
			node->__parent = ptr;
		}

		void			_rrotate_node(node_pointer node)
		{
			if (node == _nil || node->__left == _nil)
				return ;
			node_pointer	ptr = node->__left;
			if ((node->__left = ptr->__right) != _nil)
				node->__left->__parent = node;
			if ((ptr->__parent = node->__parent) == _nil)
				_root = ptr;
			else if (ptr->__parent->__right == node)
				ptr->__parent->__right = ptr;
			else
				ptr->__parent->__left = ptr;
			ptr->__right = node;
			node->__parent = ptr;
		}

		void			_flip_color(node_pointer& node, node_pointer aunt)
		{
			aunt->__color = _S_black;
			node->__parent->__color = _S_black;
			node->__parent->__parent->__color = _S_red;
			node = node->__parent->__parent;
		}

		void			_replace_node(node_pointer node_to_replace, node_pointer new_node)
		{
			node_pointer node = node_to_replace;

			if (node->__parent == _nil)
				_root = new_node;
			else if (_IS_LEFT_CHILD)
				node->__parent->__left = new_node;
			else
				node->__parent->__right = new_node;
			new_node->__parent = node->__parent;
		}

		void			_swap(self_type_reference rbt)
		{
			size_type		org_n = _n;
			node_pointer	org_nil = _nil;
			node_pointer	org_root = _root;

			_n = rbt._n;
			_nil = rbt._nil;
			_root = rbt._root;

			rbt._n = org_n;
			rbt._nil = org_nil;
			rbt._root = org_root;
		}

		node_pointer	_search_for(const Key& key) const
		{
			node_pointer i = _root;
			for (; i != _nil && extract_key(i->__value) != key;
				i = _compare(key, extract_key(i->__value)) ? i->__left : i->__right) { }
			return i;
		}

		void			_check_if_next(node_pointer& found, const  value_type& __value, iterator i)
		{
			if (i.base() && i.base() != _nil && _compare(extract_key(i.base()->__value), extract_key(__value)))
			{
				iterator	next = i;
				++next;
				if ((i.base() == _nil->__left || (next.base() != _nil && _compare(extract_key(__value), extract_key(next.base()->__value)))) && i.base()->__right == _nil)
					found = i.base(); 
			}
		}

		node_pointer	_find_whose_child(const value_type& __value)
		{
			node_pointer p = _root;

			for (; p != _nil && extract_key(p->__value) != extract_key(__value);)
			{
				if (_compare(extract_key(__value), extract_key(p->__value)))
				{
					if (p->__left == _nil)
						return p;
					p = p->__left;
				}
				else
				{
					if (p->__right == _nil)
						return p;
					p = p->__right;
				}
			}
			return p;
		}

		void			_insert_rebalance_branch(node_pointer& node, node_pointer aunt)
		{
			if (aunt->__color == _S_red)
				_flip_color(node, aunt);
			else
			{
				if (_PARENT_IS_LEFT_CHILD)
				{
					if (_IS_RIGHT_CHILD)
					{
						node = node->__parent;
						_lrotate_node(node);
					}
					node->__parent->__color = _S_black;
					node->__parent->__parent->__color = _S_red;
					_rrotate_node(node->__parent->__parent);
				}
				else
				{
					if (_IS_LEFT_CHILD)
					{
						node = node->__parent;
						_rrotate_node(node);
					}
					node->__parent->__color = _S_black;
					node->__parent->__parent->__color = _S_red;
					_lrotate_node(node->__parent->__parent);
				}
			}
			
		}

		void			_insert_rebalance(node_pointer node)
		{
			while (node != _root && node->__parent->__color == _S_red)
			{
				if (_PARENT_IS_LEFT_CHILD)
					_insert_rebalance_branch(node, node->__parent->__parent->__right);
				else
					_insert_rebalance_branch(node, node->__parent->__parent->__left);
			}
			_root->__color = _S_black;
		}

		ft::pair<iterator, bool>	_insert(const value_type& __value, iterator i = iterator())
		{
			node_pointer	found = NULL;
			ft::pair<iterator, bool> result;
			
			_check_if_next(found, __value, i);
			if (found == NULL)
				found = _find_whose_child(__value);
			if (extract_key(found->__value) == extract_key(__value))
			{
				#ifdef __DEBUG
					std::cout << "[debug] inserted key \'" << found->__value.first << "\' already exists in the tree; changing its mapped value" << std::endl;
				#endif
				result.first = iterator(found, _nil);
				result.second = false;
			}
			else
			{
				node_pointer	newnode = _create_node(__value);
				#ifdef __DEBUG
					std::cout << "[debug] Creating a new node with key, value pair: ( " << newnode->__value.first << ", " << newnode->__value.second << " )" << std::endl;
				#endif
				if (found == _nil)
				{
					_root = newnode;
					_nil->__right = newnode;
					_nil->__left = newnode;
					#ifdef __DEBUG
						std::cout << "[debug] RBT has the root node: ( " << newnode->__value.first << ", " << newnode->__value.second << " )" << std::endl;
					#endif
				}
				else if (_compare(extract_key(__value), extract_key(found->__value)))
				{
					found->__left = newnode;
					if (_nil->__right == found)
						_nil->__right = newnode;
				}
				else
				{
					found->__right = newnode;
					if (_nil->__left == found)
						_nil->__left = newnode;
				}
				newnode->__parent = found;
				result.first = iterator(newnode, _nil);
				result.second = true;
				++_n;

				_insert_rebalance(newnode);
				_nil->__parent = _nil;
			}

			return result;
		}

		void		_delete_rebalance_branch_case1(node_pointer node, node_pointer sibling)
		{
			node->__parent->__color = _S_red;
			sibling->__color = _S_black;
			_IS_LEFT_CHILD ? _lrotate_node(node->__parent) : _rrotate_node(node->__parent);
			sibling = _IS_LEFT_CHILD ? node->__parent->__right : node->__parent->__left;
		}

		void		_delete_rebalance_branch_case2(node_pointer node, node_pointer sibling)
		{
			sibling->__color = _S_red;
			node = node->__parent;
		}

		void		_delete_rebalance_branch_case3(node_pointer node, node_pointer sibling)
		{
			node_pointer niece = _IS_LEFT_CHILD ? sibling->__right : sibling->__left;
			node_pointer nephew = !(_IS_LEFT_CHILD) ? sibling->__right : sibling->__left;

			if (niece->__color == _S_black)
			{
				nephew->__color = _S_black;
				sibling->__color = _S_red;
				_IS_LEFT_CHILD ? _rrotate_node(sibling) : _lrotate_node(sibling) ;
				sibling = _IS_LEFT_CHILD ? node->__parent->__right : node->__parent->__left ;
			}
			sibling->__color = node->__parent->__color;
			node->__parent->__color = _S_black;
			niece->__color = _S_black ;
			_IS_LEFT_CHILD ? _lrotate_node(node->__parent) : _rrotate_node(node->__parent) ;
			node = _nil;
		}

		void		_delete_rebalance_branch(node_pointer node, node_pointer sibling)
		{
			if (sibling->__color == _S_red)
				_delete_rebalance_branch_case1(node, sibling);
			else if (sibling->__left->__color == _S_black && sibling->__right->__color == _S_black)
				_delete_rebalance_branch_case2(node, sibling);
			else
				_delete_rebalance_branch_case3(node, sibling);
		}
		
		void		_delete_rebalance(node_pointer node)
		{
			node_pointer	sibling;

			while (1)
			{
				if (node == _root) break;
				else if (node->__color == _S_red) break;
				#ifdef __DEBUG
					std::cout << "[debug] RBT has been successfully rebalanced upon deletion of a node; breaking out of the balancing loop" << std::endl;
				#endif
				sibling = _IS_LEFT_CHILD ? node->__parent->__right : node->__parent->__left;
				_delete_rebalance_branch(node, sibling);
			}
			#ifdef __DEBUG
				std::cout << "[debug] RBT has been successfully rebalanced upon deletion of a node; breaking out of the balancing loop" << std::endl;
			#endif
			node->__color = _S_black;	
		}

		void		_llink(node_pointer node1, node_pointer node2)
		{
			node1->__left = node2->__left;
			node1->__left->__parent = node1;
		}

		void		_rlink(node_pointer node1, node_pointer node2)
		{
			node1->__right = node2->__right;
			node1->__right->__parent = node1;
		}

		void		_delete(node_pointer node)
		{
			if (node == _nil)
				return ;
			if (node == _MIN_NODE)
				node_type::_increment(_MIN_NODE, _nil);
			if (node == _MAX_NODE)
				node_type::_decrement(_MAX_NODE, _nil);
			
			node_pointer		node_child;
			__RBT_Node_color	orig_color	= node->__color;
			
			if (node->__left == _nil)
			{
				node_child = node->__right;
				_replace_node(node, node_child);
			}
			else if (node->__right == _nil)
			{
				node_child = node->__left;
				_replace_node(node, node_child);
			}
			else
			{
				node_pointer node_successor = node_type::_get_min(node->__right, _nil);
				orig_color = node_successor->__color;
				node_child = node_successor->__right;
				if (node_successor->__parent == node)
					node_child->__parent = node_successor;
				else
				{
					_replace_node(node_successor, node_successor->__right);
					_rlink(node_successor, node);
				}
				_replace_node(node, node_successor);
				_llink(node_successor, node);
				node_successor->__color = node->__color;
			}
			
			if (orig_color == _S_black)
			{
				#ifdef __DEBUG
				std::cout << "[debug] RBT has to be rebalanced upon deletion of a black node" << std::endl;
				#endif
				_delete_rebalance(node_child);
			}
			_nil->__parent = _nil;

			_destroy_node(node);
			--_n;
		}

		template<class InputIterator>
		void	_range_init(InputIterator begin, InputIterator end)
		{
			while (begin != end)
				_insert(*begin++);
		}

		void _traverseLNR(node_pointer node) const
		{
			if (node == _nil)
				return ;
			_traverseLNR(node->__left);
			std::cout << "(" << node->__value.first << ", " << node->__value.second << ")" << "->";
			_traverseLNR(node->__right);
		}
		
		void _traverseNLR(node_pointer node) const
		{
			if (node == _nil)
				return ;
			std::cout << "(" << node->__value.first << ", " << node->__value.second << ")" << "->";
			_traverseNLR(node->__left);
			_traverseNLR(node->__right);
		}
		
		void _traverseLRN(node_pointer node) const
		{
			if (node == _nil)
				return ;
			_traverseLRN(node->__left);
			_traverseLRN(node->__right);
			std::cout << "(" << node->__value.first << ", " << node->__value.second << ")" << "->";
		}

		#undef _PARENT_IS_LEFT_CHILD
		#undef _IS_RIGHT_CHILD
		#undef _IS_LEFT_CHILD
		#undef _MIN_NODE
		#undef _MAX_NODE
	};

}

#endif