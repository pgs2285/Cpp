#include <iostream>
#include <type_traits>
#include <vector>

using std::cout;
using std::endl;


void goo(int& value)
{
    cout << "goo(int&)" << endl;
}

void goo(int&& value)
{
    cout << "goo(int&&)" << endl;
}

template<typename T>
void foo(T&& value)
{
    // goo(value);                     // goo(int&) 호출 , parameter로 lvalue를 넘겨줌.
    // goo(std::move(value));          // goo(int&&) 호출 , move의 static_cast를 통해 rvalue로 변환해서 넘겨줌.
    // 아래에서 말한 추론규칙에 의해, 아래처럼 사용할 수 있다.
    goo(static_cast<T&&>(value));       // rvalue는 그대로 출력, lvalue - > int& && 이므로 int&
                                        // 이런걸 perfect forwarding 이라고 한다. 이것을 forward를 사용하면 더 간단하게 사용할 수 있다.
    goo(std::forward<T>(value));        // 위 static_cast와 같은 구현이다.
    
}

template<typename T>
void bar(T&& t) 
{
    cout<< "is_lvalue_type:" << std::is_lvalue_reference<T>::value << endl;
    cout<< "is_rvalue_type:" << std::is_rvalue_reference<T>::value << endl;

    cout<< "is_lvalue_type(&):" << std::is_lvalue_reference<T&>::value << endl;
    cout<< "is_rvalue_type(&):" << std::is_rvalue_reference<T&>::value << endl;

    cout<< "is_lvalue_type(&&):" << std::is_lvalue_reference<T&&>::value << endl;
    cout<< "is_rvalue_type(&&):" << std::is_rvalue_reference<T&&>::value << endl;

}

int main()
{
    foo(10);
    /*  매개변수가 많아질 수록, 그 경우의수의 2승 만큼의 함수를 만들어 주어야 한다.   
        매우 비 효율적 이므로, 가변인자 앞에 &&를 붙이면 universal reference가 된다는 것을 사용하자.
        (ex : auto&& value , template<typename T> void foo(T&& value) ... 등)
        bar 템플릿 예시를 보자.
    */
    // bar(10);                        // rvalue
    /*
    T = int 이다.
    Output:
    is_lvalue_type:0                // 처음에 non-reference type이므로 lvalue도 아니고 rvalue도 아니다.
    is_rvalue_type:0               
    is_lvalue_type(&):1             // T& -> int& 이므로 true;
    is_rvalue_type(&):0
    is_lvalue_type(&&):0
    is_rvalue_type(&&):1            // T&& -> int&& 이므로 true.
    */
    int num(10);
    foo(num);
    bar(num);                       // 기존의 &&같은 r value 참조자는 l value를 받을 수 없다. 하지만 이 경우 가변인자 앞에 &&붙여 universal reference로 만들면 l value도 받을 수 있다.
    /*
    Output : 
    T = int& 이다.
    is_lvalue_type:1                // T자체는 lvalue이다.
    is_rvalue_type:0
    is_lvalue_type(&):1
    is_rvalue_type(&):0
    is_lvalue_type(&&):1            // T&& -> int& && -> int& 이므로 lvalue이다. (두개의 레퍼런스가 만나, 하나의 레퍼런스로 군집되는걸 reference collapsing 이라고 한다)    
    is_rvalue_type(&&):0            // reference collasping의 규칙은 아래와 같다.
                                    // 1. T& & -> T&
                                    // 2. T& && -> T&
                                    // 3. T&& & -> T&
                                    // 4. T&& && -> T&&
                                    // 즉 lvalue가 하나라도 있으면 lvalue 참조자가 되고, 그렇지 않으면 rvalue 참조자가 된다. (사실 당연하다.)
    */

    std::vector<int> v;
    v.push_back(10);                // push_back또한 T&&로 구현되어있지만, 이미 선언부분에서 타입을 추론해주기 때문에 여기서 &&는 rvalue 참조자가 맞다.
    v.push_back(num);               // 여기서는 lvalue로 넘어가서 const T& 로 선언되어 있다.
    return 0;
}