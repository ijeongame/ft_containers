/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:30:35 by hkwon             #+#    #+#             */
/*   Updated: 2022/05/07 21:21:05 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORITERATOR_HPP
# define VECTORITERATRO_HPP

#include "utils.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
	template <typename T, bool IsConst>
	class vector_iterator
	{
		public:
			typedef T value_type;
			typedef std::ptrdiff_t difference_type;
			typedef typename choose< IsConst,

	};
};

#endif
