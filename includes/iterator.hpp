#ifndef ITERATOR_HPP
# define ITERATOR_HPP

// #include <iterator>

/**
 * iterator implement
 * reverse_iterator
 * bidirectional or random-access iterator 를 사용해 범위를 통해 반복되는 방향을 반대로 한다,
 *
 */

namespace ft
{
	/**
 	* iterators_traits
 	*/
	/**
	 * iterator_tags
	 * categories
	 * iterator를 구분하는데 사용되는 빈 유형
	 * 구별은 무엇을 포함하느냐에 의해서가 아니라, 단지 무엇에 의해 만들어진다.
	 * 서로 다른 반복자 유형이 지원하는 서로 다른 작업을 기반으로 서로 다른 기본 알고리즘을 사용할 수 있다.
	 */
	class input_iterator_tag {};	//marking input iterators
	class output_iterator_tag {};	//marking output iterators
	class forward_iterator_tag : public input_iterator_tag {};	//Forward iterators support a superset of input iterator operations.
	class bidirectional_iterator_tag : public forward_iterator_tag {};	//Bidirectional iterators support a superset of forward iterator operations.
	class random_access_iterator_tag : public bidirectional_iterator_tag {}; //Random-access iterators support a superset of bidirectional iterator operations.

	/**
	 * iterator traits
	 * Traits class defining properties of iterators.
	 * Traits class는 iterator의 속성의 정의하는 특성 클래스
	 */
	// Generic Definition
	template<class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	//T* specialization
	template<class T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef random_access_iterator_tag iterator_category;
	};

	//const T* specialization
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
	 * @brief iterator
	 * iterator 클래스를 파생하는데 사용할 수 있는 기본 클래스 템플릿
	 * 해당 클래스는 iterator클래스가 아니며 iterator가 사용할 것으로 예상되는 기능을 제공하지 않는다.
	 * This is a base class template that can be used to derive iterator classes from it.
	 * It is not an iterator class and does not provide any of the functionality an iterator is expected to have.
	 *
	 * @tparam Category		Category to which the iterator belongs to.
	 * @tparam T			Type of elements pointed by the iterator.
	 * @tparam Distance		Type to represent the difference between two iterators.
	 * @tparam Pointer		Type to represent a pointer to an element pointed by the iterator.
	 * @tparam Reference	Type to represent a reference to an element pointed by the iterator.
	 */
	template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
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
		protected:
			Iterator current;
		public:
			typedef Iterator iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterater_category;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;


		/**
		 * iterator member function
		**/
		reverse_iterator() : current{} //default construnctor
		explicit reverse_iterator (iterator_type it) : current(it) {} //initialization construtor
		template <class Iter>
		reverse_iterator (cont reverse_iterator<Iter>& rev_it) : current(rev_it.base()) {} //copy
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
			--this->current;
			return (*this);
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = *this;
			--this->current;
			return (tmp);
		}

		reverse_iterator operator+(difference_type n) const
		{
			return (reverse_iterator(current - n));
		}

		reverse_iterator& operator+=(difference_type n)
		{
			this->current -= n;
			return (*this);
		}

		reverse_iterator operator-(difference_type n) const
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

	//non-member function overloads
	template <class Iter1, class Iter2>
	bool operator==(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return ( lhs.base() == rhs.base() );
	}

	template <class Iter1, class Iter2>
	bool operator!=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return ( lhs.base() != rhs.base() );
	}

	template <class Iter1, class Iter2>
	bool operator<(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return ( lhs.base() < rhs.base() );
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

	template<class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-( const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs )
	{
		return ( rhs.base() - lhs.base() );
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& it)
	{
		return ( it.base() - n );
	}
}

#endif
