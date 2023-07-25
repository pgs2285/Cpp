
#include <iostream>
#include <algorithm>

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
    auto func = [num]() // capture list에 없는 변수는 사용할 수 없다.
    {
        cout << num << endl;
    };
    func();

    
}