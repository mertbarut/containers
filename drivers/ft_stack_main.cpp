/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_main.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 15:19:31 by mbarut            #+#    #+#             */
/*   Updated: 2022/02/14 17:58:12 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <algorithm>
#include <cstddef>
#include <ios>
#include <ostream>
#include <vector>
#include <iterator>
#include <iostream>
#include <utility>
#include <string>

#include "../ft/stack.hpp"
#include "../ft/iterator.hpp"
#include "../ft/utility.hpp"
#include "../ft/printer.hpp"

int main()
{

	ft::stack<int> s1;
	s1.push(1);
	s1.push(5);
	s1.push(0);
	s1.push(2);
	s1.push(3);
	s1.push(4);
	ft::print_stack(s1);

	ft::stack<int> s2;
	s2.push(1);
	s2.push(5);
	s2.push(0);
	s2.push(2);
	s2.push(3);
	s2.push(4);

	std::cout << std::boolalpha << (s1 == s2) << std::endl;

}
