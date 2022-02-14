/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 14:44:40 by mbarut            #+#    #+#             */
/*   Updated: 2022/02/14 16:43:51 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "vector.hpp"
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

	private:

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

		container_type&	operator= (const container_type& rhs)
		{
			if (*this == rhs)
				return *this;
			this->_base = rhs._base;
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

		friend void	swap(stack<T, Container>& s1, stack<T, Container>& s2)
		{
			s1.swap(s2);
		}

	};

}
