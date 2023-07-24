#include <iostream>
#include <vector>
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
    return 0;
}