// 기존(c++11 이전)에 auto는 자동지역변수로 명시해주는 키워드 였지만(보통 안붙여도 자동지역변수로 인식해서 사용은 잘안했음)
// C++ 11 부터는 auto를 완전히 리뉴얼 했다. 이제 타입추론을 위한 키워드로 사용된다.
// 명시성이 불분명해진다.

#include <iostream>
#include <algorithm>
#include <map>
#include <tuple>
using std::cout;
using std::endl;

int func()
{
    return 0;
}

template <typename T, typename S>
auto Add(T a, S b) -> decltype(a+b) {// c++ 14 부터 함수 리턴값을 자동 추론할 수 있게 되었다. (즉 c++14 부턴 decltype이 필요없다), 다만 강제하고 싶으면 써라
    // T t = a + b; // 첫번째 인자를 따라 변환한다.
    auto t = a + b; // auto를 사용하면 자동으로 추론해준다.
    // auto를 decltype을 이용해 decltype(a+b) result = a+b; 로 해도 추론이 된다.
    cout << t << endl;
    return a + b;
}

template <auto... Args>
auto Sum()
{
    return (Args + ...); //fold expression (c++17 부터 지원), 
    //Args + ... : (A[0] + (A[1] +(A[2] .... A[n]))
    //... + Args  : (A[0] + A[1]) + A[2])+A[3]....+A[n]))
    // 두개의 괄호 묶는 방식이 다르다.
}

int main()
{
    auto ptr = new int[12]{1,2,3}; //크기가 12인 배열에 1,2,3을 넣고 나머지는 0으로 초기화후 포인터를 반환. 여기서 포인터(int*)는 배열의 첫번째 주소를 가리킴
    // 위 같은 코드처럼 명시적인걸 표현하는데 auto를 쓰면 가독성이 떨어진다.
    //다만 vector iter를 다루는데 auto를 사용하면 오히려 가독성이 올라가는 경우도 꽤 있다
    // ex ) std::vector<int>::iterator iter -> auto iter

    //특히나 map같이 key값이 const인 경우 auto를 사용하면 편하다.
    std::map<int, int> m;
    for(const auto& iter : m)
    // 여기서 오토는 std::map<const int, int>::iterator iter 와 동일하다. (key값이 자동으로 const형으로 변해, 위에서 선언한것과 햇갈릴수 있다.)
    {
        cout << iter.first << " " << iter.second << endl;
    }

    //추론 규칙에 대해 알아보자
    const int a = 10;
    const int& b = a;
    const int *c = &a;

    auto aa = a; //int (auto 가 const를 무시하는 경우가 존재한다)
    auto bb = b; //int (auto 가 reference를 무시하는 경우가 존재한다)
    auto cc = c; //const int* (수정을 방지하기 위해 const int pointer)

    auto& bbb = b; //const int&

    //배열에 대한 추론
    int arr[] = {1,2,3,4,5};
    auto num0 = arr; //int* (arr의 첫번째 주소를 가리킴)
    auto& num1 = arr; //int arr[5]
    cout << typeid(num1).name() << endl;

    //함수에 대한 추론
    auto func1 = func; //int(*)() (함수포인터)
    auto& func2 = func; //int(&)() (함수 참조자)

    Add<int, float>(1,2.2); // template (Add(1,2) 만해도 자동추론 되긴한다.) 

    cout << Sum<10,20,300000,4000000>() << endl; // c++17 부터 지원하는 fold expression (c++17 부터 지원) 여기도 auto 사용가능

    //map등의 pair쌍을 가져올때도 auto를 사용할 수 있다
    std::map<int, int> m2 {
        {1,2}
    };
    auto [key, value] = *m2.begin(); // auto [key, value] = std::pair<int, int> (c++17 부터 지원)
    int nums[3]{1,2,3};
    auto& [x,y,z] = nums; // x,y,z 가 각각 바인딩 된다.
    x = 10;// 참조이므로 nums[0] = 10; 과 같다.
    cout << nums[0] << endl;

    //tuple ( pair 와 비슷하지만, 개수가 제한이 없다)
    std::tuple<int, int, const char*> t(1,2,"31");
    auto t1 = std::make_tuple(1,2,"31"); // auto t1 = std::tuple<int, int, const char*>(1,2,"3"); 과 같다.
    int alpha;
    int beta;
    const char* gamma;
    std::tie(alpha, beta, gamma) = t1; // tie를 이용해 각각의 변수에 바인딩 시킬 수 있다.
    // 위 tie로 unpack 시킨것을 auto로 대체할 수 있다
    auto& [alpha1, beta1, gamma1] = t1;
    cout << alpha << " " << beta << " " << gamma << endl;
    cout << alpha1 << " " << beta1 << " " << gamma1 << endl;
    //원래는 가져올때 아래같이 가져온다
    std::get<0>(t1); // 1

    struct Person{
        int age;
        std::string name;
    };
    Person p{10, "alpha"};
    auto [age, name] = p;
    cout << age << " " << name << endl;

}