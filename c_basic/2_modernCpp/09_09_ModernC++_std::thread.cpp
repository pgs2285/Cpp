// c++ 11 이전에는 스레드작업은 platform에서 제공해주는 API를 사용해야해서 플랫폼마다 코드가 달라 파편화가 심했다.
// c++ 11 부터는 표준 라이브러리에 스레드를 지원하는 클래스가 추가되었다. 즉 플랫폼 독립적인 코드가 가능하게 되었다.

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::chrono_literals;

struct Test{
    int num;
    Test(int num) : num(num) {
        std::cout << "Constructor" << std::endl;
    }

    ~Test(){
        std::cout << "Destructor" << std::endl;
    }
};

void foo()
{
    thread_local int i = 1;
    for(; i < 10; ++i)
        std::cout << i << std::endl;
    
}

void exception(int& num)
{
    num++;
    throw std::runtime_error("Error");
}

int main()
{
    std::thread example;                 // 비어있는 thread 객체 생성. 운영체제에 할당을 하고싶으면 안에 callable 한 객체를 넣어주어야한다.

    std::cout << "Main Thread ID : "<< std::this_thread::get_id() << std::endl;

    std::thread th([](){
        std::cout << "(th) Thread ID : "<< std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(1s);
        std::cout << "Wait 1s" << std::endl;   
    });

    th.join();                          // th 스레드가 종료될때까지 기다린다. 이거 없으면 메인스레드가 종료되면서 th 스레드도 종료된다. (abort)
                                        // join은 main thread 가 후에 종료된다 하더라도 사용해줘야한다.
    // th.detach();                     // detach를 하면 thread가 분리되어 기다리지 않는다.
    // th.joinable();                   // thread가 joinable한지 확인한다. detach 혹은 이전에 join을 하면 false가 된다.

    std::thread th0 = std::move(th);    // th0에 th를 move한다. th는 비어있는 thread가 된다.
                                        // thread 는 단순 대입연산자를 받지 않는다.
    // 함수 밖에있는것들은 정적영역, 함수 안에있는것들은 스택영역에 저장된다. new로 생성한것은 힙영역에 저장된다.
    // 이밖에도 thread_local 이라는 키워드가 있다. thread_local로 선언된 변수는 스레드마다 별도의 저장공간을 가진다.
    // thread_local 은 thread가 생성될때 생성되고, thread가 종료될때 소멸된다.

    std::thread([]{}).join();
    foo();                              // 1~9까지 출력
    std::thread(foo).join();            // 1~9까지 출력
    // thread_local은 static 변수와 비슷하다. static 변수는 프로그램이 시작될때 생성되고, 프로그램이 종료될때 소멸된다.
    // 다만 foo 내부에 static이 사용되었다면 1~20 까지 출력되었을것.

    // thread 의 가장 골칫거리는 동기화 이다.
    // 동기화를 하지 않으면, 스레드가 동시에 접근하여 데이터가 꼬일수 있다.

    int num = 0;
    std::thread th1([&num](){
        for(int i = 0; i < 100000; ++i)
            ++num;
    }); 
    for(int i = 0; i < 100000; ++i)
        ++num;
    th1.join();
    
    std::cout << num << std::endl;      // 예상대로라면 200000이 나와야하지만, 스레드가 동시에 접근하여 데이터가 꼬여서 200000이 나오지 않는다.
                                        // data race현상이 나타나는데, 위 예시에서 thread0, main thread는 각각의 레지스터를 가지고 있어서
                                        // 한 변수에 대해 경쟁하는 condition이 발생한다. 이를 해결하기 위해선 동기화가 필요하다.


    volatile bool flag = false;
    std::thread th3([&flag]{
        flag = true;
    });
    std::thread th2([&flag](){
        while(!flag)
            std::cout << "Waiting" << std::endl;
        std::cout << "Finished" << std::endl;
    });

    // 매 실행마다 결과값이 다르게 나온다. flag가 true가 되기전에 th2가 실행되어 무한루프에 빠지기 때문이다.
    // flag가 변경되는 시점은 매 실행마다 다르다.

    th2.join();
    th3.join();
    
    // 1.mutex : mutual exclusion, 상호배제
    std::mutex m;
    int num0 = 0;
    auto func = [&m, &num0] {
        
        for(int i = 0; i < 100000; i++)
        {
            // m.lock();                    // lock을 걸어주면, unlock까지 critical section이 된다. 즉 다른 스레드가 접근하지 못한다.
            
            {
                std::lock_guard<std::mutex> lg(m);  // exception을 대처하기위해 RAII기능을 사용해주자.  = std::lock_guard
                try{
                    exception(num0);                  // RAII : Resource Acquisition Is Initialization (구간을 벗어나면 자동으로 해제된다.)
                    ++num0;
                }catch(...)
                {
                    
                }
            }
            //m.unlock();
            


        }
        
    };

    std::thread th4(func);
    std::thread th5(func);

    th4.join();
    th5.join();
    
    std::cout << num0 << std::endl;         // 정상적으로 2000000이 출력된다. 다만 exception이 많이나서 출력이 느리다...
                                            // critical section에서 exception이 발생하면 unlock이 되지 않아서 데드락이 발생할 수 있다.
                                            // 이럴때 RAII기능을 사용해주자.  = std::lock_guard
    
}