#include<iostream>
#include<type_traits>

using std::cout;
using std::endl;

class A{};


template <typename T>
class is_pointer{
    public:
    static const bool value = false;
};

template <typename T>
struct is_pointer<T*>
{
    public:
    static const bool value = true;
};


template <typename T>
struct remove_pointer
{
    using type = T;
};

template<typename T>
struct remove_pointer<T*>
{
    using type = T;
};

template<typename T>
struct add_pointer 
{
    using types = T*;
};

template<typename T>
struct add_pointer<T&> // 나머지는 되지만 레퍼런스에는 포인터를 붙이기 어색하므로 특수화
{
    using types = T*;
};




int main()
{
    cout << std::boolalpha;
    cout << std::is_pointer<A>::value << endl; // false, is_pointer는 포인터인지 아닌지를 판별해주는 템플릿
    // 위 함수를 자체구현 해보자
    cout << is_pointer<A*>::value << endl; // 템플릿 특수화로 직접 구현한 is_pointer
    // cppreference.com 에서 type_traits를 검색하면 많은 템플릿들을 볼 수 있다.
    // 보통 템플릿 함수 내부에 사용한다
    
    int num;
    std::add_pointer_t<int> a = &num; // int* a = 10; 과 같다.
    *a = 10; // 이 a는 add_pointer로 인해서 포인터 형태가 된다.
    cout << num << endl;

    std::remove_pointer_t<int*> b;

    remove_pointer<int*>::type c; // 위와 같은 표현
    cout << typeid(c).name() << endl; // int

    add_pointer<int>::types d = &num;
    cout << typeid(d).name() << endl; // int*

    return 0;
}