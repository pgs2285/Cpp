#include <iostream>

using namespace std;

class Vector{
public:
    float x,y,z;

    Vector(float a,float b, float c) : x(a), y(b), z(c) {

    }
    
    Vector& operator++(){
        
        return *this;
    }
};

int main(){

    Vector v1(1.0f,2.0f,3.0f);
    Vector v2 = ++v1;
    cout << &v1 <<endl;
    cout << &v2 << endl;

    return 0;
}