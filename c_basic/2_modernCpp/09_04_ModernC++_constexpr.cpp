//constexpr (상수 표현식)  :  컴파일 시간에 평가되는 표현식

#include <iostream>
#include <type_traits>

constexpr int fibo(int num)
{
    return num <= 1 ? num : fibo(num - 1) + fibo(num - 2);
    // c++ 11 까지는 constexpr 함수 내부에서는 if문을 사용할 수 없었다. return 또한 한번만 사용할 수 있었다.
    // 이후 버전에서는 조금 완화 되었다. if문을 사용할 수 있게 되었고, return도 여러번 사용할 수 있게 되었다.
}

struct Item
{
    const int power;
    constexpr Item(int power) : power(power) {}
    constexpr Item operator+(const Item& item) const
    {
        return Item(power + item.power);
    }
};

template <typename T>
auto getValue(T t)
{
    if (std::is_pointer<T>())                   //constexpr을 붙이지 않으면 컴파일 에러가 발생한다.
                                                //그이유는 템플릿은 컴파일 타임에 .구체화를 할때 컴파일 단계에서 if문 내부조건을 수행하는데, 이때 Int형은 pointer가 아니므로 오류가 발생한다.
                                                //즉 is_pointer<T>()가 컴파일 타임에 평가되어야 하는데, constexpr이 없다면 인자가 들어올때 런타임에 판독되므로 constexpr을 붙여줘야 한다.
        return *t;
    else
        return t;
}

int main()
{
    constexpr int value = fibo(10);                 // value : 6765
                                                    //컴파일 타임에 처리되어야 해서, int num = 10; fibo(num); 이렇게는 사용할 수 없다. (변수는 런타임에 처리되기 때문)
    std::cout << value << std::endl;
    int values[value];                              // 만약 컴파일 타임에 평가되지 않는다면, 에러가 발생한다.(에러 X 이므로, 컴파일 타임에 평가된다.)
    // 원래 constexpr int value = fibo(20); 이렇게 선언해야 컴파일 시간에 평가되는데, 
    // 현재 g++ 컴파일러에서는 그냥 되는거 같다.
    /*
        const vs constexpr
        const : 런타임에 읽기 전용
        constexpr : 컴파일 타임에 읽기 전용
        상수 처리되는 것은 둘 다 같다.
        재미있는건 constexpr은 recursive를 단계가 너무 많아지면 컴파일 에러를 띄운다.(recursive가 안되는건 아니다.)
    */
    constexpr Item item1(10);
    constexpr Item item2(20);
    constexpr Item item3 = item1 + item2;           // constexpr은 컴파일 타임에 평가되어야 하므로, 이렇게 사용할 수 있다.
    int nums[item3.power];                          // nums[30] 상수시간에 평가되므로 가능.

    int num = 10;
    int *ptr = &num;

    std::cout <<getValue(num) << std::endl;         // getValue(num) : 10
    std::cout <<getValue(ptr) << std::endl;         // getValue(ptr) : 10

    auto func = [](int value){
        return value;
    };

    int nums1[func(10)];                            // c++14에서는 오류가 뜨는 코드. c++17부터는 lambda 함수에 암시적으로 constexpr이 붙어있다. 
                                                    // c++17에서는 [](int value) constexpr { return value; } 이렇게 명시적으로 붙여줄 수 있다.
                                                    // c++14에서는 명시적으로도 붙여 줄 수 없다.
    return 0;
}