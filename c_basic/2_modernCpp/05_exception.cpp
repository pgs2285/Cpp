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
    cout << "TerFunc" << endl;
    exit(123); // 정상종료
}
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
    





    return 0;
}