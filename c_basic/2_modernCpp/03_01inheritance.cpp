#include <iostream>
using namespace std;
class Base{
    private: // 똑같이 상속받는 애들한테도 비공개
        
    protected : // 상속받는 객체들한테만 경유
        int _ptcNum;
    public:
        Base(){ // 상속 객체의 생성순서를 알아보자
            cout << "Base" << endl;
        }
        Base(int num) : _num(num){
            cout << "Base (" << _num << ")" << endl;
        }
        int _num;
        void Print(){
            cout << _num << endl;
        }
        void set(int value){
            _ptcNum = value;
        }
        int get(){
            return _ptcNum;
        }
        virtual ~Base(){ // 만약 virtual 을 사용하지 않는다면 Base* bb = new Derived; 를 호출할시 부모의 파괴자만 호출한다.
            cout << "~Base" << endl;
        }

};

class Derived : public Base{ // base 라는 클래스를 상속하는 Derived
    public :
    Derived() : Base(10){ // 만약 특정 생성자를 불러오고 싶다면 뒤에 : 후 불러올 생성자 매개변수 넣어주면 된다
    int _ptcNum = -10;
    //default는 기본생성자 불러옴(매개변수가 없는)
        cout << "Derived" << endl;
    }
    void func(){
        _ptcNum += 10;
    }
    void thisTest(int _ptcNum){
        cout << this -> _ptcNum << endl;
        cout << "여기서 this 는 부모생성자를 가리킨다." << endl;
    }
    ~Derived(){
        cout << "~Derived" << endl;
    }
    // using Base::Base; // 이 클래스에서 생성자 선언을 안해도 부모생성자를 사용하도록 상속시킬수 있다.

    // Derived() = delete; // 상속받은 기본생성자 삭제
};
void func(Base& param){
    param.set(100);
}
int main(){
    Base b;
    Derived d; // Debug 찍어보면 d 객체안에 Base 객체도 포함되어있음
    // base 먼저 생성 후 derived가 생성됨
    // 즉 부모클래스 -> 자식클래스 순으로 생성됨
    {
        // Derived de;
    } // 이 지역을 벗어나면 해제되는데 여기선 반대로 자식 -> 부모순으로 파괴됨
    b._num = 10;
    d._num = 20;
    
    b.Print();
    d.Print();
    d.set(30);
    d.func(); // _ptcNum 10증가
    cout << d.get() << endl;
    d.thisTest(10);

    Base* bb = new Derived; // 부모클래스가 자식클래스를 가리키는 포인터
    //자식이 가진건 부모가 가지고있어 부모의 타입으로 가리켜서  부모함수중의 일부인 get 호출가능
    bb -> get();
    //하지만 자식클래스가 기지고있는 func에는 접근 불가
    // bb -> func();

    // Derived* dd = new Base; 
    // 위 라인의 경우에는 캐스팅 전에는 오류가 뜬다.
    // 다시 71번째 line으로 돌아가서, 부모클래스 형식으로 자식클래스를 가리키는 포인터를 생성할시 virtual이 없으면 부모클래스의 파괴자만 호출하게 된다.
    // 가상함수시간에 자세히한다

    Derived param;
    func(param); // 아까 debug를 찍어서 보았지만 부모클래스의 Base를 가지고 있어 거기에 접근함
    return 0;
}