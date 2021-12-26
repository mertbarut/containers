/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 23:13:25 by mbarut            #+#    #+#             */
/*   Updated: 2021/12/25 16:09:52 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include <iterator>
#include <iostream>

namespace ft
{
	/* Any iterator */
	template<typename I>
	struct iterator_traits
	{
		typedef typename I::value_type			value_type;
		typedef typename I::difference_type		difference_type;
		typedef typename I::iterator_category	iterator_category;
		typedef typename I::pointer				pointer;
		typedef typename I::reference			reference;
	};

	/* Any pointer */
	template <typename T>
	struct iterator_traits<T*>
	{
		typedef T								value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef std::random_access_iterator_tag	iterator_category;
		typedef T*								pointer;
		typedef T&								reference;
	};

	/* Any const pointer */
	template <typename T>
	struct iterator_traits<const T*>
	{
		typedef T								value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef std::random_access_iterator_tag	iterator_category;
		typedef const T*						pointer;
		typedef const T&						reference;
	};

	/* Random access iterator */
	template <typename T>
	class random_access_iterator
	{
		typedef T								value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef std::random_access_iterator_tag	iterator_category;
		typedef T*								pointer;
		typedef T&								reference;
		typedef random_access_iterator<T>		iterator;
		typedef random_access_iterator<const T>	const_iterator;

	protected:

		pointer		_pointer;
	
		/* Getter & Setter */
		pointer		getPointer()
		{
			return this->_pointer;
		}

		void		setPointer(pointer obj)
		{
			this->_pointer = obj->getPointer();
		}
	
	public:

		/* Constructors */
		random_access_iterator(void)
		: _pointer(NULL)
		{
			std::cout << "A random access iterator has been constructed\n";
		}

		explicit random_access_iterator(T* pointer)
		: _pointer(pointer)
		{
			std::cout << "A random access iterator has been constructed using another random access iterator\n";
		}

		/* Destructors */
		~random_access_iterator(void)
		{
			std::cout << "A random access iterator has been destructed\n";
		}

		/* Copy constructors */
		random_access_iterator(const random_access_iterator& obj)
		{
			std::cout << "A copy constructor for the template class random access iterator has been called\n";
			*this = obj;
		}

		/* Assignment operator overload */
		random_access_iterator& operator= (const random_access_iterator& obj)
		{
			if (this != &obj)
				this->setPointer(obj);
			return *this;
		}

		/* Member access operators */
		reference operator[] (const difference_type d) const
		{
			return this->getPointer()[d];
		}

		reference operator* ()
		{
			return *this->getPointer();
		}

		reference operator-> ()
		{
			return this->getPointer();
		}

		pointer operator& ()
		{
			return &this->getPointer();
		}

		/* Relational operators */
		bool operator== (const iterator& obj) const
		{
			return this->getPointer() == obj.getPointer();
		}

		bool operator!= (const iterator& obj) const
		{
			return this->getPointer() != obj.getPointer();
		}

		bool operator<= (const iterator& obj) const
		{
			return this->getPointer() <= obj.getPointer();
		}

		bool operator>= (const iterator& obj) const
		{
			return this->getPointer() >= obj.getPointer();
		}

		bool operator< (const iterator& obj) const
		{
			return this->getPointer() < obj.getPointer();
		}

		bool operator> (const iterator& obj) const
		{
			return this->getPointer() > obj.getPointer();
		}

		/* Increment/decrement operators */
		iterator& operator++ ()
		{
			++this->getPointer();
			return *this;
		}

		iterator operator++ (int)
		{
			iterator tmp = *this;
			++this->getPointer();
			return tmp;
		}
		
		iterator& operator-- ()
		{
			--this->getPointer();
			return *this;
		}

		iterator operator-- (int)
		{
			iterator tmp = *this;
			--this->getPointer();
			return tmp;
		}

		/* Pointer Arithmetic operators */
		friend iterator operator+ (int d, iterator obj)
		{
			return iterator(obj.getPointer() + d);
		}
		
		iterator operator+ (const int d) const
		{
			return iterator(this->getPointer() + d);
		}
		
		difference_type operator+ (const iterator& obj)
		{
			return this->getPointer() + obj.getPointer();
		}
		
		friend iterator operator- (int d, iterator obj)
		{
			return iterator(obj.getPointer() - d);
		}
		
		iterator operator- (const int d) const
		{
			return iterator(this->getPointer() - d);
		}
		
		difference_type operator- (const iterator& obj)
		{
			return getPointer() - obj.getPointer();
		}
		
		/* Increment/decrement assignment operators */
		iterator& operator += (int d)
		{
			this->setPointer(this->getPointer() + d);
			return *this;
		}

		iterator& operator -= (int d)
		{
			this->setPointer(this->getPointer() - d);
			return *this;
		}

	};

	template <typename Iterator>
	class reverse_iterator
	{
		typedef Iterator						iterator_type;
		typedef ft::iterator_traits<Iterator>	iterator_category;
		typedef ft::iterator_traits<Iterator>	value_type;
		typedef ft::iterator_traits<Iterator>	difference_type;
		typedef ft::iterator_traits<Iterator>	pointer;
		typedef ft::iterator_traits<Iterator>	reference;

	protected:

		iterator_type	_base;
	
		/* Getter & Setter */
		iterator_type	getBase()
		{
			return this->_base;
		}

		void			setBase(iterator_type obj)
		{
			this->_base = obj->getBase();
		}
	
	public:

		/* Constructors */
		/* (1) default constructor */
		/* Constructs a reverse iterator that points to no object. */
		reverse_iterator(void)
		: _base(NULL)
		{
			std::cout << "A reverse iterator has been constructed\n";
		}

		/* (2) initalization constructor */
		/* Constructs a reverse iterator from some original iterator 'iterator'. */
		explicit reverse_iterator(iterator_type iterator)
		: _base(iterator)
		{
			std::cout << "A reverse iterator has been constructed using another reverse iterator\n";
		}

		/* Destructors */
		//~reverse_iterator(void)
		//{
		//	std::cout << "A reverse iterator has been destructed\n";
		//}

		/* Copy constructors */
		reverse_iterator(const reverse_iterator<Iterator>& obj)
		{
			std::cout << "A copy constructor for the template class reverse iterator has been called\n";
			*this = obj;
		}

		/* Assignment operator overload */
		//reverse_iterator& operator= (const reverse_iterator& obj)
		//{
		//	if (this != &obj)
		//		this->setIterator(obj);
		//	return *this;
		//}

		/* Get Base iterator */
		iterator_type	base() const
		{
			return this->getBase();
		}

		/* Member access operators */
		reference operator[] (difference_type d) const
		{
			return *(*this + d);
		}

		reference operator* ()
		{
			iterator_type tmp = this->getBase();
			--tmp;
			return *tmp;
		}

		pointer operator-> () const
		{
			iterator_type tmp = this->getBase();
			--tmp;
			return &(*tmp);
		}

		pointer operator& ()
		{
			return &this->getPointer();
		}

		/* Increment/decrement operators */
		/* ++i */
		reverse_iterator& operator++ ()
		{
			--this->getBase();
			return *this;
		}

		/* i++ */
		reverse_iterator operator++ (int)
		{
			reverse_iterator tmp = *this;
			--this->getBase();
			return tmp;
		}
		
		/* --i */
		reverse_iterator& operator-- ()
		{
			++this->getBase();
			return *this;
		}

		/* i-- */
		reverse_iterator operator-- (int)
		{
			reverse_iterator tmp = *this;
			++this->getBase();
			return tmp;
		}

		/* Pointer Arithmetic operators */
		/* Reverse_iterator_2 = Reverse_iterator_1 + d */
		reverse_iterator operator+ (difference_type d) const
		{
			return reverse_iterator(this->getBase() - d);
		}

		/* Reverse_iterator_2 = Reverse_iterator_1 - d */
		reverse_iterator operator- (difference_type d) const
		{
			return reverse_iterator(this->getBase() + d);
		}

		/* Increment/decrement assignment operators */
		/* reverse_iterator += d */
		reverse_iterator& operator += (difference_type d)
		{
			this->setBase(this->getBase() - d);
			return *this;
		}

		/* reverse_iterator -= d */
		reverse_iterator& operator -= (difference_type d)
		{
			this->setBase(this->getBase() + d);
			return *this;
		}
	};

	/* Reverse iterator non-member functions */

	/* Relational operators */
	template <class Iterator>
	bool operator == (
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
	{
		return lhs->base() == rhs->base();
	}

	template <class Iterator>
	bool operator != (
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
	{
		return lhs->base() != rhs->base();
	}
	
	template <class Iterator>
	bool operator < (
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
	{
		return lhs->base() > rhs->base();
	}
	
	template <class Iterator>
	bool operator <= (
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
	{
		return lhs->base() >= rhs->base();
	}
	
	template <class Iterator>
	bool operator > (
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
	{
		return lhs->base() < rhs->base();
	}
	
	template <class Iterator>
	bool operator >= (
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
	{
		return lhs->base() <= rhs->base();
	}

	/* return = i + obj */
	template <class Iterator>
	reverse_iterator<Iterator> operator+ (
		typename reverse_iterator<Iterator>::difference_type d,
		const reverse_iterator<Iterator>& obj)
	{
		return reverse_iterator<Iterator>(obj.base() - d);
	}

	/* distance = right - left */
	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator- (
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
	{
		return rhs.base() - lhs.base();
	}

}
