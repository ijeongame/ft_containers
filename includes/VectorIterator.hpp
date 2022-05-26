#ifndef VECTORITERATOR_HPP
# define VECTORITERATOR_HPP

#include "iterator.hpp"
#include "utils.hpp"

/**
 * @brief VectorIterator
 * Implemented for use as a random access iterator.
 * Random access iterators are iterators that can be used to access elements
 * at an arbitrary offset position relative to the element they point to,
 * offering the same functionality as pointers.
 *
 * @tparam T	Type of elements pointed by the iterator.
 */
namespace ft
{
	template <typename T>
	class VectorIterator : public ft::iterator<ft::random_access_iterator_tag, T>
	{
		public:
			typedef typename ft::iterator< ft::random_access_iterator_tag, T >::value_type	value_type;
			typedef typename ft::iterator< ft::random_access_iterator_tag, T >::pointer		pointer;
			typedef typename ft::iterator< ft::random_access_iterator_tag, T >::reference		reference;
			typedef typename ft::iterator< ft::random_access_iterator_tag, T >::difference_type	difference_type;
			typedef typename ft::iterator< ft::random_access_iterator_tag, T >::iterator_category	iterator_category;

		protected:
			pointer _ptr;

		public:
		VectorIterator(pointer ptr = NULL) : _ptr(ptr) {} //default constructor

		VectorIterator(const VectorIterator<T> &other) : _ptr(other.base()) {} // copy constructor

		VectorIterator &operator=(const VectorIterator<T> &other) //assignment operator
		{
			if (this != &other)
				this->_ptr = other.base();
			return (*this);
		}

		operator VectorIterator<const T>() const //overloading type casting
		{
			return (VectorIterator<const T>(this->_ptr));
		}

		pointer const &base() const //getter
		{
			return (this->_ptr);
		}

		virtual ~VectorIterator() {} // destructor

		/**
		 * @brief operator
		 */
		reference operator*() const
		{
			return (*this->_ptr);
		}

		pointer operator->() const
		{
			return (this->_ptr);
		}

		VectorIterator &operator++()
		{
			++this->_ptr;
			return (*this);
		}

		VectorIterator operator++(int)
		{
			VectorIterator tmp = *this;
			++this->_ptr;
			return (tmp);
		}

		VectorIterator &operator--()
		{
			--this->_ptr;
			return (*this);
		}

		VectorIterator operator--(int)
		{
			VectorIterator tmp = *this;
			--this->_ptr;
			return (tmp);
		}

		VectorIterator operator+(difference_type n) const
		{
			return (VectorIterator(this->_ptr + n));
		}

		VectorIterator operator-(difference_type n) const
		{
			return (VectorIterator(this->_ptr - n));
		}

		VectorIterator &operator+=(difference_type n)
		{
			this->_ptr += n;
			return (*this);
		}

		VectorIterator &operator-=(difference_type n)
		{
			this->_ptr -= n;
			return (*this);
		}

		reference operator[](difference_type n) const
		{
			return (*(this->_ptr + n));
		}
	};

	//Relational operators

	template <class Iter1, class Iter2>
	bool operator==(const VectorIterator<Iter1>& lhs, const VectorIterator<Iter2>& rhs)
	{
		return ( lhs.base() == rhs.base() );
	}

	template <class Iter1, class Iter2>
	bool operator!=(const VectorIterator<Iter1>& lhs, const VectorIterator<Iter2>& rhs)
	{
		return ( lhs.base() != rhs.base() );
	}

	template <class Iter1, class Iter2>
	bool operator<(const VectorIterator<Iter1>& lhs, const VectorIterator<Iter2>& rhs)
	{
		return ( lhs.base() < rhs.base() );
	}

	template <class Iter1, class Iter2>
	bool operator>(const VectorIterator<Iter1>& lhs, const VectorIterator<Iter2>& rhs)
	{
		return ( lhs.base() > rhs.base() );
	}

	template <class Iter1, class Iter2>
	bool operator>=(const VectorIterator<Iter1>& lhs, const VectorIterator<Iter2>& rhs)
	{
		return ( lhs.base() >= rhs.base() );
	}


	template <class Iter1, class Iter2>
	bool operator<=(const VectorIterator<Iter1>& lhs, const VectorIterator<Iter2>& rhs)
	{
		return ( lhs.base() <= rhs.base() );
	}

	template <class Iterator>
	ft::VectorIterator<Iterator> operator+(typename ft::VectorIterator<Iterator>::difference_type n, ft::VectorIterator<Iterator> &it)
	{
		return (it + n);
	}

	template <class Iterator>
	typename ft::VectorIterator<Iterator>::difference_type operator-(const ft::VectorIterator<Iterator> &lhs, const ft::VectorIterator<Iterator> &rhs)
	{
		return (lhs.base() - rhs.base());
	}

	//non-member non-const function overload
	// template <class Iter>
	// bool operator==(const VectorIterator<Iter>& lhs, const VectorIterator<Iter>& rhs)
	// {
	// 	return ( lhs.base() == rhs.base() );
	// }

	// template <class Iter>
	// bool operator!=(const VectorIterator<Iter>& lhs, const VectorIterator<Iter>& rhs)
	// {
	// 	return ( lhs.base() != rhs.base() );
	// }

	// template <class Iter>
	// bool operator<(const VectorIterator<Iter>& lhs, const VectorIterator<Iter>& rhs)
	// {
	// 	return ( lhs.base() < rhs.base() );
	// }

	// template <class Iter>
	// bool operator>(const VectorIterator<Iter>& lhs, const VectorIterator<Iter>& rhs)
	// {
	// 	return ( lhs.base() > rhs.base() );
	// }

	// template <class Iter>
	// bool operator>=(const VectorIterator<Iter>& lhs, const VectorIterator<Iter>& rhs)
	// {
	// 	return ( lhs.base() >= rhs.base() );
	// }

	// template <class Iter>
	// bool operator<=(const VectorIterator<Iter>& lhs, const VectorIterator<Iter>& rhs)
	// {
	// 	return ( lhs.base() <= rhs.base() );
	// }

	// template <class Iterator, class Iterator_c>
	// typename ft::VectorIterator<Iterator>::difference_type operator-(const ft::VectorIterator<Iterator> &lhs, const ft::VectorIterator<Iterator_c> &rhs)
	// {
	// 	return (lhs.base() - rhs.base());
	// }
};

#endif
