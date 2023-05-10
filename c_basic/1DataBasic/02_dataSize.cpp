#include <iostream>
#include <numeric>
#include <cfloat>
using namespace std;

int main(){
    int Integer = 0;
    long LongNum = 0;
    int *Pointer = nullptr;

    int16_t i16 = 0; // 인트형 16비트(2바이트)로 고정
    int32_t i32 = 0; // 이와같은 고정형은 암호화와 같이 비트수에 따라 결과값이 달라 질수 있는경우에 많이 사용한다.
    int64_t i64 = 0; // long long 과 동일
    uint16_t ui16 = 0; // 부호 없는 정수형 32,64도 동일

    char a = 'a';
    char16_t c16 = 'a';

    unsigned int ui = 11u; // 부호 없는 정수형 , 뒤에 u는 unsigned int형임을 나타냄(뒤에 u를 붙임으로서 타입을 명시해줌, 즉 타입변환이 일어나지 않음)
    unsigned long long ull = 10uLL; //이런식으로 타입 추가 가능


    cout << "Size of Integer: " << sizeof(Integer) << endl;
    cout << "Size of LongNum: " << sizeof(LongNum) << endl;
    cout << "Size of Pointer: " << sizeof(Pointer) << endl;
    cout << "Size of i16: " << sizeof(i16) << endl;
    cout << "Size of i32: " << sizeof(i32) << endl;
    cout << "Size of i64: " << sizeof(i64) << endl;
    cout << "Size of char: " << sizeof(a) << endl;
    cout << "Size of char16: " << sizeof(c16) << endl;


    cout << "-------------------구분선----------------------" << endl;
    cout << "numeric limit of uint16 " << numeric_limits<uint16_t>::max() << endl;
    cout << "numeric limit of uint32 " << numeric_limits<uint32_t>::max() << endl;
    cout << "numeric limit of uint64 " << numeric_limits<uint64_t>::max() << endl;
    cout << "numeric limit of int16 " << numeric_limits<int16_t>::max() << endl; // 맨앞에 비트는 부호를 나타내는데, 2의보수를 통해 음수표현(반전 후 1더하기)
    cout << "numeric limit of int32 " << numeric_limits<int32_t>::max() << endl;
    cout << "numeric limit of int64 " << numeric_limits<int64_t>::max() << endl;
    cout << "numeric limit of long " << numeric_limits<long>::max() << endl;
    cout << "numeric limit of short " << numeric_limits<short>::max() << endl;
    
    cout << "-------------------구분선----------------------" << endl;
    float f = 3.141592f; // 소수점의 기본형은 double이라 f 로 형을 표시해 주어야함.
    // 부동소수점은 부호/지수부/가수부로 나뉘어져 있음
    // 부호부는 1비트, 지수부는 8비트, 가수부는 23비트로 구성되어 있음
    // 부호부는 음수는 1 양수는 0
    // 지수부는 127을 0으로 가정하여 127 + (지수부의 수) (음수도 표기하기 위함)
    // 가수부는 소수점 아래를 전부 집어넣음

    float num1 = 0.231689453125f; 
    unsigned int num0;
    memcpy(&num0, &num1, sizeof(float)); // memcpy는 메모리를 복사하는 함수. memcpy(복사할 메모리 주소, 복사될 메모리 주소, 복사할 메모리 크기)
    cout << num0 << endl;
    cout << num1 << endl;
    // num 0 의 output은 1047347200가 되는데 이는 부동소수점으로 표현된 전체 비트를 int형으로 집어넣은것. 즉 32비트가 찬 int형이 되어버림

    float num2 = 0.1f;
    float num3 = 0.02f * 5.0f;
    cout<<"== 사용하기:";
    if (num2 == num3) // 0.1, 0.02 등은 부동소수점으로 표현이 안되어 유사값이 들어있다. ==말고 epsilon이나 고정소수점(decimal)사옹
        cout << "true" << endl;
    else
        cout << "false" << endl;

    cout<<"epsilon 사용하기:";
    if(fabsf(num2 - num3) <= FLT_EPSILON) // fabsf는 float형의 절대값을 반환하는 함수
        cout << "true" << endl;
    else
        cout << "false" << endl;

    //epslion은 0보다 큰 가장작은수이다. 하지만 오차값은 누적되니 완벽한 방법은 아님
}

/*
out put
Size of Integer: 4
Size of LongNum: 8
Size of Pointer: 8
Size of i16: 2
Size of i32: 4
Size of i64: 8
Size of char: 1
Size of char16: 2
-------------------구분선----------------------
numeric limit of uint16 65535
numeric limit of uint32 4294967295
numeric limit of uint64 18446744073709551615
numeric limit of int16 32767
numeric limit of int32 2147483647
numeric limit of int64 9223372036854775807
numeric limit of long 9223372036854775807
numeric limit of short 32767


*/