//  - 모듈 : 컴파일 과정에서 모든걸 붙여주는 헤더파일을 사용하지 않고, 빌드시 한번만 가져오는 방식
// 기존 처럼 #pragma once, #ifndef #define #endif를 사용하지 않아도 된다.
// 현재 모듈은 std.core, std.io, std.thread, std.memory 등이 있지만 불안정하므로 이번엔 자체모듈 만드는 방법을 알아보자.
// 10_01_Module.ixx 파일을 참조하자

import 10_01_Module;        

int main()
{
    int a = 10;
    int b = 20;
    swap(a,b);
    return 0;
}