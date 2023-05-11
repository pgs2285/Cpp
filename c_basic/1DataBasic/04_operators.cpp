#include <iostream>
#include <compare>
using namespace std;

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

    semi colon같은 sequence point가 등장하기 전에 모든 연산이 종료되어야함
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
    cout << (1 <=> 1.0) == partial_ordering::equivalent << endl; // true
    cout << (1 <=> 1.0) == strong_ordering::equal << endl; // false;

    //추후 자세히 다룰 예정

    //partial ordering::equivalent - 수만 같으면됨
    //strong ordering::equal // 변수 타입까지 같아야함
    
    
   
}