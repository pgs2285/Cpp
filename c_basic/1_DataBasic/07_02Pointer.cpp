#include <iostream>
#include <vector>
using namespace std;

int main(){
    //null pointer
    int* p = nullptr; // 처음에 선언할때 nullptr로 선언해주는것이 안전하다.
    // c++ 11이전에는 NULL이라는 매크로를 사용했었다. NULL = 0
    // nullptr 은 nullptr_t라는 타입이다 (값이 nullptr딱 하나밖에 없다.)
    
    //void pointer
    //형이 없음을 의미하는 포인터
    void* ptr = nullptr;
    int *a = new int;
    //기존의 int,float,double등은 각자 자신들이 포인터(주소) 의 값을 어떻게 처리할지 정해져있지만
    //void포인터는 어떤형태도 받을수 있다. 하지만 역참조를 할수 없다.(즉 주소값만 저장가능, 어떻게 메모리를 다룰지 선언이 안되어서)
    ptr = a;
    // cout << *ptr << endl; //불가능하다
    cout << (int*)ptr << endl; // 가능하다 (바꿀 형태를 명시해 주었기 때문)
    // C스타일의 할당에 malloc이라는게 있다. malloc의 return값이 void* 이다.

    void *ptr2 = malloc(sizeof(int) * 4);// C++에는 새로추가된 new쓰자
    int *ptr3 = (int*)ptr2;
    ptr3[0] = 1;
    cout << ptr3[0] << endl;
    free(ptr2); // C스타일의 할당에 free가 있다. C++에는 새로추가된 delete쓰자
    // free(ptr3);



    //std vector
    //std array 같은 경우는 정적배열을 사용하는 c++ style의 배열
    //std vector = #include <vector>

    cout << "Vector 사이즈를 입력하세요:";
    int size;
    cin >> size;
    vector<int> vec(size,10); // 입력받은 size의 크기만큼 vector를 생성하고 10으로 초기화한다
    vec.resize(5); // 5로 사이즈를 줄인다. (뒤에있는 값들은 삭제된다)
    vec.resize(10, 5); // 10으로 사이즈를 늘리고 새로생긴 5개의 공간을5로 초기화한다.
    for(int i = 0; i < vec.size(); i++){ // 초기화를 안해줘도 기본값은 0 임
        cout << vec[i] << " ";
    }

    vector<int> vec2;
    cout << vec2.size() << endl; // 0
    vec2.push_back(10); // 뒤에 10을 추가한다.
    vec2.push_back(20); // 뒤에 20을 추가한다.
    cout << vec2.size() << endl; // 2
    vec2.pop_back();
    cout<< vec2.size() <<endl;
    cout<< vec2.data() << endl; // 주소값을 반환한다.
    for(int i = 0; i < vec.size(); i++){ // 초기화를 안해줘도 기본값은 0 임
        cout << i << "번째 Number 의 주소 : " << &vec[i] << endl;
        
    }
    //std array처럼 .front, .back, .at 등 많은 함수를 지원한다

    //reference
    int num1 = 10;
    int& num2 = num1;
    num2 = 20;
    cout << num1 << endl; // 20
    // 레퍼런스 와 포인터는 형태만 다를뿐 동일하다
    // int* a = &b; cout << *a << endl; 
    // int& a = b; cout << a << endl;
    // 위 두코드를 assembly로 변환해보면 값이 완전히 동일하다
    // 사용성 편하라고 만들어 둔것. 추후 연산자 오버로딩등애서..




}
