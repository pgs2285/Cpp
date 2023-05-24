#ifndef __VILLAGE_H__ // 이름은 자유(충돌이 나면 안됨)
#define __VILLAGE_H__ // 위에것이랑 같게

#include <vector>

class Person; // include 보다 전방선언만 하는게 좋다. 구체화된 내용을 몰라도 되기때문 (같이 빌드만해주면 찾는다)
//프로젝트 컴파일시간도 줄여주고, 의존관계도 없애주는 방법!

class Village{
    private : 
        std::vector<Person> persons;

    public :
        void addPerson(Person person);
        void print();
};

#endif
//이방법이 재정의를 방지하는 표준이다.

// #ifndef(이름) = 만약 (이름)이 define되지않았다면
// #define (이름) = (이름)을 define해라
// #endif 여기까지

//위 식은 파일을 열어보고 비교하느라 컴파일시간이 #pragma once보단 지연될 수 있지만, 표준이라 모든컴파일러에 오류없이 작동된다