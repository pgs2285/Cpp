#include <iostream>
#include <vector>
#include <forward_list>
#include <list>
#include <deque>
#include <iterator>
#include <fstream>
#include <set>
#include <istream>
using std::cout;
using std::endl;

template<typename TContainer, typename T>
bool has(TContainer begin, TContainer End, T value)
{   
    for(auto iter = begin; begin != End; ++begin)
    {
        if(*begin == value)
            return true;
    }
    return false;
}

void ostreamIter(std::ostream& os)
{
    std::ostream_iterator<int>  iter(os, " ");// os에 1 2 3 이 출력된다.
    *iter = 1;
    *iter = 2;
    *iter = 3;// 이렇게 하면 1 2 3 이 출력된다.
}

void setInsert()
{
    std::set<int> s;
    std::insert_iterator<std::set<int>> iter(s, s.begin());
    *iter = 1;
    *iter = 2;
    *iter = 3;
    *iter = 0;

    for(auto& e : s)
        cout << e << " ";//inserter를 사용하면 값을 알아서 넣어준다

}

int main()
{
    std::vector<int> vec{ 1, 2, 3};
    for(std::vector<int>::const_iterator iter = vec.cbegin(); iter != vec.cend(); ++iter)
    {
        cout << (*iter) << endl;
        // const 라 수정은 불가하다. ( *iter = 2 (X) )
        // 그냥 iter은 물론 수정된다.
    }
    // 이게 그동안 사용해왔던 iterator이다.(위 예시는 const_iterator) vec.end(); 마지막원소의 다음위치를 가리킴, vec.begin(); 시작 vec을 가리킴
    // iterator는 컨테이너를 순회하는게 보통이지만, 접착제 역할을 한다 보면된다.
    // 
    cout << std::boolalpha << has(vec.begin(), vec.end(), 3) << endl; // vec.begin() : pointer, vec.end() : pointer
    // forward iterator -> forward list, unordered container 등에서 사용
    std::forward_list<int> fl{ 1, 2, 3,4,5,6,7,8,9,10};
    auto iter = fl.begin();
    iter++; ++iter; //iter+1; iter+=1; iter = iter + 1; // 이런식으로 사용할 수 없다.
     // forward iterator는 ++만 가능하다. --는 불가능하다.

    // bidirectional iterator -> list, set, map 등에서 사용
    std::list<int> li{ 1, 2, 3,4,5,6,7,8,9,10};
    auto iter2 = li.begin();
    iter2++; ++iter2; //iter2+1; iter2+=1; iter2 = iter2 + 1; // 이런식으로 사용할 수 없다.
    iter2--; --iter2; //iter2-1; iter2-=1; iter2 = iter2 - 1; // 이런식으로 사용할 수 없다.

    // random access iterator -> vector, deque 등에서 사용
    std::vector<int> vec2{ 1, 2, 3,4,5,6,7,8,9,10};
    auto iter3 = vec2.begin();
    iter3++; ++iter3; iter3+1; iter3+=1; iter3 = iter3 + 1; // 이런식으로 사용할 수 있다.
    iter3--; --iter3; iter3-1; iter3-=1; iter3 = iter3 - 1; // 이런식으로 사용할 수 있다.

    //random access는 메모리에 직접 접근할 수 있지만, forward, bidirectional은 값을 찾아가야한다.

    //contiguous iterator -> array, vector 등에서 사용(C++20)
    //physical memory contiguous
    cout << *(iter3 + 2) << endl;
    cout << *(std::addressof(*iter3) + 2) << endl;
    //위 두개의 값이 같으면 contiguous iterator이다.
    //addressof는 주소를 가져오는 함수이다. &와 차이점은 &는 오버로딩이 되면 결과값이 변경될수도 있지만, addressof는 주소값을 무조건 가져오기때문에 사용한다
    
    std::deque<int> deq{ 1, 2};
    deq.push_front(3);
    auto iter4 = deq.begin();
    cout << *(iter4 + 2) << endl; 
    cout << *(std::addressof(*iter4) + 2) << endl;// 두개의 출력값이 다르다
    //dequq는 contiguous iterator가 아니다. deque는 array를 여러개 사용하기 때문에 물리적으로 연속적이지 않다.
    
    //output iterator -> ostream_iterator, inserter 등에서 사용
    // *iter에 값넣기만 가능.

    setInsert();
    
    //input iterator -> istream_iterator 등에서 사용
    // *iter읽기만 가능 (한번만 읽을수 있다.
    
    std::istream_iterator<int> iter5(std::cin);
    auto value = *iter5; // 입력 대기상태에 들어간다.
    cout << value << endl; 
    //입출력 반복자는 입출력 스트림에서만 사용

    // 위 5개의 iterator은 아래와 같은 포함관계를 가진다
    // input iterator -> forward iterator -> bidirectional iterator -> random access iterator -> contiguous iterator
    //즉 input iterator가 가지고 있는 기능은 forward iterator도 가지고 있다.
    //output iterator는 따로 있다.
    return 0;
}