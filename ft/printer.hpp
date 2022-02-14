/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:02:03 by mbarut            #+#    #+#             */
/*   Updated: 2022/02/14 17:44:38 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <iostream>

#include <vector>
#include <map>
#include <stack>
#include <set>

#include "../ft/vector.hpp"
#include "../ft/map.hpp"
#include "../ft/stack.hpp"
#include "../ft/set.hpp"

namespace ft
{
	template<typename T>
	void	print_vector(std::vector<T>& v, size_t id = 0, const std::string& delimiter = " ")
	{
		std::cout << "vector" << id << ": " << "[ ";
		for (typename std::vector<T>::iterator it1 = v.begin(); it1 != v.end(); ++it1)
			std::cout << *it1 << delimiter;
		std::cout << "]" << std::endl;
	}

	template<typename T>
	void	print_vector(ft::vector<T>& v, size_t id = 0, const std::string& delimiter = " ")
	{
		std::cout << "vector" << id << ": " << "[ ";
		for (typename ft::vector<T>::iterator it1 = v.begin(); it1 != v.end(); ++it1)
			std::cout << *it1 << delimiter;
		std::cout << "]" << std::endl;
	}

	template<typename T, typename U>
	void	print_map(const std::map<T, U>& m, std::string comment = "")
	{
		std::cout << comment;
		for (typename std::map<T, U>::const_iterator it = m.begin(); it != m.end(); it++)
			std::cout << it->first << " = " << it->second << "; ";
		std::cout << '\n';
	}

	template<typename T, typename U>
	void	print_map(const ft::map<T, U>& m, std::string comment = "")
	{
		std::cout << comment;
		for (typename ft::map<T, U>::const_iterator it = m.begin(); it != m.end(); it++)
			std::cout << it->first << " = " << it->second << "; ";
		std::cout << '\n';
	}

	template<typename T>
	void	print_stack(std::stack<T> s, size_t id = 0, const std::string& delimiter = "\n")
	{
		size_t n_elems = s.size();
		std::cout << "stack" << id << ":\n";
		for (; !s.empty(); --n_elems)
		{
			std::cout << "[ " << s.top() << " ]" << delimiter;
			s.pop();
		}
	}

	template<typename T>
	void	print_stack(ft::stack<T> s, size_t id = 0, const std::string& delimiter = "\n")
	{
		size_t n_elems = s.size();
		std::cout << "stack" << id << ":\n";
		for (; !s.empty(); --n_elems)
		{
			std::cout << "[ " << s.top() << " ]" << delimiter;
			s.pop();
		}
	}

	template<typename T>
	void print_set(const ft::set<T>& s, std::string comment = "")
	{
		std::cout << comment;
		for (typename ft::set<T>::const_iterator it = s.begin(); it != s.end(); it++)
			std::cout << *it << " -> ";
		std::cout << "(end)" << std::endl;
	}
	
	template<typename T>
	void print_set(const std::set<T>& s, std::string comment = "")
	{
		std::cout << comment;
		for (typename std::set<T>::const_iterator it = s.begin(); it != s.end(); it++)
			std::cout << *it << " -> ";
		std::cout << "(end)" << std::endl;
	}
	
}