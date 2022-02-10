/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rbt.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:16:46 by mbarut            #+#    #+#             */
/*   Updated: 2022/02/10 19:27:21 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_iterator.hpp"
//#include "ft_pair.hpp"
#include "ft_util.hpp"
//#include "ft_iterator.hpp"
//#include "ft_vector.hpp"
#include <cstddef>
#include <memory>

namespace ft 
{

	enum __RBT_Node_color
	{
		_S_black = false,
		_S_red = true,
	};

	template <typename _T>
	struct __RBT_Node
	{

	public:

		typedef _T						value_type;
		typedef __RBT_Node<value_type>	node_type;

		value_type			__value;
		__RBT_Node*			__parent;
		__RBT_Node*			__left;
		__RBT_Node*			__right;
		__RBT_Node_color	__color;

	private:

		__RBT_Node () : __value(), __parent(u_nullptr), __left(u_nullptr), __right(u_nullptr), __color(_S_red) {}
		
	public:

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

		//static const __RBT_Node* _get_min(const __RBT_Node* node, const __RBT_Node* nil)
		//{
		//	for (; node->__left != nil; node = node->__left) {}
		//		return node;
		//}

		//static const __RBT_Node* _get_max(const __RBT_Node* node, const __RBT_Node* nil)
		//{
		//	for (; node->__right != nil; node = node->__right) {}
		//		return node;
		//}

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
		class T,
		class Compare = ft::less<T>,
		class Node = ft::__RBT_Node<T>,
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
		node_pointer									_root;
		node_allocator									_nalloc;
		compare_type									_compare;

		//#ifndef ROOT
		//# define ROOT									_nil->__parent
		//#endif

		#ifndef FIRSTNODE
		# define FIRSTNODE								_nil->__left
		#endif

		//#ifndef NILNODE
		//# define NILNODE								_nil->__right
		//#endif

		//#ifndef LASTNODE
		//# define LASTNODE								_nil
		//#endif

		//#ifndef TREESIZE
		//# define TREESIZE								_nil->__value.first
		//#endif

		/* ctor 1 */
		_RBT(const node_allocator& custom = node_allocator()) : _nalloc(custom)
		{
			_nil = _nalloc.allocate(1);
			_nalloc.construct(_nil, node_type(_nil, _nil, _nil, _S_black));
			_root = _nil;
		}

		/* dtor */
		~_RBT()
		{
			_nalloc.destroy(_nil);
			_nalloc.deallocate(_nil, 1);	
		}

		//void		_make_related(node_pointer node1, node_pointer node2)
		//{
		//	if (node1->__parent == _nil)
		//		ROOT = node2;
		//	else if (node1->__parent->__left == node1)
		//		node1->__parent->__left = node2;
		//	else
		//		node1->__parent->__left = node2;
		//	node2->__parent = node1->__parent;
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
		//		if (node->__value.first == to_find.first)
		//			return (node);
		//		if (node->__value.first > to_find.first)
		//			node = node->__left;
		//		else
		//			node = node->__right;
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
