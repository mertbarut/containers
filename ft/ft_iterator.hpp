/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 23:13:25 by mbarut            #+#    #+#             */
/*   Updated: 2022/02/10 00:01:02 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_iterator_base_funcs.hpp"
#include "ft_iterator_base_types.hpp"
#include "ft_util.hpp"
//#include "ft_base.hpp"

namespace ft
{
	template <typename Iterator>
	class reverse_iterator
	{
	public:

		typedef Iterator												iterator_type;
		typedef typename ft::iterator_traits<Iterator>::value_type		value_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
		typedef typename ft::iterator_traits<Iterator>::reference		reference;
		typedef typename ft::iterator_traits<Iterator>::pointer			pointer;

	private:

		iterator_type	_base;
	
	public:

		/* Constructors */
		/* (1) default constructor */
		/* Constructs a reverse iterator that points to NULL. */
		reverse_iterator() { }

		/* (2) initalization constructor */
		/* Constructs a reverse iterator from some original iterator 'iterator'. */
		/* explicit keyword is used because implicit conversion from other iterators is not desired */
		explicit reverse_iterator(iterator_type iterator) : _base(iterator) { }

		/* Destructors */
		/* not implemented in the original */
		//~reverse_iterator(void)
		//{
		//	std::cout << "A reverse iterator has been destructed\n";
		//}

		/* Copy constructors */
		reverse_iterator(const reverse_iterator<Iterator>& obj) : _base(obj.base())
		{
			//std::cout << "A copy constructor for the template class reverse iterator has been called\n";
		}

		/* Assignment operator overload */
		/* not implemented in the original */
		//reverse_iterator& operator= (const reverse_iterator& obj)
		//{
		//	if (this != &obj)
		//		this->setIterator(obj);
		//	return *this;
		//}

		/* Exposing Base iterator */
		iterator_type	base() const { return this->_base; }

		/* Member access operators */

		reference operator* () const
		{
			iterator_type tmp = this->_base;
			--tmp;
			return *tmp;
		}

		reference operator[] (difference_type d) const { return _base[-d - 1]; }

		pointer operator-> () const { return &(operator*()); }

		/* not implemented */
		//pointer operator& ()
		//{
		//	return &this->_base;
		//}

		/* Increment/decrement operators */

		/* ++i */
		reverse_iterator& operator++ ()
		{
			--this->_base;
			return *this;
		}

		/* i++ */
		reverse_iterator operator++ (int)
		{
			reverse_iterator tmp = *this;
			--this->_base;
			return tmp;
		}
		
		/* --i */
		reverse_iterator& operator-- ()
		{
			++this->_base;
			return *this;
		}

		/* i-- */
		reverse_iterator operator-- (int)
		{
			reverse_iterator tmp = *this;
			++this->_base;
			return tmp;
		}

		/* Pointer Arithmetic operators */
		/* Reverse_iterator_2 = Reverse_iterator_1 + d */
		reverse_iterator operator+ (difference_type d) const
		{
			return reverse_iterator(this->_base - d);
		}

		/* Reverse_iterator_2 = Reverse_iterator_1 - d */
		reverse_iterator operator- (difference_type d) const
		{
			return reverse_iterator(this->_base + d);
		}

		/* Increment/decrement assignment operators */
		/* reverse_iterator += d */
		reverse_iterator& operator+= (difference_type d)
		{
			this->_base -= d;
			return *this;
		}

		/* reverse_iterator -= d */
		reverse_iterator& operator-= (difference_type d)
		{
			this->_base += d;
			return *this;
		}
		
		/* Reverse iterator friend functions */

		/* Relational operators */

		friend bool operator== (const reverse_iterator& lhs,
								const reverse_iterator& rhs)
		{
			return lhs->base() == rhs->base();
		}
		
		friend bool operator!= (const reverse_iterator& lhs,
								const reverse_iterator& rhs)
		{
			return !(lhs->base() == rhs->base());
		}
		
		friend bool operator < (const reverse_iterator& lhs,
								const reverse_iterator& rhs)
		{
			return lhs->base() > rhs->base();
		}
		
		friend bool operator<= (const reverse_iterator& lhs,
								const reverse_iterator& rhs)
		{
			return !(lhs->base() < rhs->base());
		}
		
		friend bool operator > (const reverse_iterator& lhs,
								const reverse_iterator& rhs)
		{
			return lhs->base() < rhs->base();
		}
		
		friend bool operator>= (const reverse_iterator& lhs,
								const reverse_iterator& rhs)
		{
			return !(lhs->base() > rhs->base());
		}
		
		/* return an iterator i where obj - i = d */

		friend reverse_iterator operator+ (
			typename reverse_iterator::difference_type d,
			const reverse_iterator& obj)
		{
			return reverse_iterator(obj.base() - d);
		}
		
		/* return the distance between iterators ( = right - left ) */
		friend typename reverse_iterator::difference_type operator- (
			const reverse_iterator& lhs,
			const reverse_iterator& rhs)
		{
			return rhs.base() - lhs.base();
		}

	};

	template <typename T, class Compare>
	class _RBT_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	{
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

	public:
		T*			_node;
		T*			_nil;
		Compare     _compare;
		
	public:

		typedef typename T::value_type    value_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type   difference_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer   pointer;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference reference;
		typedef _RBT_iterator<T, Compare>	self_type;

		_RBT_iterator(const Compare& comp = Compare()) : _node(), _nil(), _compare(comp) {}
		_RBT_iterator(T* node, T* nil, const Compare& comp = Compare()) : _node(node), _nil(nil), _compare(comp) {}
		_RBT_iterator(const _RBT_iterator& i) : _node(i._node), _nil(i._nil), _compare() {}
		virtual ~_RBT_iterator() { }

		_RBT_iterator& operator= (const _RBT_iterator& rhs)
		{
			if (*this == rhs)
				return *this;
			this->_node = rhs._node;
			this->_nil = rhs._nil;
			this->_compare = rhs._compare;
			return *this;
		}

		T*			base() const { return this->_node; }
		T*			nil() const { return this->_nil; }
		Compare		compare() const { return this->_compare; }

		bool		operator==(const _RBT_iterator& i) { return this->_node == i._node; }
		bool		operator!=(const _RBT_iterator& i) { return this->_node != i._node; }
		reference	operator*() const { return this->_node->value; }
		pointer		operator->() const { return &this->_node->value; }

		_RBT_iterator& operator++(void)
		{
			T* ptr = this->_node;

			if (ptr == _nil)
				this->_node = NILNODE;
			else if (this->_node->right == _nil)
			{
				ptr = this->_node->parent;
				while (ptr != _nil && _compare(ptr->value.first, this->_node->value.first))
					ptr = ptr->parent;
				this->_node = ptr;
			}
			else
			{
				ptr = this->_node->right;
				if (ptr == _nil->parent && ptr->right == _nil)
					this->_node = ptr;
				else
					while (ptr->left != _nil)
						ptr = ptr->left;
				this->_node = ptr;
			}
			return *this;
		}

		_RBT_iterator operator++(int)
		{
			_RBT_iterator tmp(*this);
			operator++();
			return (tmp);
		}

		_RBT_iterator& operator--(void)
		{
			T* ptr = this->_node;

			if (this->ptr == _nil)
				this->_node = NILNODE;
			else if (this->_node->left == _nil)
			{
				ptr = this->_node->parent;
				while (ptr != _nil && !_compare(ptr->value.first, this->_node->value.first))
					ptr = ptr->parent;
				this->_node = ptr;
			}
			else
			{
				ptr = this->_node->left;
				if (ptr == _nil->parent && ptr->left == _nil)
					this->_node = ptr;
				else
					while (ptr->right != _nil)
						ptr = ptr->right;
				this->_node = ptr;
			}
			return *this;
		}

		_RBT_iterator operator--(int)
		{
			_RBT_iterator tmp(*this);
			operator--();
			return (tmp);
		}

	};

	template <typename T, class Compare >
	class _RBT_const_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	{
	
	private:
		T*			_node;
		T*			_nil;
		Compare		_compare;
		
	public:

		typedef typename T::value_type    value_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type   difference_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer   pointer;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference reference;

		_RBT_const_iterator(const Compare& comp = Compare()) : _node(), _nil(), _compare(comp) {}
		_RBT_const_iterator(T* node_p, T* last_node, const Compare& comp = Compare()) : _node(node_p), _nil(last_node), _compare(comp) {}
		_RBT_const_iterator(const _RBT_const_iterator& i) : _node(i._node), _nil(i._nil), _compare(i._compare) {}
		_RBT_const_iterator(const _RBT_iterator<T, Compare>& i) : _node(i._node), _nil(i._nil), _compare(i._compare) {}
		virtual ~_RBT_const_iterator() { }

		_RBT_const_iterator& operator= (const _RBT_const_iterator& rhs)
		{
			if (*this == rhs)
				return *this;
			this->_node = rhs._node;
			this->_nil = rhs._nil;
			this->_compare = rhs._compare;
			return *this;
		}

		//_RBT_const_iterator& operator= (const _RBT_iterator<T, Compare>& rhs)
		//{
		//	if (*this == rhs)
		//		return (*this);
		//	this->_node = rhs._node;
		//	this->_nil = rhs._nil;
		//	this->_comp = rhs._comp;
		//	return *this;
		//}

		T*			base() const { return this->_node; }
		T*			nil() const { return this->_nil; }
		Compare		compare() const { return this->_compare; }

		bool		operator==(const _RBT_const_iterator& i) { return this->_node == i._node; }
		bool		operator!=(const _RBT_const_iterator& i) { return this->_node != i._node; }
		reference	operator*() const { return this->_node->value; }
		pointer		operator->() const { return &this->_node->value; }

		_RBT_const_iterator& operator++(void)
		{
			T* ptr = this->_node;

			if (ptr == _nil)
				this->_node = NILNODE;
			else if (this->_node->right == _nil)
			{
				ptr = this->_node->parent;
				while (ptr != _nil && _compare(ptr->value.first, _node->value.first))
					ptr = ptr->parent;
				this->_node = ptr;
			}
			else
			{
				ptr = this->_node->right;
				if (ptr == _nil->parent && ptr->right == _nil)
					this->_node = ptr;
				else
					while (ptr->left != _nil)
						ptr = ptr->left;
				this->_node = ptr;
			}
			return *this;
		}

		_RBT_const_iterator operator++(int)
		{
			_RBT_const_iterator tmp(*this);
			operator++();
			return (tmp);
		}

		_RBT_const_iterator& operator--(void)
		{
			T* ptr = this->_node;

			if (ptr == _nil)
				this->_node = NILNODE;
			else if (this->_node->left == _nil)
			{
				ptr = this->_node->parent;
				while (ptr != _nil && !_compare(ptr->value.first, _node->value.first))
					ptr = ptr->parent;
				this->_node = ptr;
			}
			else
			{
				ptr = this->_node->left;
				if (ptr == _nil->parent && ptr->left == _nil)
					this->_node = ptr;
				else
					while (ptr->right != _nil)
						ptr = ptr->right;
				this->_node = ptr;
			}
			return *this;
		}

		_RBT_const_iterator operator--(int)
		{
			_RBT_const_iterator tmp(*this);
			operator--();
			return (tmp);
		}

	};

	template<typename Allocator, typename Container>
	class random_access_iterator
	{

	private:

		Allocator										_base;
		typedef typename ft::iterator_traits<Allocator>	trait_type;

	public:

		typedef typename trait_type::value_type			value_type;
		typedef typename trait_type::difference_type	difference_type;
		typedef typename trait_type::iterator_category	iterator_category;
		typedef typename trait_type::pointer			pointer;
		typedef typename trait_type::reference			reference;

		//using											bidirectional_iterator<Allocator>::base;

		/* ctor 1 */
		random_access_iterator() { this->_base = Allocator(); }
		/* ctor 2 */
		random_access_iterator(const Allocator& other) { this->_base = other; }
		/* copy ctor */
		random_access_iterator(const random_access_iterator& other) { this->_base = other._base; } 
		/* dtor */
		~random_access_iterator() { }

		/* assignment operator overload */
		random_access_iterator&		operator= (const random_access_iterator& other)
		{
			if (this == &other)
				return *this;
			this->_base = other._base;
			return *this;
		}

		/* iterator -> const_iterator */
		//template <typename Iter>
		//random_access_iterator(const random_access_iterator<Iter, Container>& v,
		//	typename ft::is_same<Iter, Container>::_type* _tmp = NULL)
		//: bidirectional_iterator<Allocator>(v.base()) { (void)_tmp; }

		Allocator		base() const { return (this->_base); }

		/* friends */

		friend bool						operator==(const random_access_iterator& i1, const random_access_iterator& i2)
		{
			return i1._base == i2._base;
		}

		friend bool						operator!=(const random_access_iterator& i1, const random_access_iterator& i2)
		{
			return i1._base != i2._base;
		}

		friend bool						operator< (const random_access_iterator& i1, const random_access_iterator& i2)
		{
			return i1._base < i2._base;
		}

		friend bool						operator> (const random_access_iterator& i1, const random_access_iterator& i2)
		{
			return i1._base > i2._base;
		}

		friend bool						operator<=(const random_access_iterator& i1, const random_access_iterator& i2)
		{
			return i1._base < i2._base;
		}

		friend bool						operator>=(const random_access_iterator& i1, const random_access_iterator& i2)
		{
			return i1._base > i2._base;
		}

		friend random_access_iterator	operator+ (difference_type d, const random_access_iterator& other)
		{
			return other + d;
		}
		
		friend difference_type			operator- (const random_access_iterator& i1, const random_access_iterator& i2)
		{
			return i1._base - i2._base;
		}

		/* member operators overloads */

		reference						operator* ()	const	{ return *this->_base; }
		pointer							operator->()	const	{ return this->_base; }
		reference						operator[](difference_type d) const { return this->_base[d]; }

		random_access_iterator& 		operator++()				{ ++this->_base; return *this; }
		random_access_iterator& 		operator--()				{ --this->_base; return *this; }
		random_access_iterator	 		operator++(int)				{ random_access_iterator i(*this); ++this->_base ; return i; }
		random_access_iterator	 		operator--(int)				{ random_access_iterator i(*this); --this->_base ; return i; }
			
		random_access_iterator&	 		operator+=(difference_type d)		{ this->_base += d; return *this; }
		random_access_iterator&	 		operator-=(difference_type d)		{ this->_base -= d; return *this; }
	
		random_access_iterator	 		operator+ (difference_type d) const { return random_access_iterator(this->_base + d); }		
		random_access_iterator	 		operator- (difference_type d) const { return random_access_iterator(this->_base - d); }

	};

}
