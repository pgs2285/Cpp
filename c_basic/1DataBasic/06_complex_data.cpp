#include <iostream>
#include <ctime>
#include <string>
using namespace std;
int cacheSpeed[20000][20000] = {0,};
int main(){

    //배열
    int a[3] = {1,2,3 }; //첫 배열은 1 나머지는 0으로 초기화
    int b[3];
    //배열의 사이즈 구하기
    int nSize = sizeof(a) / sizeof(int); //배열의 크기는 12 / 4 = 3
    cout << nSize <<endl;
    
    // cout<< std::size(a) <<endl; //c++ 17부터 지원하는 함수
    //이후는 배열을 복사하는 함수
    copy(a,a+3,b); //a의 0번째부터 3번째까지 b에 복사
    b[0]=3;
    cout << b[0] << endl; // 3
    cout << a[0] << endl; // 1

    int c[3];
    int d[3] = {1,2,3};
    memcpy(c,d,sizeof(d)); //메모리를 복사함
    c[0] = 3; 
    cout << c[0] << endl; // 3
    cout << d[0] << endl; // 1


    //2차원 배열을 복사하기
    int matrix[3][3] = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };
    int matrix2[3][3];
    memcpy(matrix2,matrix,sizeof(matrix)); // 1. memcpy로 복사하기
    for(int i = 0; i< std::size(matrix2); i++){
        for(int j = 0; j < std::size(matrix2[0]); j++ ){
            cout << matrix2[i][j] << " ";
        }
        cout<<endl;
    }

    std::copy(&matrix[0][0], &matrix[0][0] + 9, &matrix2[0][0]);// 2. copy로 복사하기
        for(int i = 0; i< std::size(matrix2); i++){
        for(int j = 0; j < std::size(matrix2[0]); j++ ){
            cout << matrix2[i][j] << " ";
        }
        cout<<endl;
    }


    //함수 실행시간을 보기위함
    clock_t time = clock();

    
    for(int i = 0; i< std::size(cacheSpeed); i++){
        for(int j = 0; j < std::size(cacheSpeed[0]); j++ ){
            cacheSpeed[i][j] = 1; // 이건 어느정도 빠르게 나옴
        }
    }
    cout << "함수1 실행시간 : "<<clock() - time << endl; // 1013981ms

    time = clock();
    for(int i = 0; i< std::size(cacheSpeed); i++){
        for(int j = 0; j < std::size(cacheSpeed[0]); j++ ){
            cacheSpeed[j][i] = 1; // 느림
        }
    }
    cout << "함수2 실행시간 : "<< clock() - time << endl; // 1757472ms

    //위 결과처럼 2번째 배회는 1번째보다 느림. 이유는 캐시메모리 때문.
    // 캐시메모리는 2가지 지역성이 있다. 시간지역성, 공간지역성
    // 시간지역성은 최근에 참조된 주소는 곧 다음에 참조될 확률이 높다는 것
    // 공간지역성은 최근에 참조된 주소와 인접한 주소는 곧 다음에 참조될 확률이 높다는 것
    // 위 특성때문에 캐시에 근처 메모리값을 가져와 첫번째 배회속도가 더 빠른것
    // 대용량의 배열일수록 차이가 커지니 유의해서 사용햐자.


    //문자열

    char str[] = "abc";
    cout << str << endl; // abc
    cout <<(int)str[3] << endl;// 널문자열이 들어가있음 0
    cout << sizeof(str) << endl; // 4
    cout<< strlen(str) << endl; // 3
    // str[1] =0;
    // cout << str << endl; // a
    // cout << sizeof(str) << endl; // 4
    // cout<< strlen(str) << endl; // 1
    //중간을 임의로 널문자열로 바꾸어주면 배열의 크기는 그대로이지만, 문자열의 길이는 줄어든다.
    // str[3] = 'b';
    // cout << str << endl; // null문자열을 만날때까지 다 출력할것 (컴파일러마다 살짝씩 다를수도)

    //문자열 비교
    cout << strcmp(str,"abc") <<endl;//같으면 0, str1이 크면 1, str2가 크면 -1
    char str2[2];
    strcpy(str2,str); //str을 str2에 복사 
    //strcpy역시 보안이슈가 있다. str2의 크기가 str보다 작을경우 str2에 str이 다 복사되지 않고 str2의 크기만큼만 복사되고 나머지는 복사되지 않음
    cout << str2 << endl; // 정상적으로 나오지만 메모리 영역을 침범해버림, VS에서는 경고를 띄움
    strcat(str,str2); //str2를 str에 붙임
    cout << str << endl; // abcabc
    //string이 훨씬편하니 그거쓰자...
    char str3[] = "1.1";
    cout << atoi(str3) << endl; // 1 , 문자열을 숫자로 바꿔줌
    float f = atof(str3);
    cout << f << endl; // 1.0 , 문자열을 실수로 바꿔줌

    // sprintf
    char str4[100];
    sprintf(str4, "%d %d %f", 1,100,1.234); // 문자열을 형식대로 저장함
    cout << str4 << endl; // 1 100 1.234000

    // 일반적인 cin >> 은 space를 기준으로 자르기 때문에 입력받고싶으면

    char str5[100];
    cin.getline(str5,100); // getline은 enter를 기준으로 자름
    cout << str5 <<endl;

    //string
    string str6 = "ABCDE~K"; // std::string
    //위 char 배열과 출력이 같음 다만 배열의 크기를 지정해줄 필요가 없으므로 편함
    cout<<str6<<endl;
    //이밖에도 다음과 같은 기능 포함
    string str7("abc");
    string str8("abc");
    if(str7 == str8)
        cout << "TRUE"<< endl; //등호비교도 가능하다.
    cout << str7 + str8 << endl; // 문자열 더하기
    //길이를 구하는 str.size() , str.length() 등이 있고, str.find("abc") ,  등 여러기능을 제공한다
    cout << to_string(12314314)<<endl;
    strcmp(str7.c_str(),str8.c_str()); // c_str()을 사용하면 char*로 변환가능하다.

    //stoi, stof등 여러가지 변환함수도 포함

    cout << "str 입력받기";
    getline(cin,str8); //cin으로 입력받을때는 cin.getline(str,100); 이렇게 써야함
    cout << str8;

    
    
    return 0;
}



