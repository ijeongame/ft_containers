/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:15:03 by hkwon             #+#    #+#             */
/*   Updated: 2022/05/07 21:20:57 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

// #include <iterator>

#include "iterator_traits.hpp"
/**
 * iterator implement
 * reverse_iterator
 */

namespace ft
{
/**
** iterator
	template<class Category, class T, class Distance = ptrdiff_t,
		class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
		typedef Category iterator_category;
	};
**/

	template <class Iterator>
	class reverse_iterator
	{
		protected:
			Iterator current;
		public:
			typedef Iterator iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category iterater_category;
			typedef typename iterator_traits<Iterator>::value_type;
			typedef typename iterator_traits<Iterator>::difference_type;
			typedef typename iterator_traits<Iterator>::pointer;
			typedef typename iterator_traits<Iterator>::reference;

		// constructor
		reverse_iterator() : current{} //default
		explicit reverse_iterator (iterator_type it) : current(it) {} //initialization
		template <class Iter>
		reverse_iterator (cont reverse_iterator<Iter>& rev_it) : current(rev_it.base()) {} //copy

		/**
		 * iterator member function
		**/
		template <class Iter>
		reverse_iterator& operator=(const reverse_iterator<Iter>& rev_it)
		{
			this->current = rev_it.current;
			return (*this);
		}

		iterator_type base() const
		{
			return (current);
		};

		reference operator*() const
		{
			iterator_type tmp = this->current;
			--tmp;
			return (*tmp);
		}

		pointer operator->() const
		{
			return ( &(operator*()) );
		}

		reverse_iterator& operator++()
		{
			--this->current;
			return (*this);
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator tmp = *this;
			--this->current;
			return (tmp);
		}

		reverse_iterator& operator--()
		{
			++this->current;
			return (*this);
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = *this;
			++this->current;
			return (tmp);
		}

		reverse_iterator operator+ (difference_type n) const
		{
			return (reverse_iterator(current - n));
		}

		reverse_iterator& operator+=(difference_type n)
		{
			this->current -= n;
			return (*this);
		}

		reverse_iterator operator- (difference_type n) const
		{
			return (reverse_iterator(current + n));
		}

		reverse_iterator& operator-=(difference_type n)
		{
			this->current += n;
			return (*this);
		}

		reference operator[](difference_type n) const
		{
			return (this->current[-n - 1]);
		}
	};

	//non-member function
	template <class Iter1, class Iter2>
	bool operator==(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return ( lhs.base() == rhs.base() );
	}

	template <class Iter1, class Iter2>
	bool operator<(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return ( lhs.base() < rhs.base() );
	}

	template <class Iter1, class Iter2>
	bool operator!=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return ( lhs.base() != rhs.base() );
	}

	template <class Iter1, class Iter2>
	bool operator>(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return ( lhs.base() > rhs.base() );
	}

	template <class Iter1, class Iter2>
	bool operator>=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return ( lhs.base() >= rhs.base() );
	}

	template <class Iter1, class Iter2>
	bool operator<=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return ( lhs.base() <= rhs.base() );
	}

	template< class Iterator >
	typename reverse_iterator<Iterator>::difference_type
	operator-( const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs )
	{
		return ( rhs.base() - lhs.base() );
	}

	template <class Iterator>
	reverse_iterator<Iterator>
	operator+(typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator>& it)
	{
		return ( it.base() - n );
	}
}

#endif
