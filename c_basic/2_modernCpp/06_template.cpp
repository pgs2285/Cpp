#include <iostream>

using namespace std;


template<typename T> //typename 대신에 class라고 작성해도 된다
// 또한 매개변수처럼 여러개 작성가능 template<typenameT, typename S>
//generic프로그램을 만드는데 도움이된다
void Swap(T& x, T& y) 
{
    T tmp = x;
    x = y;
    y = tmp; 
}

template <int N, typename T>
void func(T (&nums)[N]){ // 원래는 참조로 넘길땐 int (&nums)[4] 하고 배열의 크기가 맞지 않았으면 오류를 반환했었음
    for(int i = 0; i < N ; i++){
        cout << nums[i] << endl;
    }
}

template <typename T>
class Queue{ // 템플릿을 이용한 Queue 간단구현
    private: 
    size_t _size; // size_t = unsigned long
    size_t _capacity;
    T* _items;

    public:
    Queue() 
        : _size(0)
        , _capacity(1)
        , _items(new T[_capacity])
    {

    }

    ~Queue()
    {
        delete[] _items;
    }

    void push(T item)
    {
        if(_size < _capacity)
        {
            _items[_size++] = item;
        }
        else
        {
            size_t newCapacity = _capacity * 2; // queue의 크기가 capacity를 초과하면 capacity에 2를 곱해주고 
            T* oldItems = _items;
            T* newItems = new T[newCapacity]; // new Items에 옮긴후
            std::copy(oldItems, oldItems + _capacity, newItems);

            _capacity = newCapacity;
            _items = newItems; // 다시 대입해줌

            delete[] oldItems;
            push(item);
        }
    }

    void pop(){
        if(_size > 0)
        {
            --_size;
        }
        else
        {
            throw std::out_of_range("Queue Underflow");
        }
    }

    T& top();
    
};

template <typename T>
T& Queue<T> :: top() // 코드 분할
{
        return _items[_size - 1];
}

int main(){ 
    int x(10), y(20);

    Swap<int>(x,y); // 만약 함수로 구현하면 구현된것만 넘기기가 가능함, float,char등 다 만들어 주어야 한다.
    //함수에 적용할꺼라 함수템플릿
    //template자체는 함수가 아니라 호출하는 순간에 함수코드(함수에 대한 기계어가) 만들어진다
    cout << x << "  " << y << endl;
    float arr[4] = {1,2,3,4};
    func(arr); // 배열을 참조,포인터 뿐만 아닌 template 함수를 통해서도 넘겨줄 수 있다.
    //(템플릿의 컴파일 타임의 추론에 의해 알아서 넘어감) 물론 func<4, float>(arr) 이 정석 

    Queue<int> q_i;
    Queue<string> q_s; // 변수형마다 구현해줄 필요없이 템플릿 사용하면 된다.
    q_i.push(10);
    q_i.push(20);
    q_i.push(30);
    q_i.push(40);
    cout << q_i.top() << endl;
    q_i.pop();
    cout << q_i.top() << endl;

    q_s.push("ABC");
    q_s.push("DEF");
    q_s.push("HIJ");
    q_s.push("KLM");
    cout << q_s.top() << endl;
    q_s.pop();
    cout << q_s.top() << endl;

    Queue<int> q;
    try{
        q.pop();
    }catch(std::out_of_range& e)
    {
        cout << e.what() << endl; // throw zocl gn cnffur
    }

    // 두종류 모두 잘되는걸 볼수 있다. 물론 char, float 다 됨.

}