/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 14:44:43 by mbarut            #+#    #+#             */
/*   Updated: 2022/02/06 20:58:04 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pair.hpp"
#include "ft_util.hpp"
#include "ft_iterator.hpp"
#include "ft_vector.hpp"
#include <memory>

namespace ft
{
	template <class _Allocator>
	struct	_map_node
	{

	private:

		typedef typename _Allocator::value_type					value_type;
		typedef _map_node<_Allocator>							map_node;

	public:

		value_type				_value;
		map_node*				_parent;
		map_node*				_left;
		map_node*				_right;
		size_t					_level;
		size_t					_index;
		bool					_is_red;

		/* ctor 1 */
		_map_node() : _value( 0 ), _parent(nullptr), _left(nullptr), _right(nullptr), _level(0), _index(0), _is_red(false)
		{
			
		}

		/* ctor 2 */
		_map_node(map_node* tree, const value_type& value) : _value(value), _parent(tree), _left(tree), _right(tree), _level(0), _index(0), _is_red(false)
		{
			
		}

		/* copy ctor */

		_map_node(const _map_node& node) : _value(node._value), _parent(node._parent), _left(node._left), _right(node._right), _level(node._level), _index(node._index), _is_red(node._is_red)
		{
			
		}

		/* assignment operator overload */
		_map_node&		operator=(const _map_node& rhs)
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
		~_map_node()
		{
			
		}

		/* getters */
		value_type get_value() const { return this->_value; }

		value_type* get_left() const { return this->_left; }

		value_type* get_right() const { return this->_right; }
		
		size_t	get_level() const { return this->_level; }
		
		size_t	get_index() const { return this->_index; }

		template <typename Node>
		static Node	get_min(Node node, const map_node* nil)
		{
			if (node == nil)
				return node;
			for (; node->left != nil; node = node->left) {}
				return node;
		}

		template <typename Node>
		static Node	get_max(Node node, const map_node* nil)
		{
			if (node == nil)
				return node;
			for (; node->left != nil; node = node->left) {}
				return node;
		}

		template <typename Node>
		static void	next(Node& node, const map_node* nil)
		{
			if (node->right != nil)
				node = get_min(node->right, nil);
			else if (node == nil || nil->_left == node)
				node = node->right;
			else
				for (; node->parent != nil && node == node->parent->right; node = node->parent) {}
				node = node->parent;
		}

		template <typename Node>
		static void	prev(Node& node, const map_node* nil)
		{
			if (node->left != nil)
				node = get_max(node->left, nil);
			else if (node == nil || nil->_right == node)
				node = node->left;
			else
				for (; node->parent != nil && node == node->parent->left; node = node->parent) {}
				node = node->parent;
		}

	};

	template <
		class Key,
		class T,
		class Compare = ft::less<Key>,
		class Allocator = std::allocator< ft::pair<const Key, T> >
		>
	class map
	{

	public:

		typedef _map_node<Allocator> 									map_node;
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
		typedef ft::bidirectional_iterator<pointer>						iterator;
		typedef ft::bidirectional_iterator<const pointer>				const_iterator;
		typedef typename Allocator::difference_type						difference_type;
		typedef typename Allocator::size_type							size_type;

		class value_compare : public binary_function<value_type, value_type, bool>
		{
		
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

		typedef typename Allocator::template rebind<map_node>::other	node_allocator_type;
		typedef ft::pair<iterator, bool>								map_insres;
		typedef ft::bidirectional_iterator_tag							iterator_catogory;

		node_allocator_type												_allocator;
		value_compare													_compare;
		map_node*														_root;
		map_node*														_nil;
		size_type														_size;

		map_node*	_M_create(const value_type& val)
		{
			allocator_type	data_alloc(_allocator);
			map_node*	node = _allocator.allocate(1);
			node->_is_red = true;
			node->_parent = nullptr;
			node->_right = nullptr;
			node->_left = nullptr;
			_allocator.construct(&(node->data), val);
			return (node);
		}

		void		_M_destroy(map_node* node)
		{
			_allocator.destroy(node);
			_allocator.deallocate(node, 1);
		}

		void		_M_init(void)
		{
			_nil = _allocator.allocate(1);
			_nil->_is_red = false;
			_nil->_parent = _nil;
			_nil->_right = _nil;
			_nil->_left = _nil;
			_root = _nil;
		}

		void		_M_lrotate()
		{
			
		}

		void		_M_rrotate()
		{
			
		}

		void		_M_search(const key_type& key) const
		{
			map_node* i = _root;
			for (; i != _nil && i->_value.first != key;
				_compare.comp(key, i->_value.first) ? i = i->_left : i = i->right) { }
			return i;
		}

		void		_M_find(const value_type& value)
		{
			map_node* i = _root;
			for (; i != _nil && i->_value.first != value.first;)
			{
				if (_compare.comp(value, i->_value))
				{
					if (i->left == _nil)
						return (i);
					i = i->left;
				}
				else
				{
					if (i->right == _nil)
						return (i);
					i = i->right;
				}
			}
			return i;
		}

	public:

		/* ctor 1 */
		//map() : _size(0), _capacity(0), _p(allocator_type().allocate())
		//{
		//	
		//}

		/* copy ctor */
		//map(const map_type& rhs) : _size(rhs._size), _capacity(rhs._capacity), _p(allocator_type().allocate(rhs._size))
		//{
		//	int count = 0;
		//	for (const_iterator i = &rhs.begin(); i != &rhs.end(); ++i, ++count)
		//	{
		//		allocator_type().construct(&_p[count], *i);
		//	}
		//}

		//~map()
		//{
		//	if (!empty())
		//	{
		//		for (const_iterator i = begin(); i != end(); ++i)
		//			allocator_type().destroy(i);
		//		allocator_type().deallocate(_p, _capacity);
		//	}
		//}

		allocator_type get_allocator() const
		{
			return this->Allocator();
		}

		//map_type& insert(const mapped_type& value)
		//{
		//	if (++_size >= _capacity)
		//		reserve(_capacity * 2);
		//	Allocator().construct(_p.end() - 1, value);
		//	return *this;
		//}

		//void		swap(map_type& other)
		//{
		//	//size_type	capacity = this->_capacity;
		//	//size_type	size = this->_size;
		//	pointer		p = this->_p;
//
		//	//this->_capacity = other._capacity;
		//	//this->_size = other._size;
		//	this->_p = other._p;
//
		//	//other._capacity = capacity;
		//	//other._size = size;
		//	other._p = p;
		//}

		//mapped_type&	operator[] (const key_type& key)
		//{
		//	iterator i = find_if(begin(), end(), key);
		//	if (i == end())
		//	{
		//		size_type op = _size;
		//		insert(pair_type(key, mapped_type()));
		//		return _p[op].second;
		//	}
		//	else
		//		return &_p[i];
		//}

		//map_type& reserve(size_type given_capacity)
		//{
		//	int count = 0;
		//	if (given_capacity < this->_capacity)
		//		return *this;
		//	pointer tmp = allocator_type().allocate(_capacity);
		//	for (const_iterator i = this->begin(); i != end(); ++i, ++count)
		//		allocator_type().construct(&tmp[count], *i);
		//	swap(_p, tmp);
		//	for (iterator i = tmp.begin(); i != tmp.end(); ++i)
		//		Allocator().destroy();
		//	Allocator().deallocate(tmp, _capacity);
		//	_capacity = given_capacity;
		//	return *this;
		//}

		//map_node* _M_find_by_key(const key_type& key) const
		//{
		//	if (!root)
		//		return nullptr;
		//	else
		//	{
		//		if (root->getData() == item)
		//			return root;
		//		else if (root->getData() < item)
		//			return find(root->getRightNode(), item);
		//		else if (root->getData() > item)
		//			return find(root->getLeftNode(), item);
		//	}
		//	return nullptr;
		//}

		//BST_node *insert(BST_node *root, T item)
		//{
		//	if (!root)
		//	{
		//		BST_node<T>	*node = new BST_node<T>(item);
		//		return node;
		//	}
		//	else
		//	{
		//		if (root->getData() < item)
		//			root->setRightNode( insert(root->getRightNode(), item) );
		//		else if (root->getData() > item)
		//			root->setLeftNode( insert(root->getLeftNode(), item) );
		//	}
		//	return root;
		//}
		//
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
		//
		//void clear(BST_node *root)
		//{
		//	if (!root)
		//		return ;
		//	clear(root->getLeftNode());
		//	clear(root->getRightNode());
		//	delete root;
		//}
//
		//bool empty() const
		//{
		//	return _size == 0;
		//}
//
		//iterator begin() const
		//{
		//	return &_p[0];
		//}
//
		//iterator end() const
		//{
		//	return &_p[_size];
		//}
//
		//const_iterator cbegin() const
		//{
		//	return &_p[0];
		//}
//
		//const_iterator cend() const
		//{
		//	return &_p[_size];
		//}

	};
	
}
