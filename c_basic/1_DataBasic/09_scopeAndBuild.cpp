#include <iostream>
#include <string>

using namespace std;

int sum(int total, int num);

#define SQUARE(X) X*X

namespace CompanyB{
    int x;
}


int main(int argc, const char* argv[]){
    int total = 0;
    for (int i = 1; i < argc; i++){

        string arg(argv[i]);
        int num = stoi(arg);
        total = sum(total, num);

    }
    cout << "총 합 : "<<total << endl;

    //g++ -c (빌드할 파일이름)를 하면 컴파일하고 object파일을 생성해준다 (분리컴파일시 많이 사용된다.)
    // 컴파일 없이 바로 바로생성시 main이 없으면 오류나기 때문
    // 컴파일의 결과는 .o파일 (목적파일) // -c옵션은 컴파일만하고 링크는 하지않음
    //-o 옵션으로 컴파일 할 때, 생성된 목적 파일(myProgram.o)을 지정한 출력파일명(myProgram)으로 바로 실행 가능한 파일(myProgram)로 생성해주는 것
    //전처리기preprocessor: 소스 코드의 주석 제거, define을 치환하는 기능을 합니다. .i파일로 생성되어있다. 명령어는 -S
    //이전에 생성한 inline이나 매크로등은 이과정을 통해 10*10같은 숫자로 바뀐다
    SQUARE(10); // ./09_buildTestOutputs/09preprocessor.i 의 맨 밑줄을 보면 10*10이 있음

    //scope 종류 
    //1. 블록스코프

    int a = 0;
    cout << &a << " : " << a <<endl;
    {
        int a = 10; // 여기에 static쓰면 블록이 끝나도 해제되지 않지만 접근불가임(주소값접근 제외)
        cout << "InBlock" <<endl;
        cout << &a << " : " << a <<endl;
    }
    cout << &a << " : " << a <<endl;

    //위 예시처럼 블록안에서는 범위따로적용, 블록을 벗어나면 사라짐

    //2. 전역 스코프
    //함수 외부에 선언된 것들을 의미함
    // 선언은 한번만 가능하다(같이 빌드되는 파일들 포함해서)
    //나머지 다른애들은
    extern int x; // 어딘가에 x가 정의되어있다. (다른파일 어딘가에서 전역변수 가져올때 사용)
    cout << x <<endl;
    
    //3. 파일스코프 (한 파일에서만 전역 변수 선언할때)
    static int y;

    //4. 열거형 스코프 
    enum struct type{ a,b,c};
    type::a; // ::로 접근

    //5. 네임스페이스
    //사용예시 : 타회사랑 작업시 각자 작업후 merge할때 둘다 같은 변수명, 같은 struct명 등을 사용하면 이름이 겹쳐 문제가 발생 
    //x는 namespace CompanyB{} 로 둘러쌓여있음. 이럴때
    CompanyB :: x = 100;
    cout << CompanyB :: x<<endl;
    //만약 특정 변수만 네임스페이스 생략하고싶으면
    using std::cout;


    //공간
    //1. 자동공간 : 블럭을 벗어나는 순간에 메모리에서 사라짐 (메모리 스택공간 저장)
    {
        int a = 100000000;
    }
    //2. 정적공간 : 프로그램이 메모리에 올라가면 데이터 영역에 저장되는데 (스택과 힙영역이랑 다름)프로그램이 종료되야 해제
    {
        static int a = 10000000;
    }
    //3. 동적공간 : Heap이라는 영역에 저장되는데 자동변수나 정적변수처럼 이름이 있지않다. 그래서 두개에서 여길 가리켜야함.프로그래머가 명시적으로 해제해 주어야함
    {
        int *p = new int; // 여기선 new가 동적공간
        delete p;
    }
}



//컴파일러compiler: 어셈블리 파일로 변환합니다. 어셈블리 코드는 CPU 명령어 조합이며, 어셈블리어는 CPU에 의존적입니다. 
//어셈블러assembler: 오브젝트 코드 파일로 변환합니다. 오브젝트 코드는 0과 1로 이루어진 이진 코드입니다. 그리고 아직 주소 정보가 확정되지 않은 상태입니다.
//링커linker: 오브젝트 파일들을 묶어서 실행 코드 파일로 변환합니다. 운영체제가 로딩할 수 있도록 주소 정보를 할당한 파일을 만들어 냅니다. 따라서 링커는 운영체제에 의존적입니다.

//추후 project size 가 커지면 코어를 여러개사용해(컴퓨터를 여러개사용하는등) 빌드를하거나 자동화.