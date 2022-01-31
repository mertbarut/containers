/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 14:44:38 by mbarut            #+#    #+#             */
/*   Updated: 2022/01/31 18:51:59 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_H
# define FT_VECTOR_H

#include "ft_iterator.hpp"
#include "ft_construct.hpp"
#include <memory>


namespace ft
{
	template<typename T, typename Alloc>
	struct _Vector_base
	{
		typedef typename Alloc::template rebind<T>::other T_alloc_type;
		
		/* nested class */
		struct _Vector_impl : public T_alloc_type
		{
			T*		start;
			T*		finish;
			T*		end_of_storage;

			/* ctor 1 for _Vector_impl */
			_Vector_impl() : T_alloc_type(), start(0), finish(0), end_of_storage(0)
			{
				
			}

			/* ctor 2 for _Vector_impl */
			_Vector_impl(const T_alloc_type& a) : T_alloc_type(a), start(0), finish(0), end_of_storage(0)
			{
					
			}
		};

	public:

		typedef Alloc allocator_type;

		_Vector_impl impl;

		T* allocate(size_t n)
		{
			return n != 0 ? impl.allocate(n) : 0;
		}
		
		void deallocate (T* p, size_t n)
		{
			if (p)
				impl.deallocate(p, n);
		}

		T_alloc_type& get_T_allocator()
		{
			return *static_cast<T_alloc_type *>(this->impl);
		}

		allocator_type get_allocator() const
		{
			return allocator_type(get_T_allocator());
		}

		/* ctor 1 for _Vector_base */
		_Vector_base() : impl()
		{
			
		}
		
		/* ctor 2 for _Vector_base */
		_Vector_base(const allocator_type& a) : impl(a)
		{
				
		}

		/* ctor 3 for _Vector_base */
		_Vector_base(size_t n, const allocator_type& a) : impl(a)
		{
			this->impl.start = this->allocate(n);			
		}
		
		/* dtor for _Vector_base */
		~_Vector_base()
		{
			deallocate(this->impl.start, this->impl.end_of_storage - this->impl.start);
		}	
	};

	template<typename T, typename Allocator = std::allocator<T> >
	class vector : protected _Vector_base<T, Allocator>
	{
	
		typedef typename Allocator::value_type					allocator_value_type;
		typedef _Vector_base<T, Allocator>						base;
		typedef vector<T, Allocator>							vector_type;
		typedef typename base::T_alloc_type						T_alloc_type;
	
	public:

		typedef T												value_type;
		typedef typename T_alloc_type::reference				reference;
		typedef typename T_alloc_type::const_reference			const_reference;
		typedef typename T_alloc_type::pointer					pointer;
		typedef typename T_alloc_type::const_pointer			const_pointer;
		typedef ft::normal_iterator<pointer, vector_type>		iterator;
		typedef ft::normal_iterator<const_pointer, vector_type>	const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef Allocator										allocator_type;
		typedef	size_t											size_type;
		typedef ptrdiff_t										difference_type;

	protected:
	
		using base::allocate;
		using base::deallocate;
		using base::impl;
		using base::get_T_allocator;

		void fill_initialize(size_type n, const value_type& value)
		{
			std::uninitialized_fill_n(this->impl.start, n, value);
			this->impl.finish = this->impl.end_of_storage;
		}

		template<typename Integer>
		void initialize_dispatch(Integer n, Integer value, ft::true_type)
		{
			this->impl.start = allocate(static_cast<size_type>(n));
			this->impl.end_of_storage = this->impl.start + static_cast<size_type>(n);
			fill_initialize(static_cast<size_type>(n), value);
		}

		void fill_assign(size_type n, const value_type& value)
		{
			if (n > this->capacity())
			{
				vector tmp(n, value, get_T_allocator());
				tmp.swap(*this);
			}
			else if (n > this->size())
			{
				std::fill(this->begin(), this->end(), value);
				std::uninitialized_fill_n(this->impl.finish, n - this->size(), get_T_allocator());
				this->impl.finish += n - this->size();
			}
			else
				erase_at_end(std::fill_n(this->impl.start, n, value));
		}

		void erase_at_end(pointer pos)
		{
			std::allocator<T>::destroy(pos, this->impl.finish, get_T_allocator());
			this->impl.finish = pos;
		}

	public:

		/* Constructors */

		/* (1) empty container ctor (default) */
		vector(void) : base()
		{
			
		}

		/* (2) empty container ctor with allocator */
		explicit vector(const allocator_type& a) : base(a)
		{
			
		}
	
		/* (3) fill ctor */
		explicit vector(size_type n,
						const value_type& value = value_type(),
						const allocator_type& a = allocator_type()) : base(n, a)
		{
			fill_initialize(n, value);
		}

		/* (4) range ctor */
		template<typename InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& a = allocator_type()) : base(a)
		{
			typedef typename ft::is_integral<InputIterator>::value Integral;
			initialize_dispatch(first, last, Integral());
		}
		
		/* Destructors */
		~vector()
		{
			ft::_Destroy(this->impl.start);
		}

		/* Copy ctor */
		vector(const vector& obj) : base(obj.size(), obj.get_T_allocator())
		{
			this->impl.finish = std::uninitialized_copy(obj.begin(), obj.end(), this->impl.start);
		}

		/* Assignment operator */
		vector& operator= (const vector& obj)
		{
			(void)obj;
		}

		/* assign() methods */
		void assign(size_type n, const value_type& value)
		{
			fill_assign(n, value);
		}

		template<typename InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			typedef typename ft::is_integral<InputIterator>::value Integral;
			initialize_dispatch(first, last, Integral());
		}
		
		/* capacity() method */
		size_type capacity() const
		{
			return size_type(this->impl.end_of_storage - this->impl.start);
		}

		/* swap() method */
		void swap(vector& obj)
		{
			std::swap(this->impl.start, obj->impl.start);
			std::swap(this->impl.finish, obj->impl.finish);
			std::swap(this->impl.end_of_storage, obj->impl.end_of_storage);
		}

		/* size() method */
		size_type size() const
		{
			return size_type(this->impl.finish - this->impl.start);
		}

	};

}	// namespace ft

#endif