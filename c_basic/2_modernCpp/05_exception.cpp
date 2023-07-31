#include <iostream>

using namespace std;

double divide(double d, double v)
{
    if(v==0)
        return 0;
    return d/v;
}
double divideWithThrow(double d, double v)
{
    if(v==0) throw "Divided by zero"; // return처럼 여기서 함수가 종료. throw 가 발동되면 std::terminate() 를 호출해서 함수를 종료시킨다
    return d/v;
}
void terFunc()
{
    throw "EXCEPTION";
    // cout << "TerFunc" << endl;
    // exit(123); // 정상종료
}

class Parent{

};

class Child : public Parent{

}; // try-catch 예시를 위한 임시 클래스

class customException : public std::exception{
    public:
    // virtual const char* what() const override
    // {
    //     return "custom";
    // }
};
void tryCatchTest(int v = 0)try{ // 함수 try 함수 전체를 try로 묶은것과 결과값이 동일하다
    if(v==0) throw Child(); // 0일시 child를 던진다.
}
catch(std::logic_error& e){

}

void func_n () noexcept {
    throw 1;
}

class RAII{
    public:
        int* i;
        RAII(){
            i = new int;
        }

        ~RAII(){
            delete i;
        }
};

int main()
{
    // 전통적인 예외처리
    // 일반적으로 함수호출할때 오류가나면 caller한테 오류를 알려줘야함. (만약 알려주지않으면, 무시 or 강제종료)
    // std::abort(); 비정상 강제종료 , exit(1); 정상종료
    int result = printf("%d\n", 10); // 일반적으로 printf는 출력한 문자열 개수를 리턴하지만 도중에 문제가 생기면 -를 리턴한다.
    //예를들어 freopen("input.txt", "r", stdout); 표준 출력을 input.txt로 바꾸어주지만 읽기모드로 할때 -1리턴
    cout << result << endl;
    bool b = cout.fail(); // return형을 알려주니 이런식으로 예외처리도 가능.  
    double answer = divide(10,0);
    if(answer == 0)  cout << "error" << endl;
    else cout << answer << endl; // 이 방법이 전통적인 예외처리 방식이나 상당히 비효율 적이다. 
    // 함수를 사용하는 사람이 예외사항을 handling 해주고 싶은 방법은 다음과 같다
    // try-catch : 밑에있는 throw만 사용하면 프로그램이 종료되지만 try-catch와 같이사용하면 쓰면 종료되지 않음

    // throw  및 try-catch 사용예시
    std::set_terminate(terFunc);// throw가 되면(std::terminate()가 호출되면 설정된 함수 실행
    // terminate 와 abort와 다른점은 위 처럼 함수등을 세팅가능
    try{
    cout << divideWithThrow(10,0) << endl; // throw 가 발동되면 std::terminate() 를 호출해서 함수를 종료시킨다
    }catch(const char* e){ // try내부에서 throw 된게 있으면 여기서 잡아서 매개변수 e에 저장된다
        cout << e << endl;
    }// 만약 어떤 throw든 다 잡고싶으면 catch(...) 를 사용하면 된다.
    catch(...){
        cout << 1 << endl; // 현재는 string형이므로 위에서 잡힌다.
    }
    // 만약 catch에 알맞은 형식이 없다면 catch가 되지않아서 강제종료

    try{
        tryCatchTest();
    // }catch(Parent& parent){
    //     cout << "Parent" << endl;
    // }catch(Child&){
    //     cout << "Child" << endl;
    // }
    }
    catch(std::exception& e){
        cout << e.what() << endl; // (...) 과 같은기능. 근데 오류메시지를 잡을수 있다. virtual 함수라 구현해주자.( throw 로 잡아온거 what하면 문구뜸)
    }
    // output : parent, try-catch는 위처럼 클래스 인스턴스를 catch가능하다. try-catch는 위에서 부터 검사하므로 여기선 parent에 catch 된다


    //RAII;
    try{
        
        int* i = new int;
        terFunc(); // throw으로 try-catch에 잡혀서 i에 더이상 접근할 수 없지만 메모리에서 해제되진 않았다.
        //이럴떄 사용하는게 RAII이다. (스코프를 벗어나면 소멸자를 호출하는 매커니즘을 이용해 리소스를 해제해주는 매커니즘이 RAII이다. 뿐만 아니라 DB connection 을 해제할때등 사용)
        //위에서 RAII클래스 하나 선언
        RAII raii; // 여기는 블록지역변수라 이 블록을 탈출하면 자동으로 소멸자가 실행되므로 해제된다. 
        // 클래스 구현하지 않아도 unique_ptr사용하면 된다
        std::unique_ptr<int> i; // 블럭을 벗어나면 소멸자 호출하며 해제
        //std::unique_ptr<Test>test(new Test()); 로 클래스 선언 및 해제가 가능하다

    }catch(const char* e){
        // 여기에 i를 상위 스코프에 선언하고 이부분에 delete i 를 해줄순 있지만 모든 catch마다 해줘야하고 또한 예상치못한 상황도 발생 가능
        cout << e << endl;
    }

    // noexcept 컴파일러 최적화에 사용한레후
    // 형식은  :  리턴형 함수명 (매개변수) noexcept {} 이다
    // 과거에는 : 리턴형 함수명 (매개변수) throw(int,float,std::exception) 처럼 발생할수 있는 exception을 안에 채워줬다.
    // noexcept(true)  = exception이 난다, noexcept(false) = exception이 안난다. 기본적인 함수들은 noexcept(false) 이다.
    // 만약 noexcept 를했는데 throw를 한다면 terminate를 호출한다. (try catch에 넣어줘도.)
    //noexcept(noexcept(func2)) ;; func2의 noexcept성질을 그대로 이어감
    // noexcept를 쓴다면 except를 위한 스택확보를 하지 않아도 되므로 최적화된다.

    try{
        func_n(); // func_n은 noexcept가 되어있어 try안에 있지만 강제종료가 된다. 내부 &&가 가능하다
    }catch(...){
        cout <<"hello" << endl;
    }

    return 0;
}
 // 함수자체를 try block으로 지정해줄 수 있다.