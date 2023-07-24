//ordered associative container는 binary search tree를 사용하여 구현되어 있고, unordered associative container는 hash table을 사용하여 구현되어 있다.
//즉 삽입 삭제 검색이 O(logN)이 아닌 O(1), 상수시간이 걸린다. 하지만 hash table은 순서를 보장하지 않는다.
#include <iostream>
#include<unordered_map>


using std::cout;
using std::endl;

struct HashFunction{
    size_t operator()(const int& key) const
    {
        return key % 10;
    }
};

int main()
{
    std::unordered_map<int, std::string> um{
        {1, "value1"},
        std::pair(4, "value2"),//두 개체를 단일 개체로 처리하는 기능을 제공하는 구조체 즉 map의 value값은 pair이다.
        std::make_pair(3, "value3") // 이렇게 초기화를 할 수 있지만 c++17 부터 가능하다. 
    }; // 왼쪽 : key, 오른쪽 : value
    
    for(std::unordered_map<int,std::string>::iterator iter = um.begin(); iter!=um.end(); iter++)
    {//c++ 17 부터는 const auto& [key, value] : um 으로 사용할 수 있다. 앞으로 나올 대부분 auto사용가능하므로 설명은 이후엔 생략.
        cout << iter ->first << " / " << iter->second << endl;
        
        
    }
    //map이기 때문에 um[0] 같이 직접 참조가 가능하다.
    cout << um[4] << endl; // key : 4 value : value2
    //unordered map은 굉장히 빠른시간을 보장한다. find,erase,insert 등 ordered 에서 지원했던 함수 대부분을 지원한다.

    // 여기선 unordered container들이 가지는 해시테이블의 특성을 알아보자.
    // 인자에, 동일성확인, 해시함수객체등을 추가할 수 있다
    // 먼저 해시값은 충돌이 발생하면 뒤에 linked list로 연결된다. (abc, cda 둘다 hash변환시 같은값이 나오고, 같은 버킷에 저장되는 경우)
    // 해시값은 key값을 hash function을 통해 변환한 값이다. (key값이 1이면 hash function을 통해 1이 나온다)
    std::unordered_map<int, std::string, HashFunction> um2{
        {1, "value1"},
        {2, "value3"},
        {3, "value10"},
        {21,"value13"},
        {31,"value14"},
        {11,"value12"}
    }; 
    for(const auto& [key, value] : um2)
    {
        cout << key << " / " << value << endl;
    }
    cout << um2.bucket_size(1) << endl; // HashFunction안에 operator를 통해 1이라는 key값이 1이라는 hash값으로 변환되고, 이 hash값이 1번째 bucket에 저장된다.
    // 그래서 현제 1번째 bucket에 몇개의 value가 저장되어있는지를 반환한다.
    cout << um2.bucket_size(2) << endl; 
    
    //골고루 분포되어있는게 좋다. (bucket_size가 골고루 분포되어있는게 좋다) 위 같은 경우는 1버킷에 80%가 저장되어있는 상황이다. 즉 좋지않은 상황
    //골고루 분포되어 있지않으면 insert, find, erase등에 충돌이 발생해 O(n) 까지 늘어날 수도 있다.
    // 만약 hashfunction이 return 1만 하게되면 1번째 버킷에 모든 value가 저장되어있는 상황이다. 이런 경우는 hashfunction을 수정해야한다.(보통 직접 구현하지는 않는다)
    // 기본적으로 제공하는 해시함수 쓰면 골고루 해주니까 그냥 써라

    
    return 0;
}