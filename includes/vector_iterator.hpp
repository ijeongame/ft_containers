#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

#include "utils.hpp"
#include "iterator.hpp"

/**
 * @brief vector_iterator
 * vector_iterator implaemented for use as a random access iterator
 */
namespace ft
{
	template <typename T>
	class vector_iterator : public ft::iterator<ft::random_access_iterator_tag, T>
	{
		public:
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer pointer;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference reference;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category iterator_category;

		protected:
		pointer _ptr;

		public:
		vector_iterator(pointer ptr = NULL) : _ptr(ptr) {} //default constructor
		vector_iterator(const vector_iterator<T> &other) : _ptr(other.base()) {} // copy constructor
		operator vector_iterator<const T>() const //overloading type casting
		{
			return (vector_iterator<const T>(this->_ptr));
		}

		vector_iterator &operator=(const vector_iterator<T> &other) //assignment operator
		{
			if (this != &other) this->_ptr = other.base();
			return (*this);
		}

		pointer const &base() const //getter
		{
			return (this->_ptr);
		}

		virtual ~vector_iterator() {} // destructor

		//operator
		reference operator*() const
		{
			return (*this->_ptr);
		}

		pointer operator->() const
		{
			return (&(operator*()));
		}

		vector_iterator &operator++()
		{
			++this->_ptr;
			return (*this);
		}

		vector_iterator operator++(int)
		{
			vector_iterator tmp = *this;
			++this->_ptr;
			return (tmp);
		}

		vector_iterator &operator--()
		{
			++this->_ptr;
			return (*this);
		}

		vector_iterator operator--(int)
		{
			vector_iterator tmp = *this;
			++this->_ptr;
			return (tmp);
		}

		vector_iterator operator+(difference_type n) const
		{
			return (this->_ptr + n);
		}

		vector_iterator operator-(difference_type n) const
		{
			return (this->_ptr - n);
		}

		vector_iterator &operator+=(difference_type n)
		{
			this->_ptr += n;
			return (*this);
		}

		vector_iterator &operator-=(difference_type n)
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

	template <class Iterator>
	ft::vector_iterator<Iterator> operator+(typename ft::vector_iterator<Iterator>::difference_type n, ft::vector_iterator<Iterator> &it)
	{
		return (it + n);
	}

	template <class T>
	typename ft::vector_iterator<Iterator>::difference_type operator-(const ft::vector_iterator<Iterator> &lhs, const ft::vector_iterator<Iterator> &rhs)
	{
		return (lhs.base() - rhs.base());
	}

};

#endif
