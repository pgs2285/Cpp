#pragma once // 헤더파일을 include할때 한번만 한다
//즉 여러군데에서 이 Person.h 를 Include해도 한번만 정의하게 해서 오류를 피함
//비 표준이다.
//표준방법은 village.h에서 확인하세용
#include <iostream>


void testHeader();// 헤더파일에서는 선언만한다
//정의까지 해버리면 전처리 과정에서 헤더파일을 사용하는 모든곳에서 중복정의가 일어나므로 보통 선언만 작성함
//헤더파일과 같은이름의 파일(.cpp)에서 정의를해준다

//여기서 using namespace 를 사용해 버리면 이 헤더파일을 불러온 모든것에 적용된다
class Person{
    private:
        int _height;
        int _weight;
        const std::string _name;

    public:
        Person(int height, int weight, std::string name); // 위와 같은이유
        void print();
};
//위 과정이 추상화 , 캡슐화의 일부이다

//pragma once는 굳이 파일을 열어보지 않아도 되므로 컴파일 시간이 조금은 줄어들지만, 비 표준이므로 구형 컴파일러에서는 안돌아 갈수가 있다.

