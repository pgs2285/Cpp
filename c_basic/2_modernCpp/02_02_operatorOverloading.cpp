#include <iostream>

using namespace std;

class VectorF;

class VectorI{
    friend class VectorF; // VectorF에게 private 상황을 공유해준다.
private:
    int x;
    int y;
    int z;

public:
    friend VectorF operator+(const VectorI& v0, const VectorF& v1);
    VectorI(int x, int y, int z) : x(x),y(y),z(z){
        
    }


};

class VectorF{
private:
    float x;
    float y;
    float z;

public:
    VectorF(float x, float y, float z) : x(x),y(y),z(z){

    }

    friend VectorF operator+(const VectorI& v0, const VectorF& v1);
};

VectorF operator+(const VectorI& v0, const VectorF& v1){ // 교환법칙 성립시키기 위해서
    return VectorF{v1.x + v0.x, v1.y + v0.y, v1.z + v0.z};
}

int main(){


    return 0;
}