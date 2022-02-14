/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_main.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 15:19:31 by mbarut            #+#    #+#             */
/*   Updated: 2022/02/14 17:58:30 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <algorithm>
#include <ostream>
#include <vector>
#include <iterator>
#include <iostream>
#include <utility>
#include <string>

#include "../ft/vector.hpp"
#include "../ft/iterator.hpp"
#include "../ft/utility.hpp"
#include "../ft/printer.hpp"

int main()
{

	ft::vector<int> v1;
	print_vector(v1, 1);

	ft::vector<int> v2(size_t(8), int(42));
	print_vector(v2, 2);

	ft::vector<int>::iterator it_tmp1 = v2.begin() + 1;
	ft::vector<int>::iterator it_tmp2 = v2.end() - 2;
	ft::vector<int> v3(it_tmp1, it_tmp2);
	print_vector(v3, 3);

	ft::vector<int> v4(v3);
	print_vector(v4, 4);

	ft::vector<int> v5 = v4;
	print_vector(v5, 5);

	std::cout << "v1 is empty: "<< v1.empty() << std::endl;
	std::cout << "v5 is empty: "<< v5.empty() << std::endl;

	std::cout << "v1 has size " << v1.size() << " and capacity " << v1.capacity() << std::endl;
	std::cout << "v5 has size " << v5.size() << " and capacity " << v5.capacity() << std::endl;

	std::cout << "v1 has max size of " << v1.max_size() << std::endl;
	std::cout << "v5 has max size of " << v5.max_size() << std::endl;

	v5.resize(20);
	print_vector(v5, 5);
	std::cout << v5[v5.size() - 1] << std::endl;
	std::cout << v5.at(v5.size() - 1) << std::endl;

	std::cout << v5.front() << std::endl;
	std::cout << v5.back() << std::endl;

	ft::vector<int> v6;
	v6.assign(7, 100);
	print_vector(v6, 6);

	ft::vector<int>::iterator v6_it1 = v5.begin() + 3;
	ft::vector<int>::iterator v6_it2 = v5.end() - 7;

	v6.assign(v6_it1, v6_it2);
	print_vector(v6, 6);

	ft::vector<int>::iterator v6_it3 = v6.begin() + 3;
	v6.erase(v6_it3);
	print_vector(v6, 6);

	ft::vector<int>::iterator v6_it4 = v6.begin() + 1;
	ft::vector<int>::iterator v6_it5 = v6.begin() + 6;
	v6.erase(v6_it4, v6_it5);
	print_vector(v6, 6);

	ft::vector<int>::iterator it1;
	ft::vector<int>::iterator it2;
	ft::vector<int>::iterator it3;
	ft::vector<int>::const_iterator it_const;
	ft::vector<int>::reverse_iterator it_r;
	ft::vector<int>::const_reverse_iterator it_rconst;

	v1.reserve(12);
	v1.push_back( 0 );
	v1.push_back( 1 );
	v1.push_back( 2 );
	v1.push_back( 3 );
	v1.push_back( 4 );
	v1.push_back( 5 );
	v1.push_back( 6 );
	v1.push_back( 7 );
	v1.push_back( 8 );
	v1.push_back( 9 );
	v1.push_back( 10 );
	v1.push_back( 11 );

	print_vector(v1, 1);

	it1 = v1.begin();
	it2 = v1.begin() + 3;
	it3 = v1.end() - 1;

	std::cout << "it1 = v1.begin()" << std::endl;
	std::cout << "it2 = v1.begin() + 3" << std::endl;
	std::cout << "it3 = v1.end() - 2;" << std::endl;
	std::cout << std::endl;

	std::cout << "*(it1): " << *(it1) << std::endl;

	std::cout << "*(it1 + 1): " << *(it1 + 1) << std::endl;
	std::cout << "*(1 + it1): " << *(1 + it1) << std::endl;
	std::cout << "*(it2 - 1): " << *(it2 - 1) << std::endl;
	std::cout << "*(-1 + it2): " << *(-1 + it2) << std::endl;

	std::cout << "*(it1++): " << *(it1++) << " -> " << *it1 << std::endl;
	std::cout << "*(it2++): " << *(it2++) << " -> " << *it2 << std::endl;
	std::cout << "*(++it1): " << *(++it1) << " -> " << *it1 << std::endl;
	std::cout << "*(++it2): " << *(++it2) << " -> " << *it2 << std::endl;
	std::cout << "*(it1--): " << *(it1--) << " -> " << *it1 << std::endl;
	std::cout << "*(it2--): " << *(it2--) << " -> " << *it2 << std::endl;
	std::cout << "*(--it1): " << *(--it1) << " -> " << *it1 << std::endl;
	std::cout << "*(--it2): " << *(--it2) << " -> " << *it2 << std::endl;

	std::cout << "*(it1 += 3): " << *it1 << " -> " << *(it1 += 3) << std::endl;
	std::cout << "*(it2 += 3): " << *it2 << " -> " << *(it2 += 3) << std::endl;
	std::cout << "*(it1 -= 1): " << *it1 << " -> " << *(it1 -= 1) << std::endl;
	std::cout << "*(it2 -= 1): " << *it2 << " -> " << *(it2 -= 1) << std::endl;

	ft::reverse_iterator<ft::vector<int>::iterator> it4( v1.rbegin() + 6 );
	ft::reverse_iterator<ft::vector<int>::iterator> it5( v1.rbegin() );
	std::cout << "*(it4): " << *(it4) << std::endl;

	std::cout << "*(it4++): " << *(it4++) << " -> " << *it4 << std::endl;
	std::cout << "*(++it4): " << *(++it4) << " -> " << *it4 << std::endl;
	std::cout << "*(it4--): " << *(it4--) << " -> " << *it4 << std::endl;
	std::cout << "*(--it4): " << *(--it4) << " -> " << *it4 << std::endl;

	std::cout << "*(it4 + 3): " << *(it4 + 3) << std::endl;
	std::cout << "*(it4 - 3): " << *(it4 - 3) << std::endl;
	std::cout << "it4 - it5: " << it4 - it5 << std::endl;

	print_vector(v1, 1);
	print_vector(v2, 2);

	std::cout << std::boolalpha << (v1 == v2) << std::endl;
	std::cout << std::boolalpha << (v1 != v2) << std::endl;
	std::cout << std::boolalpha << (v1 < v2) << std::endl;
	std::cout << std::boolalpha << (v1 > v2) << std::endl;
	std::cout << std::boolalpha << (v1 >= v2) << std::endl;
	std::cout << std::boolalpha << (v1 <= v2) << std::endl;

	return 0;
}
