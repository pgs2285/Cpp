#include "01_03Headers/Person.h"
//헤더파일과 같은이름의 파일에서 정의를해준다


void testHeader(){
    Person person(100,200,"cpp");
    person.print();
}

Person::Person(int height, int weight, std::string name) : _height(height), _weight(weight), _name(name)
{

}
void Person::print(){ // 클래스 함수 정의시 ::앞에 클래스명
    std::cout << "Height : " << _height << " | Weight : " << _weight << " | Name : " << _name << std::endl;

} 