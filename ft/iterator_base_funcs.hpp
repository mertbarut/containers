/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_base_funcs.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 17:06:05 by mbarut            #+#    #+#             */
/*   Updated: 2021/12/28 18:09:45 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator_base_types.hpp"
#include <iterator>
#include <iostream>

namespace ft
{
	/* Distance: get the distance between two iterators */
	
	template <typename InputIterator>
	static inline typename iterator_traits<InputIterator>::difference_type
	_distance (InputIterator first, InputIterator last, std::input_iterator_tag) // do not forget to change the last argument for custom templates
	{
		// concept requirements ignored for now
		std::cout << "Compiler has decided: Input Iterator\n";
		typename iterator_traits<InputIterator>::difference_type n = 0;
		while (first != last)
		{
			++first;
			++n;
		}
		return n;
	}

	template <typename RandomAccessIterator>
	static inline typename iterator_traits<RandomAccessIterator>::difference_type
	_distance (RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag) // do not forget to change the last argument for custom templates
	{
		// concept requirements ignored for now
		std::cout << "Compiler has decided: Random Access Iterator\n";
		return last - first;
	}

	template <typename InputIterator>
	inline typename iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last)
	{
		// concept requirements ignored for now
		std::cout << "Compiler is looking for a suitable iterator template for given iterator's trait in distance()\n";
		return ft::_distance(first, last, ft::iterator_category(first));
	}

	/* Advance: advance some iterator by some position */

	template <typename InputIterator, typename Distance>
	static inline void
	_advance(InputIterator& i, Distance n, std::input_iterator_tag) // do not forget to change the last argument for custom templates
	{
		// concept requirements ignored for now
		std::cout << "Compiler has decided: Input Iterator\n";
		while (n--)
			++i;
	}

	template <typename BidirectionalIterator, typename Distance>
	static inline void
	_advance(BidirectionalIterator& i, Distance n, std::bidirectional_iterator_tag) // do not forget to change the last argument for custom templates
	{
		// concept requirements ignored for now
		std::cout << "Compiler has decided: Bidirectional Iterator\n";
		if (n > 0)
			while (n--)
				++i;
		else
			while (n++)
				--i;
	}

	template <typename RandomAccessIterator, typename Distance>
	static inline void
	_advance(RandomAccessIterator& i, Distance n, std::random_access_iterator_tag) // do not forget to change the last argument for custom templates
	{
		// concept requirements ignored for now
		std::cout << "Compiler has decided: Random Access Iterator\n";
		i += n;
	}

	template <typename InputIterator, typename Distance>
	inline void
	advance (InputIterator& i, Distance n)
	{
		// concept requirements ignored for now
		std::cout << "Compiler is looking for a suitable iterator template for given iterator's trait in advance()\n";
		typename iterator_traits<InputIterator>::difference_type d = n;
		ft::_advance(i, d, ft::iterator_category(i));
	}
}
