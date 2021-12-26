/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_enable_if.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 22:29:38 by mbarut            #+#    #+#             */
/*   Updated: 2021/12/26 16:00:17 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <typeinfo>

#include "../src/misc.hpp"

/* primary template */
template <typename T, typename T2> 
struct ReturnType;

/* case 1 */
template <>
struct ReturnType <double, double>
{
	typedef double Type;
};

/* case 2 */
template <>
struct ReturnType <double, bool>
{
	typedef double Type;
};

/* case 3 */
template <>
struct ReturnType <bool, double>
{
	typedef double Type;
};

/* case 4 */
template <>
struct ReturnType <bool, bool>
{
	typedef int Type;
};

/* sum() */
template <typename T, typename T2>
typename ReturnType<T, T2>::Type sum(T t, T2 t2)
{
	return t + t2;
};

int main() {

    std::cout << '\n';

    std::cout << "typeid(sum(5.5, 5.5)).name(): " << typeid(sum(5.5, 5.5)).name() << '\n';
    std::cout << "typeid(sum(5.5, true)).name(): " << typeid(sum(5.5, true)).name() << '\n';
    std::cout << "typeid(sum(true, 5.5)).name(): " << typeid(sum(true, 5.5)).name() << '\n';
    std::cout << "typeid(sum(true, false)).name(): " << typeid(sum(true, false)).name() << '\n';
	
    std::cout << '\n';

	std::cout << "int == double : " << isSame<int, double>::value << std::endl;
}