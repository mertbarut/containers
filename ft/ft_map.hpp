/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 14:44:43 by mbarut            #+#    #+#             */
/*   Updated: 2022/02/09 00:55:43 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_iterator_base_types.hpp"
#include "ft_pair.hpp"
#include "ft_util.hpp"
#include "ft_base.hpp"
#include "ft_iterator.hpp"
#include "ft_vector.hpp"
#include <memory>

namespace ft
{
	template <
		class Key, class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator< std::pair<const Key, T> >
		>
	class map
	{

	public:

		typedef map<Key, T, Compare, Allocator>								self_type;
		typedef Key															key_type;
		typedef T															mapped_type;
		typedef Compare														key_compare;
		typedef Allocator													allocator_type;
		typedef std::pair<key_type, mapped_type>							value_type;
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

		typedef _RBT<value_type, key_compare> 							tree_type;
		typedef typename Allocator::template rebind<tree_type>::other	node_allocator_type;

		tree_type														_rbt;
		allocator_type													_allocator;
		key_compare														_compare;

	public:

		/* ctor 1 */
		explicit map (const key_compare& compare = key_compare(), const allocator_type& allocator = allocator_type())
		:  _rbt(), _allocator(allocator), _compare(compare) {}

		/* ctor 2 */

		/* copy ctor */

		/* assignment operator overload */

		/* dtor */

		bool					empty() const
		{
			return _rbt.ROOT = _rbt._nil;
		}

		//size_type				size() const
		//{
		//	return _rbt._nil->value.first;
		//}

		size_type				max_size() const
		{
			return _rbt.max_size();
		}

		ft::pair<iterator, bool>	insert(const value_type& value)
		{
			return _rbt._insert(value);
		}

		iterator					insert(iterator i, const value_type& value)
		{
			ft::pair<iterator, bool> result = _insert(value, i);
		}

		//mapped_type&		operator[](const key_type& key)
		//{
		//	return (*(this->insert(value_type(key, mapped_type())).first)).second;
		//}

		/* iterators */
		iterator			begin() { return iterator(this->_rbt._nil->left, this->_rbt._nil); }
		const_iterator		begin() const { return const_iterator(this->_rbt._nil->left, this->_rbt._nil); }
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

		//value_compare	value_comp() const
		//{
		//	return (this->_compare);
		//}

		//iterator			find(const key_type& key)
		//{
		//	return iterator(_M_get_value_by_key(key), _nil);
		//}
//
		//const_iterator		find(const key_type& key) const
		//{
		//	return const_iterator(_M_get_value_by_key(key), _nil);
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
