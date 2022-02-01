/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 23:13:25 by mbarut            #+#    #+#             */
/*   Updated: 2022/02/01 15:55:16 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_iterator_base_funcs.hpp"
#include "ft_iterator_base_types.hpp"
#include "ft_util.hpp"

namespace ft
{
	template <typename Iterator>
	class reverse_iterator : public iterator
	<
	typename ft::iterator_traits<Iterator>::iterator_category,
	typename ft::iterator_traits<Iterator>::value_type,
	typename ft::iterator_traits<Iterator>::difference_type,
	typename ft::iterator_traits<Iterator>::pointer,
	typename ft::iterator_traits<Iterator>::reference
	>
	{
	public:

		typedef Iterator												iterator_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
		typedef typename ft::iterator_traits<Iterator>::reference		reference;
		typedef typename ft::iterator_traits<Iterator>::pointer			pointer;

	protected:

		Iterator	_base;
	
		/* Trivial Getter & Setter */
		iterator_type	getBase() const
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
		reverse_iterator(void) : _base(NULL)
		{
			// std::cout << "A reverse iterator has been constructed\n";
		}

		/* (2) initalization constructor */
		/* Constructs a reverse iterator from some original iterator 'iterator'. */
		/* explicit keyword is used because implicit conversion from other iterators is not desired */
		explicit reverse_iterator(iterator_type iterator) : _base(iterator)
		{
			// std::cout << "A reverse iterator has been constructed using another reverse iterator\n";
		}

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
		iterator_type	base() const
		{
			return this->getBase();
		}

		/* Member access operators */
		reference operator[] (difference_type d) const
		{
			return *(*this + d);
		}

		reference operator* () const
		{
			iterator_type tmp = this->getBase();
			--tmp;
			return *tmp;
		}

		pointer operator-> () const
		{
			return &(operator*());
		}

		/* not implemented */
		//pointer operator& ()
		//{
		//	return &this->getBase();
		//}

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
		reverse_iterator& operator+= (difference_type d)
		{
			this->setBase(this->getBase() - d);
			return *this;
		}

		/* reverse_iterator -= d */
		reverse_iterator& operator-= (difference_type d)
		{
			this->setBase(this->getBase() + d);
			return *this;
		}
	};

	/* Reverse iterator non-member functions */

	/* Relational operators */
	template <class Iterator>
	inline bool operator== (const reverse_iterator<Iterator>& lhs,
							const reverse_iterator<Iterator>& rhs)
	{
		return lhs->base() == rhs->base();
	}

	template <class Iterator>
	inline bool operator!= (const reverse_iterator<Iterator>& lhs,
							const reverse_iterator<Iterator>& rhs)
	{
		return !(lhs->base() == rhs->base());
	}
	
	template <class Iterator>
	inline bool operator < (const reverse_iterator<Iterator>& lhs,
							const reverse_iterator<Iterator>& rhs)
	{
		return lhs->base() > rhs->base();
	}
	
	template <class Iterator>
	inline bool operator<= (const reverse_iterator<Iterator>& lhs,
							const reverse_iterator<Iterator>& rhs)
	{
		return !(lhs->base() < rhs->base());
	}
	
	template <class Iterator>
	inline bool operator > (const reverse_iterator<Iterator>& lhs,
							const reverse_iterator<Iterator>& rhs)
	{
		return lhs->base() < rhs->base();
	}
	
	template <class Iterator>
	inline bool operator>= (const reverse_iterator<Iterator>& lhs,
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

	/* Normal iterator:
	** Converts a pointer to an iterator. */
	template <typename Iterator, typename Container>
	class normal_iterator
	{

	protected:

		Iterator ptr;
		
	public:

		typedef Iterator												iterator_type;
		typedef typename ft::iterator_traits<Iterator>::value_type		value_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
		typedef typename ft::iterator_traits<Iterator>::reference		reference;
		typedef typename ft::iterator_traits<Iterator>::pointer			pointer;

		/* Ctors */
		normal_iterator() : ptr(Iterator())
		{
			
		}

		/* Copy ctor */
		explicit normal_iterator(const Iterator& i) : ptr(i)
		{
			
		}

		/* iterator -> const_iterator */
		template<typename Iter>
		normal_iterator(const normal_iterator<
			Iter,
			typename ft::enable_if<			
				(ft::is_same<Iter, typename Container::pointer>::value), Container>::type>& i)
		: ptr(i.ptr())
		{
			
		}

		const Iterator& base() const
		{
			return ptr;
		}

		reference			operator* () const
		{
			return *ptr;
		}

		pointer				operator->() const
		{
			return ptr;
		}

		normal_iterator&	operator++()
		{
			++ptr;
			return *this;
		}

		normal_iterator		operator++(int)
		{
			return normal_iterator(ptr++);
		}

		normal_iterator&	operator--()
		{
			--ptr;
			return *this;
		}

		normal_iterator		operator--(int)
		{
			return normal_iterator(ptr--);
		}

		reference			operator[] (const difference_type& i) const
		{
			return ptr[i];
		}
		
		normal_iterator&	operator+= (const difference_type& i)
		{
			ptr += i;
			return *this;
		}

		normal_iterator&	operator-= (const difference_type& i)
		{
			ptr -= i;
			return *this;
		}

		normal_iterator		operator+ (const difference_type& i) const
		{
			return normal_iterator(ptr + i);
		}

		normal_iterator		operator- (const difference_type& i) const
		{
			return normal_iterator(ptr - i);
		}

	};

	/* Normal iterator non-member functions */

	/* Relational operators with different iterator types */
	template <class IteratorL, class IteratorR, class Container>
	inline bool operator== (const normal_iterator<IteratorL, Container>& lhs,
							const normal_iterator<IteratorR, Container>& rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <class IteratorL, class IteratorR, class Container>
	inline bool operator!= (const normal_iterator<IteratorL, Container>& lhs,
							const normal_iterator<IteratorR, Container>& rhs)
	{
		return !(lhs->base() == rhs->base());
	}

	template <class IteratorL, class IteratorR, class Container>
	inline bool operator > (const normal_iterator<IteratorL, Container>& lhs,
							const normal_iterator<IteratorR, Container>& rhs)
	{
		return lhs->base() > rhs->base();
	}

	template <class IteratorL, class IteratorR, class Container>
	inline bool operator<= (const normal_iterator<IteratorL, Container>& lhs,
							const normal_iterator<IteratorR, Container>& rhs)
	{
		return !(lhs->base() < rhs->base());
	}

	template <class IteratorL, class IteratorR, class Container>
	inline bool operator < (const normal_iterator<IteratorL, Container>& lhs,
							const normal_iterator<IteratorR, Container>& rhs)
	{
		return lhs->base() < rhs->base();
	}

	template <class IteratorL, class IteratorR, class Container>
	inline bool operator>= (const normal_iterator<IteratorL, Container>& lhs,
							const normal_iterator<IteratorR, Container>& rhs)
	{
		return !(lhs->base() > rhs->base());
	}
	
	/* Relational operators with same iterator types */
	template <class Iterator, class Container>
	inline bool operator== (const normal_iterator<Iterator, Container>& lhs,
							const normal_iterator<Iterator, Container>& rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <class Iterator, class Container>
	inline bool operator!= (const normal_iterator<Iterator, Container>& lhs,
							const normal_iterator<Iterator, Container>& rhs)
	{
		return !(lhs->base() == rhs->base());
	}

	template <class Iterator, class Container>
	inline bool operator > (const normal_iterator<Iterator, Container>& lhs,
							const normal_iterator<Iterator, Container>& rhs)
	{
		return lhs->base() > rhs->base();
	}

	template <class Iterator, class Container>
	inline bool operator<= (const normal_iterator<Iterator, Container>& lhs,
							const normal_iterator<Iterator, Container>& rhs)
	{
		return !(lhs->base() < rhs->base());
	}

	template <class Iterator, class Container>
	inline bool operator < (const normal_iterator<Iterator, Container>& lhs,
							const normal_iterator<Iterator, Container>& rhs)
	{
		return lhs->base() < rhs->base();
	}

	template <class Iterator, class Container>
	inline bool operator>= (const normal_iterator<Iterator, Container>& lhs,
							const normal_iterator<Iterator, Container>& rhs)
	{
		return !(lhs->base() > rhs->base());
	}

	/* return the distance between iterators ( = right - left ) */
	template <class IteratorL, class IteratorR, class Container>
	inline typename normal_iterator<IteratorL, Container>::difference_type operator- (
		const normal_iterator<IteratorL, Container>& lhs,
		const normal_iterator<IteratorR, Container>& rhs)
	{
		return rhs.base() - lhs.base();
	}

	template <class Iterator, class Container>
	inline typename normal_iterator<Iterator, Container>::difference_type operator- (
		const normal_iterator<Iterator, Container>& lhs,
		const normal_iterator<Iterator, Container>& rhs)
	{
		return rhs.base() - lhs.base();
	}

	template <class Iterator, class Container>
	inline normal_iterator<Iterator, Container> operator+ (
		typename normal_iterator<Iterator, Container>::difference_type d,
		const normal_iterator<Iterator, Container>& i)
	{
		return normal_iterator<Iterator, Container>(i.base() + d);
	}

}

#pragma endregion