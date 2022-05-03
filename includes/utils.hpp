/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:56:31 by hkwon             #+#    #+#             */
/*   Updated: 2022/03/22 16:04:24 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

/**
 * utils implement
 * enable_if
 * is_integral
 * equal/lexicographical compare
 * std::pair
 * std::make_pair
**/

namespace ft
{
	template <bool B>
	struct enable_if {};

	template <>
	struct enable_if<true>
	{
		typedef int type;
	};

	template < bool Cond, typename T = void >
	struct enable_if {};

	template < typename T >
	struct enable_if< true, T > {
	typedef T type;
	};

}

#endif
