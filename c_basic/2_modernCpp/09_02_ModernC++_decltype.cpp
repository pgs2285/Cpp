#include <iostream>

using std::cout;
using std::endl;

int func(int value)
{
    cout << "(func) Enter Value : " << value << endl;
    return value;
}

int func2(int value)
{
    cout << "(func2) Enter Value : " << value << endl;
    return value;
}

template<typename T>
auto getValue(T& t) -> decltype(t.getValue()) // t.getValue 부분에 auto를 넣으면 된다.
{
    return t.getValue();
}

int& testfunc()
{
    int a =10;
    return a;
}

int main()
{
    //decltype     :     타입을 컴파일 시간에 추론해준다.
    //decltype 형태 :     decltype(타입) 변수명 = 값;
    decltype(1) num = 10;               // int num = 10; 과 같다
    decltype(num)& num1 = num;          // int& num1 = num; 과 같다

    const decltype(num) num2 = 10;      // const int num2 = num; 과 같다
    const decltype(num)& num3 = num;    // const int& num3 = num; 과 같다

    const decltype((num)) num4 = num;   // 좀 특이한 case : const int& num4 = num; 과 같다
                                        // 일단 간단하게 괄호를 치면 reference가 되는 예외상황이 있다고 알아만 두자. (lvalue, rvalue, prvalue, xvalue 등을 공부하다 심화로 알아보자)
    decltype(1 + 2.2f) num5 = 1.1f;     // 이렇게 사용하면 좋지 않지만, 표현식을 넣어주는 경우도 있다. 
    int nums[5];
    decltype(nums) num6 = {1,2,3,4,5};  // int[] 와 같다.

    auto func1 = func;                  // 이전에 auto를 사용하면 함수포인터가 된것을 확인했다.
    func1(10);                          // 함수포인터
    decltype(func) func2;               // 이렇게 사용하면 함수포인터가 아니라 func2라는 함수의 선언이 된다. 즉 func2는 구현이 필요하다. 
                                        // 즉 func의 형식을 따라 func2는 parameter : int, return : int 인 함수를 선언해주어야 한다
    func2(10);                          // 그냥 쓰는거랑 뭐가다르냐? 나도 모르겠다... 찾아봐도 안나와. 그냥 같은데 함수 자체 선언 한번더 해주거로 생각하자.

    decltype(func)& func3 = func2;      // 이건 함수를 참조하는 것 이므로 뒤에 사용할 함수를 선언해주어야 한다. 
    func3(10);                          // func2(10) 과 같다.                        
    
    decltype(func)* func4 = func;       // 위에서 봤던 auto의 예시와 같은 함수 포인터 이다.

    decltype(func(10)) num7 = 10;       // func(10)의 값이 integer이기 때문에 int num7 = 10과 같다. 
                                        // decltype내부의 함수는 그냥 표현식이기 때문에 호출되지 않는다.
    cout << num7 << endl;

    /*          같은 원리로 함수의 return 값이 int&이면 decltype은 int& 가 된다. 함수의 리턴 값을 따른다.                */

    struct Person
    {
        int height;
        float weight;
        int returnHeight()
        {
            return height;
        }
    }person;                             // Person 구조체 생성과 동시에, person이라는 변수를 생성한다.

    decltype(person.weight) num8 = 10;   // 당연히 float num8 = 10; 과 같다. 
    decltype(Person::weight) num9 = 10;  // 위 예시와 동일하다. 굳이 인스턴스화 할 필요는 없다. float num9 = 10; 과 같다.

    decltype(auto) num10 = 30;           // auto와 decltype의 조합. auto num10 = 30; 과 같다.    

    struct Wrapper0
    {
        int value;
        int getValue() const{ return value; }
    };
    struct Wrapper1
    {
        float value;
        float& getValue() { return value; } 
    };

    Wrapper0 w0{ 1 };
    Wrapper1 w1{ 1.0f };
 
    cout << getValue(w0) << endl;       // 예상한 결과 대로 1이 int형으로 나온다
    cout << getValue(w1) << endl;       // float&이 리턴 될것 같지만 실제 auto로 추론하고 return된값은 float이다.
                                        // 이럴때를 대비해서 auto getValue -> decltype(t.getValue()) 로 decltype을 사용해주면 된다.
                                        // reference를 값으로 추론하던 auto와는 다르게 decltype은 reference를 그대로 유지한다.
    getValue(w1) = 20.0f;               // 레퍼런스를 유지하기 때문에 이렇게 사용할 수 있다.



    return 0;
}