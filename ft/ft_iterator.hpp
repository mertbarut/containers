/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 23:13:25 by mbarut            #+#    #+#             */
/*   Updated: 2021/12/29 18:44:50 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include <iterator>
#include <iostream>

#include "misc.hpp"

namespace ft
{

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
	: public iterator
	<
	typename ft::iterator_traits<Iterator>::iterator_category,
	typename ft::iterator_traits<Iterator>::value_type,
	typename ft::iterator_traits<Iterator>::difference_type,
	typename ft::iterator_traits<Iterator>::pointer,
	typename ft::iterator_traits<Iterator>::reference
	>
	{
	public:

		typedef Iterator											iterator_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
		typedef typename ft::iterator_traits<Iterator>::reference		reference;
		typedef typename ft::iterator_traits<Iterator>::pointer			pointer;

	protected:

		Iterator	_base;
	
		/* Trivial Getter & Setter */
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
		/* Constructs a reverse iterator that points to NULL. */
		reverse_iterator(void)
		: _base(NULL)
		{
			std::cout << "A reverse iterator has been constructed\n";
		}

		/* (2) initalization constructor */
		/* Constructs a reverse iterator from some original iterator 'iterator'. */
		/* explicit keyword is used because implicit conversion from other iterators is not desired */
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

		/* Exposing Base iterator */
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
			return &(operator*());
		}

		pointer operator& ()
		{
			return &this->getBase();
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
		reverse_iterator& operator += (difference_type d) const
		{
			this->setBase(this->getBase() - d);
			return *this;
		}

		/* reverse_iterator -= d */
		reverse_iterator& operator -= (difference_type d) const
		{
			this->setBase(this->getBase() + d);
			return *this;
		}
	};

	/* Reverse iterator non-member functions */

	/* Relational operators */
	template <class Iterator>
	inline bool operator == (
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
	{
		return lhs->base() == rhs->base();
	}

	template <class Iterator>
	inline bool operator != (
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
	{
		return !(lhs->base() == rhs->base());
	}
	
	template <class Iterator>
	inline bool operator < (
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
	{
		return lhs->base() > rhs->base();
	}
	
	template <class Iterator>
	inline bool operator <= (
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
	{
		return !(lhs->base() < rhs->base());
	}
	
	template <class Iterator>
	inline bool operator > (
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
	{
		return lhs->base() < rhs->base();
	}
	
	template <class Iterator>
	inline bool operator >= (
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
	{
		return !(lhs->base() > rhs->base());
	}

	/* return an iterator i where obj - i = d */
	template <class Iterator>
	inline reverse_iterator<Iterator> operator+ (
		typename reverse_iterator<Iterator>::difference_type d,
		const reverse_iterator<Iterator>& obj)
	{
		return reverse_iterator<Iterator>(obj.base() - d);
	}

	/* return the distance between iterators ( = right - left ) */
	template <class Iterator>
	inline typename reverse_iterator<Iterator>::difference_type operator- (
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
	{
		return rhs.base() - lhs.base();
	}

	/* Front insert iterator */
	template <typename Container>
	class front_insert_iterator
	: public iterator <output_iterator_tag, void, void, void, void>
	{
	protected:
		Container* container;

	public:
		typedef Container	container_type;
		
		/* Ctors */

		explicit front_insert_iterator(Container& cont) : container (&cont)
		{
			
		}

		/* Assignment overload operator */
		front_insert_iterator& operator= (typename Container::const_reference value)
		{
			container->push_front(value);
			return *this;
		}

		/* Access operators */
		front_insert_iterator& operator* (void)
		{
			return *this;
		}
	
		/* Trivial Increment operators */

		front_insert_iterator& operator++ (void)
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
	inline front_insert_iterator<Container> front_inserter(Container& container)
	{
		return front_insert_iterator<Container>(container);
	}

	/* Back insert iterator */
	template <typename Container>
	class back_insert_iterator
	: public iterator <output_iterator_tag, void, void, void, void>
	{
	protected:
		Container* container;

	public:
		typedef Container	container_type;
		
		/* Ctors */

		explicit back_insert_iterator(Container& cont) : container (&cont)
		{
			
		}

		/* Assignment overload operator */
		back_insert_iterator& operator= (typename Container::const_reference value)
		{
			container->push_back(value);
			return *this;
		}

		/* Access operators */
		back_insert_iterator& operator* (void)
		{
			return *this;
		}
	
		/* Trivial Increment operators */

		back_insert_iterator& operator++ (void)
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
	inline back_insert_iterator<Container> back_inserter(Container& container)
	{
		return back_insert_iterator<Container>(container);
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
	insert_iterator& operator=(typename Container::const_reference value)
	{
		iter = container->insert(iter, value);
		++iter;
		return *this;
	}

	/* Access operators */
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

	/* Returns an instance of back_insert_iterator for type Container */
	template <typename Container, typename Iterator>
	inline insert_iterator<Container> inserter(Container& container, Iterator i)
	{
		return insert_iterator<Container>(container, typename Container::iterator(i));
	}

	/* Normal iterator */
	/* Converts a pointer to an iterator */
	
	template <typename Iterator, typename Container>
	class normal_iterator
	{
	protected:
		Iterator base;
		
	public:
		typedef Iterator												iterator_type;
		typedef typename ft::iterator_traits<Iterator>::value_type		value_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
		typedef typename ft::iterator_traits<Iterator>::reference		reference;
		typedef typename ft::iterator_traits<Iterator>::pointer			pointer;

		/* Ctors */
		normal_iterator() : base(Iterator())
		{
			
		}

		/* Copy ctor */
		explicit normal_iterator(const Iterator& i) : base(i)
		{
			
		}

		/* iterator -> const_iterator */
		/* Lord help us */ 
		template<typename Iter>
		normal_iterator(const normal_iterator<
			Iter,
			typename ft::enable_if<			
				(ft::is_same<Iter, typename Container::pointer>::value),
				Container
				>::type>& i)
		: base(i.base())
		{
			
		}

	};
	
}

#pragma endregion