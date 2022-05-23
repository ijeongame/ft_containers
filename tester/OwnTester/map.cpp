/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunlee <hyunlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:36:33 by hyunlee           #+#    #+#             */
/*   Updated: 2021/11/27 15:48:19 by hyunlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"

#include <iostream>
#include <list>
#include <map>
#include <string>

#ifndef TESTED_NAMESPACE
#define TESTED_NAMESPACE ft
#endif

#define T1 int
#define T2 std::string
#define T3 TESTED_NAMESPACE::map< T1, T2 >::value_type
#define T_SIZE_TYPE typename TESTED_NAMESPACE::map< T1, T2 >::size_type

template < typename T_MAP >
void printContainers(T_MAP const &mp, bool print_content = true) {
  const T_SIZE_TYPE size = mp.size();

  std::cout << "size: " << size << std::endl;
  if (print_content) {
    typename TESTED_NAMESPACE::map< T1, T2 >::const_iterator it = mp.begin();
    typename TESTED_NAMESPACE::map< T1, T2 >::const_iterator ite = mp.end();
    std::cout << "Content is:" << std::endl;
    for (; it != ite; ++it) {
      std::cout << "- KEY: " << (*it).first << "\t|\t VALUE: " << (*it).second
                << std::endl;
    }
  }
  std::cout << "###############################################" << std::endl;
}

int main() {
  std::cout << "////////// TEST MAP //////////" << std::endl;

  std::cout << "  == default / range / copy constructor test ==" << std::endl;
  std::cout << "default constructor" << std::endl;
  TESTED_NAMESPACE::map< T1, T2 > mp;
  printContainers(mp);

  std::cout << "range constructor" << std::endl;
  std::list< T3 > lst;
  unsigned int lst_size = 10;
  for (unsigned int i = 0; i < lst_size; ++i) {
    lst.push_back(T3(i + 1, std::string(i + 1, i + 65)));
  }
  TESTED_NAMESPACE::map< T1, T2 > mp_range(lst.begin(), lst.end());
  printContainers(mp_range);

  std::cout << "copy constructor" << std::endl;
  TESTED_NAMESPACE::map< T1, T2 > mp_copy(mp_range);
  printContainers(mp_copy);

  std::cout << "assign operator" << std::endl;
  lst_size = 5;
  lst.clear();
  for (unsigned int i = 0; i < lst_size; ++i) {
    lst.push_back(T3(i + 1, std::string((lst_size - i), i + 67)));
  }
  TESTED_NAMESPACE::map< T1, T2 > mp_ot(lst.begin(), lst.end());
  mp_copy = mp_ot;
  printContainers(mp_copy);

  std::cout << "  == size / clear / empty test ==" << std::endl;
  std::cout << "before clear" << std::endl;
  printContainers(mp_ot);
  mp_ot.clear();
  std::cout << "after clear" << std::endl;
  printContainers(mp_ot);
  std::cout << "Is empty: " << (mp_ot.empty() ? "OK" : "KO") << std::endl;

  std::cout << "  == insert / erase / [] test ==" << std::endl;
  mp_ot.insert(++(++lst.begin()), lst.end());
  printContainers(mp_ot);
  mp_ot.insert(++mp_ot.begin(), TESTED_NAMESPACE::make_pair(42, "Seoul"));
  mp_ot.insert(++mp_ot.begin(), TESTED_NAMESPACE::make_pair(42, "Hi"));
  printContainers(mp_ot);
  mp_ot.insert(TESTED_NAMESPACE::make_pair(21, "Hello"));
  mp_ot.insert(TESTED_NAMESPACE::make_pair(21, "Bye"));
  mp_ot.insert(TESTED_NAMESPACE::make_pair(21, "LOLLL"));
  printContainers(mp_ot);

  mp_ot[2] = "New";
  printContainers(mp_ot);
  mp_ot[4] = "Change";
  printContainers(mp_ot);

  mp_ot.erase(++mp_ot.begin());
  printContainers(mp_ot);
  mp_ot.erase(21);
  printContainers(mp_ot);
  mp_ot.erase(++mp_ot.begin(), --mp_ot.end());
  printContainers(mp_ot);

  std::cout << "  == swap / find / count test ==" << std::endl;
  printContainers(mp_ot);
  printContainers(mp_range);
  std::cout << "swap" << std::endl;
  swap(mp_ot, mp_range);
  printContainers(mp_ot);
  printContainers(mp_range);

  std::cout << "find 5: " << mp_ot.find(5)->second << std::endl;
  std::cout << "count 5: " << mp_ot.count(5) << std::endl;
  std::cout << "count 20: " << mp_ot.count(20) << std::endl;

  std::cout << "  == lower & upper_bound / equal_range test ==" << std::endl;
  std::cout << "lower_bound " << mp_ot.lower_bound(5)->first << std::endl;
  std::cout << "upper_bound " << mp_ot.upper_bound(5)->first << std::endl;
  std::cout << "equal_range " << mp_ot.equal_range(5).first->first << ", "
            << mp_ot.equal_range(5).second->first << std::endl;

  std::cout << "  == relational operators test ==" << std::endl;
  lst_size = 7;
  lst.clear();
  for (unsigned int i = 0; i < lst_size; ++i) {
    lst.push_back(T3(i * 2, std::string((lst_size - i), i + 67)));
  }
  TESTED_NAMESPACE::map< T1, T2 > lhs(lst.begin(), lst.end());
  TESTED_NAMESPACE::map< T1, T2 > rhs(lhs);
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

  lhs[5] = "Hello";
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

  // system("leaks map");
}
