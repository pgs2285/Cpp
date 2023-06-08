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

        // strong_ordering operator<=>(const String& s) const{
        //     int result = strcmp(s._chars, _chars);
        //     if(result < 0){
        //         return strong_ordering::greater;
        //     }else if(result > 0){
        //         return strong_ordering::less;
        //     }
        //     return strong_ordering::equal;
        // } //spaceship ordering  c++17버전부터 사용가능

        void print(){
            cout << _chars << endl;
        }
};

int main(){
    String str1("abc");
    String str2("bc");
    if(str1 != str2) cout << "equals" << endl;
    if(str1 < str2) cout << "bigger" << endl;
    if(str1 >= str2) cout << "smaller" << endl;

    return 0;
}