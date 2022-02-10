/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 14:44:43 by mbarut            #+#    #+#             */
/*   Updated: 2022/02/10 12:08:58 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

//#include "ft_pair.hpp"
#include "ft_util.hpp"
#include "ft_rbt.hpp"
#include "ft_iterator.hpp"
#include "ft_vector.hpp"

#include <memory>

#include <string>

namespace ft
{
	template <
		class Key, class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator< ft::pair<const Key, T> >
		>
	class map
	{

	public:

		typedef map<Key, T, Compare, Allocator>								self_type;
		typedef Key															key_type;
		typedef T															mapped_type;
		typedef Compare														key_compare;
		typedef Allocator													allocator_type;
		typedef ft::pair<const key_type, mapped_type>						value_type;
		typedef typename allocator_type::reference							reference;
		typedef typename allocator_type::const_reference					const_reference;
		typedef typename allocator_type::pointer							pointer;
		typedef typename allocator_type::const_pointer						const_pointer;
		typedef typename allocator_type::size_type							size_type;	
		typedef typename ft::_RBT<value_type, key_compare>::iterator		iterator;
		typedef typename ft::_RBT<value_type, key_compare>::const_iterator	const_iterator;
		typedef ft::reverse_iterator<iterator>								reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type		difference_type;

		class __value_compare : public binary_function<value_type, value_type, bool>
		{
		private:

		friend class map<Key, T, Compare, Allocator>;
		
		protected:

			key_compare		comp;
			__value_compare(key_compare c) : comp(c) {}
			
		public:
			
			typedef bool		result_type;
			typedef value_type	first_argument_type;
			typedef value_type	second_argument_type;

			bool operator()(const value_type& a, const value_type& b) const
			{ return comp(a.first, b.first); }
			
		};

	private:

		typedef _RBT<value_type, key_compare> 							tree_type;
		typedef __RBT_Node<value_type>									node_type;
		typedef typename Allocator::template rebind<node_type>::other	node_allocator_type;
		typedef node_type*												node_pointer;

		tree_type														_rbt;
		allocator_type													_allocator;
		node_allocator_type												_node_allocator;
		key_compare														_compare;

		#ifndef _PARENT_IS_LEFT_CHILD
		# define _PARENT_IS_LEFT_CHILD									node->__parent == node->__parent->__parent->__left
		#endif

		#ifndef _IS_LEFT_CHILD
		# define _IS_LEFT_CHILD											node->__parent == node->__parent->__parent->__left
		#endif

		#ifndef _IS_RIGHT_CHILD
		# define _IS_RIGHT_CHILD										node->__parent == node->__parent->__parent->__left
		#endif

		node_pointer	_RBT_create_node(const value_type& __value)
		{
			allocator_type	map_allocator(_node_allocator);
			node_type*		node = _node_allocator.allocate(1);
			node->__color = _S_red;
			node->__parent = _rbt._nil;
			node->__right = _rbt._nil;
			node->__left = _rbt._nil;
			map_allocator.construct(&(node->__value), __value);
			return node;
		}

		void		_RBT_destroy_node(node_pointer node)
		{
			_node_allocator.destroy(node);
			_node_allocator.deallocate(node, 1);
		}

		//void		_RBT_init_nil()
		//{
		//	_rbt._nil = _node_allocator.allocate(1);
		//	_rbt._nil->__color = _S_red;
		//	_rbt._nil->__parent = _rbt._nil;
		//	_rbt._nil->__right = _rbt._nil;
		//	_rbt._nil->__left = _rbt._nil;
		//	_rbt.ROOT = _rbt._nil;
		//}

		void		_RBT_lrotate(node_pointer node)
		{
			if (node == _rbt._nil || node->__right == _rbt._nil)
				return ;
			node_pointer	tmp = node->__right;
			if ((node->__right = tmp->__left) != _rbt._nil)
				node->__right->__parent = node;
			if ((tmp->__parent = node->__parent) == _rbt._nil)
				_rbt.ROOT = tmp;
			else if (tmp->__parent->__left == node)
				tmp->__parent->__left = tmp;
			else
				tmp->__parent->__right = tmp;
			tmp->__left = node;
			node->__parent = tmp;
		}

		void		_RBT_rrotate(node_pointer node)
		{
			if (node == _rbt._nil || node->__left == _rbt._nil)
				return ;
			node_pointer	tmp = node->__left;
			if ((node->__left = tmp->__right) != _rbt._nil)
				node->__left->__parent = node;
			if ((tmp->__parent = node->__parent) == _rbt._nil)
				_rbt.ROOT = tmp;
			else if (tmp->__parent->__right == node)
				tmp->__parent->__right = tmp;
			else
				tmp->__parent->__left = tmp;
			tmp->__right = node;
			node->__parent = tmp;
		}

		node_pointer	_RBT_search_for(const value_type& __value) const
		{
			node_pointer i = _rbt.ROOT;
			for (; i != _rbt._nil && i->__value.first != __value.first;
				_compare(__value.first, i->___value.first) ? i = i->__left : i = i->__right) { }
			return i;
		}

		void			_RBT_flip___color(node_pointer& node, node_pointer aunt)
		{
			aunt->__color = _S_black;
			node->__parent->__color = _S_black;
			node->__parent->__parent->__color = _S_red;
			node = node->__parent->__parent;
		}

		void			_RBT_insert_rebalance(node_pointer node)
		{
			node_pointer	aunt;
			
			while (node != _rbt.ROOT && node->__parent->__color == _S_red)
			{
				if (_PARENT_IS_LEFT_CHILD)
				{
					aunt = node->__parent->__parent->__right;
					if (aunt->__color == _S_red)
						_RBT_flip___color(node, aunt);
					else
					{
						if (_IS_RIGHT_CHILD)
						{
							node = node->__parent;
							_RBT_lrotate(node);
						}
						node->__parent->__color = _S_black;
						node->__parent->__parent->__color = _S_red;
						_RBT_rrotate(node->__parent->__parent);
					}
				}
				else
				{
					aunt = node->__parent->__parent->__left;
					if (aunt->__color == _S_red)
						_RBT_flip___color(node, aunt);
					else
					{
						if (_IS_LEFT_CHILD)
						{
							node = node->__parent;
							_RBT_rrotate(node);
						}
						node->__parent->__color = _S_black;
						node->__parent->__parent->__color = _S_red;
						_RBT_lrotate(node->__parent->__parent);
					}
				}
			}
			_rbt.ROOT->__color = _S_black;
		}

		void			_RBT_check_if_next(node_pointer& found, const  value_type& __value, iterator i)
		{
			if (i.base() && i.base() != _rbt._nil && _compare(i.base()->__value.first, __value.first))
			{
				iterator	next = i;
				++next;
				if ((i.base() == _rbt._nil->__left || (next.base() != _rbt._nil && _compare(__value.first, next.base()->__value.first))) && i.base()->__right == _rbt._nil)
					found = i.base(); 
			}
		}

		node_pointer	_RBT_find_whose_child(const value_type& __value)
		{
			node_pointer p = _rbt.ROOT;

			for (; p != _rbt._nil && p->__value.first != __value.first;)
			{
				if (_compare(__value.first, p->__value.first))
				{
					if (p->__left == _rbt._nil)
						return p;
					p = p->__left;
				}
				else
				{
					if (p->__right == _rbt._nil)
						return p;
					p = p->__right;
				}
			}
			return p;
		}

		ft::pair<iterator, bool>	_RBT_insert(const value_type& __value, iterator i = iterator())
		{
			node_pointer	found = NULL;
			ft::pair<iterator, bool> result;
			
			_RBT_check_if_next(found, __value, i);
			if (found == NULL)
				found = _RBT_find_whose_child(__value);
			if (found->__value.first == __value.first)
			{
				result.first = iterator(found, _rbt._nil);
				result.second = false;
			}
			else
			{
				node_pointer	newnode = _RBT_create_node(__value);
				if (found == _rbt._nil)
				{
					_rbt.ROOT = newnode;
					_rbt._nil->__right = newnode;
					_rbt._nil->__left = newnode;
				}
				else if (_compare(__value.first, found->__value.first))
				{
					found->__left = newnode;
					if (_rbt._nil->__right == found)
						_rbt._nil->__right = newnode;
				}
				else
				{
					found->__right = newnode;
					if (_rbt._nil->__left == found)
						_rbt._nil->__left = newnode;
				}
				newnode->__parent = found;
				result.first = iterator(newnode, _rbt._nil);
				result.second = true;
				++_rbt._n;

				_RBT_insert_rebalance(newnode);
				_rbt._nil->__parent = _rbt._nil;
			}
			if (result.second == true)
				++this->_rbt._n;
			return result;
		}

		template<class InputIterator>
		void	_RBT_range_init(InputIterator begin, InputIterator end)
		{
			//_RBT_init_nil();
			while (begin != end)
				_RBT_insert(*begin++);
		}

	public:

		/* ctor 1 */
		explicit map(const key_compare& compare = key_compare(), const allocator_type& allocator = allocator_type())
		: _rbt(), _allocator(allocator), _compare(compare)
		{
			//ft::pair<const std::string, int> pair1("one", 1);
			//_RBT_create_node(pair1);
		}

		/* ctor 2 */
		template <typename InputIterator>
		map(InputIterator begin, InputIterator end, const key_compare& compare = key_compare(), const allocator_type& allocator = allocator_type()) : _rbt(), _allocator(allocator), _compare(compare)
		{
			_RBT_range_init(begin, end);
		}

		/* copy ctor */
		map(const map& other) : _rbt(), _allocator(other._allocator), _compare(other._compare)
		{
			_RBT_range_init(other.begin(), other.end());
		}

		/* assignment operator overload */

		/* dtor */

		bool					empty() const
		{
			return _rbt.ROOT = _rbt._nil;
		}

		//size_type				size() const
		//{
		//	return _rbt._nil->__value.first;
		//}

		size_type				max_size() const
		{
			return _rbt.max_size();
		}

		ft::pair<iterator, bool>	insert(const value_type& __value)
		{
			return _RBT_insert(__value);
		}

		iterator					insert(const value_type& __value, iterator i)
		{
			ft::pair<iterator, bool> result = _RBT_insert(__value, i);
		}

		mapped_type&		operator[](const key_type& key)
		{
			return (*((this->insert(value_type(key, mapped_type()))).first)).second;
		}

		/* iterators */
		iterator			begin() { return iterator(this->_rbt.FIRSTNODE, this->_rbt._nil); }
		const_iterator		begin() const { return const_iterator(this->_rbt.FIRSTNODE, this->_rbt._nil); }
		iterator			end() { return iterator(this->_rbt._nil, this->_rbt._nil); }
		const_iterator		end() const { return const_iterator(this->_rbt._nil, this->_rbt._nil); }
		iterator			rbegin() { return reverse_iterator(end()); }
		const_iterator		rbegin() const { return const_reverse_iterator(end()); }
		iterator			rend() { return reverse_iterator(begin()); }
		const_iterator		rend() const { return const_reverse_iterator(begin()); }

		//void	clear()
		//{
		//	//
		//}

		allocator_type get_allocator() const
		{
			return this->_allocator();
		}

		//void		swap(map_type& other)
		//{
		//	size_type	n = this->_n;
		//	pointer		nil = this->_nil;
		//	pointer		root = this->_root;
//
		//	this->_n = other._n;
		//	this->_nil = other._nil;
		//	this->_root = other._root;
//
		//	other._n = n;
		//	other._nil = nil;
		//	other._root = root;
		//}

		//key_compare		key_comp() const
		//{
		//	return (this->_compare.comp);
		//}

		//__value_compare	__value_comp() const
		//{
		//	return (this->_compare);
		//}

		//iterator			find(const key_type& key)
		//{
		//	return iterator(_M_get___value_by_key(key), _nil);
		//}
//
		//const_iterator		find(const key_type& key) const
		//{
		//	return const_iterator(_M_get___value_by_key(key), _nil);
		//}
//
		//size_type			count(const key_type& key) const
		//{
		//	if (find(key) != end())
		//		return 1;
		//	return 0;
		//}
//
		//iterator		lower_bound(const key_type& key)
		//{
		//	iterator		i;
		//	for (i = begin(); i != end(); ++i)
		//		if (!(_compare.comp(i->first, key)))
		//			break ;
		//	return i;
		//}
//
		//const_iterator	lower_bound(const key_type& key) const
		//{
		//	const_iterator	i;
		//	for (i = begin(); i != end(); ++i)
		//		if (!(_compare.comp(i->first, key)))
		//			break ;
		//	return i;
		//}
//
		//iterator		upper_bound(const key_type& key)
		//{
		//	iterator		i;
		//	for (i = begin(); i != end(); ++i)
		//		if (_compare.comp(key, i->first))
		//			break ;
		//	return i;
		//}
//
		//const_iterator	upper_bound(const key_type& k) const
		//{
		//	const_iterator	i;
		//	for (i = begin(); i != end(); ++i)
		//		if (_compare.comp(k, i->first))
		//			break ;
		//	return (i);
		//}

		//ft::pair<iterator, iterator>				equal_range(const key_type& key)
		//{
		//	return ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
		//}
//
		//ft::pair<const_iterator, const_iterator>	equal_range(const key_type& key) const
		//{
		//	return ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
		//}
//
		friend bool	operator==(const map& lhs, const map& rhs)
		{
			if (lhs.size() != rhs.size())
				return (false);
			return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}

		friend bool	operator!=(const map& lhs, const map& rhs) { return !(lhs == rhs); }

		friend bool	operator< (const map& lhs, const map& rhs)
		{
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}

		friend bool	operator> (const map& lhs, const map& rhs)
		{	return (rhs < lhs);		}

		friend bool	operator<=(const map& lhs, const map& rhs)
		{ return !(rhs < lhs); }
		
		friend bool	operator>=(const map& lhs, const map& rhs)
		{ return !(lhs < rhs); }

		void	swap(map& map1, map& map2)
		{ map1.swap(map2); }
		
		//void traverseLNR(BST_node *root)
		//{
		//	if (!root)
		//		return ;
		//	traverseLNR(root->getLeftNode());
		//	std::cout << root->getData() << " ";
		//	traverseLNR(root->getRightNode());
		//}
		//
		//void traverseNLR(BST_node *root)
		//{
		//	if (!root)
		//		return ;
		//	std::cout << root->getData() << " ";
		//	traverseNLR(root->getLeftNode());
		//	traverseNLR(root->getRightNode());
		//}
		//
		//void traverseLRN(BST_node *root)
		//{
		//	if (!root)
		//		return ;
		//	traverseLRN(root->getLeftNode());
		//	traverseLRN(root->getRightNode());
		//	std::cout << root->getData() << " ";
		//}

	};
	
}
