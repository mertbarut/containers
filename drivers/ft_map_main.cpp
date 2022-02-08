/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_main.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 15:19:31 by mbarut            #+#    #+#             */
/*   Updated: 2022/02/09 00:54:18 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <algorithm>
#include <ostream>
#include <map>
#include <iterator>
#include <iostream>
#include <utility>
#include <string>

#include "../ft/ft_map.hpp"
#include "../ft/ft_iterator.hpp"
#include "../ft/ft_pair.hpp"
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
 
int main()
{
    // Create a map of three (strings, int) pairs
    ft::map<std::string, int> m;
	//m["CPU"] = 10;
	//m["GPU"] = 15;
	//m["RAM"] = 20;

    //print_map(m, "1) Initial map: ");

    //m["CPU"] = 25;  // update an existing value
    //m["SSD"] = 30;  // insert a new value
    print_map(m, "2) Updated map: ");

    // using operator[] with non-existent key always performs an insert
    //std::cout << "3) m[UPS] = " << m["UPS"] << '\n';
    print_map(m, "4) Updated map: ");

    //m.erase("GPU");
    //print_map(m, "5) After erase: ");

    //std::cout << "7) m.size() = " << m.size() << '\n';

    //m.clear();
    //std::cout << std::boolalpha << "8) Map is empty: " << m.empty() << '\n';
}
