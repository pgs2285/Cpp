#include <iostream>
#include <string>

using namespace std;

class Player{ // 같이 링크된 다른 파일에서 클래스를 재정의 할때는 의미상 동일해야한다.
// 정의된 내용이 다르면 undefined behaviour가 뜬다
    private:
        string _name;
    public:
    Player(string name = "NULL") : _name(name){
        cout << _name << " : 생성자" << endl;

    }
    ~Player(){ // 명시하지 않으면 컴파일러가 자동으로 만들어준다
        cout << _name <<" : 파괴자" << endl;
    }
};

class String{
    private:
        char* _str;
    public:
        String(const char* str) {
            int len = strlen(str); // null 문자를 위한 
            _str = new char[len + 1]; // 여기서 new로 생성한것은 프로그래머가 수동으로 해제하기 전까진 메모리에 남아있는다
            strcpy(_str, str);
        }
        ~String(){
            delete[] _str;
        }
        void print(){
            cout << _str << endl;
        }
};
Player player("1Player");
Player* player2 = new Player("2Player"); // 포인터로 생성시 직접 파괴해줘야함.(자동으로 해제해주지 않는다.)

static void func(){
    static Player player3("3Player");
}



int main(){

    Player player4("4Player");
    func();
    func(); // 정적영역이라 한번만 생성,해제
    {
        Player player5("5Player"); // 블록스코프를 벗어날때 자동해제
    }
    delete player2;
    // 굳이 파괴하지 않아도 종료될때 자동으로 파괴된다
    
    String str("abc");
    str.print();

    return 0;
}