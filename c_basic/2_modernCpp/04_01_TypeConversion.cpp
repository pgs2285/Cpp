#include <iostream>

using namespace std;

class Explicit{
    public:
    Explicit(int num){
        cout << num << endl;
    }
    explicit operator bool() {
        return true;
    }
};

class A{

};

class B : public A{
    public:
    int num = 10;
};

void func(const int& i){
    int& j = const_cast<int&>(i);
    j = 10;
}

class String{

private:


public:
char* _chars;
String(const char* chars) : _chars(new char[strlen(chars) + 1]){
    strcpy(_chars, chars);
}

char& operator[](int index){
    const String& s = *this;
    const char& c = s[index];
    return const_cast<char&>(c);
}

const char& operator[](int index)const{
    return _chars[index];
}

};

class Parent{
    public:
        int id;
        Parent(int id) : id(id){

        }
        void func(){
            cout <<"FUNC" << endl;
        }
        virtual ~Parent(){};
};

class Child:public Parent{
    public:
        int basicNum = 0;
        Child(int num) : Parent(num){};
        void func(){
            cout << "func" << endl;
        }
        virtual ~Child(){
            cout << "Destroy Child" << endl; 
        }
};

void foo(Parent* p){
    Child* c = dynamic_cast<Child*>(p);
    cout << "id : " << c->id <<endl;
    c -> func();
}

int main(){

    //func(float) 에 func(1) 을 넣는것도 float 에서 int로 형변환을 하는 것이다.
    cout << typeid(1.3f + 1).name() << endl; // output : float 식으로 사용할때도 형변환이 일어남
    
    unsigned short s0 = 40000; // unsigned short는 최대값이 65535
    cout << typeid(s0 + s0).name() << endl; // output : integer (integer보다 아래있는 애들은 연산시 integer로 promotion된다)

    int i = 100000000;
    long long ll = 100000000;
    cout << typeid(i + ll).name() << endl; // integer보다 이상인것과 연산시 더 큰것으로 바뀜 

    Explicit ex(10);
    // bool a = (ex); // 이건 안되지만 (explicit는 명시가 정확해야함 bool(ex) 처럼)
    
    while(ex){
        cout << "Explicit conversion" << endl;
        break;
    }
    //이렇게는 형변환을 자동으로 해주어서 된다
    //이밖에도 int ii; const int& i = ii; 이런거도 다 형변환이다.

    //c++ 창시자는 이러한 C스타일의 형변환이 위험하다 생각해 캐스팅 방법을 나눠둠
    // 1. static cast : 컴파일 시간에 호환되는 변환인지 검사를 하는 캐스팅
    A a;
    B* b = (B*)&a; //이게 기존 C스타일 형변환이다. 형식이 잘못되었지만 알려주지 않음.
    // B* bb = static_cast<B*> &a;  
    // 위 처럼 하는게 static 형변환이다. 컴파일 시간에 형식오류를 알려줘서 컴파일이 되지 않는다.

    float f = 1.1f;
    int ii = static_cast<int>(f); // 정적 형변환에 알맞은 옛;
    // int* ii = static_cast<int*>(&f) 는 컴파일 에러 (int메모리를 float로 할당하면 예상치 못한값 출력. 즉 floa t메모리를 integer로 해석하겠다는뜻이됨.)
    int* ItoF = (int*)(&f); // 이건 된다. 오류도 안뜰거고. 이런식의 형변환을 계속사용하면 위험함.
    cout << *ItoF<< endl; // 부동소수점 형식을 인티저로 바꾼값 출력.

    bool bbb = static_cast<bool>(ex); // 구조체 열거형 클래스 전부 사용가능하다.
    B bb;
    A aa = bb;
    int iii = 0;
    iii++;
    iii++; // volatile 은 컴파일 최적화를 하지않는다는뜻. 어셈블리로 변환한 코드를 보자
    // int iii = 0; 로 선언한 경우 mov eax 2 로 최적화후 바로 대입하지만
    // volatile int iii = 0; 은 한줄한줄 mov해줌 추후 멀티스레듭 배울때 다른스레드 공유시 사용함.
    // 2. const cast  : 참조형의 상수성(const)을 잠깐 제거해준다. 또한 volatile을 잠깐 제거해주는데에도 사용.
    int &cI = iii;
    func(cI); // const cast사용예시
    cout << cI << " " << iii << endl; 

    String s1("AbC");
    s1[0] = 'b'; // const_Cast를 이용해 return값은 const를 해제해서 반환하므로 변경가능
    cout << s1._chars << endl;

    //const_cast 는 일반적인 상황에서는 사용하지 말자

    //3.dynamic cast :  자식 클래스의 포인터를 부모 클래스의 포인터로 변경했다가 다시 자식 클래스의 포인터로 변경하는 경우(동적 형변환)에 사용한다
    Parent* p = new Child(10); // 여기서 child의 func를 호출하고 싶으면 dynamic_cast사용(foo함수 참조)
    // 위 코드는 업캐스팅 (자식의 메소드는 사용할 수 없지만 공통된 부분은 호출 가능하며, 가독성등을 높일수 있다. 공통되있는게 있으면 자식호출)
    //만약 공통된개 아니면 다시 다운캐스팅을 해서 실행해야하는데 예시는 foo안에 있다 (dynamic_cast 이용)
    // dynamic cast = 다형성을 가져야함 (virtual 이 필수다.)
    foo(p);


    //4. reinterpret cast : 비트배열을 재해석할때 사용.
    union ID {
        int integer;
        char* chars;
    };
    ID id;
    id.integer = 10;
    int* pp = reinterpret_cast<int*>(&id); // union(내부 변수를 하나의 메모리로 관리)을 integer로써 인식을하겠다
    cout << *pp << endl;
    // 로우레벨 디바이스 하드코딩 할때도 가끔 사용 reinterpret_cast<Device*>(0x1234); 
    int testInt = 10;
    float* testF = reinterpret_cast<float*>(&testInt);
    cout << *testF << endl; // integer의 읽는법을 변경함(기본 Integer를 부동소수점 읽는식으로 변환)

    //5. c style casting, functional style casting
    enum Type{
        A,B,C
    };
    int num0 = (int)Type::A; // c-style casting
    int num1 = int(Type::B); // functional-style casting

    // c-style cast는 위험하다. 일단 많은 역할을 한다 예를들어
    float& f = (float&)testInt; // reinterpret cast 역할
    const int& jj = testInt;
    int& k = (int &)jj; // const cast 역할
    i = (int)Type::A; // static cast 역할등
    //c style cast는 위 c++에서의 세가지 캐스트로 나누어져 있다. 일단 코드상 가독성 문제가 하나있다. 어떤 캐스트 사용,의도가 명확하지 않다.(상수성을 제거하기위함이라는등)
    //const_cast<int&>... 는 명확 협업등에서 혼란 야기 최소화.

    

    return 0;
    
}