#include <iostream>

using namespace std;

union Variable{
    int i;
    float f;
    double d;
};

struct Person{
    int age;
    float weight;
};

int main() {
    //포인터. 메모리주소를 가리키는 변수
    int num = 147;
    int* pointer = &num; // 단항연산자로 사용하면 주소를 반환함 (이항은 and연산)
    cout << "숫자: "<< num << " 주소: " << pointer << " 역참조: "<<  *pointer << endl;
    *pointer = 100; // 포인터가 가리키고 있는곳의 값을 100으로 바꿈
    cout << num << endl;

    Variable var;
    int* ip = (int*)&var.i; //
    float* fp = (float*)&var.f;
    double* dp = (double*)&var.d;

    //포인터의 변수명은 그 값을 어떻게 다룰까 정함
    // 밑이 예시

    var.i = 1; //유니온이 가르키는 값의 형식으로 저장되어서 다른형식에 접근해 출력하면 다르게 이상하게나옴
    //1. 위 식은 int의 형식으로 저장
    // var.f = 1.0f;
    // var.d = 1.0;
    cout << ip << " " << fp << " " << dp << endl; // 모두 같은 주소를 가리킴
    // 2. 순서대로 int,float,double의 형식으로 읽어서 *ip값만 원하는 값이 나옴
    cout << *ip << " " << *fp << " " << *dp << endl; // 모두 같은 값을 가리킴
    

    // const with pointer
    int num1 = 10;
    const int* ptr1 = &num1;
    // *ptr1 = 20; // 이건 안됨
    ptr1 = &num; // 이건 됨
    // const포인터를 사용할 경우 주소값을 변경 불가능한게 아니라 주소값이 가리키는 값은 변경 불가능하다는 것임

    //However!
    int* const ptr2 = &num1;
    *ptr2 = 20; // 이건 됨
    // ptr2 = &num; // 이건 안됨
    //const의 위치를 주의해서 작성해라~ 그 어느것도 변경하기 싫다면?
    const int* const ptr3 = &num1;// 이러면 둘다 고정

    //배열과 포인터의 관계
    int arr[5] = {1,3,5,7,9};
    int* arrPtr = arr;// 배열이 포인터와 동일하다? NO. 정확히는 배열이 포인터로 암시적 형변환을 한것임 

    cout << arr <<endl; // 1
    cout << &arr <<endl; // 2
    cout << &arr[0] <<endl; // 3
    // 1,2,3 출력값은 동일하다
    // 1,3 은 완전히 동일하다. 배열의 이름은 배열의 0번째 주소를 리턴해준다
    // 2의 타입은 int가 아닌 int[5]이다.
    cout << typeid(arr).name() <<endl; // A5_i // 배열 integer
    cout << typeid(&arr).name() <<endl; // PA5_i // 배열5개인 타입의 integer
    cout << typeid(&arr[0]).name() <<endl; // Pi // 포인터 integer
    //사실이것도 1,3 예외... 1번도 타입 아이디로 넘어갈때는 Pi가 나오는데 typeid의 예외사항이다
    //원래 C++이 예외랑 복잡한게 많다
    //그냥 배열의 이름은 배열의 0번째 주소를 리턴해준다는것만 일단 기억해두자.

    cout << arrPtr[0] << " " << arrPtr[1] << endl; //이런거도 된다
    cout << arrPtr + 1 << endl; // 포인터 타입의 크기만큼 더해줌
    cout << *(arrPtr + 1) << endl; // a[1]의 값 가져옴
    cout << *(arrPtr) + 1 << endl; // a[0] + 1

    cout << sizeof(arr) << endl; // 20
    cout << sizeof(arrPtr) << endl; // 64비트에서는 8 32비트에서는 4

    cout << "---------------------" << endl;
    cout << *arrPtr << endl; // 1
    arrPtr++;
    cout << *arrPtr << endl; // 3
    cout << arrPtr[0] << endl; // 3
    

    //물론 arr++은 안된다~ 되면 햇갈려서 죽을듯
    //위에서 배운듯이 만약 포인터의 증가를 막고싶으면 int* const arrPtr

    //포인터와 문자열의 관계

    char name[] = "jisung";
    char* namePtr = name;
    namePtr[1] = '!'; // 이런식으로 문자열을 변경할 수 있다.

    cout <<  namePtr << endl; // cout 특성상 char형은 널문자 만날때까지 출력
    

    const char* namePtr2 = "jisung"; // 위에 namePtr기본 포인터와 같음
    cout << (void*) namePtr2 << endl; // 이렇게 형변환 하면 주소나옴 

    for(int i = 0; i < 3 ;i++){ 
        // int num // 자동할당 , 범위 벗어나면 메모리에서 내려감 (stack이란 유형에 할당되어 자동해제됨)
        static int num = 0;// 정적 메모리 할당, 프로그램이 실행되는 동안 메모리에 계속 존재
        cout << num << "  ";
        num++;
    }
    int *pNum = new int; // 동적 메모리 할당 (heap에 할당되어 남아있는다)
    *pNum = 10;
    delete pNum; // 메모리 해제 (해제안하고 계속 생성만하면 자동해제가 아니므로 계속 누적되어 쌓여감)
    // 위 int *pNum = new int를 좀더 자세하게보면, stack영역에 자동할당인 pNum이 생기고, heap영역에 동적할당인 new int를해준거 그리고 이 주소값을 
    // stack영역인 pNum에 넣어준것임
    while(--num1){
        int* pNum = new int; 
        cout << pNum << endl; // 조금 위험한 코드, delete를 해주지 않는다면 pNum에는 계속해서 다른 메모리 주소값이 나옴
        delete pNum;
        //delete후 다시 new int를 해주면 이전에 있던 메모리 주소값을 사용하게됨(즉 낭비없음)
    }
    //동적할당
    cout << "생성할 배열 크기를 입력하세요:";
    int size;
    cin >> size;
    int* pArr = new int[size] {1,2,3}; // 배열의 크기를 동적할당으로 받을 수 있음, 저렇게 미리 초기화도 가능
    for(int i = 0; i < size; i++){ // 다만 동적할당 받은 범위보다 미리 초기화한 범위가 크면 bac_alloc 에러가 남
        pArr[i] = i;
        cout << pArr[i] << " "; 
    }
    cout << *(pArr + 2) << endl;
    // 배열을 가리키는 포인터는 다음과 같이 해제하자
    delete[] pArr;


    // 구조체 포인터
    Person* person = new Person{ 20, 70.0f }; // heap영역에 할당되는 Person에 주소값을 붙여준거

    cout <<(*person).age << " " << (*person).weight << endl; // 이렇게 주소값을 역참조해서 가져오는게 정석이지만
    cout << person->age << " " << person->weight << endl; //포인터의 member를 바로 가져올수있는 ->연산자도 있다.

    Person* persons[2] = {
        new Person{ 20, 70.0f },
        new Person{ 30, 80.0f }
    };

    for(Person* p : persons){ //원래 *쓰기전에는 값을 불러오는것이라 값이 바뀌지 않았었는데, 이건 포인터의 주소값을 가져오는것이라서 값이 바뀜
        p->age = 10;
        cout << p->age << " " << p->weight << endl;
    }

    

    return 0;
}


    /*
    cout과 같은 출력 함수는 문자열을 출력하기 위해 특별히 오버로드(overload)되어있어서,
     문자열의 주소 대신, 해당 주소에서부터 null 문자가 나올 때까지의 문자열 내용을 출력하게 됩니다.
     따라서, 배열의 첫 번째 요소의 주소 대신, 배열의 첫 번째 요소에서부터 null 문자가 나올 때까지의 문자열 내용이 출력되는 것입니다.


     char* ptr = "Abc"는 문자열 상수 리터럴("Abc")의 주소를 ptr이 가리키도록 합니다. 
     이 경우 ptr은 문자열 상수 리터럴의 메모리 주소를 가리키기 때문에, 해당 문자열을 변경할 수 없습니다.


C++11 표준 이전의 버전에서는 문자열 상수 리터럴이 const char* 타입으로 해석되어 이러한 코드가 컴파일되지 않았습니다. 
따라서 이전 C++ 표준에서는 문자열 상수 리터럴을 const char*로 다루는 것이 올바른 방법이었습니다.


C++11부터는 문자열 상수 리터럴을 수정 가능한 문자열로 취급하기 위해, 문자열 상수 리터럴이 저장될 메모리 영역이 변경되었습니다.
 이 때문에 C++11 이후 버전에서는 문자열 상수 리터럴의 타입이 const char*가 아닌 char[](배열)로 해석되며,
 이러한 방식에서도 이전 버전과 동일하게 문자열 상수 리터럴은 수정할 수 없습니다.


따라서 이제는 char* ptr = "Abc"와 같은 코드가 컴파일됩니다.
 그러나 ptr이 가리키는 문자열 내용을 수정할 수 없기 때문에 이를 수정하면 프로그램이 예기치 않게 종료될 수 있습니다. 
 따라서 문자열 상수 리터럴을 가리키는 포인터를 사용할 때에는, 해당 포인터가 가리키는 문자열을 수정하지 않도록 주의해야 합니다.
    */
