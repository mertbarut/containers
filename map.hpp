/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 14:44:43 by mbarut            #+#    #+#             */
/*   Updated: 2022/03/13 12:07:38 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MAP_HPP
# define FT_MAP_HPP

#include "utility.hpp"
#include "rbt.hpp"
#include "iterator.hpp"
#include "algorithm.hpp"
#include "debug.hpp"
#include <memory>
#include <exception>

#ifdef __DEBUG
# include <string>
# include <iostream>
#endif

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

		typedef Key															key_type;
		typedef T															mapped_type;
		typedef Compare														key_compare;
		typedef ft::pair<const key_type, mapped_type>						value_type;
		typedef Allocator													allocator_type;
		typedef typename allocator_type::reference							reference;
		typedef typename allocator_type::const_reference					const_reference;
		typedef typename allocator_type::pointer							pointer;
		typedef typename allocator_type::const_pointer						const_pointer;
		typedef typename ft::_RBT<value_type, key_compare>::iterator		iterator;
		typedef typename ft::_RBT<value_type, key_compare>::const_iterator	const_iterator;
		typedef ft::reverse_iterator<iterator>								reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
		typedef size_t														size_type;
		typedef typename ft::iterator_traits<iterator>::difference_type		difference_type;

	private:
		
		typedef map<Key, T, Compare, Allocator>								self_type;
		typedef _RBT<value_type, key_type, key_compare> 					tree_type;
		typedef __RBT_Node<value_type>										node_type;
		typedef typename Allocator::template rebind<node_type>::other		node_allocator_type;
		typedef node_type*													node_pointer;
		typedef ft::pair<iterator, iterator>								range_type;
		typedef ft::pair<const_iterator, const_iterator>					const_range_type;

	public:

		class value_compare : public binary_function<value_type, value_type, bool>
		{
		private:

			friend class map<Key, T, Compare, Allocator>;
		
		protected:

			key_compare		comp;
			value_compare(key_compare c) : comp(c) {}
			
		public:
			
			typedef bool		result_type;
			typedef value_type	first_argument_type;
			typedef value_type	second_argument_type;

			bool operator()(const value_type& a, const value_type& b) const
			{ return comp(a.first, b.first); }
			
		};

	private:

		tree_type														_rbt;
		allocator_type													_allocator;
		node_allocator_type												_node_allocator;
		value_compare													_compare;

		#ifndef _PARENT_IS_LEFT_CHILD
		# define _PARENT_IS_LEFT_CHILD									node->__parent == node->__parent->__parent->__left
		#endif

		#ifndef _IS_LEFT_CHILD
		# define _IS_LEFT_CHILD											node == node->__parent->__left
		#endif

		#ifndef _IS_RIGHT_CHILD
		# define _IS_RIGHT_CHILD										node == node->__parent->__right
		#endif

		#ifndef _MIN_NODE
		# define _MIN_NODE												_NIL_NODE->__right
		#endif

		#ifndef _MAX_NODE
		# define _MAX_NODE												_NIL_NODE->__left
		#endif

		#ifndef _NIL_NODE
		# define _NIL_NODE												_rbt._nil
		#endif

		#ifndef _ROOT_NODE
		# define _ROOT_NODE												_rbt._root
		#endif

		#ifndef _SIZE_TREE
		# define _SIZE_TREE												_rbt._n
		#endif

	public:

		explicit map(const key_compare& compare = key_compare(), const allocator_type& allocator = allocator_type())
		: _rbt(), _allocator(allocator), _compare(compare)
		{

		}

		template <typename InputIterator>
		map(InputIterator begin, InputIterator end, const key_compare& compare = key_compare(), const allocator_type& allocator = allocator_type()) : _rbt(), _allocator(allocator), _compare(compare)
		{
			_rbt._range_init(begin, end);
		}

		map(const map& other) : _rbt(), _allocator(other._allocator), _compare(other._compare)
		{
			_rbt._range_init(other.begin(), other.end());
		}

		~map()
		{
			clear();
		}

		map&						operator= (const map& rhs)
		{
			if (this == &rhs)
				return *this;
			clear();
			_rbt._insert(rhs.begin(), rhs.end());
			return *this;
		}

		bool						empty() const
		{
			return _ROOT_NODE == _NIL_NODE;
		}

		size_type					size() const
		{
			return _SIZE_TREE;
		}

		size_type					max_size() const
		{
			return _rbt._nalloc.max_size();
		}

		ft::pair<iterator, bool>	insert(const value_type& __value)
		{
			return _rbt._insert(__value);
		}

		iterator					insert(const value_type& __value, iterator i)
		{
			ft::pair<iterator, bool> result = _rbt._insert(__value, i);
		}

		void						insert(iterator first, iterator last)
		{
			for (iterator it = first; it != last; it++)
				_rbt._insert(*it);
		}

		mapped_type&				at(const Key& key)
		{
			node_pointer found = _rbt._search_for(key);
			if (found == _rbt._nil)
			{
				std::ostringstream	oss;
				oss << "map::at";
				throw (std::out_of_range(oss.str()));
			}
			return found->__value.second;
		}
		
		const mapped_type&			at(const Key& key) const
		{
			node_pointer found = _rbt._search_for(key);
			if (found == _rbt._nil)
			{
				std::ostringstream	oss;
				oss << "map::at";
				throw (std::out_of_range(oss.str()));
			}
			return found->__value.second;
		}

		mapped_type&				operator[](const key_type& key)
		{
			return (*((_rbt._insert((value_type(key, mapped_type())))).first)).second;
		}

		iterator					begin() { return iterator(this->_rbt.FIRSTNODE, this->_NIL_NODE); }
		const_iterator				begin() const { return const_iterator(this->_rbt.FIRSTNODE, this->_NIL_NODE); }
		iterator					end() { return iterator(this->_NIL_NODE, this->_NIL_NODE); }
		const_iterator				end() const { return const_iterator(this->_NIL_NODE, this->_NIL_NODE); }
		reverse_iterator			rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator		rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator			rend() { return reverse_iterator(begin()); }
		const_reverse_iterator		rend() const { return const_reverse_iterator(begin()); }

		void						clear()
		{
			while (_SIZE_TREE != 0)
				_rbt._delete(_MAX_NODE);
			#ifdef __DEBUG
			std::cout << "[debug] RBT has been cleared" << std::endl;
			#endif
		}

		size_type					erase(const key_type& key)
		{
			node_pointer delete_me_if_you_can = _rbt._search_for(key);
			_rbt._delete(delete_me_if_you_can);
			if (delete_me_if_you_can == _NIL_NODE)
				return 1;
			else
			 	return 0;
		}

		void						erase(iterator pos)
		{
			_rbt._delete(_rbt._search_for(extract_key(*pos)));
		}

		void						erase(iterator first, iterator last)
		{
			for (iterator it = first; it != last; it++)
				erase(it);
		}

		allocator_type				get_allocator() const
		{
			return this->_allocator;
		}

		void						swap(map& other)
		{
			_rbt._swap(other._rbt);
		}

		iterator					find(const key_type& key)
		{
			return iterator(_rbt._search_for(key), _NIL_NODE);
		}

		const_iterator				find(const key_type& key) const
		{
			return const_iterator(_rbt._search_for(key), _NIL_NODE);
		}

		size_type					count(const key_type& key) const
		{
			if (find(key) != end())
				return 1;
			return 0;
		}

		iterator					lower_bound(const key_type& key)
		{
			iterator	i;
			for (i = begin(); i != end(); ++i)
				if (!(_compare.comp(i->first, key)))
					break ;
			return i;
		}

		const_iterator				lower_bound(const key_type& key) const
		{
			const_iterator	i;
			for (i = begin(); i != end(); ++i)
				if (!(_compare.comp(i->first, key)))
					break ;
			return i;
		}

		iterator					upper_bound(const key_type& key)
		{
			iterator		i;
			for (i = begin(); i != end(); ++i)
				if (_compare.comp(key, i->first))
					break ;
			return i;
		}

		const_iterator				upper_bound(const key_type& k) const
		{
			const_iterator	i;
			for (i = begin(); i != end(); ++i)
				if (_compare.comp(k, i->first))
					break ;
			return (i);
		}

		range_type					equal_range(const key_type& key)
		{
			return ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
		}

		const_range_type			equal_range(const key_type& key) const
		{
			return ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
		}

		key_compare					key_comp() const
		{
			return this->_compare.comp;
		}

		value_compare				value_comp() const
		{
			return this->_compare;
		}

		friend void					swap(map& map1, map& map2)
		{ map1._rbt._swap(map2._rbt); }

		friend bool					operator==(const map& lhs, const map& rhs)
		{
			if (lhs.size() != rhs.size())
				return false;
			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		}

		friend bool					operator!=(const map& lhs, const map& rhs)
		{ return !(lhs == rhs); }

		friend bool					operator< (const map& lhs, const map& rhs)
		{
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

		friend bool					operator> (const map& lhs, const map& rhs)
		{ return !(lhs < rhs) && !(rhs == lhs); }

		friend bool					operator<=(const map& lhs, const map& rhs)
		{ return !(lhs > rhs); }

		friend bool					operator>=(const map& lhs, const map& rhs)
		{ return !(lhs < rhs); }

		#ifdef __DEBUG
		
		void	print() const
		{
			std::cout << "Node-Left-Right: root->";
			_rbt._traverseNLR(_ROOT_NODE);
			std::cout << "nil\n";
			std::cout << "Left-Node-Right: root->";
			_rbt._traverseLNR(_ROOT_NODE);
			std::cout << "nil\n";
			std::cout << "Left-Right-Node: root->";
			_rbt._traverseLRN(_ROOT_NODE);
			std::cout << "nil\n";
		}

		#endif
		
	};

	#undef _PARENT_IS_LEFT_CHILD
	#undef _IS_RIGHT_CHILD
	#undef _IS_LEFT_CHILD
	#undef _MIN_NODE
	#undef _MAX_NODE
	#undef _NIL_NODE
	#undef _ROOT_NODE
	#undef _SIZE_TREE

}

#endif