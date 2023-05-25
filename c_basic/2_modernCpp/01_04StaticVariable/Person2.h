#pragma once
class Person2{
    private:
    static int num;

    public:
    Person2();
    static void print(); // 이렇게 선언하면 const를 못붙여줌, 구체화 없이 호출이 가능해 this의 주소가없을때가 있기떄문
};