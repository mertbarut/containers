/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 23:13:25 by mbarut            #+#    #+#             */
/*   Updated: 2022/02/08 01:40:53 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_iterator_base_funcs.hpp"
#include "ft_iterator_base_types.hpp"
#include "ft_util.hpp"

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

	template<class Node>
	class bidirectional_iterator
	{
	protected:
		Node											_base;
		Node*											_node;
		Node*											_end;
		typedef typename ft::iterator_traits<Node>		trait_type;

	public:

		typedef typename trait_type::value_type			value_type;
		typedef typename trait_type::difference_type	difference_type;
		typedef typename trait_type::pointer			pointer;
		typedef typename trait_type::reference			reference;
		typedef ft::bidirectional_iterator_tag			iterator_category;
		
		/* ctor 1 */
		bidirectional_iterator() : _base(Node()), _node(&_base), _end(NULL) { }
		/* ctor 2 */
		explicit bidirectional_iterator(Node* node, const Node* end) : _node(node), _end(end) { }
		/* copy ctor */
		bidirectional_iterator(const bidirectional_iterator& other) : _base(other._base), _node(&other._base), _end(NULL) { } 
		/* dtor */
		~bidirectional_iterator() { }

		/* expose _base */
		pointer			base() const { return (this->_base); }

		/* assignment operator overload */
		bidirectional_iterator&		operator= (const bidirectional_iterator& other)
		{
			if (this == &other)
				return *this;
			this->_base = other._base;
			this->_node = other._node;
			this->_end = other._end;
			return *this;
		}

		/* iterator -> const_iterator */
		//template <typename Iter>
		//bidirectional_iterator(const bidirectional_iterator<Iter, Container>& v,
		//	typename ft::is_same<Iter, Container>::_type* _tmp = NULL)
		//: _base(v._base()) { (void)_tmp; }

		/* friends */

		friend bool						operator==(const bidirectional_iterator& i1, const bidirectional_iterator& i2)
		{
			return i1._node == i2._node && i1._end = i2._end;
		}

		friend bool						operator!=(const bidirectional_iterator& i1, const bidirectional_iterator& i2)
		{
			return i1._base != i2._base || i1._end != i2._end;
		}

		/* member operators overloads */

		reference						operator* ()	const	{ return *_node; }
		pointer							operator->()	const	{ return _node; }

		bidirectional_iterator& 		operator++()				{ Node::next(_node, _end); return *this; }
		bidirectional_iterator& 		operator--()				{ Node::prev(_node, _end); return *this; }
		bidirectional_iterator	 		operator++(int)				{ bidirectional_iterator i = *this; ++(*this) ; return i; }
		bidirectional_iterator	 		operator--(int)				{ bidirectional_iterator i = *this; --(*this) ; return i; }

	};

	template<typename Iterator, typename Container>
	class random_access_iterator : public bidirectional_iterator<Iterator>
	{

	private:

		typedef typename ft::iterator_traits<Iterator>	trait_type;

	public:

		typedef typename trait_type::value_type			value_type;
		typedef typename trait_type::difference_type	difference_type;
		typedef typename trait_type::iterator_category	iterator_category;
		typedef typename trait_type::pointer			pointer;
		typedef typename trait_type::reference			reference;

		using											bidirectional_iterator<Iterator>::base;

		/* ctor 1 */
		random_access_iterator() { this->_base = Iterator(); }
		/* ctor 2 */
		random_access_iterator(const Iterator& other) { this->_base = other; }
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
		template <typename Iter>
		random_access_iterator(const random_access_iterator<Iter, Container>& v,
			typename ft::is_same<Iter, Container>::_type* _tmp = NULL)
		: bidirectional_iterator<Iterator>(v.base()) { (void)_tmp; }

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

#pragma endregion