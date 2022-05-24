#ifndef RBTREEITERATOR_HPP
# define RBTREEITERATOR_HPP

#include "utils.hpp"
#include "RBTreeNode.hpp"

/**
 * @brief Red Black Tree Iterator
 *
 * map에서 사용할 iterator
 * RBTreeNode를 가져와 node를 사용
 * vector와 달리 bidirectional iterator를 사용하는 이유
 * bidirectional iterator
 * 입출력이 모두 가능한 반복자
 * 증가 연산자 ++를 사용하면 순방향으로, 감소 연산자 --를 사용하면 역방향으로 이동가능
 * 참조 연산자(*)를 사용하여 몇 번이고 반복해서 같은 요소를 참조하거나, 그 값을 변경할 수 있다.
 *
 *
 */
namespace ft
{
	template <typename T, typename Pointer = T*, typename Reference = T&>
	class RBTreeIterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		public :
			typedef const T		value_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
			typedef ft::RBTreeNode<T> node_type;
		protected :
			node_type* _node;

		public:
			/**
			 * @brief Construct a new RBTreeIterator object
			 */
			//Default constructor
			RBTreeIterator(node_type* ptr = NULL) : _node(ptr) {}
			//Copy constructor
			RBTreeIterator(const RBTreeIterator<T>& copy) : _node(copy.base()) {}
			//Assignment operator
			RBTreeIterator& operator=(const RBTreeIterator& copy)
			{
				if (this != &copy)
					this->_node = copy.base();
				return (*this);
			}
			//Destructor
			virtual ~RBTreeIterator() {}
			//Getter
			node_type* const &base() const
			{
				return (this->_node);
			}

			/**
			 * @brief Operators
			 */
			reference operator*() const
			{
				return (*this->_node->value);
			}
			pointer operator->() const
			{
				return (this->_node->value);
			}

			RBTreeIterator& operator++()
			{
				node_type* tmp = NULL;
				if (_node->rightChild->value != NULL)
				{	// if rightChild exists,
					tmp = _node->rightChild;
					// search the leftmost of the rightChild.
					while (tmp->leftChild->value != NULL)
						tmp = tmp->leftChild;
				}
				else
				{	// if rightChild doesn't exist,
					tmp = _node->parent;
					if (tmp->rightChild == _node)
					{	// if current node is rightChild,
						while (tmp->parent->rightChild == tmp)
							tmp = tmp->parent;
						tmp = tmp->parent;
					}
				}
				_node = tmp;
				return (*this);
			}

			RBTreeIterator operator++(int)
			{
				RBTreeIterator tmp = *this;
				++(*this);
				return (tmp);
			}

			RBTreeIterator& operator--()
			{
				node_type* tmp = NULL;
				if (_node->value == NULL)
					tmp = _node->parent;
				else if (_node->leftChild->value != NULL)
				{	// if leftChild exists,
					tmp = _node->leftChild;
					// search the rightmost of the leftChild.
					while (tmp->rightChild->value != NULL)
						tmp = tmp->rightChild;
				}
				else
				{	// if leftChild doesn't exist,
					tmp = _node->parent;
					if (tmp->leftChild == _node)
					{	// if current node is leftChild,
						while (tmp->parent->leftChild == tmp)
							tmp = tmp->parent;
						tmp = tmp->parent;
					}
				}
				_node = tmp;
				return (*this);
			}

			RBTreeIterator operator--(int)
			{
				RBTreeIterator tmp = *this;
				--(*this);
				return (tmp);
			}

			/**
			 * @brief Relational operators
			 */
			bool operator==(const RBTreeIterator& iter)
			{
				return (_node == iter.base());
			}

			bool operator!=(const RBTreeIterator& iter)
			{
				return (_node != iter.base());
			}


	};
} // namespace ft

#endif
