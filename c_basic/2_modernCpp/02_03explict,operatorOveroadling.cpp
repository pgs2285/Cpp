#include <iostream>
#include <chrono>
using namespace std;

class String{

    private:
    const char* _strs;
    public:

    explicit String(const char* chars):_strs(chars){

    }

    String(std::initializer_list<const char*> strs){
        // 매개 변수의 개수를 여러개 받고싶을때(유동적으로)
        for(const char* str : strs){
            cout << str << endl;
        }
    }

    operator bool(){ // bool 형 operator
        return strlen(_strs) > 0;
    }
};

void func(String s){

}

class Max{ // 호출연산자 (내부적으로 상태를 저장가능함)
    private:
    int _max;
    
    public:
    int operator()(int x, int y){
        return max(x,y);
    }
    int operator()(int x){
        return _max = max(x,_max);
    }
};

class Length{ //사용자 정의 리터럴

private:

    const long double _value;
    Length(long double value) : _value(value){

    }
    friend Length operator"" _m(unsigned long long int value);
    friend Length operator"" _m(long double value);
    friend Length operator"" _km(unsigned long long int value);
    friend Length operator"" _km(long double value);
    
public:
    long double GetValue(){
        return _value;
    }
    Length operator-() const{ 
        return -Length(_value);
    }
    long double m() const{
        return _value;
    }
    long double km() const{
        return _value / 1000;
    }
    // long double operator+(const Length& value) const {
    //     return (_value + value._value);
    // }  // 여기에 km,m 리턴하는 함수 만들어주고 Length를 리턴값으로 받아도 되긴함

    Length operator+(const Length& value) const{
        return Length(_value + value._value);
    }
    

};
Length operator"" _m(unsigned long long int value){
    // https://learn.microsoft.com/ko-kr/cpp/cpp/user-defined-literals-cpp?view=msvc-170
    // 위 링크는 사용자 정의 리터럴에 들어갈수 있는 자료형에 대해 나온다.
    // 사용자 정의 리터럴에는 성능에 이점이 없고 보통 편의를 위해 사용한다
    return Length(value);
}

Length operator"" _m(long double value){
    return Length(value);
}
Length operator"" _km(unsigned long long int value){
    return Length(value * 1000);
}

Length operator"" _km(long double value){
    return Length(value * 1000);
}
int main(){

    String s = String("ABC"); // String s = "ABC"; 는 암시적 형지정이라 안되고, explicit선언된건 형 지정을 명확하게 해주어야한다.

    func(s); // explicit가 없으면 func("abc"); 해도 넘어간다
    // explicit를 제외한 모든게 암묵적 형변환을 사용하므로, 의도하지 않는것을 방지하려면 explicit를 사용한다.
    String s1 = String{"abcx", "ecds", "asdf"};
    String s2("abc");
    bool result = s2;
    cout << result << endl;

    Max mx; // 호출연산자
    cout << mx(1,2) << endl;
    cout << mx(10) << endl; // 이런식으로 상태들을 저장해가며 활용가능(class특징을 활용하며)
    cout << mx(9) << endl;
    cout << mx(17) << endl;
    //만약 explicit operator bool이면 (bool)s2 로 형변환을 명시해주어야 한다.

    //사용자 정의 리터럴
    // 123.0f, 32.1d 처럼 끝에 형식 지정해주는것을 사용자가 정의해서 사용할 수 있다
    //chrono 같은 라이브러리에 사용되어있다
    chrono::minutes m = 24h + 12min; // 여기서 h, min가 사용자 정의 리터럴임
    cout << m.count() << endl;
    // cout << (1_m + 1_km) << endl; // line 64처럼 long double 을 반환으로 하면 이렇게 써도됨
    Length l = 1_m + 1_km;
    cout << l.km() << endl;
    cout << l.m() << endl;
    
    return 0;
}