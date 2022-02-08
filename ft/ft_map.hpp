/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 14:44:43 by mbarut            #+#    #+#             */
/*   Updated: 2022/02/08 12:09:36 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator< ft::pair<const Key, T> >
		>
	class map
	{

	public:

		typedef _RBTree<Allocator> 										tree_node;
		typedef map<Key, T, Compare, Allocator>							map_type;
		typedef Key														key_type;
		typedef T														mapped_type;
		typedef Compare													key_compare;
		typedef Allocator												allocator_type;
		typedef ft::pair<const key_type, mapped_type>					value_type;
		typedef typename Allocator::reference							reference;
		typedef typename Allocator::const_reference						const_reference;
		typedef typename Allocator::pointer								pointer;
		typedef typename Allocator::const_pointer						const_pointer;
		typedef typename Allocator::difference_type						difference_type;
		typedef typename Allocator::size_type							size_type;	
		typedef ft::bidirectional_iterator<Allocator>					iterator;
		typedef ft::bidirectional_iterator<Allocator>					const_iterator;
		typedef ft::reverse_iterator<iterator>							reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;

		class value_compare : public binary_function<value_type, value_type, bool>
		{
		private:

		friend class map;
		
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

		typedef typename Allocator::template rebind<tree_node>::other	node_allocator_type;
		typedef ft::bidirectional_iterator_tag							iterator_catogory;

		node_allocator_type												_allocator;
		value_compare													_compare;
		tree_node*														_root;
		tree_node*														_nil;
		size_type														_n;

		tree_node*	_M_create(const value_type& val)
		{
			allocator_type	data_alloc(_allocator);
			tree_node*	node = _allocator.allocate(1);
			node->_is_red = true;
			node->_parent = NULL;
			node->_right = NULL;
			node->_left = NULL;
			_allocator.construct(&(node->data), val);
			return (node);
		}

		void		_M_destroy(tree_node* node)
		{
			_allocator.destroy(node);
			_allocator.deallocate(node, 1);
		}

		void		_M_init()
		{
			_nil = _allocator.allocate(1);
			_nil->_is_red = false;
			_nil->_parent = _nil;
			_nil->_right = _nil;
			_nil->_left = _nil;
			_root = _nil;
		}

		void		_M_lrotate(tree_node* node)
		{
			if (node == _nil || node->right == _nil)
				return ;
			tree_node*	tmp = node->_right;
			if ((node->_right = tmp->_left) != _nil)
				node->_right->_parent = node;
			if ((tmp->parent = node->_parent) == _nil)
				_root = tmp;
			else if (tmp->_parent->_left == node)
				tmp->_parent->_left = tmp;
			else
				tmp->_parent->_right = tmp;
			tmp->_left = node;
			node->_parent = tmp;
		}

		void		_M_rrotate(tree_node* node)
		{
			if (node == _nil || node->left == _nil)
				return ;
			tree_node*	tmp = node->_left;
			if ((node->_left = tmp->_right) != _nil)
				node->_left->_parent = node;
			if ((tmp->parent = node->_parent) == _nil)
				_root = tmp;
			else if (tmp->_parent->_right == node)
				tmp->_parent->_right = tmp;
			else
				tmp->_parent->_left = tmp;
			tmp->_right = node;
			node->_parent = tmp;
		}

		tree_node*	_M_get_value_by_key(const key_type& key) const
		{
			tree_node* i = _root;
			for (; i != _nil && i->_value.first != key;
				_compare.comp(key, i->_value.first) ? i = i->_left : i = i->right) { }
			return i;
		}

		tree_node*		_M_find_whose_child(const value_type& value)
		{
			tree_node* i = _root;
			for (; i != _nil && i->_value.first != value.first;)
			{
				if (_compare(value, i->_value))
				{
					if (i->_left == _nil)
						return (i);
					i = i->_left;
				}
				else
				{
					if (i->_right == _nil)
						return (i);
					i = i->_right;
				}
			}
			return i;
		}

		//void		_M_make_related(tree_node *node1, tree_node *node2)
		//{
		//	if (node1->_parent == _nil)
		//		_root = node2;
		//	else if (node1->_parent->_left == node1)
		//		node1->_parent->_left = node2;
		//	else
		//		node1->_parent->_left = node2;
		//	node2->_parent = node1->_parent;
		//}

		template<class InputIterator>
		void	_M_range_init(InputIterator begin, InputIterator end)
		{
			_M_init();
			while (begin != end)
				_M_insert(*begin++);
		}

		void						_M_check_if_next(tree_node*&	found, const value_type& value, iterator i)
		{
			if (i.base() && i.base() != _nil && _compare(*i, value))
			{
				iterator	next = i;
				++next;
				if ((i.base() == _nil->_left || (next.base() != _nil && _compare(value, *next))) && i.base()->_right == _nil)
					found = i.base(); 
			}
		}

		void		_M_flip_color(tree_node*& node, tree_node* aunt)
		{
			aunt->_is_red = false;
			node->_parent->_is_red = false;
			node->_parent->_parent->_is_red = true;
			node = node->_parent->_parent;
		}

		void		_M_fix_violations(tree_node* node)
		{
			tree_node*	aunt;
			
			while (node != _root && node->_parent->_is_red)
				if (node->_parent == node->parent->parent->left)
				{
					aunt = node->parent->parent->right;
					if (aunt->_is_red)
						_map_insert_fix_recolor(node, aunt);
					else
					{
						if (node == node->_parent->_right)
						{
							node = node->_parent;
							_M_lrotate(node);
						}
						node->_parent->_is_red = false;
						node->_parent->_parent->_is_red = true;
						_M_rrotate(node->_parent->_parent);
					}
				}
				else
				{
					aunt = node->parent->parent->left;
					if (aunt->_is_red)
						_map_insert_fix_recolor(node, aunt);
					else
					{
						if (node == node->_parent->_left)
						{
							node = node->_parent;
							_M_rright(node);
						}
						node->_parent->_is_red = false;
						node->_parent->_parent->_is_red = true;
						_M_lrotate(node->_parent->_parent);
					}
				}
			_root->_is_red = false;
		}

		ft::pair<iterator, bool>	_M_insert(const value_type& value, iterator i = iterator())
		{
			tree_node*	found = NULL;
			ft::pair<iterator, bool> result;
			
			_M_check_if_next(found, value, i);
			if (found == NULL)
				found = _M_find_whose_child(value);
			if (found->_value.first == value.first)
			{
				result.first = iterator(found, _nil);
				result.second = false;
			}
			else
			{
				tree_node*	newnode = _M_create(value);
				if (found == _nil)
				{
					_root = newnode;
					_nil->_right = newnode;
					_nil->_left = newnode;
				}
				else if (_compare(value, found->_value))
				{
					found->_left = newnode;
					if (_nil->_right == found)
						_nil->_right = newnode;
				}
				else
				{
					found->_right = newnode;
					if (_nil->_left == found)
						_nil->_left = newnode;
				}
				newnode->_parent = found;
				result.first = iterator(newnode, _nil);
				result.second = true;
				++_n;

				_M_fix_violations(newnode);
				_nil->_parent = _nil;
			}
			return result;
		}

	public:

		/* ctor 1 */
		explicit map(const key_compare& compare = key_compare(), const allocator_type& allocator = allocator_type()) : _allocator(allocator), _compare(compare),  _n(0) 
		{
			_M_init();
		}

		/* ctor 2 */
		template<class InputIterator>
		map(InputIterator begin, InputIterator end, const key_compare& compare = key_compare(), const allocator_type& allocator = allocator_type()) : _allocator(allocator), _compare(compare), _n(0)
		{
			_M_range_init(begin, end);
		}

		/* copy ctor */
		map(const map_type& rhs) : _allocator(rhs._allocator), _compare(rhs._compare), _n(rhs._n)
		{
			_M_range_init(rhs.begin(), rhs.end());
		}

		/* assignment operator overload */
		map&	operator= (const map& rhs)
		{
			if (this == &rhs)
				return (*this);
			clear();
			insert(rhs.begin(), rhs.end());
			return *this;
		}

		~map()
		{
			//clear();
			//_allocator.deallocate(_nil, 1);
		}

		bool					empty() const
		{
			return (this->_n == 0);
		}

		size_type				size() const
		{
			return (this->_n);
		}

		size_type				max_size() const
		{
			return (this->_allocator.max_size());
		}

		ft::pair<iterator, bool>	insert(const value_type& value)
		{
			return _M_insert(value);
		}

		iterator					insert(iterator i, const value_compare& value)
		{
			ft::pair<iterator, bool> result = _M_insert(value, i);
		}

		mapped_type&		operator[](const key_type& key)
		{
			return (*(this->insert(value_type(key, mapped_type())).first)).second;
		}

		/* iterators */
		iterator			begin() { return iterator(this->_nil->_right, this->_nil); }
		const_iterator		begin() const { return const_iterator(this->_nil->_right, this->_nil); }
		iterator			end() { return iterator(this->_nil, this->_nil); }
		const_iterator		end() const { return const_iterator(this->_nil, this->_nil); }
		iterator			rbegin() { return reverse_iterator(end()); }
		const_iterator		rbegin() const { return const_reverse_iterator(end()); }
		iterator			rend() { return reverse_iterator(begin()); }
		const_iterator		rend() const { return const_reverse_iterator(begin()); }

		void	clear()
		{
			//
		}

		allocator_type get_allocator() const
		{
			return this->_allocator();
		}

		void		swap(map_type& other)
		{
			size_type	n = this->_n;
			pointer		nil = this->_nil;
			pointer		root = this->_root;

			this->_n = other._n;
			this->_nil = other._nil;
			this->_root = other._root;

			other._n = n;
			other._nil = nil;
			other._root = root;
		}

		key_compare		key_comp() const
		{
			return (this->_compare.comp);
		}

		value_compare	value_comp() const
		{
			return (this->_compare);
		}

		iterator			find(const key_type& key)
		{
			return iterator(_M_get_value_by_key(key), _nil);
		}

		const_iterator		find(const key_type& key) const
		{
			return const_iterator(_M_get_value_by_key(key), _nil);
		}

		size_type			count(const key_type& key) const
		{
			if (find(key) != end())
				return 1;
			return 0;
		}

		iterator		lower_bound(const key_type& key)
		{
			iterator		i;
			for (i = begin(); i != end(); ++i)
				if (!(_compare.comp(i->first, key)))
					break ;
			return i;
		}

		const_iterator	lower_bound(const key_type& key) const
		{
			const_iterator	i;
			for (i = begin(); i != end(); ++i)
				if (!(_compare.comp(i->first, key)))
					break ;
			return i;
		}

		iterator		upper_bound(const key_type& key)
		{
			iterator		i;
			for (i = begin(); i != end(); ++i)
				if (_compare.comp(key, i->first))
					break ;
			return i;
		}

		const_iterator	upper_bound(const key_type& k) const
		{
			const_iterator	i;
			for (i = begin(); i != end(); ++i)
				if (_compare.comp(k, i->first))
					break ;
			return (i);
		}

		ft::pair<iterator, iterator>				equal_range(const key_type& key)
		{
			return ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
		}

		ft::pair<const_iterator, const_iterator>	equal_range(const key_type& key) const
		{
			return ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
		}

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
