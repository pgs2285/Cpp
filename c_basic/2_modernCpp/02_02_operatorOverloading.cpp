#include <iostream>
#include <cstring>
#include <compare>


using namespace std;

class String{
    private:
        char* _chars;   
        

    public:
        String(const char* chars) : _chars(new char [strlen(chars) + 1]){ 
            strcpy(_chars, chars);
        }

        bool operator==(const String& s) const{ 
            return strcmp(s._chars, _chars) == 0;
        }

        bool operator!=(const String& s) const{
            return !(*this == s);
        }

        bool operator<(const String& s)const {
            return strcmp(s._chars, _chars) > 0;
        }
        bool operator>=(const String& s) const{
            return!(*(this) < s);
        }
        bool operator!() const{
            cout << (strlen(_chars) != 0) << endl;
            return strlen(_chars) != 0;
        }
        // strong_ordering operator<=>(const String& s) const{
        //     int result = strcmp(s._chars, _chars);
        //     if(result < 0){
        //         return strong_ordering::greater;
        //     }else if(result > 0){
        //         return strong_ordering::less;
        //     }
        //     return strong_ordering::equal;
        // } //spaceship ordering  c++17버전부터 사용가능

        bool operator&&(bool b)const{
            return (strlen(_chars) > 0 || b);
        }

        void print(){
            cout << _chars << endl;
        }
};

/*
매개변수에 &사용이유
매개변수를 상수를 참조하는 형태로 선언함으로써 함수 내에서 매개변수 객체를 변경하지 않으며, 함수 내에서 객체를 복사하는 오버헤드도 낮추 효과를 가집니다.

const는 해당 인자 함수 내에서 변경되지 않도록 보호하는 효과를 가집니다. 
따라서, const MyClass& lhs와 const MyClass& rhs로 선언함으로써 해당 함수에서 객체를 변경하는 일이 없고, 매개변수로 전달된 객체를 변경하지 않는다는 것을 명시합니다.
*/

bool func(){
    cout << "함수 실행" << endl;
    return true;
}

int main(){
    String str1("");
    String str2("bc");
    // if(str1 != str2) cout << "equals" << endl;
    // if(str1 < str2) cout << "bigger" << endl;
    // if(str1 >= str2) cout << "smaller" << endl;

    if(!str1) cout << "문자열이 비어있지 않음" << endl;
    else cout<<"문자열이 비어있음" <<endl;

    if(str1 && func()){ 
        // 일반적은 &&와 다르게 앞에것이 false여도 실행하는 특징이 있다. (함수호출 개념이라 일반적인 && || 와 다르기때문에 유의)
        //또한 sequence point로의 보장도 안된다.
        cout <<"bool 실행" <<endl;
    }

    return 0;
}