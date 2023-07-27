
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <list>
#include <array>
#include <numeric>
#include <execution> // c++17 부터 지원하는 병렬처리
using std::cout;
using std::endl;

//함수 객체 복습
//함수 객체 : operator연산자를 통해 함수처럼 호출되는 객체
struct Func
{
    int operator()(int value){ // 호출 연산자
        return value;
    }
};

int main()
{
    //algorithm 의 형태는 대부분 다음과 같은 형태를 띈다 : func(iter begin, iter end, value)
    /*먼저 lambda 에 대해 간단하게 알아보자
    람다의 형태는 다음과 같다
    auto func = [](){} : []는 capture list, ()는 parameter list, {}는 body
    */
    int num = 0;
    auto func = [num](int value) // capture list에 없는 변수는 사용할 수 없다.
    {
        return num + value; // return type은 지정하지 않아도 자동으로 추론이 가능하다.
    };
    cout << func(10) << endl; //매번 함수 객체를 만들기 힘드니 간단하게 알고만 넘어가자. 람다는 추후에 자세하게 다룰 예정이다.


    //std::find (algorithm) : iterator를 통해 원하는 값을 찾는다.
    std::vector<int> vec{1,2,3};
    auto iter = std::find(vec.begin(), vec.end(), 3); // 3을 찾아라
    // 여기서 auto 는 std::vector<int>::iterator 와 동일
    if(iter != vec.end())
        cout << *iter << endl;

    std::set<int> s {1,2,3};
    // set(정렬된 containter들)도 위 방법처럼 algorithm의 find를 사용할 수 있지만 , 이미 멤버함수로 find가 존재한다.
    auto iter2 = s.find(3);
    if(iter2 != s.end())
        cout << *iter2 << endl;
    // 위 멤버함수의 set과 의 find, algorithm의 find는 동일한 기능을 수행한다. 하지만 멤버함수의 find는 set의 특성을 이용해 더 빠르게 수행한다.
    // algorithm의 find는 iterator의 특성만 가지고 find를 수행한다. 실제 뜯어보면 iter를 이용해 for문으로 돌려 찾는다.
    // ordered or unordered는 모두 각자 tree, hashtable의 자료구조를 가지고 있어, 기본 iterator는 가지고 없는 정보를 가지고있어 더욱 빠르게 수행.
    // 실제 hashtable의 find(unordered)는 O(1)이다. tree의 find(ordered)는  O(logN) .하지만 algorithm의 find는 O(n)이다.

    //이와같은 구현 방식의 차이로 인해, ordered|unordered 들은 find 는 있지만, find_if같이 특수한 멤버함수는 없으므로, 조건을 걸고 싶으면 algorithm의 find_if를 사용해야한다.
    
    // find_if(begin, end, 조건) : 조건을 만족하는 첫번째 원소의 iterator를 반환한다.
    auto iter3 = std::find_if(vec.begin(), vec.end(), [](const int& value){return value % 2 == 0;}); // 짝수를 찾으라는 람다식
    //매개변수 value에는 각각의 vector 요소가 하나씩 들어간다.
    if(iter3 != vec.end())
        cout << *iter3 << endl; 
    // ordered, unordered set 에서 find_if 를 사용하고 싶으면 멤버함수는 없고, std::find_if를 사용해야한다.


    //std::remove_if(begin, end, 조건) : 조건을 만족하는 원소를 삭제한다. (size가 변경되지는 않는다.)
    std::vector v = {1,2,3,4,5,4,3,2,1};
    auto iter4 = std::remove(v.begin(), v.end(), 3); // 모든 3을 삭제한다
    //iter4는 삭제된 원소의 다음 위치를 가리킨다.
    for(auto e : v)
        cout << e << " "; // 1 2 4 5 4 2 1 (2 1) <- 사이즈가 줄어든게 아니라 뒤에 2 1 은 그대로 남아있다.
    cout << endl;
    v.erase(iter4, v.end()); // erase를 통해 삭제하면 사이즈가 줄어든다.
    for(auto e : v)
        cout << e << " "; // 1 2 4 5 4 2 1 <- 사이즈가 줄어들어 2 1이 삭제된다.
    cout << endl;
    cout << *(v.end()) << endl; // end는 마지막 원소의 다음 위치를 가리킨다. (end는 마지막 원소가 아니다.) 위에선 폐구간이라 포함되지 않았을뿐
    
    ////remove - array////
    std::array<int,7> arr = {1,2,3,4,5,6,7};
    std::remove(arr.begin(), arr.end(), 2);
    //std::remove_if(arr.begin(), arr.end(),조건);
    std::remove_if(arr.begin(), arr.end(), [](const int& value){ // 람다식이 아니라 일반 함수 객체나 함수 포인터도 가능하다.
        return value % 2 == 0;
    });
    for(auto e : arr)
        cout << e << " "; // 1 3 4 5 6 7 7 <- array는 size가 고정되어있어서 뒤에 7이 남아있다.
    cout << endl;
    
    //// remove - list ////
    std::list<int> li = {1,2,3,4,5,6,7};
    std::remove(li.begin(), li.end(), 3); // list는 앞에서부터 탐색후 삭제하고, 다음 원소를 가리킨다. 즉 크기를 줄여줄 필요가 없다.
    // 당길필요가 없으므로 속도가 빠르다. 
    li.remove(3); // 멤버함수로도 remove가 존재한다.
    li.remove_if([](const int& value){
        return value % 2 == 0;
    }); // remove_if(begin, end, 조건) : 조건을 만족하는 원소를 삭제한다. (algorithm에 존재하지만, 위에서 이야기했듯 멤버함수가 존재한다면 속도에 이점이 있다.)
    for(auto e : li)
        cout << e << " "; // 1 2 4 5 6 7
    cout << endl;
    

    //set은 remove, remove_if가 없다. set은 iterator가 const iterator이기 때문에 원소를 삭제할 수 없다.
    std::set<int> s1 = {1,2,0,4,5,7};
    s1.erase(3); // earse(value) : value를 삭제한다.(애초에 set은 중복을 허용하지 않는다)
    //  특정조건으로 지워주고 싶으면 조금 복잡하다.(멤버함수가 없다)

    for(auto iter = s1.begin(); iter != s1.end();) //만약 조건이 수행되여 삭제된다면, 한칸씩 당겨지기 때문에 iter이 증가하면 안되므로, 조건에 맞지않으면 증가시켜주는식
    {
        if(*iter % 2 == 0)
            iter = s1.erase(iter); // erase는 삭제된 원소의 다음 위치를 반환한다.
        else
            iter++;
    }

    for(auto e : s1)
        cout << e << " "; // 0 1 2 4 5 7
    cout << endl;

    //remove, remove_if 등등 algorithm 함수들을 기본 배열에도 사용가능..
    //remove(arr, arr+1, 3); or remove(std::begin(arr), std::end(arr), 3); // 배열은 begin, end가 없으므로 std::begin, std::end를 사용해야한다.

    //std::copy(v1.begin(), v1.end(), v2.begin()); // v1의 원소를 v2에 복사한다. (v2의 크기는 v1보다 크거나 같아야한다.)
    std::vector<int> v1 = {1,2,3,4,5};
    std::vector<int> v2; // v1과 같은 크기의 v2를 만든다.

    // std::copy(v1.begin(), v1.end(), v2.begin()); // v1의 원소를 v2에 복사한다. (v2의 크기는 v1보다 크거나 같아야한다.)
    std::copy(v1.begin(), v1.end(), std::back_inserter(v2)); // back_inserter를 계속 push_back을 해준다.
    // copy의 구현을 간단히 설명하자면 for 문으로 순회하며 = 연산자를 통해 값을 넣어준다.
    // back_inserter에서 operator=는 push_back을 호출하므로, 크기가 없는 벡터에서도 값을 넣어줄 수 있다..
    for(auto e : v2)
        cout << e << " "; // 1 2 3 4 5

    std::set<int> s2;
    std::copy(v1.begin(), v1.end(), std::inserter(s2, s2.begin())); // inserter는 insert를 호출한다. insert는 중복을 허용하지 않으므로, 중복된 값은 들어가지 않는다.
    // 즉 vector -> set 으로 복사할때 중복된 값은 제거된다.
    for(auto e : s2)
        cout << e << " "; // 1 2 3 4 5
    
    std::vector<int> v3(10000);
    std::iota(v3.begin(), v3.end(), 1); // 1부터 오름차순으로 넣어준다
    std::sort(v3.begin(), v3.end(), [](const int& a, const int& b){return a > b;}); // 내림차순으로 정렬한다.
    std::sort(v3.begin(), v3.end(), std::greater<int>()); // 위와 동일한 코드 (단일 코어 사용 std::execution::seq)

    // std::sort(std::execution::par, v3.begin(), v3.end(), std::greater<int>()); // 병렬처리 (c++17 부터 지원)
    // c++ 17부터는 execution::par, execution::unseq 를 통해 코어를 여러개 사용할 수 있다.
    for(auto e : v3)
        cout << e << " ";
    cout << endl;



}