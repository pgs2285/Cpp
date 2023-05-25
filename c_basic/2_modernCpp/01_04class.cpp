#include <iostream>
#include "01_04StaticVariable/Person2.h"
#include <functional>

using namespace std;

class Person{
    private:
        float weight;
        float height;
        string name;
    public:
        Person(float weight, float height, string name) : weight(weight), height(height), name(name)
        {

        }
        void loseWeight(float weight){
            this->weight -= weight; // 이런식으로 매개변수와, 이전에 생성한 변수의 이름이 같을때 많이 사용, 여기서 this는 클래스변수를 가리킨다
            if(this->weight < 0){
                this->weight = 0; 
            }
        }

        void skipMeals(float weight){
            this->weight -= weight * 2;

        }
        void DebugLog(){
            cout << "WEIGHT : "<< weight << "HEIGHT : " << height << endl; // 여기서는 this를 안써도 지칭할게 클래스변수밖에 없다.
        }
        float GetBMI(/*  const Person* this  */) const{ // 이렇게 함수뒤에 const를 붙일수 있다.
        // 기존에 매개변수 하나가 더 넘어온다 생각하자(여기서는 Person* this , 만약 const가 붙으면 const Person* this랑 같은것)
            return weight / ((height / 100) *  (height / 100));
        }
        Person ComPareBMI(Person person){
            return (this->GetBMI() > person.GetBMI() ? *this: person);
        }
        void sayMyName(){
            cout << "NAME " << name << " | BMI : " << GetBMI() <<  endl;
        }
        
};

struct Transaction{ // struct 내부에 class를 집어넣어 transaction의 builder 인것을 명확히 해준다.
    const int txID;
    const int fromID;
    const int toID;
    const int value;
    class Builder{
    private:
        int _fromID;
        int _toID;
        int _value;

    public:
        Transaction Build(){
            int txID = _fromID ^ _toID ^ _value;
            return Transaction{txID, _fromID, _toID, _value};
        }
        Builder& setFromID(int fromID){
            _fromID = fromID;
            cout <<"from : " <<this<< endl;
            return *(this);
        }
        Builder &setToID(int toID){ // 참조를 쓰면 메모리에 직접 접근
            _toID = toID;
            cout <<"to : " <<this<< endl;
            return *(this);
        }
        Builder &setValue(int value){ // 참조를 쓰지않으면  메모리에 생성 후 접근
            _value = value;
            cout <<"value : " <<this<< endl; 
            return *(this);
        }

};
};




int main(){
    Person person(63,173, "JS");
    Person person1(77, 168, "SJ");
    // person.skipMeals(5);
    person.DebugLog();
    
    Person tmpPerson = person.ComPareBMI(person1);
    tmpPerson.sayMyName();
    Transaction::Builder txBuilder;// Transaction 구조체 내부에 있는 Builder클래스 호출
    Transaction tx= txBuilder
                .setFromID(1234)
                .setToID(4321)
                .setValue(10)
                .Build();  // this 포인터를 사용한 연쇄호출
    
    cout << tx.fromID << " "<<tx.toID << " "<<tx.value << " "<<tx.txID << endl;
    
    const Person person2(168,70,"jisung");
    person2.GetBMI(); //선언을 const로 했으면 , 클래스내부에 const로 선언한것들만 가져올 수 있음
    // 생략된 this 포인터 매개 변수가 const로 넘어가는데 return 도 const 로 통일되어야 하기 때문이다.
    //일반포인턴 const를 가리킬수 없지만
    //const포인터는 일반포인터를 가리킬수 있다

    Person2 p1;
    Person2 p2;

    p1.print();
    p2.print();
    Person2::print(); // Person2.h 에서 static void print()로 정의해서 가능하다.
    //정적멤버 함수에서는 정적멤버 변수만 접근 가능하다. (static함수는 static 변수만)
    
    void (Person::*fn) () = &Person::DebugLog; // 클래스내 함수 포인터 (멤버함수 포인터)
    // 기존 void *fn (float) = skipMeals; 함수포인터에서 범위지정해준것
    //fn(); //이렇게는 안된다. 기존에 this가 같이 넘어가야하듯이 구체화가필요
    Person personP(168,77,"Pointer");

    (personP.*fn)();
    //함수포인터와 다르게 대입에 &없으면 암시적 형변환을 해주지 않는다.
    typedef void (Person::*FuncType) ();// typedef로 좀더 간단히 써줄수있음(변수명 들어갈 부분에 호출할 이름적어주면 된다)
    // FuncType func = &Person::DebugLog;
    //이후 호출은 똑같음.
    function<void(Person*)> func = &Person::DebugLog; // python self쓰듯이 생각하면 될듯?
    //functional 을 사용해 함수포인터 생성하기
    func(&personP); //클래스 인스턴스 넘겨주기
    //low 포인터보다 성능상에 손해가 있을순 있다.

    void (*fnStatic)() = Person2::print; // static 변수 접근은 일반 함수포인터랑 동일하다 (암시적 형변환 해주는거까지 동일)

    return 0;
}