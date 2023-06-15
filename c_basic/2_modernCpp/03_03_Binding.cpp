#include <iostream>

using namespace std;

class A{

public:
    int _num;
};

class B : public A{
};


A operator+(const A& a1,const A& a2){
    cout << "Operator A" << endl;
    A a;
    a._num = a1._num + a2._num;
    return a;
}

B operator+(const B& b1, const B& b2){
    cout << "Operator B" << endl;
    B b;
    b._num = b1._num + b2._num;
    return b;
}

int main(){
    //정적바인딩 : 실행전에 무언가를 결정이 되었을대 (ex 오버로딩)
    B b1,b2;
    b1._num = 10; 
    b2._num = 20;
    
    A a = b1 + b2;
    A& a1 = b1;
    A& a2 = b2;

    A aa = a1 + a2; 
    //이 두가지가 오버로딩이다. 매개변수에 따라 같은 함수명이라도 다른 반환값, 함수를 실행하는것이다
    //오버로딩은 정적바인딩으로 변수의 타입만 보고 어디로 갈지 결정하기 실제로 가리키는것에 상관하지 않는다./ 빌드해서 어셈블리 코드를 열어보면 어떤것을 어떤것을 호출할지 결정되어있음 

    //동적바인딩 : 런타임 도중 무엇인가가 결정이 되었을때 (ex 오버라이딩)
    //오버라이딩은 03_02ExampleVirtual_WithTextGame.cpp참조 (부모에게 상속받은 함수를 변경하는 것이 오버라이딩이다)

}