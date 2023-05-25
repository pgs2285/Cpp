#include <iostream>
#include "Person2.h"

int Person2::num = 0; //num 초기값 정의 

Person2::Person2(){
    num++;
}

void Person2::print(){
    std::cout << num << std::endl;
}
