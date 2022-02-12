/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_main.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 15:19:31 by mbarut            #+#    #+#             */
/*   Updated: 2022/02/12 22:37:39 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <algorithm>
#include <functional>
#include <ostream>
#include <map>
#include <iterator>
#include <iostream>
#include <utility>
#include <string>

#include "../ft/ft_map.hpp"
#include "../ft/ft_iterator.hpp"
#include "../ft/ft_util.hpp"

/* maps & its iterators */

template<typename T, typename U>
void print_map(const ft::map<T, U>& m, std::string comment = "")
{
	std::cout << comment;
	for (typename ft::map<T, U>::const_iterator it = m.begin(); it != m.end(); it++)
		std::cout << it->first << " = " << it->second << "; ";
    std::cout << '\n';
}

template<typename T, typename U>
void print_map(const std::map<T, U>& m, std::string comment = "")
{
	std::cout << comment;
	for (typename std::map<T, U>::const_iterator it = m.begin(); it != m.end(); it++)
		std::cout << it->first << " = " << it->second << "; ";
    std::cout << '\n';
}
 
int main()
{
    // Create a map of three (strings, int) pairs
	ft::map<std::string, int> m1;
	m1["CPU"] = 10;
	m1["GPU"] = 15;
	m1["RAM"] = 20;

	std::cout << m1.empty() << std::endl;

    print_map(m1, "Initial map: ");

    m1["CPU"] = 25;  // update an existing value
    m1["SSD"] = 30;  // insert a new value
    print_map(m1, "Updated map: ");

    // using operator[] with non-existent key always performs an insert
    std::cout << "m1[UPS] = " << m1["UPS"] << '\n';
    print_map(m1, "Updated map: ");

    m1.erase("GPU");
    print_map(m1, "After erase: ");

    std::cout << "m.size() = " << m1.size() << '\n';

	ft::map<std::string, int> m2 = m1;
	print_map(m1, "Copy constructed map: ");
	
	std::cout << std::boolalpha << "m1 and m2 are equivalent: " << (m1 == m2) << '\n';
	m2["PSU"] = 34;
	m2["Peripherals"] = 12;
	print_map(m2, "Updated map: ");
	std::cout << std::boolalpha << "m1 and m2 are equivalent: " << (m1 == m2) << '\n';
	
	m1.swap(m2);
	print_map(m2, "Swapped map: ");

	ft::map<std::string, int>::key_compare key_comp = m1.key_comp();
	ft::map<std::string, int>::value_compare val_comp = m1.value_comp();

	std::cout << std::boolalpha << "Python is lexicographically less than C: " << key_comp("Python", "C") << '\n';
	std::cout << (std::string("Python") < std::string("C")) << '\n';

	ft::map<std::string, int>::value_type value1 = ft::make_pair("C", 2);
	ft::map<std::string, int>::value_type value2 = ft::make_pair("C++", 7);

	std::cout << std::boolalpha << "C is lexicographically less than C++: " << val_comp(value1, value2) << '\n';
	std::cout << (std::string("C") < std::string("C++")) << '\n';

	ft::map<std::string, int>::iterator it01 = m1.find("SSD");
	std::cout << "Key \"SSD\" is in the map: " << m1.count("SSD") << '\n';
	std::cout << "Key \"Stereo\" is in the map: " << m1.count("Stereo") << '\n';

	//m1.print();

    m1.clear();
    std::cout << std::boolalpha << "Map is empty: " << m1.empty() << '\n';
}
