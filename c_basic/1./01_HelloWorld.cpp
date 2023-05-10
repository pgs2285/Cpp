//
//  main.cpp
//  c_basic
//
//  Created by 박지성 on 2023/05/10.
//

#include <iostream>


using namespace std;

int main(int argc, const char * argv[]) {
    
    std::cout << "Hello, World!\n"<< std::endl;
    #include "header/abc.txt" //include를 함수 내부에도 사용가능하긴함. 
    
    return 0;
}

/*

Output:

Hello, World!

Hello World

*/
