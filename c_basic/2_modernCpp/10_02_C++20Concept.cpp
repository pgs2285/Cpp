// concepts : C++20 에서 추가된 기능
// 1) 컴파일 시간에 타입을 체크하는 기능
// 2) 함수 템플릿의 인자로 타입을 제한하는 기능
#include <iostream>

template<typename T>
concept NonPointer = !std::is_pointer<T>::value; // concept : 조건을 만족하는 타입을 정의하는 기능
                                                 // concept뒤에는 boolean으로 반환하는 조건을 만족하는 타입을 정의한다. is_pointer<T>::value 는 true/false를 리턴하므로 올바른 예시이다.



template <NonPointer T> // 아래 주석처럼 컴파일 에러가 발생한다. 하지만 좀더 간단하고 보기좋다. -> template <typename T> requires NonPointer<T> 와 같은말이다.
//template<typename T, typename std::enable_if<!std::is_pointer<T>::value>::value, int>::type = 0> 
// enable_if : 조건에 따라 타입을 결정하는 기능, is_pointer : 포인터인지 아닌지 체크하는 기능 , 즉 포인터가 아닌경우에, true,false 를 반환하고, true일 경우에만 뒤에 있는 int 타입을 반환하게 된다.
// 즉 true일떄 Int를 반환하며, type호출이 가능하게 되고, false일때는 type이 없으므로 컴파일 에러가 발생하게 된다. type의 기본값은 0이므로 뒤에조건도 자동만족한다.
void swap(T& a, T& b)
{
    static_assert(!std::is_pointer<T>::value, "T is pointer"); //static_assert : 컴파일 시간에 조건을 체크하는 기능 (만약 함수 내부를 들어오지 못하게 하고싶다면, typename T말고 concept나 enable_if를 사용해야한다.)
    T tmp = a;
    a = b;
    b = tmp;
}



int main()
{
    int a = 10, b = 20;
    swap(a, b); // T : int
    std::cout << a << " " << b << std::endl;
    int* px = &a, * py = &b;
    // swap(px, py); // T : int* -> static_assert 에 의해 컴파일 에러 발생
    
    return 0;
}