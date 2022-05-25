#ifndef MAP_HPP
# define MAP_HPP

#include "RBTree.hpp"

namespace ft
{
	/**
	 * @brief map class
	 *
	 * set은 연관 컨테이너 중 하나
	 * 노드 기반 컨테이너이며, bat로 구현되어 있다.
	 * key라고 불리는 원소들의 집합으로 이루어져 있다.
	 * key값은 중복이 불가능하다.
	 * 원소가 insert 멤버함수에 의해 삽입되면, 자동으로 정렬된다.
	 * default 정렬구조는 (less)오름차순이다.
	 *
	 * map과 거의 동일하지만, map은 pair를 통해 key와 value를 쌍으로 요소를 저장했지만, set의 경우 key가 곧 value 그 자체이다.
	 *
	 * @tparam Key	Type of the keys.(key_type)
	 * @tparam T	Type of the mapped value.(mapped_type) -> set에서는 사용하지 않는다.
	 * @tparam Compare	A binary predicate that takes two element keys as arguments and returns a bool.(key_compare)
	 * @tparam Alloc	Type of the allocator object used to define the storage allocation model.(allocator_type)
	 */
	template < class Key, class Compare = ft::less<Key>, class Alloc = std::allocator<Key> >
	class set {
		public :
			/**
			 * @brief Member types
			 */
			typedef Key	key_type;
			typedef Key	value_type;
			typedef Compare	key_compare;
			/**
			 * @brief value_compare
			 *
			 * 연산자< 와 동일하게 반환되는 더 작은 객체.
			 * 컨테이너 요소들과 같은 유형의 두 개의 인수를 취하는 함수 포인터, 또는 함수 객체이며
			 * 첫 번째 요소가 두 번째 요소보다 작으면 true, 그렇지 않으면 false를 반환한다.
			 * value_compare가 false를 반환하는 경우 동등한 것으로 간주된다.
			 *
			 * set container에서 요소를 정렬하는 key는 곧 value와 같으므로,
			 * value_comp와 형제 멤버함수 key_compare는 동일하다.
			 */
			typedef Compare	value_compare;
			typedef Alloc	allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename ft::RBTreeIterator<value_type, value_type*, value_type&>	iterator;
			typedef typename ft::RBTreeIterator<value_type, const value_type*, const value_type&>	const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef typename allocator_type::difference_type	difference_type;
			typedef typename allocator_type::size_type			size_type;
			typedef ft::RBTree<value_type, value_compare>		rb_tree;
			typedef ft::RBTreeNode<value_type>					node_type;

		/**
		 * @brief Member variables
		 */
		private:
			allocator_type	_alloc;
			rb_tree			_tree;
			key_compare		_comp;

		public:
			/**
			 * @brief Member functions
			 */
			//Empty constructor
			explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _tree(), _comp(comp) {}

			//Range constructor
			//[first,last) 범위와 동일한 수의 요소로 컨테이너를 구성하고 각 요소는 해당 범위의 해당 요소로 구성한다
			template <class InputIterator>
			set (InputIterator first, InputIterator last,
					const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) : _alloc(alloc), _tree(), _comp(comp)
			{
				insert(first, last);
			}

			//Copy constructor
			//x에 있는 각 요소의 복사본을 사용하여 컨테이너를 구성한다
			set (const set& x) : _alloc(x._alloc), _tree(), _comp(x._comp)
			{
				*this = x;
			}

			//Destructor
			~set() {}

			//Assignment operator
			set& operator=(const set& x)
			{
				if (this != &x)
					this->_tree.copy(x._tree);
				return *this;
			}

			// Iterators:
			iterator begin()
			{
				return iterator(this->_tree.get_begin());
			}
			const_iterator begin() const
			{
				return const_iterator(this->_tree.get_begin());
			}

			iterator end()
			{
				return iterator(this->_tree.get_end());
			}
			const_iterator end() const
			{
				return const_iterator(this->_tree.get_end());
			}

			reverse_iterator rbegin()
			{
				return reverse_iterator(this->_tree.get_end());
			}
			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(this->_tree.get_end());
			}

			reverse_iterator rend()
			{
				return reverse_iterator(this->_tree.get_begin());
			}
			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(this->_tree.get_begin());
			}

			//Capacity
			bool empty() const
			{
				return (this->_tree.empty());
			}
			size_type size() const
			{
				return (this->_tree.size());
			}
			size_type max_size() const
			{
				return (this->_tree.max_size());
			}

			/**
			 * @brief Element access
			 *
			 * operator[]
			 * k가 컨테이너에 있는 요소의 키와 일치하면 매핑된 값에 대한 참조를 반환하는 함수
			 * k가 컨테이너에 있는 요소의 키와 일치하지 않으면 함수는 해당 키를 사용하여 새 요소를 삽입하고 매핑된 값에 대한 참조를 반환한다.
			 * 이렇게 하면 요소에 매핑되니 값이 할당되지 않더라도(기본 생성자를 사용하여 생성됨) 항상 컨테이너 크기가 1씩 증가한다.
			 * at과 비슷한 역할을 하지만 map::at은 키가 있는 요소가 존재할 때 같은 동작을 하지만 그렇지 않으면 에러를 발생시킨다. -> c++11에서 사용
			 *
			 * ->이렇게 map에서는 k가 컨테이너에 저장되어있는 요소를 찾아서 매핑된 값에 대한 참조를 반환한다.
			 * ->하지만 set에서는 key == value이므로 key값을 찾으면 곧 value값이기 때문에
			 * ->해당 연산자가 필요없으며, 지원하지 않는다.
			 */
			// mapped_type& operator[](const key_type& k)
			// {
			// 	return (*(_tree.insert(ft::make_pair(k, mapped_type())).first)).value->second;
			// }

			/**
			 * @brief Modifiers
			 *
			 * insert
			 * 새로운 요소를 삽입하여 컨테이너를 확장하며 삽입된 요소의 수만큼 컨테이너의 크기를 효과적으로 증가시킨다.
			 * 맵의 요소 키가 고유하기 때문에 삽입 작업은 삽인된 각 요소가 컨테이너에 존재하는 요소와 동일한 키를 가지고 있는지 확인하고, 삽입되지 않은 경우 반복자를 통해 기존 요소로 반환한다. ->중복 요소 허용은 multi-map
			 * 맵에 요소를 삽입하는 다른 방법으로 member function인 map::operater[]를 사용할 수 있다.
			 * 내부적으로 맵 컨테이너는 비교 객체에 의해 지정된 기준에 따라 키별로 정렬된 모든 요소를 유지한다. -> 지정된 기준은 RB Tree
			 * 정렬된 후 해당 위치에 삽입된다. -> RB Tree의 삽입 방법/법칙에 따라 정렬된 후 삽입된다.
			 * 매개변수는 삽입되는 요소의 수와 초기화될 값을 결정한다.
			 *
			 * erase
			 * 단일 요소 또는 [first,last) 범위의 요소를 맵에서 제거
			 * 제거된 요소 수만큼 컨테이너 크기를 효과적으로 줄일 수 있다.
			 *
			 * swap
			 *
			 * clear
			 *
			 */
			/**
			 * @brief insert
			 * 1. single element
			 * member pair를 가진 쌍을 반환하며, 해당 멤버 pair는 새로 삽인된 요소를 가리키는 반복자 또는 맵에서 동등한 키를 가진 요소를 가리킨다. -> 요소를 가리키는 iterator 반환
			 * pair::second 요소는 새 요소가 삽인된 경우 true로 설정되고 동등한 키가 이미 존재하는 경우 false로 설정된다.
			 * insert함수를 보면 get_position 또는 다른 상태를 확인하여, make_pair를 반환한다.
			 *
			 * 2. with hint
			 * 새로 삽인된 요소 또는 맵에 이미 동등한 키가 잇는 요소를 가리키는 반복자를 반환한다.
			 *
			 * 3. range
			 * member type iterator는 요소를 가리키는 양방향 반복자 유형
			 *
			 */

			//1. single element
			//insert 성공 - pair(새로운 element를 가리키는 iterator, true) 반환.
			//insert 실패 - pair(val과 동일한 Key값 갖고있는 iterator, false) 반환.
			pair<iterator, bool> insert(const value_type& val)
			{
				ft::pair<node_type*, bool> res = _tree.insert(val);
				return (ft::make_pair(iterator(res.first), res.second));
			}

			//2. with hint
			//position은 hint, 강제가 아니다.
			//insert 성공 - 새로운 element를 가리키는 iterator 반환.
			//insert 실패 - val과 동일한 Key값 갖고있는 iterator 반환.
			iterator insert(iterator position, const value_type& val)
			{
				return (iterator(this->_tree.insert(val, position.base()).first));
			}

			//3. range
			//[first, last) 구간의 element를 insert.
			//이때, 기존 Key값과 중복되는 element는 추가하지 않는다.
			//중복되지 않는 element만 추가한다.
			template <class InputIterator>
			void insert(InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			{
				while (first != last)
					this->_tree.insert(*first++);
			}

			/**
			 * @brief erase
			 *
			 * @param position
			 */
			void erase(iterator position)
			{
				this->_tree.erase(position.base());
			}

			//지워진 요소의 수를 반환
			//erase 성공 시 1, 실패 시 0 리턴.
			//tree에 없는 key_type k가 들어온 경우 find에서 nil노드를 리턴한다.
			//nil노드 erase실행 시 실패.
			size_type erase(const key_type& k)
			{
				return (this->_tree.erase(_tree.find(value_type(k))));
			}

			void erase(iterator first, iterator last)
			{
				while (first != last)
					erase(first++);
			}

			/**
			 * @brief swap
			 *
			 * 같은 유형의 다른 맵인 x의 요소로 기존 맵 요소를 교환한다. 이 때, 사이즈가 다를 수 있다.
			 * 동일한 이름의 swap을 가진 non-member function이 존재하며, 이 멤버 함수와 같이 동작하는 최적화로 알고리즘을 오버로드한다.
			 */
			void swap(set& x)
			{
				this->_tree.swap(x._tree);
			}

			/**
			 * @brief clear
			 *
			 * 모든 요소를 맵에서 제거한다. 컨테이너의 크기는 0이다.
			 */
			void clear()
			{
				this->_tree.clear();
			}

			//Observers
			/**
			 * @brief key_comp == value_comp
			 *
			 * 컨테이너가 키를 비교하는데 사용하며 비교 객체의 복사본을 반환한다
			 *
			 * 연산자< 와 동일하게 반환되는 더 작은 객체.
			 * 컨테이너 요소들과 같은 유형의 두 개의 인수를 취하는 함수 포인터, 또는 함수 객체이며
			 * 첫 번째 요소가 두 번째 요소보다 작으면 true, 그렇지 않으면 false를 반환한다.
			 * value_compare가 false를 반환하는 경우 동등한 것으로 간주된다.
			 * key_comp가 키가 인수로 전달되는 순서에 관계없이 false를 반환하다면, 두 키는 동등한 것으로 간주한다.
			 */
			key_compare key_comp() const
			{
				return (key_compare());
			}

			value_compare value_comp() const
			{
				return (value_compare());
			}

			//Operations
			/**
			 * @brief find
			 *
			 * 컨테이너에서 k에 해당하는 키를 사용하여 요소를 검색하고 발견된 경우 반복자를 반환,
			 * 발견되지 않은 경우 반복자를 map::end로 반환
			 *
			 * 컨테이너의 비교객체가 반사적으로 false를 반환하는 경우(요소가 인자로 전달되는 순서와 관계없이) 두 키는 동일한 것으로 간주
			 *
			 * map::count를 사용하여 특정키가 존재하는지 확인할 수 있다.
			 * @param k
			 * @return iterator
			 */
			iterator find(const key_type& k)
			{
				return (iterator(this->_tree.find(value_type(k))));
			}

			const_iterator find(const key_type& k) const
			{
				return (const_iterator(this->_tree.find(value_type(k))));
			}

			/**
			 * @brief count
			 *
			 * 컨테이너에서 k에 해당하는 키를 사용하여 요소를 검색하고 일치 항목 수를 반환한다.
			 *
			 * 맵 컨테이너의 모든 요소가 고유하기 때문에 함수는 1(요소가 발견된 경우) 또는 0(요소가 발견되지 않은 경우)만 반환 가능
			 *
			 * 컨테이너의 비교객체가 반사적으로 false를 반환하는 경우(요소가 인자로 전달되는 순서와 관계없이) 두 키는 동일한 것으로 간주
			 *
			 * @param k
			 * @return size_type
			 */
			size_type count(const key_type& k) const
			{
				if (this->_tree.find(value_type(k))->value != NULL)
					return (1);
				else
					return (0);
			}

			/**
			 * @brief lower_bound & upper_bound
			 *
			 * lower_bound함수의 경우 컨테이너의 오른쪽 원소 중 기준 원소와 같거나 큰 값 중 가장 왼쪽에 있는 원소의 iterator값을 반환한다.
			 * upper_bound함수의 경우 컨테이너의 오른쪽 원소 중 기준 원소보다 큰 값중 가장 왼쪽에 있는 원소의 iterator값을 반환한다.
			 * 차이점은 같은 값을 포함하느냐 마느냐의 차이만 있다.
			 */
			/**
			 * @brief lower_bound
			 *
			 * 키가 k보다 이전인 것으로 간주되지않는 컨테이너의 첫 번째 요소를 가리키는 반복자를 반환한다.
			 *
			 * 함수는 내부 비교 객체(key_comp)를 사용하여 이를 결정하며,
			 * 반복자를 key_comp(element_key, k)가 false를 반환하는 첫 번째 요소를 반환한다.
			 *
			 * 맵 클래스가 기본 비교 타입(less)로 인스턴스화된 경우 함수는 k이상의 키를 가진 첫 번째 요소로 반복자를 반환한다.
			 *
			 * lower_bound와 upper_bound는 같은 동작을 하지만, 맵에 val와 같은 키를 가진 요소가 포함되어 있는 경우를 제외하고
			 * lower_bound는 그 요소를 가리키는 반복자를 반환
			 * upper_bound는 다음 요소를 가리키는 반복자를 반환
			 * @param k
			 * @return iterator
			 */
			iterator lower_bound(const key_type& k)
			{
				return (iterator(this->_tree.lower_bound(value_type(k))));
			}

			const_iterator lower_bound(const key_type& k) const
			{
				return (const_iterator(this->_tree.lower_bound(value_type(k))));
			}

			/**
			 * @brief upper_bound
			 *
			 * 키가 k 다음에 오는 것으로 간주되는 컨테이너의 첫 번째 요소를 가리키는 반복자를 반환한다.
			 *
			 * 함수는 내부 비교 객체(key_comp)를 사용하여 이를 결정하며,
			 * 반복자를 key_comp(element_key, k)가 true를 반환하는 첫 번째 요소를 반환한다.
			 *
			 * 맵 클래스가 기본 비교 타입(less)로 인스턴스화된 경우 함수는 k보다 큰 첫 번째 요소로 반복자를 반환한다.
			 *
			 * lower_bound와 upper_bound는 같은 동작을 하지만, 맵에 val와 같은 키를 가진 요소가 포함되어 있는 경우를 제외하고
			 * lower_bound는 그 요소를 가리키는 반복자를 반환
			 * upper_bound는 다음 요소를 가리키는 반복자를 반환
			 *
			 * @param k
			 * @return iterator
			 */
			iterator upper_bound(const key_type& k)
			{
				return (iterator(this->_tree.upper_bound(value_type(k))));
			}
			const_iterator upper_bound(const key_type& k) const
			{
				return (const_iterator(this->_tree.upper_bound(value_type(k))));
			}

			/**
			 * @brief equal_range
			 *
			 * k와 동등한 키를 가진 컨테이너의 모든 요소를 포함하는 범위의 경계를 반환한다.
			 * 맵 컨테이너의 요소에는 고유한 키가 있으므로 반환되는 범위에는 최대 단일 요소가 포함된다.
			 * 일치하는 요소가 없으면 반환되는 범위는 0이며,
			 * 두 반복자는 컨테이너의 내부 비교 객체(key_comp)에 따라 k 이후인 것으로 간되는 키를 가진 첫 번째 요소를 가리킨다.
			 *
			 * 컨테이너의 비교객체가 반사적으로 false를 반환하는 경우(요소가 인자로 전달되는 순서와 관계없이) 두 키는 동일한 것으로 간주
			 *
			 * @param k
			 * @return pair<iterator, iterator>
			 */
			pair<iterator, iterator> equal_range(const key_type& k)
			{
				return (ft::make_pair(lower_bound(k), upper_bound(k)));
			}
			// pair<const_iterator, const_iterator> equal_range(const key_type& k) const
			// {
			// 	return (ft::make_pair(lower_bound(k), upper_bound(k)));
			// }

			/**
			 * @brief Allocator
			 *
			 * 맵과 연결된 allocator object의 복사본을 반환한다.
			 * @return Allocator
			 */
			allocator_type get_allocator() const
			{
				return (this->_alloc);
			}

			void showTree()
			{
				this->_tree.showMap();
			}


	};

	/**
	 * @brief Relational operators
	 */
	template <class Key, class Compare, class Alloc>
	bool operator==(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class Key, class Compare, class Alloc>
	bool operator!=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class Key, class Compare, class Alloc>
	bool operator<(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class Compare, class Alloc>
	bool operator<=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <class Key, class Compare, class Alloc>
	bool operator>(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class Key, class Compare, class Alloc>
	bool operator>=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

	// swap
	template <class Key, class Compare, class Alloc>
	void swap(set<Key, Compare, Alloc>& x, set<Key, Compare, Alloc>& y)
	{
		x.swap(y);
	}
} // namespace ft

#endif
