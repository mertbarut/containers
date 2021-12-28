/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 13:34:24 by mbarut            #+#    #+#             */
/*   Updated: 2021/12/28 15:14:10 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


namespace ft
{
	/* ft::pair:
	** holds two objects of arbitrary type
	*/

	template <typename T1, typename T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		T1	first;
		T2	second;
		
		/* Default ctor */
		pair() : first(), second()
		{
			
		}

		/* Copy ctor (1) */
		pair(const T1& obj1, const T2& obj2) : first(obj1), second(obj2)
		{
			
		};

		/* Copy ctor (2) */
		template <typename U1, typename U2>
		pair(const pair<U1, U2>& obj) : first(obj.first), second(obj.second)
		{
			
		}
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
		return obj1.first < obj2.first || (!(obj1.first < obj2.first) && obj1.second < obj2.second );
	}

	template <typename T1, typename T2>
	inline bool operator> (const pair<T1, T2>& obj1, const pair<T1, T2>& obj2)
	{
		return obj1.first > obj2.first || (!(obj1.first > obj2.first) && obj1.second > obj2.second );
	}

	template <typename T1, typename T2>
	inline bool operator<= (const pair<T1, T2>& obj1, const pair<T1, T2>& obj2)
	{
		return !(obj2 < obj1);
	}

	template <typename T1, typename T2>
	inline bool operator>= (const pair<T1, T2>& obj1, const pair<T1, T2>& obj2)
	{
		return !(obj1 < obj2);
	}

	/* ft::make_pair */

	template <typename T1, typename T2>
	inline pair<T1, T2> make_pair(T1 obj1, T2 obj2)
	{
		return pair<T1, T2>(obj1, obj2);
	}
}
