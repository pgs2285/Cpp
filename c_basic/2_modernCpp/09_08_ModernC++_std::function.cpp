#include <functional>
#include <iostream>

using std::cout;
using std::endl;

template <typename T>
void foo()
{
    cout << typeid(T).name() << endl;
}

struct Func{
    int operator()(float f) { return f; }
};

struct Func2{
    static int func(int i) { return i; }
};

struct Func3{
    int func(int i) { return i; }
};

int main()
{

    std::function<int(float)> f1;

    foo<int(float)>();                                  // output : FifE (function<int(float)>)
    Func func;
    std::function<int(float)> f2 =  Func(); 
    cout << f2(1.1f) << endl;

    std::function<int(int)> f3 = Func2::func;           // static member function은 함수 포인터로 변환되어야 한다. 
    cout << typeid(f3).name() << endl; 
    // non-static 함수 Func3를 함수포인터로 가져오려면 다음과 같다
    int(Func3:: *f)(int) = &Func3::func;                // Func3::func의 주소를 가져온다.
    cout << (Func3().*f)(3) << endl;                    // Func3::func의 주소를 호출한다. 

    std::function<int(Func3&, int)> f4 = &Func3::func;  // Func3::func의 주소를 가져온다. function<반환형(this, parameter)> 이므로 Func3&를 넣어준다.
    std::function<int(int)> f5 = std::bind(&Func3::func, Func3(), std::placeholders::_1); // std::bind를 사용하면, Func3::func의 주소를 가져온다.
                                                        // std::bind는 함수포인터 반환, placeholders는 parameter를 받는다, _1은 첫번째 parameter를 받는다. 
    cout << f5(3) << endl;                              // 즉 Func3::func 의 주소를 가져와서, Func3()의 주소를 넣어주고, parameter를 넣어준다.
    return 0;
}