/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 15:19:31 by mbarut            #+#    #+#             */
/*   Updated: 2021/12/28 15:22:01 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vector.hpp"
#include "Stack.hpp"
#include "Map.hpp"

#include "../ft/Iterator.hpp"
#include "../ft/misc.hpp"
#include "../ft/pair.hpp"

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

/* vectors & its iterators */

//int main()
//{
//	std::vector<int> v1;
//	std::vector<int> v2;
//
//	std::vector<int>::iterator it1;
//	std::vector<int>::iterator it2;
//	std::vector<int>::iterator it3;
//	std::vector<int>::const_iterator it_const;
//	std::vector<int>::reverse_iterator it_r;
//	std::vector<int>::const_reverse_iterator it_rconst;
//	
//	v1.reserve(12);
//	v1.push_back( 1 );
//	v1.push_back( 2 );
//	v1.push_back( 3 );
//	v1.push_back( 4 );
//	v1.push_back( 5 );
//	v1.push_back( 6 );
//	v1.push_back( 7 );
//	v1.push_back( 8 );
//	v1.push_back( 9 );
//	v1.push_back( 10 );
//	v1.push_back( 11 );
//	v1.push_back( 12 );
//
//	std::cout << "v1 = [ ";
//	for (it1 = v1.begin(); it1 < v1.end(); ++it1)
//		std::cout << *it1 << " ";
//	std::cout << "]" << std::endl;
//	std::cout << std::endl;
//	
//	it1 = v1.begin();
//	it2 = v1.begin() + 3;
//	it3 = v1.end() - 1;
//
//	std::cout << "it1 = v1.begin()" << std::endl;
//	std::cout << "it2 = v1.begin() + 3" << std::endl;
//	std::cout << "it3 = v1.end() - 2;" << std::endl;
//	std::cout << std::endl;
//
//	/* Access */
//
//	std::cout << "*(it1): " << *(it1) << std::endl;
//
//	/* Arithmetic */
//	std::cout << "*(it1 + 1): " << *(it1 + 1) << std::endl;
//	std::cout << "*(1 + it1): " << *(1 + it1) << std::endl;
//	std::cout << "*(it2 - 1): " << *(it2 - 1) << std::endl;
//	std::cout << "*(-1 + it2): " << *(-1 + it2) << std::endl;
//
//	/* Increment/decrement */
//	std::cout << "*(it1++): " << *(it1++) << " -> " << *it1 << std::endl;
//	std::cout << "*(it2++): " << *(it2++) << " -> " << *it2 << std::endl;
//	std::cout << "*(++it1): " << *(++it1) << " -> " << *it1 << std::endl;
//	std::cout << "*(++it2): " << *(++it2) << " -> " << *it2 << std::endl;
//	std::cout << "*(it1--): " << *(it1--) << " -> " << *it1 << std::endl;
//	std::cout << "*(it2--): " << *(it2--) << " -> " << *it2 << std::endl;
//	std::cout << "*(--it1): " << *(--it1) << " -> " << *it1 << std::endl;
//	std::cout << "*(--it2): " << *(--it2) << " -> " << *it2 << std::endl;
//
//	/* Increment/decrement assignment */
//	std::cout << "*(it1 += 3): " << *it1 << " -> " << *(it1 += 3) << std::endl;
//	std::cout << "*(it2 += 3): " << *it2 << " -> " << *(it2 += 3) << std::endl;
//	std::cout << "*(it1 -= 1): " << *it1 << " -> " << *(it1 -= 1) << std::endl;
//	std::cout << "*(it2 -= 1): " << *it2 << " -> " << *(it2 -= 1) << std::endl;
//
//	/* Reverse iterator */
//
//	std::reverse_iterator<std::vector<int>::iterator> it4( v1.rbegin() + 6 );
//	std::reverse_iterator<std::vector<int>::iterator> it5( v1.rbegin() );
//	std::cout << "*(it4): " << *(it4) << std::endl;
//	
//	std::cout << "*(it4++): " << *(it4++) << " -> " << *it4 << std::endl;
//	std::cout << "*(++it4): " << *(++it4) << " -> " << *it4 << std::endl;
//	std::cout << "*(it4--): " << *(it4--) << " -> " << *it4 << std::endl;
//	std::cout << "*(--it4): " << *(--it4) << " -> " << *it4 << std::endl;
//
//	std::cout << "*(it4 + 3): " << *(it4 + 3) << std::endl;
//	std::cout << "*(it4 - 3): " << *(it4 - 3) << std::endl;
//	std::cout << "it4 - it5: " << it4 - it5 << std::endl;
//
//	return 0;
//}

#include <iostream>
#include <utility>
#include <string>

int main()
{
	ft::pair <std::string, double> product00;
	ft::pair <std::string, double> product01 ("lalalalalala", 42.02);
	ft::pair <std::string, double> product02 (product01);
	
	std::cout << "Name: " << product01.first << std::endl;
	std::cout << "Price: " << product01.second << std::endl;

	ft::pair <int, std::string> test00 = ft::make_pair(42, "Hey");
	std::cout << "test00: (" << test00.first << ", " << test00.second << ")" << std::endl;
}