// 우측값 참조 / 이동 의미론

#include <iostream>

using std::cout;
using std::endl;

const char* wrap(const char* str)
{
    return str ? str : "(null)";
}

class String{ // 우측값 참조를 위한 String Class 구현
    private:
        char* _str;

    public:
        explicit String(const char* str) : _str(new char[strlen(str)+ 1])
        // 복습 : explicit는 암시적인 형변환을 막아준다. 예를들어 이 string 예시에선 String str = "1"; 과 같이 사용할 수 없다.
        {
            strcpy(_str,str);
            cout << "Constructor : " << _str << endl;
        }

        String(const String& other) : _str(new char[strlen(other._str)+1])
        {
            strcpy(_str,other._str);
            cout << "Copy Constructor : " << _str << endl;
        }

        String(String&& other) noexcept : _str(other._str) // 이동 생성자
        {
            other._str = nullptr;
            cout << "Move Constructor : " << _str << endl;
        }

        String& operator=(const String& str)
        {
            cout<< "Copy Operator : " << _str << " = " << str._str << endl;
            delete[] _str;
            _str = new char[strlen(str._str)+1]; // 메모리 할당 후 복사하는 깊은복사를 한다.
            strcpy(_str,str._str);
            return *this;
        }

        String& operator=(String&& str) noexcept    // &&를 rvalue reference 즉 우측값 참조라고 한다.
                                                    // 이건 우측값 참조를 재정의한 것이다.
                                                    // Standard Library에서 noexcept를 사용하지 않으면 이동이 아니라 복사가 되는 경우가 있다.
        {
            cout << "Move Operator : " << wrap(_str) << " = " << str._str << endl;
            delete[] _str;
            _str = str._str;                        // 얕은 복사를 한다.
            str._str = nullptr;                     // 이동시킨 객체의 포인터를 제거해준다.

            return *this;

        }

        virtual ~String()
        {
            cout << "Destructor : " << wrap(_str) << endl;
            delete[] _str;
        }

        friend std::ostream& operator<<(std::ostream& os, const String& str)
        //cout을 좀더 편하게 사용하기위해 << 연산자 오버로딩
        {
            os << str._str;
            return os;
        }
};

template<typename T>
void Swap(T& x, T& y)
{
    // T temp = x; // 이상태면 x는 임시변수로 판단하지 않고, 일반 변수로 판단해 복사연산자만 호출된다
    T temp = std::move(x); // std::move를 사용하면 임시변수로 판단해 이동연산자를 호출한다.
    x = std::move(y);
    y = std::move(temp);

}

String makeString()
{
    return String("World"); // move를 사용하지 않아도 RVO(Return Value Optimization) 최적화가 되어 이동연산자가 호출된다.
}

void foo(int&)
{
    cout << "int&" << endl;
}

void foo(int&&)
{
    cout << "int&&" << endl;
}

int main()
{
    String s1("Hello");
    s1 = String("World"); // 이동 연산자가 호출된다.
    // String s2 = s1; // 복사 생성자가 호출된다.
    /*
        OutPut;
        Constructor : Hello
        Constructor : World
        Copy Constructor : Hello
        Copy Operator : Hello = World
        Copy Operator : World = Hello
        Destructor : Hello
        Destructor : Hello
        Destructor : World
        너무 많은 생성자와 소멸자가 호출된다.
    */
    //만약 임시객체인 것들을 알 수 있다면 얕은복사를 해버리고 포인터를 제거해주면 된다. -> 대입연산자를 한번더 오버로딩해준다.

    cout << " ======== SWAP ========" << endl;
    String s2("Hello");
    String s3("World");
    Swap(s2,s3);
    makeString();
    // int* ptr = &a();// a는 우측값이므로, 참조가 불가능.
    // int* ptr = &10; // 10은 우측값이므로, 참조가 불가능.
    // 즉 임시값, 더이상 사용하지 않는다고 판단되는 값들이 우측값이며 이들은 오버로딩으로 &&를 호출한다

    int a = 10;
    int& lvalue = a; // lvalue는 좌측값 참조
    int&& rvalue = 10; // rvalue는 우측값 참조
    //int&& rvalue2 = a; // a는 좌측값이므로, 참조가 불가능.
    //아이러니 하게 lvalue refernce 도 const lvalue reference를 사용하면 우측값을 참조할 수 있다.
    const int& clvalue = 10; // const lvalue reference는 우측값을 참조할 수 있다.

    String&& str = String("Hello"); // str이 유효한 경우에는 String("Hello")는 수명이 연장된다.
                                    // 이렇게 식으로 표현하는걸 pure rvalue(prvalue) 라고 한다.
                                    // 즉 String&& 는 prvalue 표현식이고, 이는 rvalue의 일종이다.
                                    // 다만 str은 따지고보면 lvalue이다.(햇갈리지 말자)
    //String&& str1 = str (error)   // 황당하게 str 은 rvalue reference이지만 다른 rvalue reference에게 묶일수 없다(이제 lvalue가 되었기 때문)
                                    // rvalue = right value = 우측값, lvalue = left value = 좌측값, 유래는 C언어이다.
    std::string("a") + std::string("b") = std::string("c"); // rvalue 이지만 왼쪽에 올수있고,
    // const int a = 10; a = 20     // 이것처럼 lvalue이지만 왼쪽에 올수없는 것들이 있어 옛날의 정의는 희미해졌다.
                                    // 이 이후는 r,lvalue에 대해 좀더 알아보자.
    int a1 = 10;
    int a2 = 20;
    int&& a3 = a1 + a2;             // a1 자체, a2 자체는 오지 못하지만 a1+a2같은 임시객체는 올 수 있다.
    int&& a4 = std::move(a1);       // lvalue 인 a1을 std::move()함수를 사용하면 rvalue안에 집어넣을 수 있다
    foo(10);                        // output : int&& (rvalue)
    foo(a1 + 10);                   // output : int&& (rvalue)
    foo (a1);                       // output : int&  (lvalue)
    foo(std::move(a1));             // output : int&& 
    foo(static_cast<int&&>(a1));    // output : int&& (rvalue 로 강제 캐스팅)
    int a5 = static_cast<int&&>(a1);
    foo(a5);                        // output : int&  (위에서 언급했지만 rvalue reference 는 lvalue이다)
    //std::move함수는 내부를 뜯어보면 static_cast<int&&>() 과 같다. 즉 실제로 이동하는게 아니라 캐스팅을 해주는 것이다.
    // 변수를 rvalue로 캐스팅 한 샘으로 새로 할당하는 과정이 없어서 빠르다. 소유권이 넘어가는 개념이므로 이후에는 변수를 사용하지 못하는게 맞지만... 접근은 된다.
    //하지만 아래같이 변경하면 이이후에 골치아파 지겠지?
    a4 = 200;
    cout << a1 << endl;  // output : 200(move로 인해 소유권이 a4로 넘어감)
    //그냥 std::move로 좌측값을 사용했다면 이이후엔 사용하지 말자.


    //위 swap에서 move를 사용했을때 이동한건, std::move 를 실행함으로써 발생하는 것이 아니라 우측값을 받는 함수들이 오버로딩 되면서 수행되는 것이다. (move 자체가 빠른것도 맞다.)
    // move를 사용하면 이동연산자가 호출되는게 아니라, 우측값을 받는 함수들이 오버로딩 되면서 수행되는 것이다. default 복사생성자는 있지만, default 이동생성자는 없다.
    // 하지만 c++의 container들인 vector, array에는 이동생성자를 구현해 놓았다. 사용자 정의 클래스에선 이동생성자를 구현해주어야 한다.
}