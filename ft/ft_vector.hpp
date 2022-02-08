/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 14:44:38 by mbarut            #+#    #+#             */
/*   Updated: 2022/02/09 00:24:38 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <exception>
#include <memory>
#include <sstream>
#include "ft_iterator_base_funcs.hpp"
#include "ft_iterator_base_types.hpp"
#include "ft_iterator.hpp"
#include "ft_util.hpp"
#include "ft_algorithm.hpp"

namespace ft
{
	template <class _Tp, class _Allocator >
	class _vector_base
	{

	protected:

		typedef _Tp										value_type;
		typedef _Allocator								allocator_type;
		typedef typename _Allocator::size_type			size_type;
		typedef typename _Allocator::pointer			pointer;
		typedef ft::iterator<pointer, pointer>			iterator;
			
		allocator_type									_allocator;
		size_type										_capacity;
		size_type										_size;
		pointer											_p;

		_vector_base(const allocator_type& alloc = allocator_type()) : _allocator(alloc), _capacity(0), _size(0)
		{
			_M_allocate();
		}

		explicit _vector_base(size_type n, const value_type& val = value_type(),
			const allocator_type& alloc = allocator_type()) : _allocator(alloc), _capacity(0), _size(0)
		{
			_M_allocate(n);
			_M_fill_assign(n, val);
		}

		template <class InputIterator>
		_vector_base(InputIterator first, InputIterator last,
			const allocator_type& alloc = allocator_type()) : _allocator(alloc), _capacity(0), _size(0)
		{
			_M_allocate();
			_M_range_assign(first, last, typename ft::is_integral<InputIterator>::type());
		}

		_vector_base(const _vector_base& b) : _allocator(b._allocator), _capacity(0), _size(0)
		{
			_M_allocate(b._size);
 			_M_copy_assign(b);
		}
		
		void		_M_allocate(size_type capacity = 0)
		{
			_capacity = capacity;
			_p = _allocator.allocate(_capacity);
		}

		void		_M_deallocate()
		{
			_allocator.deallocate(_p, _capacity);
		}

		void		_M_swap(_vector_base& _other)
		{
			size_type	capacity = this->_capacity;
			size_type	size = this->_size;
			pointer		p = this->_p;

			this->_capacity = _other._capacity;
			this->_size = _other._size;
			this->_p = _other._p;

			_other._capacity = capacity;
			_other._size = size;
			_other._p = p;
		}

		void		_M_reserve(size_type n)
		{
			if (n > this->_allocator.max_size())
				throw (std::length_error("vector::reserve"));
			if (n > this->_capacity)
			{
				_vector_base	tmp;
				tmp._M_deallocate();
				tmp._M_allocate(n);
				tmp._M_copy_assign(*this);
				_M_swap(tmp);
			}
		}

		void		_M_expand(const value_type& val)
		{
			if (_size == _capacity)
			{
				if (_capacity == 0)
					_M_reserve(1);
				else
					_M_reserve(_capacity * 2);
			}
			_allocator.construct(_p + _size, val);
			++this->_size;
		}

		void		_M_destroy()
		{
			while (_size != 0)
			{
				_allocator.destroy(_p + _size - 1);
				--_size;
			}
		}

		void		_M_range_check(size_type n, const std::string &message = "") const
		{
			if (n >= _size)
			{
				std::ostringstream	oss;
				oss << "vector::";
				if (message.empty())
					oss << "_M_check_range: n";
				oss << message << " (which is " << n <<
					") >= this->size() (which is " << this->_size << ")";
				throw (std::out_of_range(oss.str()));
			}
		}

		void		_M_fill_assign(size_type n, const value_type& val)
		{
			_M_destroy();
			if (n > _capacity)
			{
				_M_deallocate();
				_M_allocate(n);
			}
			while (_size < n)
				_M_expand(val);
		}

		template <class Integer>
		void		_M_range_assign(Integer n, Integer val, ft::true_type)
		{
			_M_fill_assign(static_cast<size_type>(n), val);
		}

		template <class InputIterator>
		void		_M_range_assign(InputIterator first, InputIterator last, ft::false_type)
		{
			_M_destroy();
			size_type	dist = static_cast<size_type>(ft::distance<InputIterator>(first, last));
			if (dist > _capacity)
			{
				_M_deallocate();
				_M_allocate(dist);
			}
			for (InputIterator it = first; it != last; it++)
				_M_expand(*it);
		}

		void		_M_copy_assign(const _vector_base& v)
		{
			_M_destroy();
			if (v._size > this->_capacity)
			{
				_M_deallocate();
				_M_allocate(v._size);
			}
			for (size_type i = 0; i < v._size; i++)
			{
				if (_size == _capacity)
				{
					if (_capacity == 0)
						_M_reserve(1);
					else
						_M_reserve(_capacity * 2);
				}
				_allocator.construct(_p + _size, v._p[i]);
				++_size;
			}				
		}

		template <class InputIterator>
		InputIterator	_M_fill_insert(InputIterator pos, size_type n, const value_type& val)
		{
			if (n == 0)
				return (pos);

			InputIterator	res = pos;
			if (n > _capacity - _size)
			{
				_vector_base	tmp;
				if (n <= _capacity * 2 - _size)
					tmp._M_reserve(_capacity * 2);
				else
					tmp._M_reserve(_size + n);

				InputIterator	it = InputIterator(_p);
				while (it != pos)
					tmp._M_expand(*it++);

				res = InputIterator(_p + _size);
				for (size_type i = 0; i < n; i++)
					tmp._M_expand(val);

				while (it != InputIterator(_p + _size))
					tmp._M_expand(*it++);

				_M_swap(tmp);
			}
			else
			{
				InputIterator	it = InputIterator(_p + _size);
				while (it != pos)
				{
					--it;
					_allocator.construct(it.base() + n, *it);
					_allocator.destroy(it.base());
				}
				for (size_type i = 0; i < n; i++)
				{
					_allocator.construct(it.base(), val);
					++it;
					++_size;
				}
			}
			return (res);
		}

		template <class Integer>
		void		_M_range_insert(iterator pos, Integer n, Integer val, ft::true_type)
		{
			_vector_fill_insert(pos, static_cast<size_type>(n), val);
		}

		template <class InputIterator>
		void		_M_range_insert(iterator pos, InputIterator first, InputIterator last, ft::false_type)
		{
			if (first == last)
				return ;

			_vector_base		tmp(first, last);

			for (size_type i = 0; i < tmp._size; i++)
			{
				_vector_check_range(i, "at: n");
				pos = _vector_fill_insert(pos, 1, tmp._p(i));
				++pos;
			}
		}
	};

	template <typename T, class Allocator = std::allocator<T> >
	class vector : protected _vector_base<T, Allocator>
	{
	
	public:

		typedef T													value_type;
		typedef Allocator											allocator_type;
		typedef typename Allocator::reference						reference;
		typedef typename Allocator::const_reference					const_reference;
		typedef typename Allocator::pointer							pointer;
		typedef typename Allocator::const_pointer					const_pointer;
		typedef typename Allocator::difference_type					difference_type;
		typedef typename Allocator::size_type						size_type;
		typedef random_access_iterator<pointer, pointer>			iterator;
		typedef random_access_iterator<const_pointer, pointer>		const_iterator;
		typedef ft::reverse_iterator<iterator>						reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;
		typedef _vector_base<T, Allocator>							base;	
		typedef ft::random_access_iterator_tag						iterator_category;

	protected:

		using	base::_M_allocate;
		using	base::_M_deallocate;
		using	base::_M_copy_assign;
		using	base::_M_range_check;
		using	base::_M_range_assign;
		using	base::_M_fill_assign;
		using	base::_M_fill_insert;
		using	base::_p;
		using	base::_size;
		using	base::_capacity;
		using	base::_allocator;

	public:

		/* ctor 1 */
		explicit vector(const allocator_type& alloc = allocator_type()) : base(alloc) { }

		/* ctor 2 */
		explicit vector(size_type n, const value_type& val = value_type(),
			const allocator_type& alloc = allocator_type()) : base(n, val, alloc) { }

		/* ctor 3 */
		template <class InputIterator>
		vector(InputIterator first, InputIterator last,
			const allocator_type& alloc = allocator_type()) : base(first, last, alloc) { }

		/* ctor 4 */
		vector(const vector& v) : base(v) { }

		/* ctor 5 */
		~vector()
		{
 			clear();
			_M_deallocate();
 		}

		/* assignment operator overload */
		vector&		operator=(const vector& rhs)
		{
			if (this == &rhs)
				return (*this);
			_M_copy_assign(rhs);
 			return (*this);
		}

		/* iterators */
		iterator				begin()
		{
			return (iterator(_p));
		}

		const_iterator			begin() const
		{
			return (const_iterator(_p));
		}

		iterator				end()
		{
			return (iterator(_p + _size));
		}

		const_iterator			end() const
		{
			return (const_iterator(_p + _size));
		}

		reverse_iterator		rbegin()
		{
			return (reverse_iterator(end()));
		}

		const_reverse_iterator	rbegin() const
		{
			return (const_reverse_iterator(end()));
		}

		reverse_iterator		rend()
		{
			return (reverse_iterator(begin()));
		}

		const_reverse_iterator	rend() const
		{
			return (const_reverse_iterator(begin()));
		}

		/* member functions */
		bool			empty() const
		{
			return (this->_size == 0);
		}

		size_type		size() const
		{
			return (this->_size);
		}

		size_type		capacity() const
		{
			return (this->_capacity);
		}

		size_type		max_size() const
		{
			return (this->_allocator.max_size());
		}

		void			resize(size_type n, value_type val = value_type())
		{
			while (n < _size)
				pop_back();
			if (n > _capacity)
				reserve(n);
			while (n > _size)
				push_back(val);
		}

		void			reserve(size_type n)
		{
			if (n > this->max_size())
				throw (std::length_error("vector::reserve"));
			if (n > this->_capacity)
			{
				vector	tmp;
				tmp._M_allocate(n);
				tmp._M_copy_assign(*this);
				swap(tmp);
			}
		}

		allocator_type get_allocator() const
		{
			return this->Allocator();
		}

		/* access operators */
 		reference			operator[](size_type n)
		{
			return (this->_p[n]);
		}

		const_reference		operator[](size_type n) const
		{
			return (this->_p[n]);
		}

		reference			at(size_type n)
		{
			_M_range_check(n, "_M_range_check: __n");
			return (this->_p[n]);
		}

		const_reference		at(size_type n) const
		{
			_M_range_check(n, "_M_range_check: __n");
			return (this->_p[n]);
		}

		reference			front()
		{
			return (this->_p[0]);
		}

		const_reference		front() const
		{
			return (this->_p[0]);
		}

		reference			back()
		{
			return (this->_p[this->_size - 1]);
		}

		const_reference		back() const
		{
			return (this->_p[this->_size - 1]);
		}

		/* modifiers */
		template <class InputIterator>
		void		assign(InputIterator first, InputIterator last)
		{
			_M_range_assign(first, last, ft::is_integral<InputIterator>());
		}

		void		assign(size_type n, const value_type& val)
		{
			_M_fill_assign(n, val);
		}

		void		push_back(const value_type& val)
		{
			if (_size == _capacity)
			{
				if (_capacity == 0)
					reserve(1);
				else
					reserve(_capacity * 2);
			}
			_allocator.construct(_p + _size, val);
			++_size;
		}

		void		pop_back()
		{
			if (_size == 0)
				return ;
			_allocator.destroy(_p + _size - 1);
			--_size;
		}

		iterator	insert(iterator position, const value_type& val)
		{
			return (_M_fill_insert(position, 1, val));
		}

		void		insert(iterator position, size_type n, const value_type& val)
		{
			_M_fill_insert(position, n, val);
		}

		template <class InputIterator>
		void		insert(iterator position, InputIterator first, InputIterator last)
		{
			_M_range_insert(position, first, last, ft::is_integral<InputIterator>());
		}

		iterator	erase(iterator position)
		{
			_allocator.destroy(position.base());

			iterator	it = position;
			while (++it != end())
			{
				_allocator.construct(it.base() - 1, *it);
				_allocator.destroy(it.base());
			}
			--_size;
			return (position);
		}

		iterator	erase(iterator first, iterator last)
		{
			difference_type	diff = ft::distance(first, last);
			if (diff <= 0)
				return (first);
			iterator	it = first;
			while (it != last)
				_allocator.destroy((it++).base());
			--it;
			while (++it != end())
			{
				_allocator.construct((it - diff).base(), *it);
				_allocator.destroy(it.base());
			}
			_size -= diff;
			return (first);
		}

		void		swap(vector& v)
		{
			size_type	capacity = this->_capacity;
			size_type	size = this->_size;
			pointer		p = this->_p;

			this->_capacity = v._capacity;
			this->_size = v._size;
			this->_p = v._p;

			v._capacity = capacity;
			v._size = size;
			v._p = p;
		}

		void		clear()
		{
			while (_size != 0)
				pop_back();
		}
	};

	/* non-member comparison operator overloads */
	template <class T, class Allocator>
	bool	operator== (const ft::vector<T, Allocator>& lhs, const ft::vector<T, Allocator>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <class T, class Allocator>
	bool	operator!= (const ft::vector<T, Allocator>& lhs, const ft::vector<T, Allocator>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Allocator>
	bool	operator < (const ft::vector<T, Allocator>& lhs, const ft::vector<T, Allocator>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Allocator>
	bool	operator<= (const ft::vector<T, Allocator>& lhs, const ft::vector<T, Allocator>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Allocator>
	bool	operator > (const ft::vector<T, Allocator>& lhs, const ft::vector<T, Allocator>& rhs)
	{
		return rhs < lhs;
	}

	template <class T, class Allocator>
	bool	operator>= (const ft::vector<T, Allocator>& lhs, const ft::vector<T, Allocator>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class T, class Allocator>
	void	swap(ft::vector<T, Allocator>& v1, ft::vector<T, Allocator>& v2)
	{
		v1.swap(v2);
	}
}
