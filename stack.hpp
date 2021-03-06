/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 14:44:40 by mbarut            #+#    #+#             */
/*   Updated: 2022/03/12 23:32:48 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "vector.hpp"
#include "debug.hpp"
#include <cstddef>

namespace ft
{
	template<
		typename T,
		typename Container = ft::vector<T>
	> class stack
	{

	public:

		typedef T											value_type;
		typedef Container									container_type;
		typedef size_t										size_type;
		typedef typename container_type::reference			reference;
		typedef typename container_type::const_reference	const_reference;	

	protected:	

		container_type			c;

	public:

		stack()
		{
			
		}

		~stack()
		{
			
		}

		stack(const stack& other): c(other.c)
		{

		}

		container_type&	operator= (const container_type& rhs)
		{
			if (*this == rhs)
				return *this;
			this->c = rhs.c;
			return *this;
		}

		void			push( const value_type& value )
		{
			c.push_back(value);
		}

		void			pop()
		{
			c.pop_back();
		}

		size_type		size() const
		{
			return c.size();
		}
	
		reference		top()
		{
			return c.back();
		}
		
		const_reference	top() const
		{
			return c[size() - 1];
		}

		bool			empty() const
		{
			return size() == 0;
		}
		
		friend bool operator== (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{ return lhs.c == rhs.c; }
		
		friend bool operator!= (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{ return !(lhs == rhs); }

  		friend bool operator<  (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{ return lhs.c < rhs.c; }

		friend bool operator>  (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{ return lhs.c > rhs.c; }

		friend bool operator<= (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{ return !(lhs > rhs); }

		friend bool operator>= (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{ return !(lhs < rhs); }

	};

}
