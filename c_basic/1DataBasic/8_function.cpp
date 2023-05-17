#include <iostream>

using namespace std;

struct Node;

int abssum(int, int);
int fac(int);
int fibo(int);

void PostOrderTree(Node*);
void InOrderTree(Node*);
void PreOrderTree(Node*);
void recruit(int);

struct Node{
    int value;
    Node* left;
    Node* right;
};

int main(int argc, const char* argv[]){ // int argc 뒤에 argv의 인자 개수를받는다
                                        // argv[0]에는 실행파일의 경로+이름이 들어간다, argv[1]~ 는 실행시 같이 넣어준 명령줄 인자가 들어간다
                                        //Ex) ./8_function 1 2 -> argv[0] = 경로 + 이름, argv[1] = 1, argv[2] = 2
    cout << argv[0] << endl; // /Users/bagjiseong/Desktop/c++/c_basic/c_basic/1DataBasic/8_function

    cout << abssum(-1,10) << " " << abssum(10,10) << endl; // 아래있는 함수를 인식못함 -> 함수 프로토타입을 위에 선언해줘야함

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

    return 0;
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
