#include <iostream>
#include <vector>
using namespace std;

class Queue : protected std::vector<int>{ // 원래대로라면 클래스 내부에 std::vector<int> v 해서 v.push_back()이런식으로 접근해야한다
    public:
        virtual void push(int value){
            push_back(value); // vector 내부 함수를 사용하는부분이 private로 간주되어 클래스 내부에서만 사용가능
            //외부입장에서는 선언한것만 사용가능하므로 has-a
        }
        void pop(){
            pop_back();
        }
        int top(){
            return back();
        }

        
};
// protected상속도 비슷한개념이다. 다만 그것을 상속받는 함수들이 인터페이스를 볼수있다는게 차이점이다.

class A{
    public:
    void func(){

    }
};

struct B : A{

};

class PriorityQueue : public Queue{ // 앞에 public안붙이면 기본적으로 private 상속이므로 붙여라

    public:
        void pop(){
            pop_heap(begin(), end());
            Queue::pop();
        }

        virtual void push(int value) override{
            Queue::push(value);
            push_heap(begin(), end()); // 힙은 특징상 자동정렬됨
        }

        int top(){
            return front();
        }

};


class Base{
    public:
        Base(){
            cout << "BASE 0 " << endl;
        }
};

class BaseA : virtual public Base {
    public:
        BaseA(){
            cout << "BASE A" << endl;
         }
};

class BaseB : virtual public Base {
    public:
        BaseB(){
            cout << "BASE B" << endl;
        }
};

class BaseC : public BaseA, public BaseB{
    public :
        BaseC(){
            cout << "Base C" << endl;
        }
};

int main(){
    // is-a 관계 : Shape -> Circle, Rectangle, Triangle... 과같은 연관관계
    // 보통 is-a 관계는 public 그동안 해왔던 상속을 통해 표현한다.
    
    // has-a 관계 : Rectangle -> width, height 와 같은 포함관계
    // 보통 has-a관계는 private or protected 상속을 통해 표현한다.
    Queue q;
    q.push(100);
    q.push(200);
    cout << q.top() <<endl; // 여기서 private 와 public 상속의 차이가 들어난다. public으로 상속했다면 vector에 포함된 모든 인터페이스가 노출된다.
    //private 로 상속하면 직접 정의한것만 노출된다

    // std::vector<int> v , v.push() 이런식으로 할수있지 않나?
    // 저렇게 구현할 수 있다면 저렇게 하는게 좋다. private 상속은 왠만하면 하지 않는것이 좋다. 의존성, 가시성등 측면에서 private가 좋지않다

    PriorityQueue prQ;
    prQ.push(100);
    prQ.push(0);
    prQ.push(10);
    prQ.push(30);

    for(int i = 0; i < 4; i++){
        cout<< prQ.top() << endl;
        prQ.pop();
    } 
    // 위 예제가 protected 상속 사용한 예시. 설명은 위 참조
    
    
    B b;
    b.func(); // 다만 구조체는 기본이 public 상속이다.

    //다중상속은 위 상속에서 크게 달라질건 없다. 상속된 객체가 2개가 됬을뿐. 
    //다중상속의 문제점인 diamond of death에 대해 알아보자.
    
    //클래스 구조는 다음과 같다
    //      Base
    // BaseA    BaseB
    //      BaseC

    BaseC bc;
    /* 
    출력값 
    BASE 0 
    BASE A
    BASE 0 
    BASE B
    Base C
    */
   // BaseC는 Base를 상속받긴 했지만 두번상속받은것을 볼수 있다. 즉 BaseA -> Base ,BaseB -> Base 이런구조를가지지만 이것은 제한하려면 상속할때 virtual 키워드를 붙여주면 
   // BaseA, BaseB, Base 같은 선형구조로 생성한다

   /*
   virtual을 붙여주고 출력값
    BASE 0   
    BASE A
    BASE B
    Base C
   */
  // virtual없이 다중상속을 하면 위 문제도 생기고, BaseC에서는 Base C : Base A(20) 같은 생성자 지정도 해줄수가 없다
    BaseA* ba = new BaseC;
    Base* bb = ba; // 모호함으로 이것도 안됨. A를 기준으로 자신을 가리킬지, B를 기준으로 가리킬줄 모르니 , 위 라인에 추가한거처럼 명확히
    // 이밖에도 다중상속에는 제한이 많으므로 사용자제, 보통 인터페이스에서만 가끔 사용함
    // 대표적으로 iostream이 다이아몬드 상속을 사용하긴함 iosBase, isteam, ostream, iostream의 순서로 구조라.
    // 굳이 사용한다면 다이아몬드 상속, 함수의 모호함을 주의해서 사용해라~
    return 0;
}