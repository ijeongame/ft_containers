/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:56:31 by hkwon             #+#    #+#             */
/*   Updated: 2022/05/07 20:51:59 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

#include "reverse_iterator.hpp"

/**
 * utils implement
 * enable_if
 * is_integral
 * equal/lexicographical compare
 * std::pair
 * std::make_pair
 */

namespace ft
{
	/**
	 * enable_if
	 *
	 * Cond가 true인 경우를 specialize하여 type을 typename으로 사용할 수 있게한다.
	 * enable_if는 특정 타입으로 템플릿을 제한하여 사용하고 싶거나 타입별로 분기를 한다거나 할 때 사용할 수 있다.
	 * enable_if의 템플릿 첫번째 인자로 true가 오면, enable_if의 구주체 안에는 type이라는 자료형이 생긴다.
	 * 따라서 enable_if의 템플릿 첫번쨰 인자로 boolean을 반환하는 구문을 넣어두고 해당구문에서 판별을 요청하면,
	 * 결과값에 따라 type이 생기거나 생기지않는 것을 이용할 수 있다.
	 * template<typename T, std::enable_if<std::is_integral<T>::value, int>:: type = 0>
	 * void foo(const T& bar) { isInt(); }
	 * is_integral 는 T가 integral계열인지 true, false로 반환한다. integral 계열일 때만 ::type 호출이 가능하다.
	 * integral 계열이 아니라면, 이 foo 함수는 적합하지 않은 것으로 판단하고 인스턴스화하지 않고 넘어간다.
	 */
	template <bool Cond, typename T = void>
	struct enable_if {};

	template <typename T>
	struct enable_if<true, T> {
		typedef T type;
	};

	/**
	 * is_integral
	 *
	 * T가 Integral type인지 확인한다.
	 * bool, char, char16_t, char32_t, wchar_t, short, int, long, long long,
	 * unsinged char, unsigned short, unsigned int, unsigned long, unsigned long long,
	 * or any inplementation-defined extended integer types,
	 * including any signed, unsigned, and cv-qualified variants.
	 * 그렇지 않으면 false.
	 */
	template <bool is_integral, typename T>
	struct integral_traits {
		typedef T type;
		static const bool value = is_integral;
	};

	//float, double, long double은 false로 처리된다.
	//char16_t, char32_t, long long, unsigned long long -> c++11
	template <typename>
	struct is_integral_type : public integral_traits<false, bool> {};

	// template 특수화
	// bool 타입에 대해 특수화
	template <>
	struct is_integral_type<bool> : public integral_traits<true, bool> {};

	template <>
	struct is_integral_type<char> : public integral_traits<true, bool> {};

	template <>
	struct is_integral_type<signed char> : public integral_traits<true, bool> {};

	template <>
	struct is_integral_type<wchar_t> : public integral_traits<true, bool> {};

	template <>
	struct is_integral_type<short int> : public integral_traits<true, bool> {};

	template <>
	struct is_integral_type<int> : public integral_traits<true, bool> {};

	template <>
	struct is_integral_type<long int> : public integral_traits<true, bool> {};

	template <>
	struct is_integral_type<long long int> : public integral_traits<true, bool> {};

	template <>
	struct is_integral_type<unsigned char> : public integral_traits<true, bool> {};

	template <>
	struct is_integral_type<unsigned short> : public integral_traits<true, bool> {};

	template <>
	struct is_integral_type<unsigned int> : public integral_traits<true, bool> {};

	template <>
	struct is_integral_type<unsigned long int> : public integral_traits<true, bool> {};

	template <>
	struct is_integral_type<unsigned long long int> : public integral_traits<true, bool> {};

	/**
	 * T가 integral type인지 식별하는 class.
	 * is_integral_type< T > 를 상속받아 T에 따라 type을 다르게 갖는다.
	 */
	template < typename T >
	struct is_integral : public is_integral_type< T > {};

	//equality
	template <class InputIterator1, class InputIterator2>
	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1! == *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	};

	/**
	 * predicate
	 *
	 * pred
	 * binary predicate which returns ​true if the elements should be treated as equal.
	 * 두 요소를 인수로 받아들이고(같은 순서로 두 시퀀스 각각 중 하나) 부울로 변환 가능한 값을 반환하는 이진 함수입니다.
	 * 반환되는 값은 요소가 이 함수의 컨텍스트에서 일치하는 것으로 간주되는지 여부를 나타냅니다.
	 * 함수는 인수를 수정하지 않아야 한다.
	 * 이것은 함수 포인터 또는 함수 객체일 수 있다.
	 */
	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1)
		{
			if (!pred(*first1, *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	};

	/**
	 * lexicographical compare
	 * ver1 : default
	 * ver2 : custom
	 */

	/**
	 * default
	 */
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	};

	/**
	 * custom
	 * binary comparison function comp
	 * comparison function object (i.e. an object that satisfies the requirements of Compare)
	 * which returns ​true if the first argument is less than the second.
	 */
	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1))
				return false;
			else if (cmop(*first1, *first2))
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	};

	template <class T1, class T2>
	struct pair
	{
		public:
			typedef T1 first_type;
			typedef T2 second_type;

			first_type first;
			second_type second;

			//default
			pair() : first(T1), second(T2) {}
			//copy
			template<class U, class V> pair (const pair<U, V>& pr) : first(pr.first), second(pr.second) {}
			//initialization
			pair(const first_type& a, const second_type& b) : first(a), second(b) {}
			//assign
			pair& operator= (const pair& pr)
			{
				if (this != &pr)
				{
					this->first = pr.first;
					this->second = pr.second;
				}
				return (*this);
			}
	};

	template <class T1, class T2>
	pair<T1, T2> make_pair(T1 x, T2 y)
	{
		return ( pair<T1, T2>(x,y) );
	};

	template <class T1, class T2>
	bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	};

	template <class T1, class T2>
	bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (!(lhs == rhs));
	};

	template <class T1, class T2>
	bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (lhs.first < rhs.first || !(rhs.first < lhs.first) && lhs.first < rhs.second);
	};

	template <class T1, class T2>
	bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (!(rhs < lhs));
	};

	template <class T1, class T2>
	bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (rhs < lhs);
	};

	template <class T1, class T2>
	bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return !(lhs < rhs);
	};
}

#endif
