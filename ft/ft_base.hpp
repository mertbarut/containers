/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:16:46 by mbarut            #+#    #+#             */
/*   Updated: 2022/02/08 11:35:26 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_iterator_base_types.hpp"
#include "ft_pair.hpp"
#include "ft_util.hpp"
//#include "ft_iterator.hpp"
//#include "ft_vector.hpp"
#include <memory>

namespace ft 
{
	template <class _Allocator>
	struct	_RBTree
	{

	public:

		typedef _RBTree<_Allocator>								tree_node;
		typedef typename _Allocator::value_type					value_type;
		typedef typename _Allocator::difference_type			difference_type;
		typedef typename _Allocator::pointer					pointer;
		typedef typename _Allocator::reference					reference;
	//public:

		value_type				_value;
		tree_node*				_parent;
		tree_node*				_left;
		tree_node*				_right;
		size_t					_level;
		size_t					_index;
		bool					_is_red;

		/* ctor 1 */
		_RBTree() : _value( 0 ), _parent(NULL), _left(NULL), _right(NULL), _level(0), _index(0), _is_red(false)
		{
			
		}

		/* ctor 2 */
		_RBTree(tree_node* tree, const value_type& value) : _value(value), _parent(tree), _left(tree), _right(tree), _level(0), _index(0), _is_red(false)
		{
			
		}

		/* copy ctor */

		_RBTree(const _RBTree& node) : _value(node._value), _parent(node._parent), _left(node._left), _right(node._right), _level(node._level), _index(node._index), _is_red(node._is_red)
		{
			
		}

		/* assignment operator overload */
		_RBTree&		operator=(const _RBTree& rhs)
		{
			if (this == &rhs)
				return *this;
			this->_value = rhs._value;
			this->_parent = rhs._parent;
			this->_left = rhs._left;
			this->_right = rhs._right;
			this->_is_red = rhs._is_red;
			return *this;
		}
		
		/* dtor */
		~_RBTree()
		{
			
		}

		/* getters */
		value_type get_value() const { return this->_value; }

		value_type* get_left() const { return this->_left; }

		value_type* get_right() const { return this->_right; }
		
		size_t	get_level() const { return this->_level; }
		
		size_t	get_index() const { return this->_index; }

		template <typename Node>
		static Node	get_min(Node node, const tree_node* nil)
		{
			if (node == nil)
				return node;
			for (; node->_left != nil; node = node->_left) {}
				return node;
		}

		template <typename Node>
		static Node	get_max(Node node, const tree_node* nil)
		{
			if (node == nil)
				return node;
			for (; node->_left != nil; node = node->_left) {}
				return node;
		}

		template <typename Node>
		static void	next(Node& node, const tree_node* nil)
		{
			if (node->right != nil)
				node = get_min(node->_right, nil);
			else if (node == nil || nil->_left == node)
				node = node->_right;
			else
				for (; node->_parent != nil && node == node->_parent->_right; node = node->_parent) {}
				node = node->_parent;
		}

		template <typename Node>
		static void	prev(Node& node, const tree_node* nil)
		{
			if (node->_left != nil)
				node = get_max(node->_left, nil);
			else if (node == nil || nil->_right == node)
				node = node->_left;
			else
				for (; node->_parent != nil && node == node->_parent->_left; node = node->_parent) {}
				node = node->_parent;
		}

	};

}

#pragma endregion