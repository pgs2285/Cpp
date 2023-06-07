#include <iostream>

using namespace std;

class Vector{

private:
    float x;
    float y;
    float z;
public:
    Vector(float x, float y, float z): x(x), y(y), z(z){
        
    }

    Vector operator+(){
        return *this;
    }

    Vector operator+(const Vector& v){
        return Vector{x + v.x , y+v.y , z+ v.y};
    }

    Vector operator-(){
        return Vector{-x, -y, -z};
    }

    Vector operator-(const Vector& v){
        return Vector{x - v.x, y - v.y, z-v.z};
    }

    Vector operator*(const float& num){

        return Vector{num * x, num * y, num * z};
    }

    Vector operator*(const Vector& v){
        return Vector{v.x * x, v.y * y, v.z * z};
    }

    Vector operator/(const Vector& v){
        return Vector{v.x / x, v.y / y, v.z / z};
    }
// 참조를 쓰지 않는경우
//Vector a(1, 2, 3);
//Vector b = --a;
// 위 식의 주손 서로 다른걸 가리킬거다
// 참조쓰면 같은값 가리키고
    Vector& operator++(){
        
        ++x;
        ++y;
        ++z;
        // cout << "감소연산자 증가주소" <<this << endl;
        // cout << this << endl;
        return *(this);
    }

    Vector& operator--(){
        --x;
        --y;
        --z;
        // cout << "감소연산자 반환주소" <<this << endl;
        return *this;
    }
    Vector& operator--(int){ // 후위연산자의 규칙같은거임
        Vector& tmp = *this;
        --(*this);
        // cout << "감소연산자 반환주소" <<this << endl;
        return tmp;
    }
    
    friend Vector operator*(float num, Vector& v1);
    void printVec(){
        cout << "X : " << x << " Y : " << y << " Z : " << z << endl;
    }
};

Vector operator*(float num, Vector& v1){
    return Vector{num*v1.x, num*v1.y, num*v1.z}; // x,y,z 가 private로 등록되어있어 접근할 수 없다.
    // 클래스 내부에 friend로 프로토타입선언 해주면 접근 가능하다.
}


int main(){
    Vector v0 = {1,2,3};
    Vector v1 = {0,1,2};
    Vector nums = {-1,5,-3};

    Vector v2 = v0.operator+(v1); // + 연산자 오버로딩(이항)
    Vector v3 = v1.operator-(); // - 연산자 오버로딩(단항)
    Vector v4 = nums.operator+(); // + 연산자 오버로딩(단항)
    Vector v5 = v0.operator-(v1); // - 연산자 오버로딩(이항)
    Vector v6 = v0.operator*(3.0f); // * 연산자 오버로딩 (이항, float 받아서)

    Vector v7 = v0.operator*(nums); // * 연산자 오버로딩 (이항, vec받아서)
    Vector v8 = v0.operator/(v1);// / 연산자 오버로딩 (이항, vec받아서)
    Vector v9 = v0.operator++(); // ++연산자 오버로딩 (단항, 후위연산자) 자기자신이 직접 올라감
    Vector v10 = v0.operator--(); // --연산자 오버로딩 (단항, 후위연상자) 자기자신이 직접 올라감

    Vector v11 = v0 + v1; // 이제 이런식으로 직접 식에 넣는거도 가능하다.
    Vector v12 = ++v0;
    Vector v13 = 3.0f * v1; // 이건 전역변수함수를 호출한거. (Vector 클래스 내부에서 제작한 함수가 아님)
    // Vector v13 = ++v12;

    // v2.printVec(); //  + 
    // v3.printVec();
    // v4.printVec();
    // v5.printVec();
    // v6.printVec();
    // v7.printVec();
    // v8.printVec();
    // v9.printVec();
    // v10.printVec();
    // // v12.printVec();
    // // v13.printVec();
    // v12.printVec();
    v13.printVec();
    cout << &v12 << endl;
    cout << &v0 << endl;
    return 0;
}