/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_construct.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:37:39 by mbarut            #+#    #+#             */
/*   Updated: 2022/01/31 18:52:22 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <new>
#include "ft_iterator_base_types.hpp"

namespace ft 
{
	template <typename T>
	inline T* __addressof(T& r)
	{
		return reinterpret_cast<T*>(&const_cast<char&>(reinterpret_cast<const volatile char&>(r)));
	}

	/* Construct an object by invoking an allocated object's constructor
	with an initializer. */

	template<typename T1, typename T2>
	inline void _Construct(T1* p, const T2& value)
	{
		::new(static_cast<void *>(p)) T1(value);
	}

	/* Destruct the object pointed to by a pointer type. */
	template<typename T>
	inline void _Destroy(T* p)
	{
		p->~T();
	}

	template<bool>
	struct _Destroy_aux
	{
		template<typename ForwardIterator>
		static void __destroy(ForwardIterator first, ForwardIterator last)
		{
			for (; first != last; ++first)
				ft::_Destroy(ft::__addressof(*first));
		}
	};

	template<>
	struct _Destroy_aux<true>
	{
		template<typename ForwardIterator>
		static void __destroy(ForwardIterator, ForwardIterator)
		{

		}
	};

	/* Destroy a range of objects. */
	template<typename ForwardIterator>
	inline void _Destroy(ForwardIterator first, ForwardIterator last)
	{
		//typedef typename ft::iterator_traits<ForwardIterator>::value_type value_type;
		(void)first;
		(void)last;
	}
	
}

#pragma endregion