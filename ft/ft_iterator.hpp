/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 23:13:25 by mbarut            #+#    #+#             */
/*   Updated: 2022/02/01 22:19:33 by mbarut           ###   ########.fr       */
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


	/* Back insert iterator */
	
	template <typename Container>
	class back_insert_iterator : public iterator<output_iterator_tag, void, void, void, void>
	{

	protected:

		Container* container;

	public:

		typedef Container	container_type;
		
		/* Ctor */
		explicit back_insert_iterator(Container& cont) : container(&cont)
		{
			
		}

		/* Assignment overload operator */
		back_insert_iterator& operator= (typename Container::const_reference value)
		{
			container->push_back(value);
			return *this;
		}

		/* Trivial access operator */
		back_insert_iterator& operator* (void)
		{
			return *this;
		}
	
		/* Trivial Increment operators */

		back_insert_iterator& operator++ ()
		{
			return *this;
		}
	
		back_insert_iterator operator++ (int)
		{
			return *this;
		}
	};

	/* Returns an instance of back_insert_iterator for type Container */
	template <typename Container>
	inline back_insert_iterator<Container> back_inserter(Container& cont)
	{
		return back_insert_iterator<Container>(cont);
	}

	/* Front insert iterator */
	
	template <typename Container>
	class front_insert_iterator : public iterator <output_iterator_tag, void, void, void, void>
	{
	
	protected:

		Container* container;

	public:

		typedef Container	container_type;
		
		/* Ctor */
		explicit front_insert_iterator(Container& cont) : container(&cont)
		{
			
		}

		/* Assignment overload operator */
		front_insert_iterator& operator= (typename Container::const_reference value)
		{
			container->push_front(value);
			return *this;
		}

		/* Trivial access operator */
		front_insert_iterator& operator* (void)
		{
			return *this;
		}
	
		/* Trivial Increment operators */

		front_insert_iterator& operator++ ()
		{
			return *this;
		}
	
		front_insert_iterator operator++ (int)
		{
			return *this;
		}
	};

	/* Returns an instance of front_insert_iterator for type Container */
	template <typename Container>
	inline front_insert_iterator<Container> front_inserter(Container& cont)
	{
		return front_insert_iterator<Container>(cont);
	}

	/* Insert Iterator */
	template <typename Container>
	class insert_iterator : public iterator<output_iterator_tag, void, void, void, void>
	{

	protected:

		Container* container;
		typename Container::iterator iter;
		
	public:

		typedef Container container_type;
		
	/* Ctor */
	insert_iterator(Container& cont, typename Container::iterator i) : container(&cont), iter(i)
	{
		
	}

	/* Assignment operator overload */
	insert_iterator& operator= (typename Container::const_reference value)
	{
		iter = container->insert(iter, value);
		++iter;
		return *this;
	}

	/* Trivial access operator */
	insert_iterator& operator* (void)
	{
		return *this;
	}
	
	/* Trivial Increment operators */

	insert_iterator& operator++ (void)
	{
		return *this;
	}
	
	insert_iterator operator++ (int)
	{
		return *this;
	}

	};

	/* Returns an instance of insert_iterator for type Container */
	template <typename Container, typename Iterator>
	inline insert_iterator<Container> inserter(Container& container, Iterator i)
	{
		return insert_iterator<Container>(container, typename Container::iterator(i));
	}

	/* Any iterator inline functions */

	/* Relational operators with different iterator types */
	//template <class IteratorL, class IteratorR, class Container>
	//inline bool operator== (const base_iterator<IteratorL, Container>& lhs,
	//						const base_iterator<IteratorR, Container>& rhs)
	//{ return lhs.base() == rhs.base(); }
	//
	//template <class IteratorL, class IteratorR, class Container>
	//inline bool operator!= (const base_iterator<IteratorL, Container>& lhs,
	//						const base_iterator<IteratorR, Container>& rhs)
	//{ return !(lhs->base() == rhs->base()); }
	//
	//template <class IteratorL, class IteratorR, class Container>
	//inline bool operator > (const base_iterator<IteratorL, Container>& lhs,
	//						const base_iterator<IteratorR, Container>& rhs)
	//{ return lhs->base() > rhs->base(); }
	//
	//template <class IteratorL, class IteratorR, class Container>
	//inline bool operator<= (const base_iterator<IteratorL, Container>& lhs,
	//						const base_iterator<IteratorR, Container>& rhs)
	//{ return !(lhs->base() < rhs->base()); }
	//template <class IteratorL, class IteratorR, class Container>
	//inline bool operator < (const base_iterator<IteratorL, Container>& lhs,
	//						const base_iterator<IteratorR, Container>& rhs)
	//{ return lhs->base() < rhs->base(); }
	//template <class IteratorL, class IteratorR, class Container>
	//inline bool operator>= (const base_iterator<IteratorL, Container>& lhs,
	//						const base_iterator<IteratorR, Container>& rhs)
	//{ return !(lhs->base() > rhs->base()); }
	//
	///* Relational operators with same iterator types */
	//template <class Iterator, class Container>
	//inline bool operator== (const base_iterator<Iterator, Container>& lhs,
	//						const base_iterator<Iterator, Container>& rhs)
	//{ return lhs.base() == rhs.base(); }
	//template <class Iterator, class Container>
	//inline bool operator!= (const base_iterator<Iterator, Container>& lhs,
	//						const base_iterator<Iterator, Container>& rhs)
	//{ return !(lhs->base() == rhs->base()); }
	//template <class Iterator, class Container>
	//inline bool operator > (const base_iterator<Iterator, Container>& lhs,
	//						const base_iterator<Iterator, Container>& rhs)
	//{ return lhs->base() > rhs->base(); }
	//template <class Iterator, class Container>
	//inline bool operator<= (const base_iterator<Iterator, Container>& lhs,
	//						const base_iterator<Iterator, Container>& rhs)
	//{ return !(lhs->base() < rhs->base()); }
	//template <class Iterator, class Container>
	//inline bool operator < (const base_iterator<Iterator, Container>& lhs,
	//						const base_iterator<Iterator, Container>& rhs)
	//{ return lhs->base() < rhs->base(); }
	//template <class Iterator, class Container>
	//inline bool operator>= (const base_iterator<Iterator, Container>& lhs,
	//						const base_iterator<Iterator, Container>& rhs)
	//{ return !(lhs->base() > rhs->base()); }

	///* return the distance between iterators ( = right - left ) */
	//template <class IteratorL, class IteratorR, class Container>
	//inline typename base_iterator<IteratorL, Container>::difference_type operator- (
	//	const base_iterator<IteratorL, Container>& lhs,
	//	const base_iterator<IteratorR, Container>& rhs)
	//{ return rhs.base() - lhs.base(); }

	//template <class Iterator, class Container>
	//inline typename base_iterator<Iterator, Container>::difference_type operator- (
	//	const base_iterator<Iterator, Container>& lhs,
	//	const base_iterator<Iterator, Container>& rhs)
	//{ return rhs.base() - lhs.base(); }

	//template <class Iterator, class Container>
	//inline base_iterator<Iterator, Container> operator+ (
	//	typename base_iterator<Iterator, Container>::difference_type d,
	//	const base_iterator<Iterator, Container>& i)
	//{ return base_iterator<Iterator, Container>(i.base() + d); }

	template<typename Iterator, typename Container>
	class random_access_iterator
	{

	private:

		typedef typename ft::iterator_traits<Iterator>		trait_type;
		Iterator											_base;

	public:

		typedef typename trait_type::value_type			value_type;
		typedef typename trait_type::difference_type	difference_type;
		typedef typename trait_type::iterator_category	iterator_category;
		typedef typename trait_type::pointer			pointer;
		typedef typename trait_type::reference			reference;

		/* ctor 1 */
		random_access_iterator() : _base(Iterator()) { }
		/* ctor 2 */
		random_access_iterator(const Iterator& other) : _base(other) { }
		/* copy ctor */
		random_access_iterator(const random_access_iterator& other) : _base(other._base) { } 
		/* dtor */
		~random_access_iterator() { }

		/* expose _base */
		pointer			base() const { return (this->_node); }

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
		: _base(v._base()) { (void)_tmp; }

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

		reference						operator* ()	const	{ return *_base; }
		pointer							operator->()	const	{ return _base; }
		reference						operator[](difference_type d) const { return _base[d]; }

		random_access_iterator& 		operator++()				{ ++_base; return *this; }
		random_access_iterator& 		operator--()				{ --_base; return *this; }
		random_access_iterator	 		operator++(int)				{ random_access_iterator r(*this); ++_base ; return r; }
		random_access_iterator	 		operator--(int)				{ random_access_iterator r(*this); --_base ; return r; }
			
		random_access_iterator&	 		operator+=(difference_type d)		{ _base += d; return *this; }
		random_access_iterator&	 		operator-=(difference_type d)		{ _base -= d; return *this; }
	
		random_access_iterator	 		operator+ (difference_type d) const { return random_access_iterator(_base + d); }		
		random_access_iterator	 		operator- (difference_type d) const { return random_access_iterator(_base - d); }

	};

}

#pragma endregion