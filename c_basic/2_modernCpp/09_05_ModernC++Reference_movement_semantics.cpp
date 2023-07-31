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
    //std::move를 시키면 무효화된 객체가 되므로, 이후에는 사용하지 말아야 한다.
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
}