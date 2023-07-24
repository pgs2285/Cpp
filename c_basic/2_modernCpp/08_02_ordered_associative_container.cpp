#include <iostream>
#include <map> 
#include <set>
#include <functional> // std::less
using std::cout;
using std::endl;


int main()
{
    std::map<int, std::string> m{
        {1, "value1"},
        std::pair(2, "value2"),//두 개체를 단일 개체로 처리하는 기능을 제공하는 구조체 즉 map의 value값은 pair이다.
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
    
    //insert를 할때마다 return값으로 pair를 반환한다.
    std::pair<std::map<int, std::string>::iterator, bool> result = m.insert({21, "value1"});
    // pair의 형태는 위와 같은데 bool은 insert가 성공했는지 실패했는지를 반환한다. 성공했다면 insert된 iterator를 반환하고 실패했다면 이전의 iterator를 반환한다.
    // 저런 복잡한 식들은 auto로 대체할 수 있다. : auto result = m.insert({21, "value1"});
    //c++17 부터는 구조적바인딩을 사용할 수 있다. : 
    auto [iter, success] = m.insert({21, "value1"});
    cout << std::boolalpha <<result.first->first << " / " << result.first->second <<" / "<< result.second <<endl;
    cout << std::boolalpha <<iter->first << " / " << iter->second <<" / "<< success <<endl;
    //이를 활용해 c++ 17부터 가능한 기능을 사용할 수 있다.
    if(auto [iter, success] = m.insert({121, "value1"}); success) // 실행후 success를 반환하므로 if문이 실행된다.
        cout << "insert success" << endl;
    else
        cout << "insert fail" << endl;

    cout << "auto를 이용한 for문 순회 " << endl;
    for(auto [key,value] : m) // 1
    {
        cout << key << " / " << value << endl;
    }
    // m.count(1) : 1이라는 key를 가진 value의 개수를 반환한다.

    if(m.find(4) != m.end()) // find는 iterator를 반환한다. 찾지 못하면 end()를 반환한다. 
        cout << "found" << endl;
    else
        cout << "not found" << endl;
    std::map<int,std::string>::iterator iter1 = m.find(1); // 물론 auto로도 가능
    if(iter1 != m.end())
    {
        cout << "found" << endl;
        cout << iter1->first << " / " << iter1->second << endl;
    }
    // m.erase(1); // key가 1인 value를 삭제한다.
    m.erase(iter1); // iterator를 통해 삭제할 수도 있다.

    //multimap : map은 key가 중복되면 안되지만 multimap은 key가 중복되어도 된다.
    std::multimap<int, std::string> mm{
        {1, "value1"},
        {1, "value2"},
        {2, "value3"},
        {2, "value4"},
        {8, "value5"},
        {3, "value6"},
    };
    cout << "multimap" << endl;
    for(const auto& [k,v] : mm)
    {
        // k는 마찬가지로 tree의 정확도를 위해 const인데 바꿀수있는 방법은 다음과 같다
        // const_cast<int&>(k) = 10;
        cout << k << " / " << v << endl;
        // map과는 다르게 첨자연산자를 통해 값을 바꿀 수 없다.
    }
    //multimap 의 insert는 중복을 허용하므로 무조건 성공
    std::multimap<int,std::string>::iterator iter2 = mm.insert({1, "value1"});
    cout << iter2->first <<  " / " << iter2 -> second << endl;

    auto lower = mm.lower_bound(1); // 1이라는 key를 가진 iterator를 반환한다.
    auto upper = mm.upper_bound(1); // 1이라는 key를 가진 iterator의 다음 iterator를 반환한다.
    cout << "lower_bound(1) : " << lower->first << " / " << lower->second << endl;
    cout << "upper_bound(1) : " << upper->first << " / " << upper->second << endl;
    for(auto iter = lower; iter != upper; iter++)
    {
        cout << " Founded Value " << iter->first << " / " << iter->second << endl;
    }

    //equal_range는 lower_bound와 upper_bound를 pair로 반환한다.
    auto range = mm.equal_range(1); // std::pair<std::multimap<int,std::string>::iterator, std::multimap<int,std::string>::iterator>
    // == auto [lower, upper] = mm.equal_range(1); // c++17 부터 가능
    std::multimap<int,std::string>::iterator lower2 = range.first;
    auto upper2 = range.second;
    cout << "eqaul_range를 이용한 순회" << endl;
    for(auto iter = lower2; iter != upper2; iter++)
    {
        cout << " Founded Value " << iter->first << " / " << iter->second << endl;
    }

    //set : map과 거의 동일하지만 key와 value가 분리되어있지 않다.

    std::set<int> s{1,2,3,4,5,6,7,8,9,10};
    std::pair<std::set<int>::iterator ,bool> result2 = s.insert(10); // 
    cout << std::boolalpha << result2.second << endl; // insert가 성공했는지 실패했는지를 반환한다.

    //multiset : set과 동일하지만 중복을 허용한다.
    std::multiset<int> ms{1,2,3,4,1,5};
    std::set<int>::iterator iter3 = ms.insert(1); // insert는 항상 성공
    cout << *iter3 << endl;
    cout << ms.count(1) << endl; // 1이라는 key를 가진 value의 개수를 반환한다.

    //set은 map과 사용할 수 있는 함수는 거의 동일하다.
    // 위 모든건 자동으로 정렬된다. (key값을 기준으로 정렬)

    //set,map의 두번째 인자에 std::less를 넣어주면 오름차순으로 정렬된다.
    std::set<int, std::less<int>> s1{1,2,3,4,5,6,7,8,9,10};
    std::map<int, std::string, std::greater<int>> m1{ // std::greater를 넣어주면 내림차순으로 정렬된다.
        {1, "value1"},
        {2, "value2"},
        {3, "value3"},
        {4, "value4"},
        {5, "value5"},
        {6, "value6"},
        {7, "value7"},
        {8, "value8"},
        {9, "value9"},
        {10, "value10"},
    };
    for(auto iter = s1.begin(); iter != s1.end(); iter++)
    {
        cout << *iter << endl;
    }
    for(auto iter = m1.begin(); iter != m1.end(); iter++) //greater를 사용하려면 key가 부등호를 지원해야한다
    {
        cout << iter->first << " / " << iter->second << endl;
    }
}

//greater를 직접 구현한다면
struct Greator{
    bool operator()(int a, int b) const
    {
        return a > b;
    }
};