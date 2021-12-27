/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 14:09:36 by mbarut            #+#    #+#             */
/*   Updated: 2021/12/27 18:41:32 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft
{
	/* ft::is_same */

	template <typename T, typename U>
	struct is_same
	{
		static const bool value = false;
	};
	
	template <typename T>
	struct is_same<T, T>
	{
		static const bool value = true;
	};

	/* ft::enable_if */

	template <bool condition, class T = void>
	struct enable_if
	{
		
	};

	template <class T>
	struct enable_if <true, T>
	{
		typedef T type;
	};
	
	/* ft::integral_constant */
	
	template <class T, T v>
	struct integral_constant 
	{
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T, v> type;
	};

	template <class T, T v> const 
	T integral_constant<T, v>::value;

	/* true_type, false_type */

	typedef integral_constant<bool, true>  true_type;
	typedef integral_constant<bool, false> false_type;

	/* ft::is_integral */
	template <class T> struct is_integral : false_type { };

	template <> struct is_integral<bool> : true_type { };
	template <> struct is_integral<char> : true_type { };
	template <> struct is_integral<unsigned char> : true_type { };
	template <> struct is_integral<signed char> : true_type { };
	template <> struct is_integral<short> : true_type { };
	template <> struct is_integral<unsigned short> : true_type { };
	template <> struct is_integral<int> : true_type { };
	template <> struct is_integral<unsigned int> : true_type { };
	template <> struct is_integral<long long> : true_type { };
	template <> struct is_integral<unsigned long long> : true_type { };
	
	/* lexicographical compare:
	** return true if the first sequence is lexicographically smaller than the second sequence,
	** else return false 
	*/
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 begin1, InputIterator1 end1, InputIterator2 begin2, InputIterator2 end2)
	{
		while (begin1 != end1)
		{
			if (begin2 == end2 || *begin2 < *end1)
				return false;
			else if (*begin1 < *begin2)
				return true;
			++begin1; ++begin2;
		}
		return (begin2 != end2);
	}
}
