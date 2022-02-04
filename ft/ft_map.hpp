/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 14:44:43 by mbarut            #+#    #+#             */
/*   Updated: 2022/02/04 21:57:10 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pair.hpp"
#include "ft_util.hpp"
#include "ft_iterator.hpp"
#include "ft_vector.hpp"
#include <algorithm>
#include <memory>

namespace ft
{
	template <
		class Key,
		class T,
		class Compare = ft::less<Key>,
		class Allocator = std::allocator< ft::pair<const Key, T> >
		>
	class map
	{

	public:
		typedef map<Key, T, Compare, Allocator>			map_type;
		typedef Key										key_type;
		typedef T										value_type;
		typedef Compare									compare_type;
		typedef Allocator								allocator_type;
		typedef ft::pair<const key_type, value_type>	pair_type;
		typedef typename Allocator::reference			reference;
		typedef typename Allocator::const_reference		const_reference;
		typedef typename Allocator::pointer				pointer;
		typedef typename Allocator::const_pointer		const_pointer;
		typedef ft::iterator<pointer, pointer>			iterator;
		typedef const ft::iterator<pointer, pointer>	const_iterator;
		typedef typename Allocator::difference_type		difference_type;
		typedef typename Allocator::size_type			size_type;


	private:
		pointer											_p;
		size_type										_size;
		size_type										_capacity;

		/* ctor 1 */
		map() : _size(0), _capacity(0), _p(allocator_type().allocate())
		{
			
		}

		/* copy ctor */
		map(const map_type& rhs) : _size(rhs._size), _capacity(rhs._capacity), _p(allocator_type().allocate(rhs._size))
		{
			int count = 0;
			for (const_iterator i = &rhs.begin(); i != &rhs.end(); ++i, ++count)
			{
				allocator_type().construct(&_p[count], *i);
			}
		}

		~map()
		{
			if (!empty())
			{
				for (const_iterator i = begin(); i != end(); ++i)
					allocator_type().destroy(i);
				allocator_type().deallocate(_p, _capacity);
			}
		}

		map_type& insert(const value_type& value)
		{
			if (++_size >= _capacity)
				reserve(_capacity * 2);
			Allocator().construct(_p.end() - 1, value);
			return *this;
		}

		void		swap(map_type& other)
		{
			//size_type	capacity = this->_capacity;
			//size_type	size = this->_size;
			pointer		p = this->_p;

			//this->_capacity = other._capacity;
			//this->_size = other._size;
			this->_p = other._p;

			//other._capacity = capacity;
			//other._size = size;
			other._p = p;
		}

		value_type&	operator[] (const key_type& key)
		{
			iterator i = find_if(begin(), end(), key);
			if (i == end())
			{
				size_type op = _size;
				insert(pair_type(key, value_type()));
				return _p[op].second;
			}
			else
				return &_p[i];
		}

		map_type& reserve(size_type given_capacity)
		{
			int count = 0;
			if (given_capacity < this->_capacity)
				return *this;
			pointer tmp = allocator_type().allocate(_capacity);
			for (const_iterator i = this->begin(); i != end(); ++i, ++count)
				allocator_type().construct(&tmp[count], *i);
			swap(_p, tmp);
			for (iterator i = tmp.begin(); i != tmp.end(); ++i)
				Allocator().destroy();
			Allocator().deallocate(tmp, _capacity);
			_capacity = given_capacity;
			return *this;
		}

		bool empty() const
		{
			return _size == 0;
		}

		iterator begin() const
		{
			return &_p[0];
		}

		iterator end() const
		{
			return &_p[_size];
		}

		const_iterator cbegin() const
		{
			return &_p[0];
		}

		const_iterator cend() const
		{
			return &_p[_size];
		}

	};
	
}
