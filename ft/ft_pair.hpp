/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pair.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 13:34:24 by mbarut            #+#    #+#             */
/*   Updated: 2022/01/31 20:34:44 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
	/* ft::pair:
	** Holds two objects of arbitrary type.
	*/
	template <typename T1, typename T2>
	struct pair
	{
		T1	first;
		T2	second;

		/* Default ctor */
		pair() : first(T1()), second(T2()) { }

		/* Copy ctor (1) */
		pair(const T1& obj1, const T2& obj2) : first(obj1), second(obj2) { }

		/* Copy ctor (2) */
		template <typename U1, typename U2>
		pair(const pair<U1, U2>& other) : first(other.first), second(other.second) { }
	};

	/* Relational operators for ft::pair */

	template <typename T1, typename T2>
	inline bool operator== (const pair<T1, T2>& obj1, const pair<T1, T2>& obj2)
	{
		return obj1.first == obj2.first && obj1.second == obj2.second;
	}

	template <typename T1, typename T2>
	inline bool operator!= (const pair<T1, T2>& obj1, const pair<T1, T2>& obj2)
	{
		return !(obj1 == obj2);
	}

	template <typename T1, typename T2>
	inline bool operator< (const pair<T1, T2>& obj1, const pair<T1, T2>& obj2)
	{
		return obj1.first < obj2.first \
			|| (!(obj1.first < obj2.first) && obj1.second < obj2.second );
	}

	template <typename T1, typename T2>
	inline bool operator> (const pair<T1, T2>& obj1, const pair<T1, T2>& obj2)
	{
		return obj1.first > obj2.first \
			|| (!(obj1.first > obj2.first) && obj1.second > obj2.second );
	}

	template <typename T1, typename T2>
	inline bool operator<= (const pair<T1, T2>& obj1, const pair<T1, T2>& obj2)
	{
		return !(obj2 > obj1);
	}

	template <typename T1, typename T2>
	inline bool operator>= (const pair<T1, T2>& obj1, const pair<T1, T2>& obj2)
	{
		return !(obj1 < obj2);
	}

	/* ft::make_pair */

	template <typename T1, typename T2>
	inline ft::pair<T1, T2> make_pair(T1 obj1, T2 obj2)
	{
		return ft::pair<T1, T2>(obj1, obj2);
	}
}

#pragma endregion