// RTTI : RunTime Type Information
// type_traits와는 달리 컴파일 타임이 아닌 런타임에 타입을 설정, 확인하는 기능

#include <iostream>
#include <typeinfo>

using std::cout;
using std::endl;

class Parent{
    public:
    virtual ~Parent(){};
};

class Child : public Parent{

};



int main()
{
    Parent* p = new Child();
    cout << typeid(*p).name() << endl; // output : Child
    dynamic_cast<Child*>(p); // dynamic_cast는 런타임에 타입을 변환해주는 기능이다.
    cout << typeid(*p).name() << endl; // output : Child
    // 위 예시들이 런타임에 타입을 확인하는 예시들이다. 즉 RTTI를 사용하는 예시들임 (다운캐스팅)
    //upcasting 하는 경우에는 RTTI를 꺼도 문제가 없다. (g++설정에서 꺼야함)
    // 또한 Parent pp 같이 컴파일 타임에 타입을 확인하는 경우에는 RTTI를 꺼도 문제가 없다.

    /*
        복습
    다운캐스팅은 다형성을 가지는 것만 가능하다
    즉 
    class Parent{};
    class Child : public Parent{}; 
    와 같이 다형성이 없는(부모클래스에 virtual이 없는)경우에는 다운캐스팅이 불가능하다.
    */
    
    return 0;
}