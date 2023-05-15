#include <iostream>
#include <cstring>

using namespace std;

int main(){

    struct EyeSight{
        float left;
        float right;
    };
    //struct (구조체)
    struct Person{
        float height;
        float weight;
        int age;
        char name[10];
        EyeSight eye;
    };
    Person person = {.height = 180.0f, 70.0f, 20, "Jisung",{1.0f,1.2f}}; // 순서대로 입력해야함;
    cout << person.height << " " << person.weight << " " << person.age << " " <<person.name <<"    " << person.eye.left << " " << person.eye.right << endl;
    Person person1 = person ; //구조체는 복사가 가능함 메모리를 통째로 복사하기 때문
    person1.age = 30;

    // 구조체가 메모리를 먹는 방법
    // 1. 구조체의 크기는 구조체 내부의 가장 큰 데이터타입의 크기의 배수가 됨
    //ex
    // float      float       char[10]       short
    //  4           4           10            2 //20으로 떨어지니 추가하지 않음

    // float      short       char[10]       float
    //  4           2(2)           10          4  (2) // 22로 떨어지니 2바이트를 추가로 사용함

    //위처럼 short의 2바이트는 4바이트의 배수를 맞추기위해 (2) 바이트를 사용하지 않는체로 내비두고, 마지막까지 22 -> 24로 맞추기 위해서 (2)바이트를 사용하지 않는다.
    //메모리 layout을 잘 생각해야함. 구조체 내의 변수 순서만으로 변수의 크기가 달라짐

    //struct alignas(16) Person 처럼 배수를 강제로 설정할 수 있다.
    //float     float       short        char[10]      
    //  4           4         2 (6)         10  (12)
    //16의 배수로 강제하면 사용하지 않는 4는 맞추고 2는 사용하지 않는다.         
    

    //union (공용체)
    //구조체와 비슷하지만 메모리를 공유한다.
    //구조체는 각각의 변수가 메모리를 차지하지만 공용체는 가장 큰 변수만 메모리를 차지한다.

    union ID //굳이 두가지 다 사용 할 필요가 없을때.
    {
        int integer;
        float floating;
    };

    struct Product1{
        int idType;
        ID id; // 만약 여기에 int, float를 선언한다면 메모리가 8byte를 차지하게 될것.
    };

    // 즉 구조체와 동일하나 메모리 차지 방식이 다르다. 메모리를 공유하기 때문에 두가지 값을 동시에 넣을 수 없음
    
    
    Product1 product1 = {1, {.floating = 1.34} }; // 구조체와 마찬가지로 순서대로 입력해야함
    cout<< product1.id.floating << " " << endl; // 1 123
    cout << product1.id.integer << endl; // 1065353216 부동소수점을 integer로 표시한값
    

}