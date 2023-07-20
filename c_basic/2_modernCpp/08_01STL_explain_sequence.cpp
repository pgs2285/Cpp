/*
STL :  C++을 위한 라이브러리로서 C++ 표준 라이브러리의 많은 부분에 영향을 끼쳤다. 
container, literator, algorithm 으로 이루어져 있다.

container - 추상화된 데이터 모음, 배열 트리 해시테이블 등...
    - sequence container(순차컨테이너) : vector, list, deque // 사용자가 삽입한(의도한) 순서대로 나옴
    - associative container(연관컨테이너) : set, multiset, map, multimap (정렬이 되어서 나온다)
    - container adapter : stack, queue, priority_queue

iterator - 컨테이너를 순회하는데 사용한다. 포인터와 호환이 된다.
    - input iterator : 읽기만 가능
    - output iterator : 쓰기만 가능
    - forward iterator : 읽기와 쓰기가 가능
    - bidirectional iterator : 양방향으로 이동 가능
    - random access iterator : 임의의 위치로 이동 가능

algorithm - 컨테이너에 저장된 데이터를 다루는 알고리즘을 제공한다. 보통 iterator나 함수객체들을 넘겨서 처리한다.
    - sort, find, copy, for_each, transform, accumulate, count, remove, reverse, replace, swap, unique 등등
*/
#include <iostream>
#include <vector> // 순차 컨테이너 vector
#include <array> // 순차 컨테이너 array
#include <deque> // 순차 컨테이너 deque
#include <list> // 순차 컨테이너 list
#include <forward_list> // 순차 컨테이너 forward_list

using std::cout;
using std::endl;

int main()
{
    std::array<int, 10> arr; // array는 자료형, 크기를 지정해줘야함
    arr.fill(1); // 1로 초기화
    arr[0] = 10; // 일반 배열과 사용은 동일하다 swap, fill, sort 등의 함수를 사용할 수 있다.
    std::vector<int> vec; // vector 선언
    vec.push_back(10);
    vec.push_back(40);
    vec.push_back(30);
    vec.insert(vec.begin() + 1, 20); // 1번째에 20을 삽입
    vec.erase(vec.begin() + 1, vec.begin() + 2); // 1~2번째를 삭제
    vec.insert(vec.begin() + 3, 100); // 3번째에 100을 삽입˜
    // for(int v : vec)
    //     cout << v << endl; //순차 컨테이너의 예시로 넣은 순서대로 나옴.
        // output: 10 40 30
    // iterator를 이용한 순회
    for(std::vector<int>::iterator iter = vec.begin(); iter != vec.end(); iter++)
        cout << *iter << endl; // *iter로 접근
    
    // 주의사항
    cout << "vector 의 reserve를 증가시킬때 주의사항" << endl;
    
    std::vector<int>::iterator iter = vec.begin();
    cout << *iter << endl; 
    vec.reserve(vec.capacity() + 1); // reserve : 메모리를 미리 할당해놓는다. 새로운 공간 할당하고 복사하는 과정이 사라져, 속도측면에서 이득 capacity : 할당된 메모리의 크기를 알려준다.
    vec[0] = 0; 
    cout << *iter << endl; // 0이 나오지 않는다. reserve로 재할당 되면서 기존의 데이터는 새로운 공간으로 복사되었기 때문에 iter가 가리키는 곳은 유효하지 않다.
    // vector의 시간복잡도
    // 뒤에 삽입시 O(1), 추가 및 제거 O(n) : 데이터 이동시간 포함, 재할당시 O(n) 


    // 매번 재할당을 방지하기 위해 크기를 reserve로 저장하면 좋다. 지정하지 않을시 재할당 공식은 현재capacity + (현재 capacity / 2) 이다.
    
    // deque
    std::deque<int> deq;
    deq.push_back(10);
    deq.push_front(11); // deque는 앞에도 넣을 수 있다.

    //deque 의 시간복잡도
    // 뒤에 삽입시 O(1), 앞에 삽입시 O(1), 추가 및 제거 O(n) : 데이터 이동시간 포함, 재할당시 O(n)

    //vector와 deque의 차이점
    std::vector<int> vec2;
    vec2.reserve(10);
    vec2.push_back(10);
    cout << &vec2[0] << endl;
    vec2.insert(vec2.begin(),20);
    cout << &vec2[1] << endl; // insert하면서 미뤘기때문에 메모리값이 4바이트씩 밀려남

    std::deque<int> deq2;
    deq2.push_back(10);
    cout << &deq2[0] << endl;
    deq2.push_front(20);
    cout << &deq2[1] << endl; // deque는 앞에 넣어도 대상 메모리값이 그대로임
    // 앞에 넣을때 배열을 하나 더만들어서 앞에 넣는다. 그래서 메모리값이 그대로임. 물론 중간삽입의 시간복잡도는 똑같다.

    // list
    std::list<int> list0{1,4,2,1,3,7,8,6,20,12,18};
    // 리스트는 list[0] 과같이 첨자연산이 불가(성능이 안나와서 막아둠) - double linked list로 구현되어있기 때문에
    // head <->node <-> node <-> tail
    // list는 iterator를 사용해야한다.
    std::list<int>::iterator iter2 = list0.begin();
    std::advance(iter2, 2); // 2번째로 이동
    cout << "list의 3번째 값(head에서 2칸이동) : "<< *iter2 << endl; // 3이 나온다.
    list0.remove(1); // 1을 지운다 (중복이 있을시 모두 지운다)
    list0.remove_if([](int i){return i > 10;}); // 10보다 큰 값을 지운다 (remove if 는 함수를 넘겨줘야한다.)
    // 예시는 람다식이었지만 함수도 가능 bool remove(const int& i) {return i > 10;}같이. 이경우에는 remove_if(remove) 이런식으로 넘겨준다.

    list0.sort();
    for(int i : list0)
        cout << i << endl; // 1 2 3 sorting 되어서 나온다
    // algorithm 의 std::sort(begin,end)는 사용할 수 없다. list는 random access(list0[0])가 불가능하기 때문에
    // list의  iterator 는 iter++, iter-- 만 가능하다. iter + 2 와 같은 연산은 불가능하다.
    // list는 중간삽입삭제가 O(1)이다. (vector, deque는 O(n)) 매우빠르다.
    std::list<int> list1{2,3,5,14};
    
    cout << " MERGE 값 계산" << endl;
    cout << "list0 : ";
    for(int i : list0)  cout << i << " ";
    cout << "list1 : " ;
    for(int i : list1)  cout << i << " ";
    list0.sort(); list1.sort(); // merge할때 정렬해줘야함! 아니면 오류뜬다.
    list0.merge(list1); // 합치고 정렬까지 해준다.
    for(int i : list0)  cout << i << endl;
    //이밖에도 unique (중복제거), reverse(역순), splice(합치기), swap(교환) 등등의 함수가 있다.

    // forward_list : 싱글링크드리스트 (제약이 많아서 많이 사용되진 않는다.)
    std::forward_list<int> flist{1,2,3,4,5};
    flist.push_front(10); // 앞에 삽입
    flist.insert_after(flist.begin(), 20); // 1번째 노드 뒤에 삽입 (1,10,2,3,4,5) , 싱글리스트에서 노드는 자기자신과 다음노드를 가리키는 포인터만 가지고있어 뒤에만 삽입가능
    flist.erase_after(flist.begin()); // 1번째 노드 뒤에 삭제
    // forward_list는 iterator가 bidirectional iterator(양방향이 아니라)가 아니라서 -- 연산이 불가능하다.
    // forward_list는 중간삽입삭제가 O(1)이다. (vector, deque는 O(n)) 매우빠르다.
    // forward_list는 list와 달리 sort, merge, unique, reverse, splice, swap 등의 함수가 없다.
    // forward_list는 list보다 메모리를 적게 사용한다. (list는 더블링크드리스트라서 노드당 2개의 포인터를 사용한다.)

    
    return 0;
}



