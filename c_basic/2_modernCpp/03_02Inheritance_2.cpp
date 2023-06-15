#include <iostream>
using namespace std;

class Base{
    public: // 이러한 가상함수는 인스턴스 생성시 가상함수 포인터들이 가리킨다.
    // 즉 가상함수 테이블에 없는 애들은 그냥 자기 클래스에 맞는함수 실행, 가상함수 테이블에 있으면 그것이 가리키는 함수를 실행시킴
        virtual void func(int a, int b){
            cout << "shadow 2" << endl;
        }
        virtual void func(int a){
            cout << "Shadow " << endl;
        }
        virtual void func(){ // 가상함수
            cout << "Base" << endl;
        }

        virtual ~Base(){
            cout << "DESTROYED Base" << endl;
        }
        int a;

};

class Derived : public Base{
    private:
    // int a; 가리는 현상 발행
    using Base::a; // shadow방지하고 위에거를 여기선 private로 선언했기때문에 접근도 불가. a라는 변수도 메모리상 하나만 생성된다.
    public:
        using Base::func;
        void func() override{ // 위 func를 오버라이딩 한것
        // override 는 여기서 func가 아닌 fuc등으로 오타를 냈을때 에러를 띄워줌으로써 프로그래머의 의도를 명확히 해줌
        //only virtual member functions can be marked 'override'
            cout << "Derived" << endl;
        }
        virtual ~Derived(){
            cout << "DESTROYED Derived" << endl;
        }
};

class Derived1 : public Derived{
    public:
        void func() override{
            cout <<"Derived1"<<endl;
        }
};

class Shape{
    public:
        virtual float getArea() const = 0; // virtual (함수명) = 0; 은 순수 가상함수 선언.
        //오버라이딩 하기 전에는 인스턴스 생성 불가능하다.
  
        
};

class Circle : public Shape{
    private:
    float _radius;

    public:
    
    Circle(float radius)
        : _radius(radius)
    {
    }

    virtual float getArea() const override {
        return _radius * _radius * 3.14f;
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
    // 가상함수를 선언하지 않고 클래스 들이 같은 이름을 공유하면(상속으로) Base에 있는 func를 Derived에 있는 func가 가렸다고 표현한다.(동일 함수명 부모의 함수에 접근 X)
    Base* base = new Derived;
    // 소멸자를 virtual 로 선언하는 이유도 이와같다.
    // virtual 이 없으면 선언한 타입만 보고 호출할 객체를 결정한다 (여기서 Base*)
    // virtual을 써주면 실제 base가 어떤 타입을 가리키고있는지를 보고 호출한다.
    // 위처럼 가리는 현상을 막아주고 싶으면 using 클래스명::함수명 으로 가져와주면 가능.
    d.func(); // 이건되지만
    d.func(1); // 원래는 쉐도우(가리는현상)때문에 불가능함, 하지만 using 클래스명::함수명 을 사용해주어서 접근 가능하다
    d.func(1,2); //이거도 마찬가지
    //using은 함수 뿐만 아니라 변수 shaow를 막기위해서도 사용한다.

    //순수 가상함수(추상함수) 
    // 만약 Shape클래스를 만든다 가정한다. Shape 클래스에는 도형의 넓이를 구하는 함수가 포함되어 있는데 도형이 구체화되기전까지(상속해서 구현하기 전까지) 만들수 없음
    //오버라이딩 하기 전에는 인스턴스 생성 불가능하다.

    Circle c(3.0f); // circle 에 getArea가 구현되어 있지않으면 unimplemented pure virtual method 'getArea' in 'Circle' 오류가뜬다
    cout << c.getArea() << endl;
    // Shape s; 부모클래스인 Shape는 순수 가상함수 때문에 객체로 만들지 못하지만, 포인터, 참조로 활용가능
    Shape* s = &c;
    Shape& ss = c;
    return 0;
}