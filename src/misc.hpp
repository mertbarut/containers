/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 14:09:36 by mbarut            #+#    #+#             */
/*   Updated: 2021/12/26 16:01:22 by mbarut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ft::is_same

namespace ft
{
	template<typename T, typename U>
	struct isSame
	{
		static const bool value = false;
	};
	
	template<typename T>
	struct isSame<T, T>
	{
		static const bool value = true;
	};
}

