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

enum struct Scoped : long long
{
    A,
    B = 1000000000000
};

template <typename T>
struct is_scope_enum
{
    static const bool value = std::is_enum<T>::value && !std::is_convertible<T,int>::value;
};


template <typename T, typename S = typename std::enable_if<is_scope_enum<T>::value>::type> // template parameter 가 같이 쓰일때에는 typename을 붙여줘야한다.
// template 를 이용해서 미리 scope시에만 작동되게 만들어준다.
// enable_if 함수는 true가 들어오면, 뒤에 후행하는 타입으로 만들어주지만, false가 들어오면 아예 변수를 만들지 않는다.
// 즉 뒤에있는 typename S부분에 빨간줄(오류) 가 뜬것으로 판단, 원래있던 ostream을 overloading 하므로 방문하지 않는다
// "치환실패는 오류가 아니다" sfinane의 기법 중 하나
//template <typename T, typename std::enable_if<is_scope_enum<T>::value, int>::type = 0(적당히 0으로 해준거)> // 이렇게 해도 똑같은 결과가 나오므로 이걸권장
// 추구 typename S 때문에 같은 템플릿 특수화를 할때 같은거라 판단할때도 있다.
//enable_if(BOOL, TYPE) 형으로 사용하는데 TYPE은 기본적으로 void이다. 앞에 bool이 true가 되면 TYPE을 반환한다.
std::ostream& operator<<(std::ostream& os, const T& s)
// 모든 cout 은 operator << 을 호출하기 때문에 여기서 오버로딩 시켜 설정을 변경시켜준다.
// cout 은 자기자신, 인수로 받을걸 받아서 return 해주므로 요렇게 한다.
{
    cout << "SCOPED" << endl;
    return os << static_cast<std::underlying_type<Scoped>::type>(s);
}



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

    cout << (long long)Scoped::B << endl;// 캐스팅이 필요함 
    //하지만 여기서 int 로 캐스팅 할 경우 오류가 발생할 수 있다. (overflow)
    cout << static_cast<std::underlying_type_t<Scoped>>(Scoped::B) << endl; // 이렇게 캐스팅을 해주면 overflow걱정 없다.
    //하지만 너무 길다. 위에 ostream의 operator overloading 을 활용해 바로 해보자.
    cout << Scoped::B << endl; // 위에서 ostream을 오버로딩해 바로 사용가능해짐
    /*
    복습 (범위가 있는 열거형 vs 범위가 없는 열거향)
    범위가 없는 열거형은 enum (변수명) {A,B,C}; 으로 선언했다
    범위가 있는 열거형은 enum ((class) or (struct)) (변수명) {D,E,F} 으로 선언했다
    범위가 없는 열거형은 바로 사용이 가능하다. 즉 이름 누수가 발생한다 int A = 10; = Error
    범위가 있는 열거형은 그 안에서만 보이기 떄문에 누수가 발생하지 않는다 int D = 10; = OK
    
    범위가 있는 열거형은 서술했듯 그냥 사용은 불가하다. 
    (변수명) (변수) = (변수명)::D 으로 사용해야한다.
    */

   cout << is_scope_enum<Scoped>::value << endl; // true

   enum UnScoped{A,B,C};
   cout << UnScoped::A << endl;

    return 0;
}