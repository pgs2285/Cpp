#include "01_03Headers/Village.h"
#include "01_03Headers/Person.h" // 추후 vector.push_back할경우 person의 모양을 알아야하므로, 전방선언으로는 부족하다
#include <iostream>

void Village::addPerson(Person person){
    persons.push_back(person);
}

void Village::print(){
    for(Person person : persons){
        std::cout<<"마을 구성원 : ";
        person.print();
    }
}
