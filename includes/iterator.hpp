/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:15:03 by hkwon             #+#    #+#             */
/*   Updated: 2022/04/27 17:30:47 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

/**
 * iterator implement
 * iterators_traits
 * reverse_iterator
**/

namespace ft
{

	/**
	 * iterator categories
	**/
	class input_iterator_tag {};
	class output_iterator_tag {};
	class forward_iterator_tag : public input_iterator_tag {};
	class bidirectional_iterator_tag : public forward_iterator_tag {};
	class random_access_iterator_tag : public bidirectional_iterator_tag {};

	/**
	 * iterator traits
	**/
	template<class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	template<class T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef random_access_iterator_tag iterator_category;
	};

	template<class T>
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T* pointer;
		typedef const T& reference;
		typedef random_access_iterator_tag iterator_category;
	};

	/**
	 * iterator
	**/
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

	template <class Iterator>
	class reverse_iterator
	{
		public:
			typedef Iterator iterator_type;
			typedef typename iterator_traits<Iterator>::value_type;
			typedef typename iterator_traits<Iterator>::difference_type;
			typedef typename iterator_traits<Iterator>::pointer;
			typedef typename iterator_traits<Iterator>::reference;
		protected:
			Iterator current;

		// default constructor
		reverse_iterator() : current{}
		// initialization constructor
		explicit reverse_iterator (iterator_type it) : current(it) {}
		// copy / type-cast constructor
		template <class Iter>
		reverse_iterator (const reverse_iterator<Iter>& rev_it) : current(rev_it.base()) {}

		/**
		 * iterator member function
		**/
		template <class Iter>
		reverse_iterator& operator=(const reverse_iterator<Iter>& rev_it)
		{
			this->current = rev_it.current;
			return (*this);
		}

		iterator_type base() const { return current; };

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
			--(this->current);
			return (*this);
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator tmp = *this;
			++(*this);
			return (tmp);
		}

		reverse_iterator& operator--()
		{
			++(this->current);
			return (*this);
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = *this;
			--(*this);
			return (tmp);
		}

		reverse_iterator operator+ (difference_type n) const
		{

		}

		reverse_iterator& operator+=(difference_type n)
		{

		}

		reverse_iterator operator- (difference_type n) const
		{

		}

		reverse_iterator& operator-=(difference_type n)
		{

		}

		reference operator[](difference_type n) const
		{

		}
	};
}

#endif
