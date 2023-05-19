#include <iostream>
#include <cstring>
#include <array>

using namespace std;

enum color : int64_t{ // 범위가 없는 열거형태, 크기 지정 가능
    red,
    green,
    blue,
    alpha = 255, // 명시적으로 지정도 가능하다
    SIZE
    //순서대로 0,1,2,3
};

// enum color2{ // 범위가 없는 열거형태 // 이런 중복선언이 불가능하다
//     red,
//     green,
//     blue,
//     alpha = 255, // 명시적으로 지정도 가능하다
//     SIZE
//     //순서대로 0,1,2,3
// };
enum struct textAttrib{ // 범위가 있는 열거형태 C++11부터 지원 // enum class도 가능
    bold = 1,
    italic = 2,
    underline = 4,
    strikethrough = 8
    // 0001, 0010, 0100, 1000
};


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

    //열거형은 맨위 에 선언한거 같은 enum형
    int textA = 0; 
    // textA |= textAttrib::bold; // bold형은 enum형인 0001 (1)  
    //범위가 있는것들은 위와같이 연산이 불가함
    textA |= (int)textAttrib::italic; // italic형은 enum형인 0010 (2)
    textA |= (int)textAttrib::underline; // underline형은 enum형인 0100 (4)
    textA |= (int)textAttrib::strikethrough; // strikethrough형은 enum형인 1000 (8)
    //위와같이 캐스팅을 해주어야함
    cout << textA << endl;
    cout<<"ITALIC:" << ((textA) & (int)textAttrib::italic ? true : false); 

    // 일반 enum은 그냥 연산 가능
    // 범위가 없는 enum이 더 편해보일 순 있지만, 범위가 있는 enum이 더 명확함.
    
    textAttrib tAttrib = textAttrib::bold; 
    color Color = color::red;

    //위 예시처럼 선언도 가능하긴함


    //std array
    //<array> header파일 가능
    array<int, 10> arr = {1,2,3,4,5,6,7,8,9,0}; // 이런식으로 선언가능
    array<int,10> arr2 = {1,2,3,4,5,6}; // 일반 배열과 다를게 없다
    
    for(int i = 0; i < arr.size(); i++){
        cout << arr[i] << " ";
    }
    //일반 배열과 다른게 뭐냐?
    // 여러가지 기능을 제공한다
    cout << "\n" <<arr.at(3) << endl; // 일반 array접근과 다르게 at을 사용하면 범위에 벗어날시 쓰레기값이 아닌 오류를 반환한다
    cout << arr.size() << endl;// .size()를 통해 배열의 크기를 알 수 있다.
    
    // int arr2[10];
    // cout << size(arr2) << endl; // 물론 c++17 부터는 이렇게 일반배열도 사이즈를 쉽게 알 수 있긴허다

    // 그밖에 std-array이는 다음과 같은 함수를 가지고 있다
    cout << "맨 앞:" <<arr.front() << " 맨 뒤:" << arr.back() <<  endl;// front가장 앞에있는걸 가져옴, back 가장 뒤에있는걸 가져옴

    arr.swap(arr2); //배열 두개를 바꾸어줌 크기가 같아야함
    for(int i = 0; i < arr.size(); i++){
        cout << arr[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < arr2.size(); i++){
        cout << arr2[i] << " ";
    }
    //기존 일반 배열과는 다르게
    arr = arr2; // 이런식으로 대입이 가능하다
    if(arr == arr2 ){ // == 연산자도 지원한다
        cout << "같다" << endl;
    }else if(arr > arr2){ //첫번째 비교해서 하나라도 더 크면 크다고 판단
        cout << "arr이 더 크다" << endl; 
    }


    //배열 순회방법
    for(int num : arr){ // 이건 std-array가 아니더라도 사용가능
        cout << num << " ";
    }
    cout << endl;
    //구조체도 쌉가능
    
    Person persons[2] = {{180.0f, 70.0f, 20, "Jisung1",{1.0f,1.2f}}, {180.0f, 70.0f, 20, "Jisung2",{1.0f,1.2f}}};
    cout << &persons << endl; // 배열의 주소
    for(Person person : persons){
        person.height = 190.0f; // 이런식으로 순회하면 값은 변경되지 않음
        cout << person.height << " " << person.weight << " " << person.age << " " <<person.name <<"    " << person.eye.left << " " << person.eye.right << endl;
        cout << &person << endl; // 두 주소가 같음 (복사본) / 위에서 찍어본 배열의 주소랑도 다름 / 값으로 참조
        //바뀌네?
        /*
        C11에서는 range-based for loop에서도 값이 변경되지 않는 것이 일반적으로 알려져 있습니다.
        그러나 이는 C++11 표준에서는 명시되어 있지 않은 부분이기 때문에 컴파일러마다 다르게 구현될 수 있습니다.
        MSVC에서는 오류뜬다.
        */
    }

    for(Person& person : persons){  //복사가 아닌 원본을 나타내주려면 & 를 붙여줘야함(참조자)
        person.height = 200.0f; // 이런식으로 참조를 사용하면 값이 변경됨
        cout << person.height << " " << person.weight << " " << person.age << " " <<person.name <<"    " << person.eye.left << " " << person.eye.right << endl;
        cout << &person << endl; // 두 주소가 값이 다름 // 위에서 찍어본 배열의 주소랑 시작이 같음 / 주소로 참조
    }

}