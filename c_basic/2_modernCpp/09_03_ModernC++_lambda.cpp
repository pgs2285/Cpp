#include <iostream>

using std::cout;
using std::endl;

struct Func{                                    // lambda의 구조를 struct를 통해 간단히 표현해보자.
    int value;                                  // capture 할 부분. 후에 Func func; func.value = 10; 이 부분이 capture list와 같은기능이다.
    void operator()(int value2) const           // 여기서 const는 operator() 함수 내부에서 멤버변수를 변경하지 않겠다는 의미이다.
                                                // 즉 lambda에 Mutable을 붙여줬다는건 const를 빼준다는 의미이다.
    {
        cout << value + value2 << endl;
        // value = 20;
        // return value + value2;
                                                // 이 주석들을 제거하면 밑에 lambda와 같은 기능, 구조가 된다
    }
};


int main()
{
    /*lambda : 함수를 만들어서 사용하는 방법 [capture list](parameter list) -> return type {function body} 
    return type 은 생략이 가능하다. parameter 가 없으면 ()도 생략이 가능하다.
    capture list는 lambda가 만들어질 때, 외부의 변수를 가져오는 방법이다. */

    int value = 10;
    auto func = [value](int value2) mutable     // mutable을 붙이면 capture list의 변수를 변경할 수 있다.(외부로는 값이 변경되지 않는다.)
    {   

        ++value;                                // 
        return value;
    };                                          // lambda 함수 끝에 ()를 붙이면 바로 호출이 된다.

                                                // 어떤 함수가 void foo(std::function<void(void)> func) 와 같이 형태를 강제로 받는디면 capture list와 parameter list를 적절히 조합해서 사용해자.  
    cout << func(20) << endl;                   // 11 (함수 호출로 value가 11로 변경되었다.)
    cout << func(20) << endl;                   // 12 (이전 함수 호출에의해 11->12로 변경되었다.)
                                                // 이러한 상황을 미리 생각하고 구현하라고 평소에는 const로 막아져 있다.
    cout << value <<endl;                       // 10 (capture된 변수가 직접적으로 변경되지 않는다.)

    auto func2 = [=]()                          // capture list에 =를 넣으면 외부의 모든 변수를 복사해서 사용한다.
    {
        cout << value << endl;
    };
    func2();

    auto func3 = [&]()                          // 모든 변수들을 reference로 capture하겠다는 의미이다.
    {
        value = 20;                             // 외부의 값이 변하진 않지만, reference로 capture했기 때문에 변경이 가능하다.
    };                                          // [&, num0] 와 같이 조합을 할 수도 있다. (num0는 value capture, 나머지는 reference capture)
    cout << value << endl;
    return 0;
}