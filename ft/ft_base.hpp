/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:16:46 by mbarut            #+#    #+#             */
/*   Updated: 2022/02/09 00:23:54 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_iterator.hpp"
#include "ft_iterator_base_types.hpp"
#include "ft_pair.hpp"
#include "ft_util.hpp"
//#include "ft_iterator.hpp"
//#include "ft_vector.hpp"
#include <cstddef>
#include <memory>

namespace ft 
{

	template <typename _T>
	struct _RBT_Node
	{

	public:

		typedef _T	value_type;

		value_type	value;
		_RBT_Node*	parent;
		_RBT_Node*	left;
		_RBT_Node*	right;
		bool		is_red;

		_RBT_Node () : value(), parent(u_nullptr), left(u_nullptr), right(u_nullptr), is_red(true) {}
		_RBT_Node (_RBT_Node* parent = u_nullptr, _RBT_Node* left = u_nullptr, _RBT_Node* right = u_nullptr, bool is_red = true) : value(), parent(parent), left(left), right(right), is_red(is_red) {}
		_RBT_Node (const value_type& value, _RBT_Node* parent = u_nullptr, _RBT_Node* left = u_nullptr, _RBT_Node* right = u_nullptr, bool is_red = true) : value(value), parent(parent), left(left), right(right), is_red(is_red) {}
		_RBT_Node (const _RBT_Node& node) : value(node.value), parent(node.parent), left(node.left), right(node.right), is_red(node.is_red) {}
		virtual ~_RBT_Node() {}

		_RBT_Node& operator= (const _RBT_Node& rhs)
		{
			if (rhs == *this)
				return (*this);
			this->value = rhs.value;
			this->parent = rhs.parent;
			this->left = rhs.left;
			this->right = rhs.right;
			this->is_red = rhs.is_red;
			return (*this);
		}

		bool operator==(const _RBT_Node& rhs)
		{
			if (value == rhs.value)
				return (true);
			return (false);
		}

		template <typename Node>
		static Node	get_min(Node node, const _RBT_Node* nil)
		{
			if (node == nil)
				return node;
			for (; node->left != nil; node = node->left) {}
				return node;
		}

		template <typename Node>
		static Node	get_max(Node node, const _RBT_Node* nil)
		{
			if (node == nil)
				return node;
			for (; node->right != nil; node = node->right) {}
				return node;
		}

		template <typename Node>
		static void	next(Node& node, const _RBT_Node* nil)
		{
			if (node->right != nil)
				node = get_min(node->right, nil);
			else if (node == nil || nil->left == node)
				node = node->right;
			else
				for (; node->parent != nil && node == node->parent->right; node = node->parent) {}
				node = node->parent;
		}

		template <typename Node>
		static void	prev(Node& node, const _RBT_Node* nil)
		{
			if (node->left != nil)
				node = get_max(node->left, nil);
			else if (node == nil || nil->right == node)
				node = node->left;
			else
				for (; node->parent != nil && node == node->parent->left; node = node->parent) {}
				node = node->parent;
		}

    };

	template <
		class T,
		class Compare = ft::less<T>,
		class Node = ft::_RBT_Node<T>,
		class Allocator_T = std::allocator<T>,
		class Allocator_Node = std::allocator<Node>
	>
	class	_RBT
	{

	public:

		typedef _RBT									self_type;
		typedef _RBT&									self_type_reference;
		typedef T										value_type;
		typedef Node									node_type;
		typedef Node*									node_pointer;
		typedef Allocator_Node							node_allocator;
		typedef ft::_RBT_iterator<Node, Compare>		iterator;
		typedef ft::_RBT_const_iterator<Node, Compare>	const_iterator;
		typedef size_t									size_type;
		typedef Compare									compare_type;

		size_t											_n;
		node_pointer									_nil;
		node_allocator									_nalloc;
		compare_type									_compare;

		#ifndef ROOT
		# define ROOT									_nil->parent
		#endif

		#ifndef FIRSTNODE
		# define FIRSTNODE								_nil->left
		#endif

		#ifndef LASTNODE
		# define LASTNODE								_nil
		#endif

		#ifndef TREESIZE
		# define TREESIZE								_nil->value.first
		#endif

		/* ctor 1 */
		_RBT(const node_allocator& nalloc_initializer = node_allocator()) : _nalloc(nalloc_initializer)
		{
			_nil = _nalloc.allocate(1);
			_nalloc.construct(_nil, node_type(_nil, _nil, _nil));
		}

		/* dtor */
		~_RBT()
		{
			_nalloc.destroy(_nil);
			_nalloc.deallocate(_nil, 1);	
		}

		node_pointer	_create_node(const value_type& value)
		{
			node_pointer	node = _nalloc.allocate(1);
			node->is_red = true;
			node->parent = NULL;
			node->right = NULL;
			node->left = NULL;
			_nalloc.construct(&(node->value), value);
			return node;
		}

		void		_destroy_node(node_pointer node)
		{
			_nalloc.destroy(node);
			_nalloc.deallocate(node, 1);
		}

		//void		_init_nil()
		//{
		//	_nil = _nalloc.allocate(1);
		//	_nil->is_red = false;
		//	_nil->parent = _nil;
		//	_nil->right = _nil;
		//	_nil->left = _nil;
		//	ROOT = _nil;
		//}

		void		_M_lrotate(node_pointer node)
		{
			if (node == _nil || node->right == _nil)
				return ;
			node_pointer	tmp = node->right;
			if ((node->right = tmp->left) != _nil)
				node->right->parent = node;
			if ((tmp->parent = node->parent) == _nil)
				ROOT = tmp;
			else if (tmp->parent->left == node)
				tmp->parent->left = tmp;
			else
				tmp->parent->right = tmp;
			tmp->left = node;
			node->parent = tmp;
		}

		void		_M_rrotate(node_pointer node)
		{
			if (node == _nil || node->left == _nil)
				return ;
			node_pointer	tmp = node->left;
			if ((node->left = tmp->right) != _nil)
				node->left->parent = node;
			if ((tmp->parent = node->parent) == _nil)
				ROOT = tmp;
			else if (tmp->parent->right == node)
				tmp->parent->right = tmp;
			else
				tmp->parent->left = tmp;
			tmp->right = node;
			node->parent = tmp;
		}

		node_pointer	_get_value_by_key(const value_type& value) const
		{
			node_pointer i = ROOT;
			for (; i != _nil && i->value.first != value.first;
				_compare(value.first, i->_value.first) ? i = i->left : i = i->right) { }
			return i;
		}

		//void		_make_related(node_pointer node1, node_pointer node2)
		//{
		//	if (node1->parent == _nil)
		//		ROOT = node2;
		//	else if (node1->parent->left == node1)
		//		node1->parent->left = node2;
		//	else
		//		node1->parent->left = node2;
		//	node2->parent = node1->parent;
		//}

		//template<class InputIterator>
		//void	_range_init(InputIterator begin, InputIterator end)
		//{
		//	_init_nil();
		//	while (begin != end)
		//		_insert(*begin++);
		//}

		void		_flip_color(node_pointer& node, node_pointer aunt)
		{
			aunt->is_red = false;
			node->parent->is_red = false;
			node->parent->parent->is_red = true;
			node = node->parent->parent;
		}

		void		_fix_violations(node_pointer node)
		{
			node_pointer	aunt;
			
			while (node != ROOT && node->parent->is_red)
				if (node->parent == node->parent->parent->left)
				{
					aunt = node->parent->parent->right;
					if (aunt->is_red)
						_flip_color(node, aunt);
					else
					{
						if (node == node->parent->right)
						{
							node = node->parent;
							_lrotate(node);
						}
						node->parent->is_red = false;
						node->parent->parent->is_red = true;
						_rrotate(node->parent->parent);
					}
				}
				else
				{
					aunt = node->parent->parent->left;
					if (aunt->is_red)
						_flip_color(node, aunt);
					else
					{
						if (node == node->parent->left)
						{
							node = node->parent;
							_rright(node);
						}
						node->parent->is_red = false;
						node->parent->parent->is_red = true;
						_lrotate(node->parent->parent);
					}
				}
			ROOT->is_red = false;
		}

		void						_check_if_next(node_pointer& found, const  value_type& value, iterator i)
		{
			if (i.base() && i.base() != _nil && _compare(*i, value))
			{
				iterator	next = i;
				++next;
				if ((i.base() == _nil->left || (next.base() != _nil && _compare(value, *next))) && i.base()->right == _nil)
					found = i.base(); 
			}
		}

		ft::pair<iterator, bool>	_insert(const value_type& value, iterator i = iterator())
		{
			node_pointer	found = NULL;
			ft::pair<iterator, bool> result;
			
			_check_if_next(found, value, i);
			if (found == NULL)
				found = _find_whose_child(value);
			if (found->value.first == value.first)
			{
				result.first = iterator(found, _nil);
				result.second = false;
			}
			else
			{
				node_pointer	newnode = _create(value);
				if (found == _nil)
				{
					ROOT = newnode;
					_nil->right = newnode;
					_nil->left = newnode;
				}
				else if (_compare(value, found->value))
				{
					found->left = newnode;
					if (_nil->right == found)
						_nil->right = newnode;
				}
				else
				{
					found->right = newnode;
					if (_nil->left == found)
						_nil->left = newnode;
				}
				newnode->parent = found;
				result.first = iterator(newnode, _nil);
				result.second = true;
				++_n;

				_fix_violations(newnode);
				_nil->parent = _nil;
			}
			return result;
		}

		node_pointer		_find_whose_child(const value_type& value)
		{
			node_pointer p = ROOT;

			for (; p != _nil && p->_value.first != value.first;)
			{
				if (_compare(value, p->_value))
				{
					if (p->left == _nil)
						return p;
					p = p->left;
				}
				else
				{
					if (p->right == _nil)
						return p;
					p = p->right;
				}
			}
			return p;
		}

		node_pointer _find(value_type to_find)
		{
			node_pointer node = ROOT;

			while (node != _nil)
			{
				if (node->value.first == to_find.first)
					return (node);
				if (node->value.first > to_find.first)
					node = node->left;
				else
					node = node->right;
			}
			return node;
		}

		size_type	_max_size() const
		{
			return (this->_nalloc.max_size());
		}

		void 		_swap(self_type_reference x)
		{
			if (x == this)
				return ;
			node_pointer save = this->_nil;
			this->_nil = x._nil;
			x._nil = save;
		}

	};

}
