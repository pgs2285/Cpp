#include <iostream>
#include <functional>

#define SQUARE(X) X*X

using namespace std;

typedef float real32;
typedef double real64;
// typedef int (*FuncType)(int,int);

struct Weapon;
int& WeaponPrice(Weapon&);
void weaponDefaultParameter(Weapon* w = nullptr);

inline int square(int x);
//inline함수같은 경우는 프로토타입선언을 안하고 밑에 함수만 작성해주는 관행같은게 있긴하다.

// int pow(int num, int exp);
int pow(int, int = 2); // 디폴트 매개변수가 있으면 그 뒤에있는 애들도 전부다 디폴트매개변수여야한다
//각 파일별로 선언하는 프로토타입 변수의 모양에따라 결과값이달라짐(같은 함수명이라도 디폴트매개변수를 달리줄수있다)
int countDigit(string num);
int countDigit(int num);// 오버로딩 , 같은 함수명이라도 매개변수를 달리하여 리턴값을 달리할 수 있다
//오버로딩되는 함수는 반환값들이 일치해야한다
//컴파일 될때 네임맹글링 (name mangling) or 네임 데코레이션(name decoration) 이 된다.
//오버로딩은 위 과정을 통해 서로 다른함수로 구분된다 ex)countdigit#string, countdigit#int //이런식으로




struct Weapon{
    int price;
};

enum struct typeLogin{
    Login, Update, Delete,
};

bool OnLogin(string id, string password){
    cout<<"OnLogin : " << id << "  " << password <<endl;
    return true;
}


bool OnUpdate(string id, string password){
    cout<<"OnUpdate : " << id << "  " << password <<endl;
    return true;
}

bool OnDelete(string id, string password){
    cout<<"OnDelete : " << id << "  " << password <<endl;
    return true;
}

int main(int argc, const char* argv[]){
    Weapon weapon = {10};
    WeaponPrice(weapon) = 20; // 이런식으로 참조를 사용하면 함수에 대입도 가능하다
    cout << weapon.price << endl;

    cout << "pow Ans : " << pow(10) << endl; 
    weaponDefaultParameter(); // structure로 사용하기
    cout << countDigit(100000) << endl;

    //함수포인터
    int (*f)(int, int) = &pow; // 괄호를 해야함 (함수포인터) 
    // pow를 &안붙여도되긴함 ( 주소값이 필요할때는 자신이 암시적으로 변환한다.)
    //int *변수명(int, int) =  integer pointer 를 반환하는 함수프로토타입의 주소
    cout << "함수포인터 " << (*f)(2,2) << endl;
    cout << "함수포인터2: " << f(2,2) << endl; //이것도 허용한다(표준은아님)  
    //함수 레퍼런스
    int (&t)(int,int) = pow;
    cout << t(2,4) << endl; 

    //함수포인터 활용
    //콜백함수를 만들때 활용하기도한다.
    //이벤트(특정조건,함수등)에 의해서 자동으로 실행되는함수
    bool (*callback[])(string, string) = {
        OnLogin,
        OnUpdate,
        OnDelete
    };
    callback[(int)typeLogin::Login]("pgs2285", "123456");
    callback[(int)typeLogin::Delete]("pgs2285", "123456");
    callback[(int)typeLogin::Update]("pgs2285", "123456");
    //위 콜백들은 사실 if문들의 조합으로 대체가 가능하다
    //콜백은 호출 했다는 느낌보다 타입별로 호출이 되었다는 느낌이 강함.

    //auto 써도된다
    auto func = pow;
    cout << "auto사용: " << func(2,2) << endl;
    //여기뿐만 아니라 auto i = 1; 하면 i 타입은 int가 된다.

    //<functional>헤더파일사용해 비슷한 기능
    function<int(int,int)> func2 = pow;
    cout << "functional 사용" <<func2(2,8) << endl;
    //함수포인터보다 성능적으론 비효율적
    //typedef사용하기;
    //C++ 11에서는 using을 통해 대체가 가능하다
    //using real = float;
    //using real2 = double;
    real32 real = 1.0f;
    real64 real2 = 2.0;
    cout << typeid(real).name() << " " <<typeid(real2).name() << endl;

    //typedef int (*FuncType)(int,int);
    using FuncType = int(*)(int,int);
    
    FuncType test = pow;
    cout<<test(2,10)<<endl; 
    //함수의 inline화
    // 기존함수는 베이스포인터(bp), return address 저장등 함수호출의 비용이 늘아남(호출 규약 참조)
    // 인라인 함수는 위와 같은 비용을 줄일 수 있다.
    int x = square(10); // 함수위치에 바로 10*10이 들어가게 된다.
    //함수호출 비용X(스택을 쌓을필요도 없고 레지스터에 대입할필요도 없는등...)
    //인라인 함수가 길어질경우 컴파일의 크기가 커짐. 고로 자주호출되고 크기가 작은함수에 사용
    cout << x <<endl;
    //레거시 코드같은경우는 #define SQUARE(X) X*X  같이 써있는경우도 있다(전처리기지시사) 인라인과 비슷함
    cout << SQUARE(10);

}

inline int square(int x){
    return (x*x);
}

int& WeaponPrice(Weapon& weapon){
    return weapon.price;
}

int pow(int num, int exp){ // 뒤에 2를 넣으면 디폴트 매개변수가됨. (매개변수를 안넣으면 2가 자동으로 삽입됨)
    int result = 1;
    
    for(int i = 0; i < exp; i++){
        result *= num;
    }
    return result;
}

Weapon w = Weapon{10};

void weaponDefaultParameter(Weapon* w){
    if(w){
        cout << w->price << endl;
    }else{
        cout << "invalid" << endl;
    }
}

int countDigit(int num){
    if(num == 0) return 1;
    int count = 0;
    while (num > 0){
        num /= 10;
        count++;
    }
    return count;
}

int countDigit(string num){ // 오버로딩 , 같은 함수명이라도 매개변수를 달리하여 리턴값을 달리할 수 있다
    return countDigit(stoi(num));
}

