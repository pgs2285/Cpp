#include <cstdio>
#include <iostream>
#include <iomanip>
#include <limits>

int main(){
    // printf - c표준이나 다른 언어에서도 파생형 많음 
    // %d, %i = 정수형
    // %u = 부호없는 정수형 (음수를 넣으면 unsigned int의 최대값에서 빼줌)
    // %c = 문자(char)
    // %f %lf = 각각 float형 double형 이지만 printf에서는 승급 규칙때문에 다 double로 받으므로 굳이 구분할 필요 X
    // %x = 16진수 %o = 8진수 %b = 2진수     //16진수 경우 %X로 대문자로 출력가능
    // %hhx = unsigned char
    // %010.1f = 10자리수, 빈공간 0으로 , 소수점 한자리만 출력
    printf("%010.1f\n", 3.141592f);
    printf("%10.1f\n", 123.456f);

    //printf 는 prints formatted output to stdout 이라는 의미를 가지고있다. std값을 조정해주면 파일에도 출력가능
    freopen("output.txt", "w", stdout); // stdout = output.txt로 바꿔줌
    printf("hello World");
    freopen("/dev/tty", "w", stdout);    // 기본 출력을 터미널로 변경



    // scanf - read formatted input from stdin
    // scanf는 c표준이니 주소값을 받는다는거만 주의.
    // scanf의 return값은 입력받은 변수의 개수를 반환함
    int num, num1;
    int cnt; // cnt에 입력받은 변수의 개수를 반환함
    if(scanf("%d %d", &num, &num1) == 2){ // int 값이 2개들어왔을때만 출력
        printf("%d %d \n ", num, num1);
    }

    scanf("%d + %d", &num, &num1); //옆 형식대로 입력된 값만 집어넣음
    printf("%d %d \n", num, num1);

    //scanf는 printf와 다르게 메모리에서 차지하는 비트수가 달라 %lf (double) %f(float)를 구분함
    
    // %c 는 ENTER를 입력받음 (\n ASCII : 10)
    char c;
    scanf("%c", &c);
    printf("0 : %c\n", c);
    // fflush(stdin); // stdin의 버퍼를 비워주지만 c표준에서는 정의되어있지 않음
    // getchar(); // newline 을 하나 먹어줌
    while(getchar() != '\n'); // \n이 나올때까지 대기
    scanf("%c", &c);
    printf("1 : %d\n", c); 

    //마찬가지로 freopen을 통해 파일을 읽어올 수 있다
    char c1,c2;
    freopen("input.txt", "r", stdin);
    scanf("%c", &c1);
    while(getchar() != '\n');
    scanf("%c", &c2);
    printf("line 1: %c \n line 2: %c\n", c1,c2); // 
    freopen("/dev/tty", "r", stdin); // 기본 입력을 터미널로 변경


    // cout - writes to the standard c output stream stdout
    //cout의 다양한 형태
    std::cout.put('a'); // 문자 하나만 출력
    std::cout.write("hello", 5)<<std::endl; // 문자열 출력 (문자열, 출력할 문자열의 길이)
    std::cout << "abc" << std::endl; 

    std::cout.width(10); // 출력할 문자열의 길이를 10으로 설정
    std::cout.fill('*'); // 빈공간을 *로 채움   영구적이지 않고 다음 출력들만 
    std::cout.setf(std::ios::left); // 왼쪽정렬
    std::cout << "abc" << std::endl; // output : *******abc
    std::cout.unsetf(std::ios::left);
    

    std::cout.precision(5); // 소수점 5자리까지 출력
    std::cout << 0.141592 << std::endl; // output : 3.1416

    std::cout.setf(std::ios_base :: showpos); // 앞에 부호까지, 해제 직전에는 계속 적용됨
    std::cout << 123.456 << std::endl; // output : +123.456
    std::cout.unsetf(std::ios_base :: showpos); // 해당 세팅 해제

    //ios_base 종류 - https://en.cppreference.com/w/cpp/io/ios_base

    std::cout.setf(std::ios_base::left, std::ios_base::adjustfield); // 이와같이 적용 필드를 지정해야할때도 있음 (left, right, internal)
    std::cout.unsetf(std::ios_base::adjustfield); // 해당 세팅 해제

    std::cout<<std::setw(10)<<std::setfill('*')<<std::setprecision(5)<<std::setiosflags(std::ios_base::showpos)<<123.456<<std::endl; // 위의 세팅들을 한번에 적용가능
    //출력 결과를 영구적으로 지정하는 것은 flags() 함수와 마찬가지로 전역적으로 적용하기 때문에 권장되지 않는다. 대신, setfill() 함수와 setw() 함수는 임시로 사용하는 것이 좋습니다    
    std::cout.unsetf(std::ios_base::showpos); // 해당 세팅 해제
    //cin - reads from the standard input stream stdin
    int a = 0;
    if(std::cin >> a) { //int 값만 들어갔을때(성공했을때) 실행
        std::cout << "a : " << a << std::endl;
    }

    //cin 또한 개행을 입력받기 때문이 cin.ignore()를 통해서 개행을 먹어줘야함
    std::cout<<"개행입력방지:"<<std::endl;
    // if(std::cin.fail()) //int형에 char을 넣는등 오류가 발생하면 1, 아니면 0
    //     std::cin.clear();// 에러플래그를 초기화

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 개행을 만날때까지 streamsize::max 만큼무시
    std::cin >> a;
    std::cout<<"a1 : "<<a<<std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 개행을 만날때까지 streamsize::max 만큼무시
    std::cin>>a;
    std::cout<<"a2 : "<<a<<std::endl;

    //cin 도 setf 가능함. 참조링크 - https://en.cppreference.com/w/cpp/io/basic_ios/setf
    std::cin.setf(std::ios_base::hex, std::ios_base::basefield); // 16진수로 입력받음
    std::cin>>a;
    std::cout<<"a3 : "<<a<<std::endl;
}
