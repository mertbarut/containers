/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterator_base_funcs.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 17:06:05 by mbarut            #+#    #+#             */
/*   Updated: 2022/02/09 00:23:59 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_iterator_base_types.hpp"

namespace ft
{
	/* Distance: get the distance between two iterators */
	
	template <typename InputIterator>
	static inline typename iterator_traits<InputIterator>::difference_type
	_distance (InputIterator first, InputIterator last, ft::input_iterator_tag)
	{
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
	_distance (RandomAccessIterator first, RandomAccessIterator last, ft::random_access_iterator_tag)
	{
		return last - first;
	}

	template <typename InputIterator>
	inline typename iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last)
	{
		return ft::_distance(first, last, ft::iterator_category(first));
	}

	/* Advance: advance some iterator by some position */

	template <typename InputIterator, typename Distance>
	static inline void
	_advance(InputIterator& i, Distance n, ft::input_iterator_tag)
	{
		while (n--)
			++i;
	}

	template <typename BidirectionalIterator, typename Distance>
	static inline void
	_advance(BidirectionalIterator& i, Distance n, ft::bidirectional_iterator_tag)
	{
		if (n > 0)
			while (n--)
				++i;
		else
			while (n++)
				--i;
	}

	template <typename RandomAccessIterator, typename Distance>
	static inline void
	_advance(RandomAccessIterator& i, Distance n, ft::random_access_iterator_tag)
	{
		i += n;
	}

	template <typename InputIterator, typename Distance>
	inline void
	advance (InputIterator& i, Distance n)
	{
		typename iterator_traits<InputIterator>::difference_type d = n;
		ft::_advance(i, d, ft::iterator_category(i));
	}
}
