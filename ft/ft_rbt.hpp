/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rbt.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:16:46 by mbarut            #+#    #+#             */
/*   Updated: 2022/02/09 23:49:55 by mbarut           ###   ########.fr       */
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

	enum _RBT_color
	{
		_S_black = false,
		_S_red = true,
	};

	template <typename _T>
	struct _RBT_Node
	{

	public:

		typedef _T						value_type;
		typedef _RBT_Node<value_type>	link_type;

		value_type	value;
		_RBT_Node*	parent;
		_RBT_Node*	left;
		_RBT_Node*	right;
		_RBT_color	color;

		_RBT_Node () : value(), parent(u_nullptr), left(u_nullptr), right(u_nullptr), color(_S_red) {}
		_RBT_Node (_RBT_Node* parent = u_nullptr, _RBT_Node* left = u_nullptr, _RBT_Node* right = u_nullptr, _RBT_color color = _S_red) : value(), parent(parent), left(left), right(right), color(color) {}
		_RBT_Node (const value_type& value, _RBT_Node* parent = u_nullptr, _RBT_Node* left = u_nullptr, _RBT_Node* right = u_nullptr, _RBT_color color = _S_red) : value(value), parent(parent), left(left), right(right), color(color) {}
		_RBT_Node (const _RBT_Node& node) : value(node.value), parent(node.parent), left(node.left), right(node.right), color(node.color) {}
		virtual ~_RBT_Node() {}

		_RBT_Node& operator= (const _RBT_Node& rhs)
		{
			if (rhs == *this)
				return (*this);
			this->value = rhs.value;
			this->parent = rhs.parent;
			this->left = rhs.left;
			this->right = rhs.right;
			this->color = rhs.color;
			return (*this);
		}

		bool operator==(const _RBT_Node& rhs)
		{
			if (value == rhs.value)
				return (true);
			return (false);
		}

		static _RBT_Node* _get_min(_RBT_Node* node, const _RBT_Node* nil)
		{
			for (; node->left != nil; node = node->left) {}
				return node;
		}

		static _RBT_Node* _get_max(_RBT_Node* node, const _RBT_Node* nil)
		{
			for (; node->right != nil; node = node->right) {}
				return node;
		}

		static const _RBT_Node* _get_min(const _RBT_Node* node, const _RBT_Node* nil)
		{
			for (; node->left != nil; node = node->left) {}
				return node;
		}

		static const _RBT_Node* _get_max(const _RBT_Node* node, const _RBT_Node* nil)
		{
			for (; node->right != nil; node = node->right) {}
				return node;
		}

		template <typename Node>
		static void	_increment(Node& node, const _RBT_Node* nil)
		{
			if (node->right != nil)
				node = _get_min(node->right, nil);
			else if (node == nil || nil->left == node)
				node = node->right;
			else
				for (; node->parent != nil && node == node->parent->right; node = node->parent) {}
				node = node->parent;
		}

		template <typename Node>
		static void	_decrement(Node& node, const _RBT_Node* nil)
		{
			if (node->left != nil)
				node = _get_max(node->left, nil);
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

		#ifndef NILNODE
		# define NILNODE								_nil->right
		#endif

		#ifndef LASTNODE
		# define LASTNODE								_nil
		#endif

		//#ifndef TREESIZE
		//# define TREESIZE								_nil->value.first
		//#endif

		/* ctor 1 */
		_RBT(const node_allocator& custom = node_allocator()) : _nalloc(custom)
		{
			_nil = _nalloc.allocate(1);
			_nalloc.construct(_nil, node_type(_nil, _nil, _nil));
			ROOT = _nil;
		}

		/* dtor */
		~_RBT()
		{
			_nalloc.destroy(_nil);
			_nalloc.deallocate(_nil, 1);	
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

		//node_pointer _find(value_type to_find)
		//{
		//	node_pointer node = ROOT;
//
		//	while (node != _nil)
		//	{
		//		if (node->value.first == to_find.first)
		//			return (node);
		//		if (node->value.first > to_find.first)
		//			node = node->left;
		//		else
		//			node = node->right;
		//	}
		//	return node;
		//}

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
