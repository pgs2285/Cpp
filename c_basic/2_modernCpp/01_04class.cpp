#include <iostream>

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
        float GetBMI(){
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
            return *(this);
        }
        Builder& setToID(int toID){
            _toID = toID;
            return *(this);
        }
        Builder& setValue(int value){
            _value = value;
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
    

    return 0;
}