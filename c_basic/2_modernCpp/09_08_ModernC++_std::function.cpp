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


int main()
{

    std::function<int(float)> f1;

    foo<int(float)>();                          // output : FifE (function<int(float)>)
    Func func;
    std::function<int(float)> f2 =  Func(); 
    cout << f2(1.1f) << endl;

    std::function<int(int)> f3 = Func2::func;   // static member function은 함수 포인터로 변환되어야 한다. 
    cout << typeid(f3).name() << endl;  
    return 0;
}