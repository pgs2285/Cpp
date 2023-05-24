#include <iostream> // 시스템에서 지원되는 헤더파일은 <>
#include "01_03Headers/Person.h" // 유저가 define 한 header 는 ""사용
#include "01_03Headers/Village.h"
//전처리 과정해서 헤더파일들은 복붙됨
using namespace std;
int main(){
    testHeader();
    Person person(192,80,"jisung");
    person.print();
    Person person2(188,72,"gnusij");
    Village village1;
    village1.addPerson(person);
    village1.addPerson(person2);
    village1.print();
    
    
    return 0;
}