#include <iostream>

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

int main(){

    String s = String("ABC"); // String s = "ABC"; 는 암시적 형지정이라 안되고, explicit선언된건 형 지정을 명확하게 해주어야한다.

    func(s); // explicit가 없으면 func("abc"); 해도 넘어간다
    // explicit를 제외한 모든게 암묵적 형변환을 사용하므로, 의도하지 않는것을 방지하려면 explicit를 사용한다.
    String s1 = String{"abcx", "ecds", "asdf"};
    String s2("abc");
    bool result = s2;
    cout << result << endl;

    //만약 explicit operator bool이면 (bool)s2 로 형변환을 명시해주어야 한다.
    return 0;
}