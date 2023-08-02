#include <iostream>

using std::cout;
using std::endl;

class Person {
	
public:
    
    char _name[10];
    Person(const char* name) {
        strncpy(_name, name, sizeof(_name));
        _name[sizeof(_name) - 1] = '\0';
    }
    ~Person() {
        cout << "소멸자 호출" << endl;
    }
};

int main() {
	Person p1("Jisung"); // 원본 객체. age = 20으로 생성
	Person p2(p1); // 복사된 객체. 원본 객체 p1을 복사해 생성
    // 오해할 수 있는게 같은 힙영역을 가리키는거지 p1 과 p2의 주소가 같다는게 아니다
    // 얕은 복사의 오류는 대게 여기서 발생한다. 만약 p1을 delete하면 p2가 가리키던 힙영역이 같이 반환되어, p2가 낙동강 오리알 신세가 된다. (가리키던 주소가 반환이 되었음)
    //    즉 얕은 복사 방식은 멤버변수가 힙(HEAP)의 메모리 공간을 참조하는 경우에 문제가 된다. 
    //    즉 "할당" 시에 문제가 발생한다.
    p2._name[3] = 'k';
    cout << p1._name << endl;
    cout << p2._name << endl;
    delete &p1;

}


// #include<iostream>
// using namespace std;

// class MyArray {
// public:
// 	int size;
// 	int* data;

// 	MyArray(int size)
// 	{
// 		this->size = size;
// 		data = new int[size];
// 	}

// 	MyArray(const MyArray& other);

// };

// MyArray::MyArray(const MyArray& other) {
// 		//모든걸 복사한 후 새로운 객체 생성
// 		this->size = other.size;
// 		this->data = new int[size];

// 		for (int i{ 0 }; i < other.size; i++) {
// 			this->data[i] = other.data[i];
// 		}
// }



// int main() {

// 	MyArray buffer(10);
// 	buffer.data[0] = 2;

// 	MyArray clone = buffer;
// 	buffer.data[0] = 3;

// 	cout << "clone.data[0] = " << clone.data[0] << endl;
//     delete &buffer;
// 	return 0;
// }