#include <iostream>
using namespace std;

class Base{
    public: 
        virtual void func(){ // 가상함수
            cout << "Base" << endl;
        }

};

class Derived : public Base{
    public:
        void func() override{ // 위 func를 오버라이딩 한것
        // override 는 여기서 func가 아닌 fuc등으로 오타를 냈을때 에러를 띄워줌으로써 프로그래머의 의도를 명확히 해줌
        //only virtual member functions can be marked 'override'
            cout << "Derived" << endl;
        }
};

class Derived1 : public Derived{
    public:
        void func() override{
            cout <<"Derived1"<<endl;
        }
};

int main(){
    Derived d;
    Base& b = d;
    Base* bb = &d;
    
    bb -> func(); // 
    b.func(); // (둘다 일반 함수로 생성기준)Derived의 객체를 생성해주어서 Derived가 출력될거 같지만 실제로 Base가 출력된다
    // 위와같은 상황이 의도된것이 아니라면, virtual 함수를 사용해주면 된다.
    Base* bbb = new Derived1;
    bbb->func(); // 제일 위에있는 부모클래스가 virtual이면 그 이후 상속을 받는 함수들도 재정의시 모두 virtual 처럼 작동 (관례상 적어주는게 좋다)
    // 가상함수를 선언하지 않고 클래스 들이 같은 이름을 공유하면(상속으로) Base에 있는 func를 Derived에 있는 func가 가렸다고 표현한다
    return 0;
}