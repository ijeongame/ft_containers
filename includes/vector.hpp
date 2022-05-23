#ifndef VECTOR_HPP
# define VECTOR_HPP

// #include <vector>
#include <memory>
#include <stdexcept>
#include "vector_iterator.hpp"

namespace ft
{
	template < typename T, typename Allocator = std::allocator<T> >
	class vector
	{
		public:
			/**
			 * @brief vector member types
			 *
			 */
			typedef T value_type;
			typedef Allocator allocator_type;
			typedef typename allocator_type::size_type			size_type;
			typedef typename allocator_type::difference_type	difference_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef ft::vector_iterator<T>						iterator;
			typedef ft::vector_iterator<const T> 				const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		private:
			allocator_type	_alloc;
			pointer			_start;
			pointer			_end;
			pointer			_end_of_capacity;

		public:

		/**
		 * @brief vector member function
		 */
		//default constructor
		explicit vector(const allocator_type &alloc = allocator_type())
		: _alloc(alloc), _start(ft_nullptr), _end(ft_nullptr), _end_of_capacity(ft_nullptr){}

		//fill constructor
		explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
		: _alloc(alloc), _start(ft_nullptr), _end(ft_nullptr), _end_of_capacity(ft_nullptr)
		{
			this->_start = this->_alloc.allocate(n);
			this->_end = this->_start;
			this->_end_of_capacity = this->_start + n;
			while (n--)
				this->_alloc.construct(this->_end--, val);
		}

		//range constructor
		template <typename InputIterator>
		vector(InputIterator first, InputIterator last,
				const allocator_type &alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = ft_nullptr)
		: _alloc(alloc), _start(ft_nullptr), _end(ft_nullptr), _end_of_capacity(ft_nullptr)
		{
			difference_type n = ft::distance(first, last);
			this->_start = this->_alloc.allocate(n);
			this->_end = this->_start;
			this->_end_of_capacity = this->_start + n;
			while (n--)
				this->_alloc.construct(this->_end++, *first++)
		}

		//copy constructor
		vector(const vector &x)
		: _alloc(alloc), _start(ft_nullptr), _end(ft_nullptr), _end_of_capacity(ft_nullptr)
		{
			difference_type n = x._end - x._start;
			this->_start = this->_alloc.allocate(n);
			this->_end = this->_start;
			pointer tmp = x._start;
			while (n--)
				_alloc.construct(_end++, *tmp++)
			this->_end_of_capacity = this->_end;
		}

		//destructor
		~vector()
		{
			this->clear();
			this->_alloc.deallocate(this->_start, this->_end_of_capacity - this->_start);
		}

		//assignemt operator
		vector &operator=(const vector &x)
		{
			if (this != &x)
			{
				this->clear();
				this->assign(x.begin(), x.end());
			}
			return (*this);
		}

		/**
		 * @brief Iterator
		 * cbegin, cend, crbegin, crend is c++11
		 */
		iterator begin()
		{
			return (iterator(this->_start));
		}

		const_iterator begin() const
		{
			return (const_iterator(this->_start));
		}

		iterator end()
		{
			return (iterator(this->_end));
		}

		const_iterator end() const
		{
			return (const_iterator(this->_end));
		}

		reverse_iterator rbegin()
		{
			return (reverse_iterator(this->_end));
		}

		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(this->_end));
		}

		reverse_iterator rend()
		{
			return (reverse_iterator(this->_start));
		}

		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(this->_start));
		}

		/**
		 * @brief capacity
		 * shringk_to_fit is c++11
		 */
		size_type size() const
		{
			return (this->_end - this->_start);
		}

		size_type max_size() const
		{
			return (this->_alloc.max_size());
		}
		// n개의 val값들을 갖는 vector로 resize한다.
		void resize(size_type n, value_type val = value_type())
		{
			if (n < size())
				erase(_start + n, _end);
			else if (n > size())
				insert(_end, n - size(), val);
		}

		// element의 갯수가 아닌, 할당받은 메모리의 갯수. (잠재적 크기)
		size_type capacity() const
		{
			return (this->_end_of_capacity - this->_start);
		}

		bool empty() const
		{
			return (_start == _finish);
		}

		void reserve(size_type n)
		{
			if (n > max_size())
				throw(std::length_error("Error: ft::vector::reserve"));
			else if (n > this->capacity())
			{
				pointer start = this->_start;
				pointer end = this->_end;
				pointer end_of_capacity = this->_end_of_capacity;

				this->_start = this->_alloc.allocate(n);
				this->_end = this->_start;
				this->_end_of_capacity = this->_start + n;
				pointer tmp = start;
				while (tmp != end)
				{
					this->_alloc.construct(this->_end++, *tmp);
					this->_alloc.destroy(tmp++);
				}
				this->_alloc.deallocate(start, end_of_capacity - start);
			}
		}

		/**
		 * @brief elememt
		 */
		//access element
		reference operator[](size_type n)
		{
			return (*(this->_start + n));
		}

		//const access element
		const_reference operator[](size_type n) const
		{
			return (*(this->_start + n));
		}

		//access element
		reference at(size_type n)
		{
			if (n >= this->size())
				throw(std::out_of_range("Error: ft::vector::at"));
			return ((*this)[n]);
		}

		//const access element
		const_reference at(size_type n) const {
			if (n >= this->size())
				throw(std::out_of_range("Error: ft::vector::at"));
			return ((*this)[n]);
		}

		// 벡터의 첫번째 element를 리턴.
		reference front()
		{
			return (*(this->_start));
		}

		const_reference front() const
		{
			return (*(this->_start));
		}

		// 벡터의 마지막 element를 리턴.
		reference back()
		{
			return (*(this->_end - 1));
		}

		const_reference back() const
		{
			return (*(this->_end - 1));
		}

		/**
		 * @brief modifier
		 */
		//assign
		template < typename InputIterator >
		void assign(InputIterator first, InputIterator last,
					typename ft::enable_if< !ft::is_integral< InputIterator >::value, InputIterator >::type * = ft_nullptr)
		{
			this->clear();
			size_type n = ft::distance(first, last);
			if (n <= this->capacity())
			{
				while (n--)
					this->_alloc.construct(this->_end++, *first++);
			}
			else
			{
				pointer start = this->_start;
				pointer end_of_capacity = this->_end_of_capacity;

				this->_start = this->_alloc.allocate(n);
				this->_end = this->_start;
				this->_end_of_capacity = this->_start + n;
				const_pointer tmp = &*(first);
				while(tmp != &(*last))
					this->_alloc.construct(this->_end++, *tmp++);
				this->_alloc.deallocate(start, end_of_capacity - start);
			}
		}

		//assign range
		void assign(size_type n, const value_type &val)
		{
			this->clear();
			if (n <= this->capacity())
			{
				while (n--)
					this->_alloc.construct(this->_end++, val);
			}
			else
			{
				pointer start = this->_start;
				pointer end_of_capacity = this->_end_capacity;

				this->_start = this->_alloc.allocate(n);
				this->_end = this->_start;
				this->_end_capacity = this->_start + n;
				while (n--)
					this->_alloc.construct(this->_end++, val);
				this->_alloc.deallocate(start, end_capacity - start);
			}
		}

		// 벡터의 뒤에 새로운 element를 추가한다.
		// 늘어난 벡터의 크기가 capacity를 넘어갈 경우, 이전 capacity * 2의 크기로
		// 늘어남.
		void push_back(const value_type &val)
		{
			if (this->_end == this->_end_of_capacity)
			{
				if (this->size() == 0)
					this->reserve(1);
				else
					this->reserve(this->capacity() * 2);
			}
			this->_alloc.construct(this->_end++, val);
		}

		// 벡터의 맨 뒤 요소를 하나 제거한다.
		void pop_back()
		{
			this->_alloc.destroy(--this->_end);
		}

		iterator insert(iterator position, const value_type &val)
		{
			size_type n = &(*position) - this->_start;
			this->insert(position, 1, val);
			return (this->begin() + n);
		}

		void insert(iterator position, size_type n, const value_type &val)
		{
			// size_type mv_back_count = this->_end - &(*position);
			// pointer tmp = this->_end - 1;
			// for (; mv_back_count > 0; mv_back_count--, tmp--) {
			// this->_alloc.construct(tmp, *(tmp - n));
			// this->_alloc.destroy(tmp - n);
			// }
			// while (n--) {
			// this->_alloc.construct(tmp--, val);
			// }
			// this->resize(this->size() + n);
			if (this->size() + n < this->capacity())
			{
				pointer val_tmp = this->_end;
				size_type range = this->_end - &(*position);
				this->_end += n;
				pointer tmp = this->_end;
				while (range--)
					this->_alloc.construct(--tmp, *(--val_tmp));
				while (n--)
					this->_alloc.construct(--tmp, val);

			}
			else
			{
				pointer tmp = this->_start;
				size_type _size = n + size();
				size_type front_tmp = &(*position) - this->_start;
				size_tupe back_tmp = _end - &(*position);
				this->_start = _alloo.allocate(_size);
				this->_end = _start;
				this->_end_of_capacity = this->_start + _size;
				while (front_tmp--)
				{
					_alloc.construct(_end++, *tmp);
					_alloc.destroy(tmp++);
				}
				while (n--)
					_alloc.construct(_end++, val);
				while (back_tmp--)
				{
					_alloc.construct(_end++, *tmp);
					_alloc.destroy(tmp++);
				}
			}

		}

		template < typename InputIterator >
		void insert(iterator position, InputIterator first, InputIterator last,
			typename ft::enable_if< !ft::is_integral< InputIterator >::value >::type* = ft_nullptr)
		{
			// size_type n = this->_end - &(*position);

			// this->resize(this->size() + n);
			// pointer tmp = this->_end - 1;
			// for (; mv_back_count > 0; mv_back_count--, tmp--) {
			// this->_alloc.construct(tmp, *(tmp - n));
			// this->_alloc.destroy(tmp - n);
			// }
			// while (first != last) {
			// this->_alloc.construct(tmp--, *(--last));
			// }
			// this->resize(this->size() + n);


			size_type n = ft::distance(first, last);
			if (this->size() + n < this->capacity())
			{
				pointer val_tmp = this->_end;
				size_type range = this->_end - &(*position);
				this->_end += n;
				pointer tmp = this->_end;
				while (range--)
					this->_alloc.construct(--tmp, *(--val_tmp));
				while (n--)
					this->_alloc.construct(--tmp, val);

			}
			else
			{
				pointer tmp = this->_start;
				size_type _size = n + size();
				size_type front_tmp = &(*position) - this->_start;
				size_tupe back_tmp = this->_end - &(*position);
				this->_start = this->_alloo.allocate(_size);
				this->_end = this->_start;
				this->_end_of_capacity = this->_start + _size;
				while (front_tmp--)
				{
					_alloc.construct(_end++, *tmp);
					_alloc.destroy(tmp++);
				}
				while (n--)
					_alloc.construct(_end++, val);
				while (back_tmp--)
				{
					_alloc.construct(_end++, *tmp);
					_alloc.destroy(tmp++);
				}
			}
		}

		iterator erase(iterator position)
		{
			this->_alloc.destroy(&(*position));
			size_type n = this->_end - &(*position) - 1;
			pointer tmp = (&(*position));

			while (n--)
			{
				this->_alloc.consturct(tmp, *(tmp + 1));
				this->_alloc.destroy(tmp++);
			}
			--_end;
			return (position);
		}

		iterator erase(iterator first, iterator last)
		{
			pointer tmp = &(*first);
			while (tmp != &(*last))
				_alloc.destroy(tmp++);
			size_type n = this->_end - &(*last);
			size_type range = ft::distance(first, last);
			tmp = &(*first);
			while (n--)
			{
				_alloc.construct(tmp, *last++);
				_alloc.destroy(tmp++);
			}
			this->_end -= range;
			return first;
			// pointer location = &(*first);
			// pointer f_ptr = &(*first), l_ptr = &(*last);
			// size_type erase_size = l_ptr - f_ptr;

			// for (; f_ptr != l_ptr; f_ptr++) {
			// this->_alloc.destroy(f_ptr);
			// }
			// for (f_ptr = &(*first); l_ptr != this->_end; f_ptr++, l_ptr++) {
			// this->_alloc.construct(f_ptr, *l_ptr);
			// this->_alloc.destroy(l_ptr);
			// }
			// this->_end -= erase_size;
			// return (iterator(location));
			// pointer tmp = &(*first);
			// while (tmp != &(*last))
			// 	_alloc.destroy(tmp++);
			// size_type n = _finish - &(*last);
			// size_type range = ft::distance(first, last);
			// tmp = &(*first);
			// while (n--) {
			// 	_alloc.construct(tmp, *last++);
			// 	_alloc.destroy(tmp++);
			// }
			// _finish -= range;
			// return first;
		}

		void swap(vector &x) {
			if (*this == x)
				return ;

			allocator_type tmp_alloc = x._alloc;
			pointer tmp_start = x._start;
			pointer tmp_end = x._end;
			pointer tmp_end_of_capacity = x._end_of_capacity;

			x._alloc = this->_alloc;
			x._start = this->_start;
			x._end = this->_end;
			x._end_of_capacity = this->_end_of_capacity;

			this->_alloc = tmp_alloc;
			this->_start = tmp_start;
			this->_end = tmp_end;
			this->_end_of_capacity = tmp_end_of_capacity;
		}

		void clear()
		{
			while (this->_start != this->_end)
				this->_alloc.destroy(--this->_end);
		}

		//allocatot
		allocator_type get_allocator() const
		{
			return (this->_alloc);
		}
	};

	template <typename T, typename Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename ft::vector< T, Alloc >::const_iterator it_lhs = lhs.begin();
		typename ft::vector< T, Alloc >::const_iterator it_rhs = rhs.begin();

		while (it_lhs != lhs.end())
			if (it_rhs == rhs.end() || *it_lhs != *it_rhs)
				return (false);
		return (true);
	}

	template < typenameT, typename Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <typename T, typename Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <typename T, typename Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(rhs < lhs));
	}

	template <typename T, typename Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (rhs < lhs);
	}

	template <typename T, typename Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(lhs < rhs));
	}

	template <typename T, typename Alloc>
	void swap(vector< T, Alloc > &x, vector< T, Alloc > &y)
	{
		x.swap(y);
	}
}

#endif
