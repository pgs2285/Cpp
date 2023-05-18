#include <iostream>
#include <typeinfo>
using namespace std;

struct Node;
struct Weapon;

int abssum(int, int);
int fac(int);
int fibo(int);

void func(int, char (*argv)[5]);
void PostOrderTree(Node*);
void InOrderTree(Node*);
void PreOrderTree(Node*);
void recruit(int);
void UpgradeWeapon(Weapon*);
void arrayFunc(int* arr);
void intFunc(int argc, int (*arr)[5]);

Weapon UpgradeWeaponByValue(Weapon);

struct Node{
    int value;
    Node* left;
    Node* right;
};

struct Weapon{
    int attack;
    int shield;
};

int main(int argc, const char* argv[]){ // int argc 뒤에 argv의 인자 개수를받는다
                                        // argv[0]에는 실행파일의 경로+이름이 들어간다, argv[1]~ 는 실행시 같이 넣어준 명령줄 인자가 들어간다
                                        //Ex) ./8_function 1 2 -> argv[0] = 경로 + 이름, argv[1] = 1, argv[2] = 2
    cout << &argv[0] << endl; // /Users/bagjiseong/Desktop/c++/c_basic/c_basic/1DataBasic/8_function
    cout << &argv[1] << endl;
    cout << abssum(-1,10) << " " << abssum(10,10) << endl; // 아래있는 함수를 인식못함 -> 함수 프로토타입을 위에 선언해줘야함

    // char* argv[] -> 더블포인터이다. char** argv 랑 똑같음
    

    recruit(5); 
    // 재귀함수
    // 재귀함수는 탈출조건이 필수임
    cout << "5! = " <<(fac(5)) << endl;
    cout<<"재귀 피보 : " << fibo(5) << endl;

    //이진트리를 위한 노드 10개를 생성한다

    
    Node node1{0};
    Node node2{1};
    Node node3{2};
    Node node4{3};
    Node node5{4};
    Node node6{5};
    Node node7{6};
    Node node8{7};

    node1.left = &node2;
    node1.right = &node3;
    node2.left = &node4;
    node2.right = &node5;
    node3.left = &node6;
    node3.right = &node7;
    node4.left = &node8;

    PreOrderTree(&node1);
    cout << endl;
    InOrderTree(&node1);
    cout << endl;
    PostOrderTree(&node1);


    Weapon weapon = {10,20};
    cout << "\n공격력 : " << weapon.attack <<" 방어력 : " << weapon.shield << endl;
    UpgradeWeapon(&weapon);
    cout << "공격력 : " << weapon.attack <<" 방어력 : " << weapon.shield << endl;
    weapon = UpgradeWeaponByValue(weapon);
    cout << "공격력 : " << weapon.attack <<" 방어력 : " << weapon.shield << endl;
    // 값으로 넘겨주면 안바뀜 (scanf가 주소값을 넘겨받던이유도 같다.)
    //혹은 그냥 return쓰면 된다
    int arr[4] = {1,2,3,4};
    arrayFunc(arr); // 배열을 넘겨받을때는 사이즈에 대한 정보를 잃어버린다.
    char str[][5] = {"abcd", "efgh"};
    func(2, str);

    int dimen[][5] {
        {1,2,3,4,5},
        {3,2,1,5,4}
    };
    intFunc(2,dimen);
    char* arg1;
    char (*arg2)[5];
    cout<<typeid(arg1).name() << " " << typeid(arg2).name()<< endl;
    int a = 1;
    int b=2;
    swap(a,b); // 참조를 사용하면 그냥보낸다 (추상화로 포인터를 숨김)
    cout << a << " " << b << endl;

    float f1 = 1.0f;
    const float& f = f1;
    f1 = 10.0f;
    cout << f1 << "  " << f << endl; //MSVC에서는 값이 변하지않음 , 참조객체를 직접 참조하지않기때문
                                    // G++에서는 값이 변경됨, 참조객체를 직접참조하기 때문
    

    return 0;
}

//char ** = char* argv[] =  // 실제로 연속되어있지않음
//|"9_function의주소(1바이트)||주소||주소|
//  |
//   -->  "9_function\0"....
//이부분은 2중포인터라 알아서 포인터 비트수만큼 메모리에 접근하겠지만

//char [2][5] = char (*argv)[5] //연속되어있음
// |"abcd\0"의 주소(5비트)||"efgh\0" 의주소|
// 메모리를 읽을 크기를 정해주어야함

//번외) char* argv[5]  vs   char (*argv)[5]
// 1.  길이가 5인 문자열 포인터 배열을 선언. 즉 char* 타입의 포인터가 5개 생성된다
// 2.  길이가 5인 문자 배열을 가리키는 1차원 배열을 선언
//char* argv[5]에서는 char* 타입의 포인터가 5개 생성되므로 각각의 원소는 포인터의 크기(4바이트 또는 8바이트)만큼의 메모리 공간을 차지
//char (*argv)[5]은 각각의 원소가 5개의 문자를 저장할 수 있는 1차원 배열들이 모인 2차원 배열을 가리키는 포인터이므로, 포인터의 크기만큼의 메모리 공간을 차지

void intFunc(int argc, int (*arr)[5]){
    for(int i = 0; i < argc; i++){
        for(int j = 0; j < 5; j++){
            cout << *(arr[i] + j) << endl;
        }
        
    }
    
    
}

void swap(int& px, int& py){ // 참조는 그냥 *해줄필요없이 쓰면됨
    int tmp = px;
    px = py;
    py = tmp;
}

void func(int argc, char (*argv)[5]){
    

    cout << *argv << " " << *(argv + 1) << endl;

    cout << argv << " " << (argv + 1) << endl;
    
}


void arrayFunc(int* arr){
    *arr += 1;
    
}

Weapon UpgradeWeaponByValue(Weapon weapon){
    weapon.attack += 10;
    weapon.shield += 10;
    return weapon;
}


void UpgradeWeapon(Weapon* weapon){ // 이렇게 주소로 전달해야 값이 바뀐답니다
//값이 변경되었지 않을음 보장하려면 const Weapon*을 매개변수로 받아라
    weapon->attack+= 10;
    weapon->shield+= 10;

}


void PreOrderTree(Node* nodes){
    
    if(nodes == nullptr) return;
    cout << " "<< nodes -> value; //preorder
    PreOrderTree(nodes->left); // 왼쪽부터 순회
    PreOrderTree(nodes->right);
    //
}
void InOrderTree(Node* nodes){
    
    if(nodes == nullptr) return;
    
    InOrderTree(nodes->left); // 왼쪽부터 순회
    cout << " "<< nodes -> value; //Inorder
    InOrderTree(nodes->right);
    //
}
void PostOrderTree(Node* nodes){
    
    if(nodes == nullptr) return;
    
    PostOrderTree(nodes->left); // 왼쪽부터 순회
    PostOrderTree(nodes->right);
    cout << " "<< nodes -> value; //postOrder
    //
}

void recruit(int num){ // 재귀함수 예시
    if(num <= 0) return;
    cout << "재귀함수 도는중 : " << num << endl;
    recruit(num-1);
    cout << "재귀함수 반복종료, 잔여값 : " << num << endl; 
}

int abssum(int x, int y){ // 함수
    x = x > 0 ? x : -x;
    y = y > 0 ? y : -y;
    return x+y;
}

int fac(int x){ //재귀함수 팩토리얼
    if(x == 1) return 1;
    else return x * fac(x-1);
}


int fibo(int x){ //재귀함수 피보나치
    if (x<= 1) return 1;
    return fibo(x - 1) + fibo(x - 2);
}

