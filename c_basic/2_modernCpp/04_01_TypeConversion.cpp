#include <iostream>

using namespace std;

class Explicit{
    public:
    explicit operator bool() {
        return true;
    }
};

int main(){

    //func(float) 에 func(1) 을 넣는것도 float 에서 int로 형변환을 하는 것이다.
    cout << typeid(1.3f + 1).name() << endl; // output : float 식으로 사용할때도 형변환이 일어남
    
    unsigned short s0 = 40000; // unsigned short는 최대값이 65535
    cout << typeid(s0 + s0).name() << endl; // output : integer (integer보다 아래있는 애들은 연산시 integer로 promotion된다)

    int i = 100000000;
    long long ll = 100000000;
    cout << typeid(i + ll).name() << endl; // integer보다 이상인것과 연산시 더 큰것으로 바뀜 

    Explicit ex;
    // bool a = (ex); // 이건 안되지만 (explicit는 명시가 정확해야함 bool(ex) 처럼)
    
    while(ex){
        cout << "Explicit conversion" << endl;
        break;
    }
    //이렇게는 형변환을 자동으로 해주어서 된다
    //이밖에도 int ii; const int& i = ii; 이런거도 다 형변환이다.

    return 0;
    
}