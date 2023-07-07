#include <iostream>
#include <cstdarg>

using std::cout;
using std::endl;

// 가변인자, 정해주지 않고 여러개의 인자를 받고싶을때

int sum(int count, ...) // void sum(int count...) 처럼 사용가능
{
    int result = 0;
    va_list args; // va_list는 가변인자를 받을때 사용하는 타입
    va_start(args, count); // 시작점이 count이고, 스택에 순서대로 쌓여있으므로 쌓인만큼 전진시켜주면 된다.
    for(int i = 0; i < count ; i++)
    {
        result += va_arg(args, int); // args를 integer사이즈만큼 전진시켜준다. 
    }
    return result;
}
int sum2(int value) // 밑 가변인자 함수의 탈출조건
{
    return value;
}
// 가변템플릿
template<typename... Args>
int sum2(int value, Args... args) // unpack 하기, value에는 args값의 첫번째 인자가 들어가 있다. 딋 args에는 남은 인자들이 들어가있음
{
    // 즉 순서대로 넘어오니까 value에는 10, args에는 20,30,40 이 들어가있음
    return value + sum2(args...); // 재귀함수. 탈줄조간 필요
}

template<typename T>
T mul(T value)
{
    return value;
}

template<typename T, typename... Args>
T mul(T value, Args... args)
{
    return value * mul(args...);
}

int factorial(int value){
    if(value == 1) return 1;
    return value * factorial(value - 1);
}

template <int N>
struct Factorial{
    static const int value = N * Factorial<N-1>::value;
};

template<>
struct Factorial<1>{
    static const int value = 1;
};


int main()
{
    int result = sum(4,10,20,30,40); // 가변인자들은 stack에 저장된다.
    cout << result <<endl;
    cout << sum2(10,20,30,40,50) << endl;
    cout<< mul<float>(1.1f,2.2f,3.3f,4.4f) << endl; // 위 sum함수를 변수상관없이 받게 만든거. 물론 mum(1.1f,2.2f,3.3f,4.4f) 이렇게만 써도 암시적으로 형변환된다.
    // 뿐만아니라, 형식이 모두 같을필요도 없다. 하나씩 넘겨받는 value가 T로 받기때문에 가능
    cout << mul(1, 1.0f, 3u, 'c') << endl;  // 다만  처음 추론된게 int이므로 integer반환한다, 이게 싫으면 명시해줘여함

    //템플릿 메타 프로그래밍
    //메타프로그래밍이란?
    //컴파일 타임에 실행되는 프로그래밍
    //기존에 함수를 사용해서 팩토리얼을 구현해보자.
    factorial(5); // 이건 런타임에 실행된다.
    cout << Factorial<6>::value << endl; // 이건 컴파일 타임에 실행된다. 컴파일 타임에 실행되는건 템플릿 메타 프로그래밍이다. 즉 런타임에는 이미 고정된 값임.
    //즉 컴파일 타임이기떄문에 int a = 10,  Factorial<a>::value 같이 변수를 넣어주는건 불가능하다.
    //메타프로그래밍은 memorization이 되기때문에 중복호출이 없다. 이는 피보나치를 생성할때 차이가 보인다. Fibo<5> -> Fibo<4> + Fibo<3> 이라면 이 이후에 Fibo<4>값을 찾을때는 
    //다시 구하는게 아닌 memorization된 값을 사용한다. 즉 중복호출이 없다.
    int a = 10;

    return 0;
}