#ifndef VECTOR_HPP
# define VECTOR_HPP

// #include <vector>
#include <memory>
#include <stdexcept>
#include "VectorIterator.hpp"
#include "utils.hpp"

/**
 * @brief vector
 *
 * Sequence : 모든 값들이 선형으로 정렬되고, 개별노드는 이 순서에 의해 접근 가능
 * Dynamic array : 모든 요소에 직접적인 접근([]연산을 통해)이 가능하다. 배열의 마지막 요소를 비교적 빠르게 추가 및 제거할 수 있다.
 * Allocator : allocater 객체를 이용해 동적할당을 한다.
 *
 * 벡터는 크기가 변경될 수 있는 배열을 나타내는 시퀀스 컨테이너입니다.
 * 벡터는 배열과 마찬가지로 요소에 대한 연속적인 저장 위치를 사용하는데, 이는 벡터가 배열과 마찬가지로 효율적으로 요소에 대한 일반 포인터의 오프셋을 사용하여 요소에 액세스할 수 있다는 것을 의미한다. 그러나 어레이와 달리 스토리지 크기는 컨테이너에서 자동으로 처리되므로 동적으로 변경될 수 있습니다.
 * 내부적으로 벡터는 동적으로 할당된 배열을 사용하여 요소를 저장합니다. 새 요소를 삽입할 때 크기를 늘리기 위해 이 어레이를 다시 할당해야 할 수 있습니다. 즉, 새 어레이를 할당하고 모든 요소를 이 어레이로 이동해야 합니다. 이것은 처리 시간 측면에서 상대적으로 비용이 많이 드는 작업이며, 따라서 벡터는 컨테이너에 요소를 추가할 때마다 재할당하지 않는다.
 * 대신 벡터 컨테이너는 가능한 성장을 수용하기 위해 일부 추가 스토리지를 할당할 수 있으며, 따라서 컨테이너는 요소(즉, 크기)를 포함하는 데 엄격하게 필요한 스토리지보다 더 큰 실제 용량을 가질 수 있습니다. 라이브러리는 메모리 사용과 재할당 사이의 균형을 맞추기 위해 성장을 위한 다른 전략을 구현할 수 있지만, 어떤 경우에도 재할당은 벡터 끝에 있는 개별 요소의 삽입이 상각된 일정한 시간 복잡성과 함께 제공될 수 있도록 로그적으로 증가하는 크기의 간격에서만 일어나야 한다.
 * 따라서 어레이에 비해 벡터는 스토리지를 관리하고 효율적인 방식으로 동적으로 확장할 수 있는 기능을 제공하는 대신 더 많은 메모리를 소비합니다.
 * 다른 동적 시퀀스 컨테이너(데크, 목록, forward_lists)에 비해 벡터는 배열과 마찬가지로 요소에 접근하는 것이 매우 효율적이며, 엔드에서 요소를 추가하거나 제거하는 것이 상대적으로 효율적이다. 엔드가 아닌 위치에 요소를 삽입하거나 제거하는 작업의 경우 다른 작업보다 성능이 떨어지며 lists와 forward_lists보다 일관성 있는 반복자와 참조가 덜하다.
 *
 * 요소들은 연속적으로 저장되는데, 이는 요소들은 반복자를 통해서뿐만 아니라 요소에 대한 일반적인 포인터들에 대한 오프셋을 통해서도 접근할 수 있다는 것을 의미한다. 이것은 벡터의 요소에 대한 포인터가 배열의 요소에 대한 포인터를 기대하는 함수에 전달될 수 있다는 것을 의미한다.
 * 벡터의 저장소는 자동으로 처리되며 필요에 따라 확장 및 축소됩니다. 벡터는 일반적으로 정적 배열보다 더 많은 공간을 차지하는데, 이는 미래의 성장을 처리하기 위해 더 많은 메모리가 할당되기 때문이다. 이러한 방식으로 벡터는 요소를 삽입할 때마다 재할당할 필요가 없으며, 추가 메모리가 소진될 때만 재할당한다. 할당된 메모리의 총량은 capacity() 함수를 사용하여 쿼리할 수 있습니다. 추가 메모리는 shrink_to_fit()을 호출하여 시스템에 반환할 수 있습니다.
 * 재할당은 일반적으로 성능 측면에서 비용이 많이 드는 작업입니다. 예비() 함수는 요소의 수를 미리 알고 있는 경우 재할당을 제거하는 데 사용할 수 있습니다.
 *
 * 벡터는 컨테이너가 자라는 것을 핸들하기 위해 더 많은 메모리를 할당하기 때문에 일반적으로 정적 배열(static memory)에 비해 더 많은 공간을 차지합니다. 이 방법은 요소(element)가 삽입될 때마다 메모리를 벡터를 다시 할당할 필요가 없게 만들며, 오직 메모리가 모두 소진되었을 때만 추가적인 메모리를 위해 재할당됩니다.
 *
 * vector를 구현하기 위해서는 iterator가 필요하다. 반복자를 통해서 요소를 삽입,추적,삭제 등을 하기때문이다.
 *
 * 그렇다면 array를 사용하지않고 vector를 쓰는 이유는 무엇인가?
 * array는 컴파일 시 크기가 결정된다 -> 즉 크기를 미리 설정하고 선언해야한다.
 * 크기가 고정되어있으므로 원소의 데이터는 바꿀 수 있어도 원소를 추가하거나 삭제하는 일은 불가능하다.
 * 메모리적은 측면에서 컴파일 할때 크기가 결정되므로 무조건 스택 메모리를 사용한다.
 * 데이터를 동적으로 사용하고 유동적으로 크기를 조절하며, 원소를 추가 및 삭제하기 위해 가변 크기의 데이터 컨테이너가 필요 -> 이 때, 사용하는 것이 vector
 *
 * 데이터를 추가하거나 삭제할 수 있지만 vector 역시 array이 처럼 연속된 메모리 영역을 사용하기 때문에 주소 시작점부터 데이터를 쌓아나가기 때문에
 * 자연스레 벡터 시작 또는 중간에 데이터를 삽입하거나 삭제하는 과정은 비효율적일 수 있다.
 * 하지만 마지막 위치에 데이터를 추가/삭제하는 것은 간단하며, index를 통해 데이터에 바로 접근이 가능하다.
 * 데이터의 위치만 알고 있다면 빠르게 데이터를 찾을 수 있다.
 * 하지만 데이터의 위치를 모르는 경우 선형 탐색을 통해 데이터를 찾아야하며, 시간복잡도는 O(N)이다.
 *
 * Allocator
 *
 * Allocator는 std::allocator<T> class를 사용한다. need #include <memory> header
 * 유연한 메모리 관리를 위한 클래스로 할당자라고도 한다.
 * 일반적으로 c++에서 메모리를 동적으로 할당하고 해제할 떄 new/delete 연산자를 사용하는데 allocator는 언제 사용하는가?
 * allocator는 주로 라이브러리를 작성할 때, 특히 표준 라이브러리의 컨테이너를 구현할 때 많이 사용된다. 여기서 표준 라이브러리 컨테이는 현재 구현하고자 하는 vector, map 등을 의미
 * 할당자는 fine-grained 방식, 메모리 관리를 더욱 세밀하게 컨트롤하고 유연하고 효율적으로 사용해야할 경우 유저가 원하는 메모리 할당 방식으로 구현할 수 있다.
 * allocator 클래스를 상속받아 멤버함수를 override해서 커스텀할 수 있다.
 *
 * 그렇다면 왜 new/delete를 사용하지 않고 allocator를 사용하라고 하는가?
 * 컨테이너는 메모리를 최대한 효율적으로 관리할 수 있어야하는데 new/delete 연산자로는 세밀한 메모리 관리 능력이 떨어진다.
 * 컨테이너는 주로 데이터를 저장하고 관리하는 공간이므로 저장공간의 생성,확장,추가,삭제 등이 빈번하게 발생하므로 new/delete연산자를 사용할 경우 다음과 같은 문제가 발생한다.
 *
 * new 연산자를 사용하면 따라오는 조건 3가지(if class type)
 * 1. 기본 생성자 필요
 * 2. 메모리 할당
 * 3. 모든 요소 초기화
 * 위의 3가지 조건이 필요하게 되는데 이는 요소가 많아질수록 컴퓨터 자원의 사용량이 상당량 증가하게된다.
 * 또한 new연산자는 라이브러리 개발자가 원하는 메모리 할당 방식으로 커스텀마이징 할 수 없다.
 * allocator 클래스를 사용하면 위 단계들을 각각 원할 때 마다 사용할 수 있다.
 * 대표적인 컨테이너, 해당 파일에서 구현하고자 하는 vector를 보면 std::allocator<T>가 기본 타입 매개변수로 사용된다.
 * 특정 컨테이너에 최적화된 유연한 메모리 사용과 관리를 위해 대부분의 컨테이너들은 allocator를 사용한다.
 *
 * allocator의 장점
 * 우선 메모리를 동적할당할 경우 초기화되지 않은 공간(uninitialized)으로 메모리를 할당할 수 있다.
 * new 연산자의 경우 메모리를 할당하고 기본적으로 값 또는 객체를 의무적으로 초기화가 필요하다. 이는 요소가 많을수록 오버헤드가 높이지고 초기화를 원치않은 경우에도 불필요한 오버헤드가 발생하게된다.
 * 예시)
 *  class 타입 요소를 갖는 크기가 10인 벡터를 선언
 *  내부적으로 벡터가 new연산자를 통해 생성된다면 벡터는 할당과 동시에 모든 요ㅛ소들이 해당 클래스 타입에 맞게 기본 생성자를 통해 초기화가 되어 있을 것이고, 사용자가 이 벡테에 원하는 요소를 저장한다.
 *  이는 각 요소들을 두 번씩 초기화 하는 것과 같다. 불필요한 초기화가 선택이 아닌 필수적이라는 의미이다.
 * allocator의 멤버함수를 이용하면 메모리 할당은 되었지만 초기화되지 않은 상태의 메모리의 시작 주소를 얻을 수 있다.
 * 초기화되지 않은 메모리 공간에 객체를 직접 할당할 수 없지만 해당 클래스의 멤버함수 또는 관련함수가 초기화되지 않은 공간에 객체를 저장할 수 있도록 해준다.
 * 할당받은 메모리에 객체를 생성후 메모리 해제없이 생성한 객체를 소멸시킬 수 있다. 메모리의 재할당없이 공간을 allocate했던 초기 상태로 만들 수 있다.
 * new 연산자로 할당한 메모리 공간은 delete를 사용하면 메모리 공간이 해제된다. 이러한 과정을 세밀하게 나누어 컨트롤할 수 있다.
 * 또한 할당받은 메모리 공간 중 객체가 생성된 공간과 초기화되지 않은 공간을 알 수 있는 방법을 제공한다.
 * allocate class는 4개의 멤버함수와 용도에 따라 사용할 수 있는 함수2개를 제공한다.
 *
 * allocate : 초기화되지않은 메모리공간을 할당하여 그 시작 주소를 반환하는 함수
 * 매개변수는 byte단위가 아닌 필요한 T객체의 개수(n)이며, 인자로 전달된 개수만큼 타입의 개체를 충분히 할당할 수 있는 공간을 생성
 * 충분히라는 의미 - 1bytes, 4bytes, 8bytes 또는 그 이상이든 할당된 크기의 + 4bytes만큼 공간을 할당해준다고 한다.
 * 예시)
 *  8bytes 타입의 객체를 5개 저장할 공간을 만들기위해 인자로 5를 전달 -> 8bytes * 5 + 4bytes = 44bytes가 할당되고 그 시작주소를 반환한다.
 *
 * deallocate : 메모리 공간을 해제하는 함수
 * 인자로 포인터와 개수 - 포인터는 allocate로 할당했던 메모리의 시작 주소를 가리키는 포인터이며, allocate로 전달했던 인자의 개수
 * cpp 레퍼런스에서 반드시 allocate로 전달했던 인자의 개수와 동일해야한다고 한다.
 *
 * construct : 초기화되지 않은 공간에 요소를 저장하는 함수
 * T타입 포인터와 객체를 레퍼런스로 받으며 포인터가 가리키는 위치에 객체를 저장한다.
 * 초기화되지 않은 공간에 *(간접참조) 연산자를 사용하여 값을 대입할 경우 에러가 발생하므로 construct 함수를 통해 에러없이 저장할 수 있다.
 *
 * destroy : 객체를 소멸시키는 함수
 * 소멸과 메모리해제는 다르다.
 * T타입 포인터를 인자로 받으며 포인터가 가리키는 위치의 객체의 소멸자를 호출한다. 즉, 인자로 전달된 포인터가 가리키는 객체의 소멸자를 호출하는 것
 * destroy를 호출하지 않고 deallocate를 호출할 경우 각 요소에 저장된 객체는 사라지겠지만 사라진 객체가 가리키던 객체는 그대로 메모리에 남아있기 때문에 메모리 누수가 발생할 수 있다.
 *
 * allocate는 템플릿으로 만들어야 하며, 템플릿 매개변수에는 할당하고자 하는 객체의 타입 T를 사용한다.
 * pointer(T*)와 reference(T&)라는 typedef를 제공해야한다.
 * 표준 컨테이너에서 필요로 하는 rebind라는 중첩 구조체 템플릿을 반드시 제공해야한다.
 *
 * rebind는 어떤 종류의 객체를 얻기 위해 사용된다.
 * Its member type other is the equivalent allocator type to allocate elements of type Type
 * 해당 멤버 유형 other는 Type의 요소를 할당하는 등가 할당자 유형입니다.
 * Class whose member other is a typedef of allocator for type Type.
 * 멤버 other가 Type에 대한 할당자의 typedef인 클래스입니다.
 * 할당자 클래스에서 파생 하는 경우 해당 typedef가 새로 파생 된 클래스를 참조 하는 리바인딩 구조체를 제공 해야 합니다.
 * 한 형식의 개체에 할당자를 사용하여 다른 형식의 개체에 저장소를 할당할 수 있는 구조체
 * struct rebind { typedef allocator<_Other> other; };
 * other : 메모리를 할당 중인 요소의 형식
 * 구현 중인 컨테이너의 요소형식과는 다른 형식의 메모리를 할당하는데 유용하다.
 * typedef typename Alloc::template rebind< node_type >::other node_alloc_type;
 */
namespace ft
{
	template < typename T, typename Allocator = std::allocator<T> >
	class vector
	{
		public:
			/**
			 * @brief vector member types
			 *
			 * value_type : 컨테이너에 담을 변수 타입 저장
			 * allocator_type : allocator의 타입과 reference, pointer
			 * size_type : Unsigned integer type
			 * difference_type : Signed integer type, 노드 간 거리 연산을 위한 타입
			 * iterator
			 * const_iterator : 참조된 값을 바꿀 수 없다.
			 * reverse_iterator : 제일 마지막 요소가 begin이 되고, ++연산을 하면 역순으로 연산이 이뤄진다.
			 */
			typedef T value_type;
			typedef Allocator allocator_type;
			typedef typename allocator_type::reference			  reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			    pointer;
			typedef typename allocator_type::const_pointer	  const_pointer;
			typedef ft::VectorIterator<T>						iterator;
			typedef ft::VectorIterator<const T> 				const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef typename allocator_type::size_type			size_type;
			typedef typename allocator_type::difference_type	difference_type;

		/**
		 * @brief value
		 *
		 * start : 벡터 배열
		 * end : 백터의 현재 위치
		 * end_of_capacity : 벡터 저장공간의 마지막 위치
		 */
		private:
			allocator_type	_alloc;
			pointer			_start;
			pointer			_end;
			pointer			_end_of_capacity;

		public:

		/**
		 * @brief vector member function
		 *
		 * default construct : 요소가 없는 빈 컨테이너
		 * fill construct : n개의 요소로 구성된 컨테이너. 각 요소는 val의 복사본이다.
		 * range construct : range[first, last)와 같은 수의 요소로 구성된 컨테이너. 각 요소는 해당 범위의 해당 요소의 순서로 구성된다.
		 * copy construct : x에 있는 각 요소의 복사본을 같은 순서로 구성한 컨테이너
		 * 각 요소에 대한 저장 공간은 allocator를 사용해 할당된다.
		 * destruct
		 */
		//default constructor
		explicit vector(const allocator_type &alloc = allocator_type())
		: _alloc(alloc), _start(NULL), _end(NULL), _end_of_capacity(NULL){}

		//fill constructor
		explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
		: _alloc(alloc), _start(NULL), _end(NULL), _end_of_capacity(NULL)
		{
			this->_start = this->_alloc.allocate(n);
			this->_end = this->_start;
			this->_end_of_capacity = this->_start + n;
			while (n--)
				this->_alloc.construct(this->_end++, val); //각 요소는 val의 복사본
		}

		//range constructor
		template <typename InputIterator>
		vector(InputIterator first, InputIterator last,
				const allocator_type &alloc = allocator_type(),
				typename ft::enable_if< !ft::is_integral< InputIterator >::value, InputIterator >::type* = NULL)
		: _alloc(alloc), _start(NULL), _end(NULL), _end_of_capacity(NULL)
		{
			//type
			difference_type n = ft::distance(first, last);
			// while (first++ != last)
			//   n++;
			this->_start = this->_alloc.allocate(n);
			this->_end = this->_start;
			this->_end_of_capacity = this->_start + n;
			while (n--)
				this->_alloc.construct(this->_end++, *first++);
		}

		//copy constructor
		vector(const vector &x)
		: _alloc(x._alloc), _start(NULL), _end(NULL), _end_of_capacity(NULL)
		{
			difference_type n = x._end - x._start;
			this->_start = this->_alloc.allocate(n);
			this->_end = this->_start;
			pointer tmp = x._start;
			while (n--)
				_alloc.construct(_end++, *tmp++);
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
		 * begin : 벡터의 첫 번째 요소에 대한 반복자 반환
		 * end : 벡터의 끝(마지막 요소 다음)에 대한 반복자 반환
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
		//return size
		size_type size() const
		{
			return (this->_end - this->_start);
		}

		//사용가능한 메모리가 모두 사용되기 전에 allocator 클래스의 객체가 할당할 수 있는 type형식의 요소 수, allocator 함수
		//return max_size
		size_type max_size() const
		{
			return (this->_alloc.max_size());
		}

		//change size
		//n개의 val값들을 갖는 vector로 resize한다.
		//n이 현재 컨테이너 크기보다 작으면, 그 이상의 요소를 제거하고 크기를 축소시킨다.
		//n이 현재 컨테이너 크기보다 크면, n의 크기만큼 새로운 값을 삽입한다. value가 지정되면 새 요소가 value의 복사본으로 초기화되고, 그렇지 않으면 값이 초기화된다.
		void resize(size_type n, value_type val = value_type())
		{
			if (n < size())
				erase(_start + n, _end);
			else if (n > size())
				insert(_end, n - size(), val);
		}

		//Return size of allocated storage capacity
		//element의 갯수가 아닌, 할당받은 메모리의 갯수. (잠재적 크기)
		size_type capacity() const
		{
			return (this->_end_of_capacity - this->_start);
		}

		//Test whether vector is empty
		bool empty() const
		{
			return (this->_start == this->_end);
		}

		//Request a change in capacity
		//벡터의 용량(재할당 없이 벡터가 보유할 수 있는 총 요소 수)을 보다 크거나 같은 값으로 늘 new_cap립니다.
		//현재 capacity() new_cap 보다 크면 새 스토리지가 할당되고, 그렇지 않으면 함수가 아무 작업도 수행하지 않습니다.
		void reserve(size_type n)
		{
			if (n > max_size()) //최대 크기를 넘어가면 에러
				throw(std::length_error("Error: ft::vector::reserve"));
			else if (n > this->capacity())
			{
				pointer prev_start = this->_start;
				pointer prev_end = this->_end;
				pointer prev_end_of_capacity = this->_end_of_capacity;

				this->_start = this->_alloc.allocate(n);
				this->_end = this->_start;
				this->_end_of_capacity = this->_start + n;
				pointer tmp = prev_start;
				while (tmp != prev_end)
				{
					this->_alloc.construct(this->_end++, *tmp);
					this->_alloc.destroy(tmp++);
				}
				this->_alloc.deallocate(prev_start, prev_end_of_capacity - prev_start);
			}
		}

		/**
		 * @brief elememt access
		 */

		/**
		 * @brief operator[]
		 *
		 * 배열처럼 접근하여 인덱스에 대한 참조를 반환
		 */

		reference operator[](size_type n)
		{
			return (*(this->_start + n));
		}

		//const access element
		const_reference operator[](size_type n) const
		{
			return (*(this->_start + n));
		}

		/**
		 * @brief
		 * 벡터의 n위치에 있는 요소에 대한 참조를 반환합니다. n은 값이 아니라 위치!
		 * 이 함수는 n이 벡터에서 유효한 요소의 범위 내에 있는지 여부를 자동으로 검사하고 그렇지 않으면 out_of_range 예외를 던진다.
		 * 이는 out_of_range 대해 검사하지 않는 멤버 연산자[]와 대조된다.
		 *
		 * @param n
		 * @return reference
		 */
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
		//벡터에 새 내용을 할당하고 현재 내용을 교체하고 그에 따라 크기를 수정한다.
		template < typename InputIterator >
		void assign(InputIterator first, InputIterator last,
					typename ft::enable_if< !ft::is_integral< InputIterator >::value, InputIterator >::type * = NULL)
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
				pointer prev_start = this->_start;
				pointer prev_end_of_capacity = this->_end_of_capacity;

				this->_start = this->_alloc.allocate(n);
				this->_end = this->_start;
				this->_end_of_capacity = this->_start + n;
				const_pointer tmp = &(*first);
				while(tmp != &(*last))
					this->_alloc.construct(this->_end++, *tmp++);
				this->_alloc.deallocate(prev_start, prev_end_of_capacity - prev_start);
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
				pointer prev_start = this->_start;
				pointer prev_end_of_capacity = this->_end_of_capacity;

				this->_start = this->_alloc.allocate(n);
				this->_end = this->_start;
				this->_end_of_capacity = this->_start + n;
				while (n--)
					this->_alloc.construct(this->_end++, val);
				this->_alloc.deallocate(prev_start, prev_end_of_capacity - prev_start);
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

		//insert
		//1. single element
		//2. fill
		//3. range

		//1.single element insert
		iterator insert(iterator position, const value_type &val)
		{
			size_type n = &(*position) - this->_start;
			this->insert(position, 1, val);
			return (this->begin() + n);
		}

		//2.fill element insert
		void insert(iterator position, size_type n, const value_type &val)
		{
			if (this->size() + n <= this->capacity())
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
				size_type _size = n + this->size();
				size_type front_tmp = &(*position) - this->_start;
				size_type back_tmp = _end - &(*position);
				this->_start = _alloc.allocate(_size);
				this->_end = _start;
				this->_end_of_capacity = this->_start + _size;
				while (front_tmp--)
				{
					_alloc.construct(this->_end++, *tmp);
					_alloc.destroy(tmp++);
				}
				while (n--)
					_alloc.construct(this->_end++, val);
				while (back_tmp--)
				{
					_alloc.construct(this->_end++, *tmp);
					_alloc.destroy(tmp++);
				}
			}
		}

		//3.range element instert
		template < typename InputIterator >
		void insert(iterator position, InputIterator first, InputIterator last,
			typename ft::enable_if< !ft::is_integral< InputIterator >::value >::type* = NULL)
		{
			size_type n = ft::distance(first, last);
			if (this->size() + n <= this->capacity())
			{
				pointer val_tmp = this->_end;
				size_type range = this->_end - &(*position);
				this->_end += n;
				pointer tmp = this->_end;
				while (range--)
					this->_alloc.construct(--tmp, *(--val_tmp));
				while (n--)
					this->_alloc.construct(--tmp, *(--last));
			}
			else
			{
				pointer tmp = this->_start;
				size_type _size = n + this->size();
				size_type front_tmp = &(*position) - this->_start;
				size_type back_tmp = this->_end - &(*position);
				this->_start = this->_alloc.allocate(_size);
				this->_end = this->_start;
				this->_end_of_capacity = this->_start + _size;
				while (front_tmp--)
				{
					_alloc.construct(this->_end++, *tmp);
					_alloc.destroy(tmp++);
				}
				while (n--)
					_alloc.construct(this->_end++, *first++);
				while (back_tmp--)
				{
					_alloc.construct(this->_end++, *tmp);
					_alloc.destroy(tmp++);
				}
			}
		}

		//단일 요소(위치) 제거
		iterator erase(iterator position)
		{
			this->_alloc.destroy(&(*position));
			size_type n = this->_end - &(*position) - 1;
			pointer tmp = &(*position);

			while (n--)
			{
				this->_alloc.construct(tmp, *(tmp + 1));
				this->_alloc.destroy(tmp++);
			}
			--this->_end;
			return (position);
		}

		//범위[first, last) 제거
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
			return (first);
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

		//allocator
		//벡터와 연결된 할당자 객체의 복사본을 반환한다.
		allocator_type get_allocator() const
		{
			return (this->_alloc);
		}
	};

	/**
	 * @brief vector non-member function
	 *
	 */
	template <typename T, typename Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename ft::vector< T, Alloc >::const_iterator it_lhs = lhs.begin();
		typename ft::vector< T, Alloc >::const_iterator it_rhs = rhs.begin();

		while (it_lhs != lhs.end())
		{
			if (it_rhs == rhs.end() || *it_lhs++ != *it_rhs++)
				return (false);
		}
		return (true);
	}

	template < typename T, typename Alloc>
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
