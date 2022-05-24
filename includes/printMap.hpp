#if !defined(PRINTMAP_HPP)
#define PRINTMAP_HPP

#include <iostream>

#include "RBTree.hpp"

#define C_RED "\033[0;31m"
#define C_RESET "\e[0m"

namespace ft {
template < typename T >
void printMap(RBTreeNode< T >* node, int depth) {
  if (depth == 0) {
    std::cout << "// SHOW TREE //" << std::endl;
  }
  int tmp_depth = depth;
  if (node->value == NULL) {
    while (tmp_depth--) {
      std::cout << "     ";
    }
    std::cout << "nil" << std::endl;
    return;
  }
  while (tmp_depth--) {
    std::cout << "     ";
  }
  std::cout << (node->color ? C_RESET : C_RED)
            << (node->parent->value == NULL ? "Root" : (node->parent->leftChild == node ? "L" : "R"))
            << " - key: " << node->value->first << C_RESET << std::endl;
  if (node->leftChild->value != NULL) {
    // std::cout << "left?" << std::endl;
    printMap(node->leftChild, depth + 1);
  }
  if (node->rightChild->value != NULL) {
    printMap(node->rightChild, depth + 1);
  }
    // std::cout << "right?" << std::endl;
  return;
}
}  // namespace ft

#endif  // PRINTTREE_HPP
