#include "vector.hpp"
#include <iostream>
#include <string>
#include <vector>

#ifndef TESTED_NAMESPACE
#define TESTED_NAMESPACE ft
#endif

#define TYPE int
#define T_SIZE_TYPE typename TESTED_NAMESPACE::vector<T>::size_type

template <typename T>
void printContainers(TESTED_NAMESPACE::vector<T> const &vec, bool print_content = true) {
	const T_SIZE_TYPE size = vec.size();
	const T_SIZE_TYPE capacity = vec.capacity();
	const std::string isCapacityOK = (capacity >= size) ? "OK" : "KO";

	std::cout << "size: " << size << std::endl;
	std::cout << "capacity: " << isCapacityOK << std::endl;
	if (print_content) {
		typename TESTED_NAMESPACE::vector<T>::const_iterator it = vec.begin();
		typename TESTED_NAMESPACE::vector<T>::const_iterator ite = vec.end();
		std::cout << std::endl << "Content is: " << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	std::cout << "------------------------" << std::endl;
}

int main() {
	std::cout << "################ Test Vector ################" << std::endl;

	std::cout << "===== default | fill | range | copy constructor =====" << std::endl;
	TESTED_NAMESPACE::vector<TYPE> v_default;
	TESTED_NAMESPACE::vector<TYPE> v_fill(5, 42);
	TESTED_NAMESPACE::vector<TYPE> v_range(v_fill.begin(), --(v_fill.end()));
	TESTED_NAMESPACE::vector<TYPE> v_copy(v_range);

	printContainers(v_default);
	printContainers(v_fill);
	printContainers(v_range);
	printContainers(v_copy);
	std::cout << std::endl;

	std::cout << "===== assignment operator =====" << std::endl;
	TESTED_NAMESPACE::vector<TYPE> v_assign(4, 21);
	printContainers(v_assign);
	v_assign = v_copy;
	printContainers(v_assign);

	std::cout << "\n################################################" << std::endl;
	std::cout << "===== begin | end | rbegin | rend =====" << std::endl;
	TESTED_NAMESPACE::vector<TYPE> v_iter(7);
	for (unsigned int i = 0; i < v_iter.size(); ++i)
		v_iter[i] = i * 3;
	printContainers(v_iter);

	TESTED_NAMESPACE::vector<TYPE> v_riter(v_iter.rbegin(), v_iter.rend());
	printContainers(v_riter);

	std::cout << "\n################################################" << std::endl;
	std::cout << "===== size | resize | capacity =====" << std::endl;
	TESTED_NAMESPACE::vector<TYPE> v_size(5);
	for (unsigned int i = 0; i < v_size.size(); ++i)
		v_size[i] = i * 3;

	std::cout << "capacity before resize: " << v_size.capacity() << std::endl;
	printContainers(v_size);

	std::cout << "resize to size = 10 ..." << std::endl;
	v_size.resize(10);

	std::cout << "capacity after resize: " << v_size.capacity() << std::endl;
	printContainers(v_size, false);

	std::cout << "\n################################################" << std::endl;
	std::cout << "===== reserve test =====" << std::endl;
	TESTED_NAMESPACE::vector<TYPE> v_reserve;
	std::cout << "capacity before reserve: " << v_reserve.capacity() << std::endl;
	printContainers(v_reserve, false);

	v_reserve.reserve(7);
	std::cout << "capacity after reserve: " << v_reserve.capacity() << std::endl;
	printContainers(v_reserve);

	std::cout << "\n################################################" << std::endl;
	std::cout << "===== [] | at | front | back =====" << std::endl;
	TESTED_NAMESPACE::vector<TYPE> v_element(7);
	for (unsigned int i = 0; i < v_element.size(); ++i)
		v_element[i] = v_element.size() - (i * 2);
	printContainers(v_element);

	v_element[0] = 42;
	v_element[6] = 21;
	printContainers(v_element);

	std::cout << "at[0]: " << v_element.at(0) << std::endl;
	std::cout << "at[5]: " << v_element.at(5) << std::endl;
	std::cout << "front: " << v_element.front() << std::endl;
	std::cout << "back: " << v_element.back() << std::endl;

	std::cout << "\n################################################" << std::endl;
	std::cout << "===== assign test =====" << std::endl;
	TESTED_NAMESPACE::vector<TYPE> vecA(10);
	TESTED_NAMESPACE::vector<TYPE> vecB(5);
	TESTED_NAMESPACE::vector<TYPE> vecC;
	TESTED_NAMESPACE::vector<TYPE> vecD;

	for (unsigned int i = 0; i < vecA.size(); ++i)
		vecA[i] = (vecA.size() - i) * 2;
	for (unsigned int i = 0; i < vecB.size(); ++i)
		vecB[i] = (vecB.size() - i) * 5;
	printContainers(vecA);
	printContainers(vecB);

	vecC.assign(vecA.begin(), vecA.end());
	vecA.assign(vecB.begin(), vecB.end());
	vecB.assign(2, 42);
	vecD.assign(4, 24);

	std::cout << "after assign: " << std::endl;
	printContainers(vecA);
	printContainers(vecB);
	printContainers(vecC);
	printContainers(vecD);

	vecD.assign(6, 42);
	printContainers(vecD);

	std::cout << "assign on enough capacity and low size: " << std::endl;
	vecA.assign(5, 84);
	vecB.assign(vecC.begin(), vecC.begin() + 3);
	printContainers(vecA);
	printContainers(vecB);

	std::cout << "\n################################################" << std::endl;
	std::cout << "===== push_back | pop_back =====" << std::endl;
	TESTED_NAMESPACE::vector<TYPE> v_pushpop;
	for (unsigned int i = 0; i < 6; ++i) {
		v_pushpop.push_back((i * 7) % 4);
		std::cout << "+++ push +++" << i + 1 << std::endl;
		std::cout << "size: " << v_pushpop.size() << std::endl;
		std::cout << "capacity: " << v_pushpop.capacity() << std::endl;
		std::cout << "......." << std::endl;
	}
	std::cout << "+++ push done +++" << std::endl;
	printContainers(v_pushpop);
	std::cout << "+++ pop +++" << std::endl;
	v_pushpop.pop_back();
	printContainers(v_pushpop);
	std::cout << "+++ pop +++" << std::endl;
	v_pushpop.pop_back();
	printContainers(v_pushpop);
	std::cout << "+++ pop +++" << std::endl;
	v_pushpop.pop_back();
	printContainers(v_pushpop);
	std::cout << "capacity: " << v_pushpop.capacity() << std::endl;

	std::cout << "\n################################################" << std::endl;
	std::cout << "===== insert | erase =====" << std::endl;
	TESTED_NAMESPACE::vector<TYPE> v_insert;
	TESTED_NAMESPACE::vector<TYPE> v_insert2(5);
	for (unsigned int i = 0; i < v_insert2.size(); ++i)
		v_insert2[i] = i + 1;
	printContainers(v_insert);

	std::cout << "+++ insert +++" << std::endl;
	v_insert.insert(v_insert.begin(), 42);
	printContainers(v_insert);

	std::cout << "+++ insert +++" << std::endl;
	v_insert.insert(v_insert.begin(), 3, 21);
	printContainers(v_insert);

	std::cout << "+++ insert +++" << std::endl;
	v_insert.insert(++v_insert.begin(), ++v_insert2.begin(), v_insert2.end());
	printContainers(v_insert);

	std::cout << "+++ erase +++" << std::endl;
	v_insert.erase(++(++v_insert.begin()));
	printContainers(v_insert);

	std::cout << "+++ erase +++" << std::endl;
	v_insert.erase(--(--v_insert.end()), v_insert.end());
	printContainers(v_insert);

	std::cout << "\n################################################" << std::endl;
	std::cout << "===== swap =====" << std::endl;
	TESTED_NAMESPACE::vector<TYPE> v_swapA(5);
	TESTED_NAMESPACE::vector<TYPE> v_swapB(3);
	for (unsigned int i = 0; i < v_swapA.size(); ++i)
		v_swapA[i] = i + 1;
	for (unsigned int i = 0; i < v_swapB.size(); ++i)
		v_swapB[i] = (i + 1) * 2;

	std::cout << "before swap: " << std::endl;
	printContainers(v_swapA);
	printContainers(v_swapB);

	v_swapA.swap(v_swapB);
	std::cout << "after swap: " << std::endl;
	printContainers(v_swapA);
	printContainers(v_swapB);

	TESTED_NAMESPACE::swap(v_swapA, v_swapB);
	std::cout << "after non-member swap: " << std::endl;
	printContainers(v_swapA);
	printContainers(v_swapB);

	std::cout << "\n################################################" << std::endl;
	std::cout << "===== clear =====" << std::endl;
	TESTED_NAMESPACE::vector<TYPE> v_clear(7);
	for (unsigned int i = 0; i < v_clear.size(); ++i)
		v_clear[i] = (i + 1) * 3;

	std::cout << "before clear: " << std::endl;
	printContainers(v_clear);

	v_clear.clear();
	std::cout << "after clear: " << std::endl;
	printContainers(v_clear);

	std::cout << "\n################################################" << std::endl;
	std::cout << "===== relational operators =====" << std::endl;
	TESTED_NAMESPACE::vector<TYPE> v_lhs(5);
	TESTED_NAMESPACE::vector<TYPE> v_rhs;
	for (unsigned int i = 0; i < v_lhs.size(); ++i)
		v_lhs[i] = (i * 3) + 2;

	v_rhs.insert(v_rhs.begin(), v_lhs.begin(), v_lhs.end());
	printContainers(v_lhs);
	printContainers(v_rhs);

	std::cout << "same vector..." << std::endl;
	std::cout << "operator==: " << ((v_lhs == v_rhs) ? "OK" : "KO") << std::endl;
	std::cout << "operator!=: " << ((v_lhs != v_rhs) ? "OK" : "KO") << std::endl;
	std::cout << "operator<:  " << ((v_lhs < v_rhs) ? "OK" : "KO") << std::endl;
	std::cout << "operator<=: " << ((v_lhs <= v_rhs) ? "OK" : "KO") << std::endl;
	std::cout << "operator>:  " << ((v_lhs > v_rhs) ? "OK" : "KO") << std::endl;
	std::cout << "operator>=: " << ((v_lhs >= v_rhs) ? "OK" : "KO") << std::endl;
	std::cout << std::endl;

	std::cout << "different vector..." << std::endl;
	v_rhs.erase(v_rhs.begin());
	std::cout << "operator==: " << ((v_lhs == v_rhs) ? "OK" : "KO") << std::endl;
	std::cout << "operator!=: " << ((v_lhs != v_rhs) ? "OK" : "KO") << std::endl;
	std::cout << "operator<:  " << ((v_lhs < v_rhs) ? "OK" : "KO") << std::endl;
	std::cout << "operator<=: " << ((v_lhs <= v_rhs) ? "OK" : "KO") << std::endl;
	std::cout << "operator>:  " << ((v_lhs > v_rhs) ? "OK" : "KO") << std::endl;
	std::cout << "operator>=: " << ((v_lhs >= v_rhs) ? "OK" : "KO") << std::endl;
}
