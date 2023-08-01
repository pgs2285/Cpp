#include <iostream>

using std::cout;
using std::endl;

int main()
{

    int&& a = 10;
    a = 20;
    cout << a << endl;
    return 0;
}