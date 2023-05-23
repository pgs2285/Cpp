#include <iostream>
#include <string>

using namespace std;


class Player{ //보통 클래스의 정의가 작성되는 파일 이름은 주로 클래스 이름과 같다.(필수는 아니다)
    private: // 보통 없으면 private이다
    // 데이터가 외부로 노출가능하면 실수할 가능성이 높아짐.
        int _health;
        int _power; // 클래스의 멤버변수
        string _name;

    public: // 내부에서는 private접근가능(같은level)
        Player(int health, int power, string name = "NULL"){ // 밑에랑 의미가 완전히 같음(default 파라미터 사용해서 매개변수 2개인거도 받는다)
            _health = health;
            _power = power;
            _name = name;
            // getInfo();
        } // private 를 접근하기 위한 생성자
        // Player(int health, int power){ // 매개변수의 개수에따라 생성자를 다르게 줄수 있다.
        //     _health = health;
        //     _power = power;
        //     _name = "NULL";
        // }
        Player() : Player(100,50){
            cout <<" 정보입력이 필요합니다(DEFAULT 생성자) 기본값으로 대체됩니다" << endl;
            // Player(100,50); // 이딴 짓은 의도된거 아니면 하지말자 
            // 위 함수는 player 함수를 하나 더 만든거랑 똑같다.
            // 위처럼 위임 생성자를 만들면 자동으로 채워준다
            getInfo();
        }

        void Attack(Player& target){
            cout << "Attack " << _name << " -> " << target._name << endl;
            target.damaged(_power);
        }
        void damaged(int power){
            _health -= power;
            if(_health <= 0){
                cout << "Died" << endl;
            }
        }
        void getInfo(){
            cout << "health : " << _health << " power : " << _power <<" name : " << _name << endl;
        }
        void getInfo(string name){ // 생성자 뿐만아니라 다른함수도 매개변수 개수에따른 오버로딩 가능하다
            _name = name;
            cout << "health : " << _health << " power : " << _power <<" name : " << _name << endl;
        }
};

class Player2{
    private:
        const string _name;
        int _health;

    public:
    Player2(int health, string name) : _name(name), _health(health){ //이런식으로 하면 const 도 변경가능
    //이와같은 방법은 대입연산자를 사용하는 것이 아니라 성능에 이점이 있다.
    //위 방법들중 의도한 목적에 맞게 골라서 사용하자.
        cout << health << " " << name << endl;
    }
    // Player2() = default; // 기본생성자로 한다 (private에서 초기화 것으로)
    // Player2() = delete; // 생성 X (Instance를 할수없는 class이다)
};

int main(){

    // Player player0 = {200,1}; //인스턴스화.
    // player0.health = 100;
    // cout << player0.health << " " <<player0.power << endl;
    Player player0(200,100,"Jisung"); // 생성자 
    Player player1(200,100,"David");
    player0.Attack(player1);
    //player0.health -= 1000 ; 이런 상황 방지
    player0.Attack(player1);

    Player* player2 = new Player(100,200); // 포인터 class선언 (struct와 같다)
    // player2->getInfo();
    player2->getInfo("Jisung"); // 생성자 뿐만아니라 다른함수도 매개변수 개수에따른 오버로딩 가능하다

    Player player3; // 아무것도 입력하지 않으면 default 생성자 실행한다
    
    Player2 player4(100, "jisung"); //위임생성자, 
    return 0;
}
