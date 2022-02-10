/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algorithm.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 21:12:01 by mbarut            #+#    #+#             */
/*   Updated: 2022/02/10 11:17:47 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
	/* lexicographical compare:
	** Returns true if the first sequence is lexicographically smaller than the second sequence,
	** otherwise returns false. 
	*/
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 begin1, InputIterator1 end1, InputIterator2 begin2, InputIterator2 end2)
	{
		while (begin1 != end1)
		{
			if (begin2 == end2 || *begin2 < *end1)
				return false;
			else if (*begin1 < *begin2)
				return true;
			++begin1; ++begin2;
		}
		return (begin2 != end2);
	}

	/* equal:
	** Returns true if for every iterator i in the range [first1,last1), *i equals *(first2 + (i - first1)),
	** returns false otherwise.
	*/
	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator2 last1, InputIterator2 first2)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!(*first1 == *first1))
				return false; 
		}
		return true;
	}
	
	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal(InputIterator1 first1, InputIterator2 last1, InputIterator2 first2, BinaryPredicate p)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!p(*first1, *first1))
				return false; 
		}
		return true;
	}

}
