/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 14:09:36 by mbarut            #+#    #+#             */
/*   Updated: 2022/02/09 00:46:26 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sstream>

namespace ft
{
	/* ft::is_same
	** Sets its member constant 'value' to true if the given types are the same,
	** otherwise to false.
	*/

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

	/* ft::enable_if
	** Forms its member constant 'type' if the given condition is true,
	** otherwise 'type' is not formed.
	*/

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

	/* ft::is_integral
	** Sets its member constant 'value' to true if the given type is an integral,
	** if not to false.
	*/
	template <class T> struct is_integral : public false_type { };

	template <> struct is_integral<bool> : public true_type { };
	template <> struct is_integral<char> : public true_type { };
	template <> struct is_integral<unsigned char> : public true_type { };
	template <> struct is_integral<signed char> : public true_type { };
	template <> struct is_integral<short> : public true_type { };
	template <> struct is_integral<unsigned short> : public true_type { };
	template <> struct is_integral<int> : public true_type { };
	template <> struct is_integral<unsigned int> : public true_type { };
	template <> struct is_integral<long long> : public true_type { };
	template <> struct is_integral<unsigned long long> : public true_type { };

	/* ft::less
	** Used to express that you want to use operator< to perform comparisons.
	*/
	template<typename T>
	struct less
	{
	    bool operator()(T const& lhs, T const& rhs) { return lhs < rhs; }
	};

	/* ft::find_if
	** Searches for an element for which predicate p returns true.
	*/
	template<class InputIt, class UnaryPredicate>
	InputIt find_if(InputIt first, InputIt last, UnaryPredicate p)
	{
		for (; first != last; ++first)
		{
			if (p(*first))
				return first;
		}
		return last;
	}

	/* ft::binary_function */
	template <typename Arg1, typename Arg2, typename Result>
	struct binary_function
	{
		typedef Arg1		first_argument_type;
		typedef Arg2		second_argument_type;
		typedef Result		result_type;
	};

	/* ft::unary_function */
	template <class Arg, class Result>
	struct unary_function
	{
		typedef Arg argument_type;
		typedef Result result_type;
	};

	static class nullptr_t
	{

    public:

        template <class T>
        operator T*() const { return (0); }

        template<class C, class T>
        operator T C::*() const { return (0); }

    private:

        void operator&() const;

	} u_nullptr = {};

	template <typename T>
    std::string to_string(T n)
    {
    	std::ostringstream ss;
        ss << n;
        return (ss.str());
    }

	/* c00l factorial trick, no calculation made during runtime */
	
	template <unsigned n>
	struct factorial : ft::integral_constant<long long, n * factorial<n - 1>::value> { };

	template <>
	struct factorial<0> : ft::integral_constant<long long, 1> { };

}
