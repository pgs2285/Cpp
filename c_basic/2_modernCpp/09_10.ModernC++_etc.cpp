//std::future : 어떤값을 미래에 받겠다는 약속을 나타내는 클래스
//std::promise : 어떤값을 미래에 보내겠다는 약속을 나타내는 클래스
// 즉 promise는 future에게 값을 보내는 역할을 한다.
//std::packaged_task
//std::async

// 기존에 설명한 thread는 low-level thread로, 직접제어하기가 여간 까다로운게 아니다.
// 그보다 높은 추상화 레벨을 제공하는것들이 위의 4가지이다.

#include <future>
#include <iostream>
#include <chrono>

using std::cout;
using std::endl;
using namespace std::chrono_literals;
int main()
{   
    std::promise<int> pro;
    std::future<int> fut = pro.get_future();

    pro.set_value(10);
    cout << fut.get() << endl;                          //만약 promise에서 값이 세팅되지 않는다면 blocking(무한대기) 된다. get도 한번만 된다.
    // 이걸 어디에 쓰냐 궁금할 수 있는데, 이걸 thread에서 사용할 수 있다.
    std::promise<int> pro2;
    std::future<int> fut2 = pro2.get_future();
    std::thread th(
        [](std::promise<int> pro){
            std::this_thread::sleep_for(1s);
            pro.set_value(10);
        }, std::move(pro2)                              // promise는 복사가 불가능, 이동만 가능하다.
    );
    cout << fut2.get() << endl;
    th.join();


    std::promise<int> pro3;
    std::future<int> fut3 = pro3.get_future();
    std::thread th2(
        [](std::promise<int> pro)
        {
            try{
                throw std::runtime_error("Runtime Error");
            }catch(...)
            {
                std::exception_ptr e = std::current_exception();    // 현재 예외를 저장한다.
                pro.set_exception(e);                               // 예외를 저장한다.
            }
        }, std::move(pro3)
    );
    try{
    cout <<fut3.get() << endl;
    }catch(std::runtime_error& e)
    {
        cout << e.what() << endl;
    }
    th2.join();

    // 위 과정이 다소 복잡하다 느낄수 있어서 std::packaged_task를 사용한다.
    // std::packaged_task는 promise와 try catch를 내부적으로 처리해준다.
    std::packaged_task<int(int)> task(
        [](int value)
        {
            if(value < 0) throw std::runtime_error("value is negative");
            return value;                                           // return으로 값을 보내준다.
        }
    );
    std::future fut4 = task.get_future();
    std::thread th3(std::move(task), -1);                           // task는 복사가 불가능하다. 이동만 가능하다.

    try{
    std::cout << fut4.get() << endl;                                // 굳이 try-catch를 하지 않아도, task를 사용하면 내부적으로 처리해준다.
    }catch(std::runtime_error& e)
    {
        cout << e.what() << endl;
    }

    th3.join();    

    // 위 과정마저 복잡하다 느낄수 있어서 std::async를 사용한다.
    std::future<int> fut5 = std::async(                             // 자체적으로 다른 thread id를 가진다.(스레드의 제작 여부는 자체적으로 판단한다)
                                                                    // async(std::launch::deferred, [](int value){}) 처럼 사용하면, 스레드를 생성하지 않는다.
                                                                    // 즉 밑에함수를 바로 실행하지 않고, get()을 호출할때 실행한다.
        [](const int& value){
            if(value < 0) throw std::runtime_error("value is negative");
            return value;
        }, 100
    );
    try{
        cout << fut5.get() << endl;
    }catch(std::runtime_error& e)
    {
        cout << e.what() << endl;
    }

    return 0;
}