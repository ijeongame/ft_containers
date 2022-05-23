/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunlee <hyunlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:36:50 by hyunlee           #+#    #+#             */
/*   Updated: 2021/11/27 15:48:30 by hyunlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"

#include <iostream>
#include <string>
#include <vector>

#ifndef TESTED_NAMESPACE
#define TESTED_NAMESPACE ft
#endif

#define TESTED_TYPE int
#define T_SIZE_TYPE typename TESTED_NAMESPACE::vector< T >::size_type

template < typename T >
void printContainers(TESTED_NAMESPACE::vector< T > const &vct,
                     bool print_content = true) {
  const T_SIZE_TYPE size = vct.size();
  const T_SIZE_TYPE capacity = vct.capacity();
  const std::string isCapacityOk = (capacity >= size) ? "OK" : "KO";

  std::cout << "size: " << size << std::endl;
  std::cout << "capacity: " << isCapacityOk << std::endl;
  if (print_content) {
    typename TESTED_NAMESPACE::vector< T >::const_iterator it = vct.begin();
    typename TESTED_NAMESPACE::vector< T >::const_iterator ite = vct.end();
    std::cout << std::endl << "Content is:" << std::endl;
    for (; it != ite; ++it) {
      std::cout << "- " << *it << std::endl;
    }
  }
  std::cout << "###############################################" << std::endl;
}

int main() {
  std::cout << "////////// TEST VECTOR //////////" << std::endl;

  std::cout << "  == default / fill / range / copy constructor test =="
            << std::endl;
  TESTED_NAMESPACE::vector< TESTED_TYPE > v_default;
  TESTED_NAMESPACE::vector< TESTED_TYPE > v_fill(5, 42);
  TESTED_NAMESPACE::vector< TESTED_TYPE > v_range(v_fill.begin(),
                                                  --(--v_fill.end()));
  TESTED_NAMESPACE::vector< TESTED_TYPE > v_copy(v_range);

  printContainers(v_default);
  printContainers(v_fill);
  printContainers(v_range);
  printContainers(v_copy);

  std::cout << "  == assign operator test ==" << std::endl;
  TESTED_NAMESPACE::vector< TESTED_TYPE > v_assign(4, 21);

  printContainers(v_assign);
  v_assign = v_copy;
  printContainers(v_assign);

  std::cout << "  == begin / end / rbegin / rend test ==" << std::endl;
  TESTED_NAMESPACE::vector< TESTED_TYPE > v_iterator(7);
  for (unsigned int i = 0; i < v_iterator.size(); ++i) {
    v_iterator[i] = i * 3;
  }
  printContainers(v_iterator);
  TESTED_NAMESPACE::vector< TESTED_TYPE > v_riter(v_iterator.rbegin(),
                                                  v_iterator.rend());
  printContainers(v_riter);

  std::cout << "  == size / resize / capacity test ==" << std::endl;
  TESTED_NAMESPACE::vector< TESTED_TYPE > v_size(10);
  for (unsigned int i = 0; i < v_size.size(); ++i) {
    v_size[i] = i * 3;
  }
  std::cout << "capacity before resize: " << v_size.capacity() << std::endl;
  printContainers(v_size);
  std::cout << "resize to size 15\n..." << std::endl;
  v_size.resize(15);
  std::cout << "capacity after resize: " << v_size.capacity() << std::endl;
  printContainers(v_size, false);

  std::cout << "  == reserve test ==" << std::endl;
  TESTED_NAMESPACE::vector< TESTED_TYPE > v_reserve;

  std::cout << "capacity before reserve: " << v_reserve.capacity() << std::endl;
  printContainers(v_reserve, false);
  v_reserve.reserve(7);
  std::cout << "capacity after reserve: " << v_reserve.capacity() << std::endl;
  printContainers(v_reserve);

  std::cout << "  == [] / at / front / back test ==" << std::endl;
  TESTED_NAMESPACE::vector< TESTED_TYPE > v_element(7);
  for (unsigned int i = 0; i < v_element.size(); ++i) {
    v_element[i] = v_element.size() - (i * 2);
  }
  printContainers(v_element);

  v_element[0] = 42;
  v_element[6] = 24;
  printContainers(v_element);
  std::cout << "at[0]: " << v_element.at(0) << std::endl;
  std::cout << "at[5]: " << v_element.at(5) << std::endl;
  std::cout << "front: " << v_element.front() << std::endl;
  std::cout << "back: " << v_element.back() << std::endl;

  std::cout << "  == assign test ==" << std::endl;
  TESTED_NAMESPACE::vector< TESTED_TYPE > vctA(10);
  TESTED_NAMESPACE::vector< TESTED_TYPE > vctB(5);
  TESTED_NAMESPACE::vector< TESTED_TYPE > vctC;
  TESTED_NAMESPACE::vector< TESTED_TYPE > vctD;

  for (unsigned int i = 0; i < vctA.size(); ++i) {
    vctA[i] = (vctA.size() - i) * 2;
  }
  for (unsigned int i = 0; i < vctB.size(); ++i) {
    vctB[i] = (vctB.size() - i) * 5;
  }
  printContainers(vctA);
  printContainers(vctB);
  vctC.assign(vctA.begin(), vctA.end());
  vctA.assign(vctB.begin(), vctB.end());
  vctB.assign(2, 42);
  vctD.assign(4, 21);

  std::cout << "  # after assign(): #" << std::endl;

  printContainers(vctA);
  printContainers(vctB);
  printContainers(vctC);
  printContainers(vctD);

  vctD.assign(6, 42);
  printContainers(vctD);

  std::cout << "  # assign on enough capacity and low size: #" << std::endl;

  vctA.assign(5, 53);
  vctB.assign(vctC.begin(), vctC.begin() + 3);

  printContainers(vctA);
  printContainers(vctB);

  std::cout << "  == push & pop back test ==" << std::endl;
  TESTED_NAMESPACE::vector< TESTED_TYPE > v_pushpop;
  for (unsigned int i = 0; i < 6; ++i) {
    v_pushpop.push_back((i * 7) % 4);
    std::cout << "PUSH " << i + 1 << std::endl;
    std::cout << "size: " << v_pushpop.size() << std::endl;
    std::cout << "capacity: " << v_pushpop.capacity() << std::endl;
    std::cout << "..." << std::endl;
  }
  std::cout << "DONE.\n" << std::endl;
  printContainers(v_pushpop);
  std::cout << "POP!" << std::endl;
  v_pushpop.pop_back();
  printContainers(v_pushpop);
  std::cout << "POP!" << std::endl;
  v_pushpop.pop_back();
  printContainers(v_pushpop);
  std::cout << "POP!" << std::endl;
  v_pushpop.pop_back();
  printContainers(v_pushpop);
  std::cout << "capacity: " << v_pushpop.capacity() << std::endl;

  std::cout << "  == insert / erase test ==" << std::endl;
  TESTED_NAMESPACE::vector< TESTED_TYPE > v_insert;
  TESTED_NAMESPACE::vector< TESTED_TYPE > v_insert2(5);
  for (unsigned int i = 0; i < v_insert2.size(); ++i) {
    v_insert2[i] = i + 1;
  }
  printContainers(v_insert);
  v_insert.insert(v_insert.begin(), 42);
  printContainers(v_insert);
  v_insert.insert(v_insert.begin(), 3, 21);
  printContainers(v_insert);
  v_insert.insert(++v_insert.begin(), ++v_insert2.begin(), v_insert2.end());
  printContainers(v_insert);

  v_insert.erase(++(++v_insert.begin()));
  printContainers(v_insert);
  v_insert.erase(--(--(v_insert.end())), v_insert.end());
  printContainers(v_insert);

  std::cout << "  == swap test ==" << std::endl;
  TESTED_NAMESPACE::vector< TESTED_TYPE > v_swapA(5);
  TESTED_NAMESPACE::vector< TESTED_TYPE > v_swapB(3);
  for (unsigned int i = 0; i < v_swapA.size(); ++i) {
    v_swapA[i] = i + 1;
  }
  for (unsigned int i = 0; i < v_swapB.size(); ++i) {
    v_swapB[i] = (i + 1) * 2;
  }
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

  std::cout << "  == clear test ==" << std::endl;
  TESTED_NAMESPACE::vector< TESTED_TYPE > v_clear(7);
  for (unsigned int i = 0; i < v_clear.size(); ++i) {
    v_clear[i] = (i + 1) * 3;
  }

  std::cout << "before clear" << std::endl;
  printContainers(v_clear);
  v_clear.clear();
  std::cout << "after clear" << std::endl;
  printContainers(v_clear);

  std::cout << "  == relational operators test ==" << std::endl;
  TESTED_NAMESPACE::vector< TESTED_TYPE > v_lhs(5);
  TESTED_NAMESPACE::vector< TESTED_TYPE > v_rhs;

  for (unsigned int i = 0; i < v_lhs.size(); ++i) {
    v_lhs[i] = (i * 3) + 2;
  }

  v_rhs.insert(v_rhs.begin(), v_lhs.begin(), v_lhs.end());

  printContainers(v_lhs);
  printContainers(v_rhs);
  std::cout << "operator ==" << std::endl;
  std::cout << ((v_lhs == v_rhs) ? "OK" : "KO") << std::endl;

  std::cout << "operator !=" << std::endl;
  std::cout << ((v_lhs != v_rhs) ? "OK" : "KO") << std::endl;

  std::cout << "operator <" << std::endl;
  std::cout << ((v_lhs < v_rhs) ? "OK" : "KO") << std::endl;

  std::cout << "operator <=" << std::endl;
  std::cout << ((v_lhs <= v_rhs) ? "OK" : "KO") << std::endl;

  std::cout << "operator >" << std::endl;
  std::cout << ((v_lhs > v_rhs) ? "OK" : "KO") << std::endl;

  std::cout << "operator >=" << std::endl;
  std::cout << ((v_lhs >= v_rhs) ? "OK" : "KO") << std::endl;

  // system("leaks vector");
}
