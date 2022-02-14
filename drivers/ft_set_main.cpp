/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_main.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 15:19:31 by mbarut            #+#    #+#             */
/*   Updated: 2022/02/14 17:55:28 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <algorithm>
#include <functional>
#include <ostream>
#include <set>
#include <iterator>
#include <iostream>
#include <utility>
#include <string>

#include "../ft/set.hpp"
#include "../ft/iterator.hpp"
#include "../ft/utility.hpp"
#include "../ft/printer.hpp"

int main()
{
    // Create a set of strings
	ft::set<std::string> s1;
	s1.insert("CPU");
	s1.insert("GPU");
	s1.insert("RAM");

	std::cout << s1.empty() << std::endl;

    ft::print_set(s1, "Initial set: ");

    s1.insert("CPU");  // update an existing value
    s1.insert("SSD");  // insert a new value
    ft::print_set(s1, "Updated set: ");

    s1.erase("GPU");
    ft::print_set(s1, "After erase: ");

    std::cout << "m.size() = " << s1.size() << '\n';

	ft::set<std::string> s2 = s1;
	ft::print_set(s2, "Copy constructed set: ");
	
	std::cout << std::boolalpha << "s1 and s2 are equivalent: " << (s1 == s2) << '\n';
	s2.insert("PSU");
	s2.insert("Peripherals");
	ft::print_set(s2, "Updated set: ");
	std::cout << std::boolalpha << "s1 and s2 are equivalent: " << (s1 == s2) << '\n';

	s1.swap(s2);
	ft::print_set(s2, "Swapped set: ");

	ft::set<std::string>::key_compare key_comp = s1.key_comp();
	ft::set<std::string>::value_compare val_comp = s1.value_comp();

	std::cout << std::boolalpha << "Python is lexicographically less than C: " << key_comp("Python", "C") << '\n';
	std::cout << (std::string("Python") < std::string("C")) << '\n';

	ft::set<std::string>::value_type value1 = (std::string)"C";
	ft::set<std::string>::value_type value2 = (std::string)"C++";

	std::cout << std::boolalpha << "C is lexicographically less than C++: " << val_comp(value1, value2) << '\n';
	std::cout << (std::string("C") < std::string("C++")) << '\n';

	ft::set<std::string>::iterator it01 = s1.find("SSD");
	std::cout << "Key \"SSD\" is in the set: " << s1.count("SSD") << '\n';
	std::cout << "Key \"Stereo\" is in the set: " << s1.count("Stereo") << '\n';

	//s1.print();

    s1.clear();
    std::cout << std::boolalpha << "Map is empty: " << s1.empty() << '\n';
}
