/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 14:44:38 by mbarut            #+#    #+#             */
/*   Updated: 2021/12/23 19:37:22 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_H
# define FT_VECTOR_H

# include <memory>
# include <iterator>

namespace ft
{
	template<typename T, typename Allocator = std::allocator<T> >
	class Vector
	{
	
	public:

		/* Type definitions to make life easier */

		typedef T										value_type;
		typedef T&										reference;
		typedef const T&								const_reference;
		typedef T*										pointer;
		typedef const T*								const_pointer;
		typedef Allocator								allocator_type;
		typedef	size_t									size_type;

	private:
	
		T									*_data;
		size_t								_capacity;
		size_t								_size;
		allocator_type						_allocator;

	public:

		/* Constructors */
		/* (1) empty container constructor (default constructor) */
		Vector(void)
		{
			this->_data = this->_allocator.allocate(5);
			this->_capacity = 5;
			this->_size = 0;
		}

		/* (2) fill constructor */
		//Vector()


		/* Destructors */
		~Vector(void)
		{
			this->_allocator.deallocate(this->_data, this->_capacity);
		}

		/* Copy constructor */
		Vector( const Vector &obj )
		{
			this->_data = this->_allocator.allocate(this->_capacity);
			for (size_t i = 0; i < obj._size; i++)
				this->_allocator.construct(&this->_data[i], obj._data[i]);
		}
		
		/* Assignment operator overload */

		Vector& operator= ( const Vector &obj )
		{
			this->_data = this->_allocator.allocate(this->_capacity);
			for (size_t i = 0; i < obj._size; i++)
				this->_allocator.construct(&this->_data[i], obj._data[i]);
			return *this;	
		}
		
	};
	
	
}	// namespace ft

#endif