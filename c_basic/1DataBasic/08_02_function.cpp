#include <iostream>

using namespace std;

struct Weapon;
int& WeaponPrice(Weapon&);
void weaponDefaultParameter(Weapon* w = nullptr);

// int pow(int num, int exp);
int pow(int, int = 2); // 디폴트 매개변수가 있으면 그 뒤에있는 애들도 전부다 디폴트매개변수여야한다
//각 파일별로 선언하는 프로토타입 변수의 모양에따라 결과값이달라짐(같은 함수명이라도 디폴트매개변수를 달리줄수있다)

struct Weapon{
    int price;
};

int main(int argc, const char* argv[]){
    Weapon weapon = {10};
    WeaponPrice(weapon) = 20; // 이런식으로 참조를 사용하면 함수에 대입도 가능하다
    cout << weapon.price << endl;

    cout << "pow Ans : " << pow(10) << endl; 
    weaponDefaultParameter(); // structure로 사용하기
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