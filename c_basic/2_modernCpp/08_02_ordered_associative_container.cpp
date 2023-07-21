#include <iostream>
#include <map> 
using std::cout;
using std::endl;


int main()
{
    std::map<int, std::string> m{
        {1, "value1"},
        std::pair(2, "value2"),
        std::make_pair(3, "value3") // 이렇게 초기화를 할 수 있지만 c++17 부터 가능하다. 
    }; // 왼쪽 : key, 오른쪽 : value
    // 즉 key가 value에 매핑된다(인덱스 역할을 한다)
    m[1] = "value1";
    cout << m[1] << endl;
    cout << m[4] << endl;
    cout << m.size() << endl; // 없는 key를 참조하면 사이즈 증가. value는 default로 초기화

    //출력시 아래와 같이
    for(std::pair<int, std::string> p : m) //트리의 정확도를 높이기 위해 pair의 key값은 const로 선언되어있다.
        cout << p.first << " : " << p.second << endl; // auto& p : m 으로 해도 된다.

    for(std::map<int, std::string>::const_iterator iter = m.cbegin(); iter != m.cend(); iter++)
    {
        cout << iter->first << " / " << iter->second << endl; // iter->first == (*iter).first
        // 변경을 방지하기 위해 const_iterator를 사용한다.
    }
    //m[1] = 1 로 변경하면 값이 바뀌지만 m.insert({1, 1})로 하면 값이 바뀌지 않는다.
    if(m.find(4) != m.end()) // find는 iterator를 반환한다. 찾지 못하면 end()를 반환한다. 
        cout << "found" << endl;
    else
        cout << "not found" << endl;
    
}