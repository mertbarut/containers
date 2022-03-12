/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 14:09:36 by mbarut            #+#    #+#             */
/*   Updated: 2022/03/12 22:15:05 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILITY_HPP
# define FT_UTILITY_HPP

#include <sstream>
#include "debug.hpp"

namespace ft
{

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

	template <bool condition, class T = void>
	struct enable_if
	{
		
	};

	template <class T>
	struct enable_if <true, T>
	{
		typedef T type;
	};

	template <class T, T v>
	struct integral_constant 
	{
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T, v> type;
	};

	template <class T, T v> const 
	T integral_constant<T, v>::value;

	typedef integral_constant<bool, true>  true_type;
	typedef integral_constant<bool, false> false_type;

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

	template<class InputIt, class UnaryPredicate>
	inline InputIt find_if(InputIt first, InputIt last, UnaryPredicate p)
	{
		for (; first != last; ++first)
		{
			if (p(*first))
				return first;
		}
		return last;
	}

	template <typename Arg1, typename Arg2, typename Result>
	struct binary_function
	{
		typedef Arg1		first_argument_type;
		typedef Arg2		second_argument_type;
		typedef Result		result_type;
	};

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

	template <typename T1, typename T2>
	struct pair
	{
		T1	first;
		T2	second;

		pair() : first(T1()), second(T2()) { }

		pair(const T1& obj1, const T2& obj2) : first(obj1), second(obj2) { }

		template <typename U1, typename U2>
		pair(const pair<U1, U2>& other) : first(other.first), second(other.second) { }
	};

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

	template <typename T1, typename T2>
	inline ft::pair<T1, T2> make_pair(T1 obj1, T2 obj2)
	{
		return ft::pair<T1, T2>(obj1, obj2);
	}

	template <class value>
	value extract_key(value v) { return v; }

	template <class first, class second>
	first extract_key(ft::pair<first, second> pair) { return pair.first; }

	template <class value>
	value extract_value(value v) { return v; }

	template <class first, class second>
	second extract_value(ft::pair<first, second> pair) { return pair.second; }

	template <typename>
	struct is_pair : ft::false_type { };
	
	template <typename T, typename U>
	struct is_pair<ft::pair<T, U> > : ft::true_type { };

	template <unsigned n>
	struct factorial : ft::integral_constant<long long, n * factorial<n - 1>::value> { };

	template <>
	struct factorial<0> : ft::integral_constant<long long, 1> { };

}

#endif