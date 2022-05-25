#include <iostream>
#include <list>
#include <map>
#include <string>

#include "map.hpp"


#define T1 int
#define T2 std::string
#define T3 ft::map< T1, T2 >::value_type

int main() {
  std::list< T3 > lst;
  unsigned int lst_size = 10;
  for (unsigned int i = 0; i < lst_size; ++i) {
    lst.push_back(T3(i + 1, std::string(i + 1, i + 65)));
  }
  ft::map< T1, T2 > mp(lst.begin(), lst.end());

  mp.showTree();
	system("leaks map");
}
