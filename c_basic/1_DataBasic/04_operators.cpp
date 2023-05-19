#include <iostream>
#include <compare>
#include <cmath>
using namespace std;
int num = 0;
int main(){
    //연산자 -> <- 방향만 조심 예를들어 -+-+1 같은 단항연산자 오른쪽에서 왼쪽으로, 이항연산자는 왼쪽에서 오른쪽으로 사이트참조 : https://en.cppreference.com/w/cpp/language/operator_precedence

    //주의할점
    int num = 10;
    cout << ++num + num++ << endl;
    cout << num << endl;

    printf("%d %d\n", ++num, num++);
    printf("%d\n", num);
    /*
    04_operators.cpp:10:13: warning: multiple unsequenced modifications to 'num' [-Wunsequenced]
    cout << ++num + num++ << endl;
            ^          ~~
    04_operators.cpp:13:23: warning: multiple unsequenced modifications to 'num' [-Wunsequenced]
        printf("%d %d\n", ++num, num++);
    실행은 되지만 컴파일러마다 반환값이 다름

    semi colon,||,&& 같은 sequence point가 등장하기 전에 모든 연산이 종료되어야함
    이러한것은 컴파일러마다 반환값이 다르기때문에 사용 X
    documetation에 '인수사이의 실행순서가 보장되지 않음' 이라고 명시되어있음
    즉 한 식에서 한 변수가 두번이상 변경하면 안됨
    */

   //비교연산자 - ==, >=, <= 같은것들. 
   //C++20 에서 한가지가 추가됨 <=> 특이하게 반환값이 true/false 가 아님
    // 만약 a<=>b 라면 a와b의 관계를 묻는형식 
    cout.setf(ios::boolalpha); // true/false로 출력

    // 1 <=> 1 은 왼쪽에 있는 숫자와 비교해서 -1,0,1 중 하나를 반환
    // 같으면 0, 왼쪽이 크면 0보다 큰값, 오른쪽이 크면 0보다 작은값 반환 (우주선 연산자라고함)
    //우주선 연산자는 문맥에 따라서 std::strong_ordering, std::weak_ordering, std::partial_ordering를 리턴

    // cout << (1 <=> 1.0) == partial_ordering::equivalent << endl; // true
    // cout << (1 <=> 1.0) == strong_ordering::equal << endl; // false;

    //추후 자세히 다룰 예정

    //partial ordering::equivalent - 수만 같으면됨
    //strong ordering::equal // 변수 타입까지 같아야함
    
    //논리 연산자 && ||,
    if(true || false && false){ // &&가 ||보다 우선순위가 높음
        cout << "true" << endl;
    }
    //&& 연산의 경우에는 좌항이 false면 우항은 실행조차 하지 않는다. 반면 ||경우 좌항이 true면 우항은 실행조차 하지 않는다.
    bool a = printf("") && printf("123"); // printf는 출력한 문자열의 길이를 반환함 즉 아무것도 나오지 않음
    bool b = printf("1") || printf("abc"); // 1만 출력되고 abc는 출력되지 않음

    // bitwise 연산자 - &, |, ^, ~, <<, >>
    // ~ not 
    cout << ~0 << endl; // -1
    // 00000000000000000000000000000000 -> 11111111111111111111111111111111 (-1)

    // & | 는 각각 and, or 연산자, 같은 숫자만.
    // boolean 은 1byte, 8bit로 이루어져있음 하지만 32개의 bool배열을 만들면 메모리 낭비가 심하다 생각될때
    uint32_t boolCheck = 0u; // 00000000000000000000000000000101 나중에 |로 비트를 하나씩 채워주면 됨

    boolCheck |=(int)pow(2,0); // 0번째 비트를 1로 채움
    boolCheck |=(int)pow(2,2); // 2번째 비트를 1로 채움

    string str = (boolCheck & (int)pow(2,0)) == (int)pow(2,0) ? "true" : "false"; //0번째 비트가 1이니 true
    cout << str << endl; // true
    str = (boolCheck & (int)pow(2,1)) == (int)pow(2,1) ? "true" : "false"; // 1번째 비트가 0이니 false
    cout << str << endl; // false
    str = (boolCheck & (int)pow(2,2)) == (int)pow(2,2) ? "true" : "false"; // 2번째 비트가 1이니 true
    cout << str << endl; // true
    str = (boolCheck & (int)pow(2,0) + (int)pow(2,1)) > 0 ? "true" : "false"; // (0,1 번째 비트중 하나라도 1인가? )0번째 비트가 1이니 true
    cout << str << endl; // true
    str = (boolCheck & (int)pow(2,0) + (int)pow(2,1)) == (int)pow(2,0) + (int)pow(2,1) ? "true" : "false"; //(0,1 번쨰 비트가 둘다 1인가?) false
    cout << str << endl; // false
    boolCheck &= ~(int)pow(2,2); // 2번째 비트만 0으로 바꿈
    cout << boolCheck << endl; // 1
    //이런식으로 | & 를 사용해 메모리를 절약하며 bool형과 비슷한걸 만들순 있다.... 이정도로 메모리를 절약해야할 일이 있을까?
    
    // ^ xor 연산. ^연산 끼리는 교환법칙 성립

    int num1 = 1, num2 = 2, num3 = 3, num4 = 2, num5 = 1;
    cout<< (num1 ^ num2 ^ num3 ^ num4 ^ num5)<<endl; // 3 괄호 꼭써야함!!! 연산자 우선순위때문에 엮임
    // 위 식은 교환법칙으로 하면 num1 ^ num5 ^ num2 ^ num4 ^ num3 이렇게 됨
    //즉 0^0^3이므로 3


    //shift 연산자
    //이전에 이미 cout <<. cin >> 하면서 써본적이 있다. 같은 모양 하지만 위 두가지의 경우 override해서 사용하는 것이라 살짝 다름
    cout << (1<<3) << endl; // 0001 -> 1000 (8)
    cout << (8>>1) << endl; // 1000 -> 0100 (4)
    //만약 15 >> 3 일시 1111 -> 0001 로 자르고 버림

    //기타연산자.
    // 1. 조건연산자
    // (조건식) ? (참일때 실행) : (거짓일때 실행) // 실행때의 타입을 맞춰줘야 함
    num1 > num2 ? cout<< "num1 > num2" << endl : cout << "num1 < num2" << endl;
    //cout 의 return은 자기자신이라 위처럼 사용가능한것.
    // 2. sizeof 연산자 크기를 반환함
    cout << sizeof(num1) << endl; // 4
    // 3. 범위 연산자
    // :: 특정것의 안에있는것을 엑세스할때 사용함.
    num = 10;
    cout << ::num << endl; // ::num = 만약 외부, 지역변수 num이 모두 선언되었을시 전역변수 num을 사용한다.

    //4. 형변환 연산자
    // 암시적, 명시적으로 나뉨.
    // 암시적 형변환은 자동으로 형변환을 해주는것
    // 명시적 형변환은 (형변환할 타입)을 앞에 붙여줌
    unsigned uI = 1; // unsigned int -> int 로 암시적 형변환
    float f= 1.0; // double -> float로 암시적 형변환
    cout << (int)'a' <<endl; // 명시적 형변환

    //casting은 총 4가지 형식이 존재한다
    //1. static_cast : C 스타일 캐스터와 똑같은 의미와 형변환 능력을 가지고 있는, 가장 기본적인 캐스트 연산자
    //2. dynamic_cast : 상속 계층 관계를 가로지르거나 다운캐스팅시 사용되는 캐스팅 연산자
    //3. const_cast : 상수성(const)을 없애는 데 사용된다.
    //4. reinterpret_cast :  int* 에서 char* 처럼 포인터 형변환에 사용
    //나중에 포인터 및 클래스할때 다시한번 공부한다
   
}