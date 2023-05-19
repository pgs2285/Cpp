#include <iostream>
using namespace std;

int main(){
    //if문에 semi colon을 붙인다면?
    if(false);{
        cout << "Hello World" << endl; //당연히 그냥 실행된다 ㅎㅎ statement를 종료시켰기 때문에
    }
    int num1, num2;
    if(int count = scanf("%d %d", &num1, &num2)){ // 스코프는 좁을수록 좋다. 추후 변수관리를 위해서 (scanf는 입력받은 개수를 반환함)
        cout << "입력받은 숫자의 개수는 " << count << "개 입니다." << endl;
    }
    else{
        cout << "입력실패" << endl;
    }

    //위 스코프를 벗어나면 count변수는 소멸됨
    
    //c++17 이후부터는 아래와 같이 if문에 초기화를 할 수 있음
    if(int a,b; int count = scanf("%d %d", &a, &b)){ //그렇다고 int a,b; 만 넣지마라... 조건식은 필수임
        cout << "입력받은 숫자의 개수는 " << count << "개 입니다." << endl;
    }
    else{
        cout << "입력실패" << endl;
    }

    //switch - case
    //switch문에는 break가 없으면 다음 case문을 실행함
    int switchTest;
    cout <<"변수 입력(10,20,30):";
    cin >> switchTest;
    switch(switchTest){ //다른사람이 보면 의도한 것인지 아닌지 알기 힘듬. 또한 gcc 에서는 warning을 띄움
        case 10:
            cout << "10" << endl;
            // [[fallthrough]] //이렇게 명시적으로 break를 건너뛰는것을 명시할 수 있음 이것또한 g++17부터
        case 20:
            cout << "10 or 20" << endl;
        break;

        case 30:
            cout << "30" << endl;
        break;
    }
    //switch는 범위 연산이 안됨. 하지만 이런 특성때문에 성능적으로 이득을 보긴함 (if는 조건문이 일치할때까지 모든 조건을 다 비교함, switch-case는 내부적으로 테이블이 있어 한번만)
    //특수한 사항이 아니면 유의미한 차이는 없긴하다.

    //switch case 도 마찬가지로 scanf 안에 사용가능 cin은 자기자신 반환이라 어렵고.

    //for문
    /*for (1;2;3){
        4
    }
    1->2->4->3 ->(2->4->3)->조건false->끝
     순으로 가는거만 알아둬라
    */
   for(int i =0, j = 0; i <10 && j < 10; i++, j+=3){ //이런식으로 복합 사용가능 시간복잡도는 똑같이 O(n)
        cout<<i<<" "<<j<<endl;
   }
   //문자도 된다
    for(char c = 'a'; c <= 'z'; c++){
         cout << c << " ";
    }
    int tmp = 4;
    
    // do-while 문 while괴는 다르게 끝에 semi colon이 붙음
    do{
        cout << "do-while" << endl;
    }while(false); // 무조건 한번은 실행하고 조건을 돌음

    //goto 
    //스파게티코드의 원인, 인터프리터,하드웨어,운영체제등 제한된 환경에서만 사용.

    cin >> tmp;
    if(tmp == 10) goto go;
    
    cout<<"not goto"<<endl;
go:
    cout<<"goto"<<endl;

    

}