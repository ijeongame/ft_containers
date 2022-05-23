/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunlee <hyunlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:36:42 by hyunlee           #+#    #+#             */
/*   Updated: 2021/11/27 15:48:25 by hyunlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set.hpp"

#include <iostream>
#include <list>
#include <set>
#include <string>

#ifndef TESTED_NAMESPACE
#define TESTED_NAMESPACE ft
#endif

#define T1 int
#define T3 TESTED_NAMESPACE::set< T1 >::value_type
#define T_SIZE_TYPE typename TESTED_NAMESPACE::set< T1 >::size_type

template < typename T_SET >
void printContainers(T_SET const &st, bool print_content = true) {
  const T_SIZE_TYPE size = st.size();

  std::cout << "size: " << size << std::endl;
  if (print_content) {
    typename TESTED_NAMESPACE::set< T1 >::const_iterator it = st.begin();
    typename TESTED_NAMESPACE::set< T1 >::const_iterator ite = st.end();
    std::cout << "Content is:" << std::endl;
    for (; it != ite; ++it) {
      std::cout << "- KEY: " << (*it) << std::endl;
    }
  }
  std::cout << "###############################################" << std::endl;
}

int main() {
  std::cout << "////////// TEST SET //////////" << std::endl;

  std::cout << "  == default / range / copy constructor test ==" << std::endl;
  std::cout << "default constructor" << std::endl;
  TESTED_NAMESPACE::set< T1 > st;
  printContainers(st);

  std::cout << "range constructor" << std::endl;
  std::list< T3 > lst;
  unsigned int lst_size = 10;
  for (unsigned int i = 0; i < lst_size; ++i) {
    lst.push_back(T3(i + 1));
  }
  TESTED_NAMESPACE::set< T1 > st_range(lst.begin(), lst.end());
  printContainers(st_range);

  std::cout << "copy constructor" << std::endl;
  TESTED_NAMESPACE::set< T1 > st_copy(st_range);
  printContainers(st_copy);

  std::cout << "assign operator" << std::endl;
  lst_size = 5;
  lst.clear();
  for (unsigned int i = 0; i < lst_size; ++i) {
    lst.push_back(T3(i + 1));
  }
  TESTED_NAMESPACE::set< T1 > st_ot(lst.begin(), lst.end());
  st_copy = st_ot;
  printContainers(st_copy);

  std::cout << "  == size / clear / empty test ==" << std::endl;
  std::cout << "before clear" << std::endl;
  printContainers(st_ot);
  st_ot.clear();
  std::cout << "after clear" << std::endl;
  printContainers(st_ot);
  std::cout << "Is empty: " << (st_ot.empty() ? "OK" : "KO") << std::endl;

  std::cout << "  == insert / erase test ==" << std::endl;
  st_ot.insert(++(++lst.begin()), lst.end());
  printContainers(st_ot);
  st_ot.insert(++st_ot.begin(), 42);
  st_ot.insert(++st_ot.begin(), 42);
  printContainers(st_ot);
  st_ot.insert(21);
  st_ot.insert(21);
  st_ot.insert(21);
  printContainers(st_ot);

  st_ot.erase(++st_ot.begin());
  printContainers(st_ot);
  st_ot.erase(21);
  printContainers(st_ot);
  st_ot.erase(++st_ot.begin(), --st_ot.end());
  printContainers(st_ot);

  std::cout << "  == swap / find / count test ==" << std::endl;
  printContainers(st_ot);
  printContainers(st_range);
  std::cout << "swap" << std::endl;
  swap(st_ot, st_range);
  printContainers(st_ot);
  printContainers(st_range);

  std::cout << "find 5: " << *st_ot.find(5) << std::endl;
  std::cout << "count 5: " << st_ot.count(5) << std::endl;
  std::cout << "count 20: " << st_ot.count(20) << std::endl;

  std::cout << "  == lower & upper_bound / equal_range test ==" << std::endl;
  std::cout << "lower_bound " << *st_ot.lower_bound(5) << std::endl;
  std::cout << "upper_bound " << *st_ot.upper_bound(5) << std::endl;
  std::cout << "equal_range " << *st_ot.equal_range(5).first << ", "
            << *st_ot.equal_range(5).second << std::endl;

  std::cout << "  == relational operators test ==" << std::endl;
  lst_size = 7;
  lst.clear();
  for (unsigned int i = 0; i < lst_size; ++i) {
    lst.push_back(T3(i * 2));
  }
  TESTED_NAMESPACE::set< T1 > lhs(lst.begin(), lst.end());
  TESTED_NAMESPACE::set< T1 > rhs(lhs);
  printContainers(lhs);
  printContainers(rhs);

  std::cout << "operator ==" << std::endl;
  std::cout << ((lhs == rhs) ? "OK" : "KO") << std::endl;

  std::cout << "operator !=" << std::endl;
  std::cout << ((lhs != rhs) ? "OK" : "KO") << std::endl;

  std::cout << "operator <" << std::endl;
  std::cout << ((lhs < rhs) ? "OK" : "KO") << std::endl;

  std::cout << "operator <=" << std::endl;
  std::cout << ((lhs <= rhs) ? "OK" : "KO") << std::endl;

  std::cout << "operator >" << std::endl;
  std::cout << ((lhs > rhs) ? "OK" : "KO") << std::endl;

  std::cout << "operator >=" << std::endl;
  std::cout << ((lhs >= rhs) ? "OK" : "KO") << std::endl;

  // system("leaks set");
}
