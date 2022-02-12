/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rbt.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:16:46 by mbarut            #+#    #+#             */
/*   Updated: 2022/02/12 22:36:12 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_iterator.hpp"
#include "ft_util.hpp"
#include <cstddef>
#include <memory>
#include <iostream>

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
		class Compare = ft::less<T>,
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
		# define _MIN_NODE										_NIL_NODE->__right
		#endif

		#ifndef _MAX_NODE
		# define _MAX_NODE										_NIL_NODE->__left
		#endif

	public:

		typedef _RBT											self_type;
		typedef _RBT&											self_type_reference;
		typedef T												value_type;
		typedef Node											node_type;
		typedef Node*											node_pointer;
		typedef Allocator_T										allocator_type;
		typedef Allocator_Node									node_allocator;
		typedef ft::_RBT_iterator<Node, Compare>				iterator;
		typedef ft::_RBT_const_iterator<Node, Compare>			const_iterator;
		typedef size_t											size_type;
		typedef Compare											compare_type;

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
