#include <iostream>

using namespace std;

class Character{

protected:
    int _health;
    int _power;

public:
    Character(int health, int power) : _health(health), _power(power){

    }
    virtual void damaged(int power){
        _health -= power;
    }
    void attack(Character& target){
        target.damaged(_power);
    }
    
};

class Player : public Character {

public:
    Player(int health, int power) : Character(health, power){ // 부모생성자로 초기화

    }
    virtual void damaged(int power) override{ // 나머지를 사용하기위해 Character를 상속받긴 했지만 damaged는 재정의 하고싶을때
    //virtual은 써주는게 관례, override는 의도 명확화(오타방지등)
        Character::damaged(_power); // 일단 hp감소는 character에서 선언한거 그대로 사용
        cout << "으악" << endl;
    }
};

class Monster : public Character{
    public : 

    using Character::Character; // 위에서 : 를 이용한 초기화와 같다
    virtual void damaged(int power) override{
        // _health -= power;
        //오버라이딩 해주는것은 매개변수의 개수가 동일해야함
        
        Character::damaged(power); // 위 라인과 동일한 의미
        cout <<"끼약" << endl;
    }
};

int main(){
    Monster monster(10,20);
    Player player(100,20);
    Character ch = Player(10,20);
    ch.attack(player);
    player.attack(monster);
    monster.attack(player);
}