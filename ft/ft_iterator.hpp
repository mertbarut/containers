/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 23:13:25 by mbarut            #+#    #+#             */
/*   Updated: 2022/02/11 19:45:09 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

//#include "ft_iterator_base_funcs.hpp"
//#include "ft_iterator_base_types.hpp"
#include "ft_util.hpp"
//#include "ft_base.hpp"

#include <cstddef>

namespace ft
{
	/* Iterator Tags */

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {} ;
	struct bidirectional_iterator_tag : public forward_iterator_tag {} ;
	struct random_access_iterator_tag : public bidirectional_iterator_tag {} ;

	/* Typedefs for any iterator */ 
	template <
		typename Category,
		typename T,
		typename Distance = ptrdiff_t,
		typename Pointer = T*,
		typename Reference = T&
		>
	struct iterator
	{
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef	Distance	difference_type;
		typedef	Pointer		pointer;
		typedef Reference	reference;
	};

	/* type_traits */
	template <typename Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
	};

	template <typename T>
	struct iterator_traits <T*>
	{
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef ptrdiff_t					difference_type;
		typedef T*							pointer;
		typedef T&							reference;
	};

	template <typename T>
	struct iterator_traits <const T*>
	{
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef ptrdiff_t					difference_type;
		typedef T*							pointer;
		typedef T&							reference;
	};
	
	/* Get the iterator category of any iterator type */
	template <typename Iterator>
	inline typename iterator_traits<Iterator>::iterator_category iterator_category(const Iterator&)
	{
		return typename iterator_traits<Iterator>::iterator_category();
	}

		/* Distance: get the distance between two iterators */
	
	template <typename InputIterator>
	static inline typename iterator_traits<InputIterator>::difference_type
	_distance (InputIterator first, InputIterator last, ft::input_iterator_tag)
	{
		typename iterator_traits<InputIterator>::difference_type n = 0;
		while (first != last)
		{
			++first;
			++n;
		}
		return n;
	}

	template <typename RandomAccessIterator>
	static inline typename iterator_traits<RandomAccessIterator>::difference_type
	_distance (RandomAccessIterator first, RandomAccessIterator last, ft::random_access_iterator_tag)
	{
		return last - first;
	}

	template <typename InputIterator>
	inline typename iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last)
	{
		return ft::_distance(first, last, ft::iterator_category(first));
	}

	/* Advance: advance some iterator by some position */

	template <typename InputIterator, typename Distance>
	static inline void
	_advance(InputIterator& i, Distance n, ft::input_iterator_tag)
	{
		while (n--)
			++i;
	}

	template <typename BidirectionalIterator, typename Distance>
	static inline void
	_advance(BidirectionalIterator& i, Distance n, ft::bidirectional_iterator_tag)
	{
		if (n > 0)
			while (n--)
				++i;
		else
			while (n++)
				--i;
	}

	template <typename RandomAccessIterator, typename Distance>
	static inline void
	_advance(RandomAccessIterator& i, Distance n, ft::random_access_iterator_tag)
	{
		i += n;
	}

	template <typename InputIterator, typename Distance>
	inline void
	advance (InputIterator& i, Distance n)
	{
		typename iterator_traits<InputIterator>::difference_type d = n;
		ft::_advance(i, d, ft::iterator_category(i));
	}

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
		
		/* return the distance between iterators ( = __right - __left ) */
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
		//#ifndef ROOT
		//# define ROOT									_nil->__parent
		//#endif

		#ifndef FIRSTNODE
		# define FIRSTNODE								_nil->__right
		#endif

		//#ifndef NILNODE
		//# define NILNODE								_nil->__right
		//#endif

	public:
		T*			_node;
		T*			_nil;
		Compare     _compare;
		
	public:

		typedef typename T::value_type		value_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type   difference_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer   pointer;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference reference;
		typedef _RBT_iterator<T, Compare>	self_type;
		typedef T*							link_type;

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
		reference	operator*() const { return static_cast<link_type>(_node)->__value; }
		pointer		operator->() const { return &static_cast<link_type>(_node)->__value; }

		_RBT_iterator& operator++(void)
		{
			T::_increment(_node, _nil);
			return *this;
		}

		_RBT_iterator operator++(int)
		{
			_RBT_iterator tmp = *this;
			++*this;
			return tmp;
		}

		_RBT_iterator& operator--(void)
		{
			T::_decrement(_node, _nil);
			return *this;
		}

		_RBT_iterator operator--(int)
		{
			_RBT_iterator tmp = *this;
			--*this;
			return tmp;
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
		typedef _RBT_iterator<T, Compare>	self_type;
		typedef T*							link_type;

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
		reference	operator*() const { return this->_node->__value; }
		pointer		operator->() const { return &this->_node->__value; }

		_RBT_const_iterator& operator++(void)
		{
			T::_increment(_node, _nil);
			return *this;
		}

		_RBT_const_iterator operator++(int)
		{
			_RBT_const_iterator tmp = *this;
			++*this;
			return tmp;
		}

		_RBT_const_iterator& operator--(void)
		{
			T::_decrement(_node, _nil);
			return *this;
		}

		_RBT_const_iterator operator--(int)
		{
			_RBT_const_iterator tmp = *this;
			++*this;
			return tmp;
		}
	};

	template <class T>
	class bidirectional_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category     iterator_category;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type            value_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type       difference_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer               pointer;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference             reference;
	};

	template<typename T, typename Container>
	class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T>
	{

	private:

		T												_base;
		typedef typename ft::iterator_traits<T>			trait_type;

	public:

		typedef typename trait_type::value_type			value_type;
		typedef typename trait_type::difference_type	difference_type;
		typedef typename trait_type::iterator_category	iterator_category;
		typedef typename trait_type::pointer			pointer;
		typedef typename trait_type::reference			reference;

		//using											bidirectional_iterator<Allocator>::base;

		/* ctor 1 */
		random_access_iterator() { this->_base = T(); }
		/* ctor 2 */
		random_access_iterator(const T& other) { this->_base = other; }
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

		T		base() const { return (this->_base); }

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
