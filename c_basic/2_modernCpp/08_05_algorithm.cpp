
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
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
}