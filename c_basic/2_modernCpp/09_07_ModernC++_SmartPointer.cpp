#include <iostream>
#include <memory>

using std::cout;
using std::endl;

struct B;
struct A{
    std::shared_ptr<B> b;
    ~A(){
        cout << "A" << endl;
    }
};

struct B{
    std::weak_ptr<A> a;
    ~B(){
        cout << "B" << endl;
    }
};


struct Test{                                // 간단하게 생성 , 소멸 시점알기위한 test 구조체 
    int _num;
    Test(int num) : _num(num)
    {
        cout << "Constructor : " << _num << endl;
    }

    ~Test()
    {
        cout << "Destructor : " << _num << endl;
    }  
};

int foo(std::unique_ptr<Test>& p0)           // 만약 main함수에서 더이상 사용하지 않는다고 판단되는 객체를 넘겨준다면, 이렇게 사용하면 된다. 즉 소유권을 넘겨받음
                                            // 참조로 받는다면 수정등에 보다 자유롭다
{
    p0.reset(new Test(100));
    return p0->_num;
}

struct Deleter{
    void operator()(Test* p) const
    {
        cout << "Deleter" << endl;
        delete p;
    }
};

int exception()
{
    throw std::exception();
}

void bar(int , std::shared_ptr<Test> p)
{

}


int main()
{
    //스마트 포인터에는 4종류가 있다
    // 1.auto_ptr -> 스마트포인터의 시초이다. C++11에서부터 사용중지 권고를 했고, C++17 에서는 폐기가 되었다. 굳이 알아보지 말자.

    int* num0 = new int(10);
    int* num1 = num0;                       // 이러한 상황에서 무엇을 반환할지 애매하다. 둘다 반환하면 undefined behaviour 발생할거고.
                                            // 이러한 경우를 해결하고자 하는게 스마트 포인터이다.
    // 2.unique_ptr
    Test* test = new Test(10);
    std::unique_ptr<Test> p0(test);         // unique_ptr은 사라지는 시점에 반환해줌 (여기선 함수 종료블럭)
    std::unique_ptr<Test> p1(new Test(20)); // 이렇게 사용하는게 중복 지정(해제)을 방지할 수 있어 안전하다.
    auto p2 = std::make_unique<Test>(30);   // auto를 사용해서 unique_ptr을 만들어 줄 수도 있다. (C++14)
    // std::unique_ptr<Test> p3 = p2;       // 이렇게 사용하면 에러가 발생한다. (복사 생성자가 없다는 에러. 즉 단독으로 사용한다.)
    std::unique_ptr<Test> p3 = std::move(p2);// 이렇게 사용하면 p2가 p3로 이동하게 된다. (p2 가 rvalue로 바뀐다.) -> p2 는 empty가 된다.
    int a = foo(p3);                        // 만약 main함수에서 더이상 사용하지 않는다고 판단되는 객체를 넘겨준다면, 매개변수로 std::unique_ptr<Test>사용.
                                            // unique ptr은 복사가 허용되지 않으므로, move를 사용해서 넘겨주자. 혹은 std::unique_ptr<Test>& 로 넘겨주면, 참조로 넘겨줄 수도 있다.
    cout << a << endl;                      //(참조로 넘기며 100으로 바꿈.)
    p3.get()->_num = 200;                   // p3.get() 은 Test* 를 반환한다. 즉 p3.get() 을 통해 Test* 를 반환받아서 사용할 수 있다. 이를 함수에 사용해도 됨.
    cout << p3->_num << endl;               
    /*
    unique pointer는 원래 RAII이다. 
    소멸할때 할 행동을 정의해놓고 소멸시점에 자동으로 호출되게 만들어 줄 수 있다.
    함수객체를 만들어서 unique_ptr<type, destructor> 형태로 넣어주면 된다. 구현은 Deleter함수 참조
    */
   std::unique_ptr<Test, Deleter> p4(new Test(40)); //deleter 출력후 삭제.

    // 3.shared_ptr : 위에서 본 unique_ptr 과는 다르게 복사가 가능하다. (참조 계수를 사용한다.)
    std::shared_ptr<Test> p5(new Test(50));
    std::shared_ptr<Test> p6 = p5;          // 복사가 가능하다. 

    cout << p5.use_count() << endl;         // p5의 참조 계수(참조를 하는 개수)를 반환한다. (p5, p6 두개가 참조하므로 2가 반환된다.)
    cout << p6.use_count() << endl;         // p6의 참조 계수(참조를 하는 개수)를 반환한다. (p5, p6 두개가 참조하므로 2가 반환된다.)
                                            // 즉 내가 가리키고 있는걸 몇개가 참조하고 있는지 알 수 있다.(자기 자신도 포함) 

    p5.reset();

    cout << p5.use_count() <<endl;         // p5 가 reset되었으므로 0이 반환된다.
    cout << p6.use_count() <<endl;         // p6 가 p5를 참조하므로 1이 반환된다.

    Test* test2 = new Test(10);
    std::shared_ptr<Test> p7(test2);
    
    /*
    std::shared_ptr<Test> p8(test2);         // Error
    Error p7->control block(1) , p8->control block(1) 이므로, p7,p8 둘다 소멸시키면 test가 두번 소멸되므로 에러가 발생한다.
    같은 자원(raw 포인터)에 대해 다수의 control block이 생성된다면 같은 자원에대해 레퍼런스 카운터가 별도로 동작하고, 
    그래서 각각 0이 된 시점이 달라 별도로 해제하고, 그러면 댕글링 포인터문제(해제된 메모리를 접근하는문제)가 발생할 수밖에 없다. 
    */

    std::shared_ptr<Test> p8(p7);           // 이렇게 사용하면, p7의 참조 계수가 1 증가한다. (p7,p8->control block(2))
                                            // shared pointer 또한 deleter를 지정할 수 있다. 사용법은 아래와 같다.
    std::shared_ptr<Test> p9(new Test(60), Deleter()); //deleter 출력후 삭제.
    std::shared_ptr<Test> p10(p9);          // 여기서는 sharedpointer 사용불가
    auto p11 = std::make_shared<Test>(70);  // 이런 표현을 선호한다. 그 이유는 throw같이 예외가 났을때 메모리 누수를 방지할 수 있기때문이다.
    try{
        bar(exception(), std::shared_ptr<Test>(new Test(80)));  // 이런식으로 사용하면 예외가 발생하면서 메모리 누수가 발생할 수 있다.
                                                                // 왜냐하면 new Test(80) 이 먼저 실행되고, exception()이 실행되기 때문이다. shared_ptr은 생성되지 않은체 exception()이 실행되므로
                                                                // release모드에서는 문제가 발생하지만, debug모드에서는 문제가 발생하지 않을수도 있다.
        bar(exception(), std::make_shared<Test>(90));           // 이런식으로 사용하면 예외가 발생하면서 메모리 누수가 발생하지 않는다.
    }catch(...)
    {
        cout << "exception" << endl;
    }
    // 만약 class a->class b, class b->class a를 가리키면 순환참조가 발생하므로 조심하자.
    // scope에서 사라져봤자 main에 선언된 shared만 사라지지, 구조체 내부의 shared는 사라지지 않는다. 즉 순환참조가 발생하면 메모리 누수가 발생한다.
    // 아래같이 weak_ptr을 사용하면 순환참조를 방지할 수 있다.

    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>(); // 둘다 shared_ptr로 맞물리지말고, 하나를 weak_ptr로 맞물리자. (B구조체 참고)
 

    // 4.weak_ptr . 즉 weak_ptr은 레퍼런스를 카운터를 증가시키지 않으면서 빌려간다. 즉 해제에 대한 책임또한 없다.
    auto k = std::make_shared<Test>(100);
    std::weak_ptr<Test> p12(k);             // 이렇게 사용하면, p12는 k를 참조하지만, k의 참조 계수는 증가하지 않는다. (p12->control block(0), k->control block(1))
    auto shared = p12.lock();               // weak_ptr 은 사용하려면 lock을 걸어주어 shared_ptr로 변환해주어야 한다. (lock을 걸어주면, p12->control block(1), k->control block(2))
    
    if(shared) shared->_num = 200;          // 이렇게 사용하면 된다. (여기서 shared는 위에서 만든 shared_ptr<Test> k와 같다.)
    //보통 weak pointer는 자식ui가 부모ui를 가리킬때 사용한다.
    return 0;
}