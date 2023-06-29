#pragma once
template <typename T>
void swap(T& a, T& b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

//여기서 명시적 구체화를 해주어야 밑에 함수들에서 호출가능 (암시적 형변환들을 구현해주자.)
template
void swap<int>(int& a, int& b);
template
void swap<float>(float& a, float& b); // 템플릿은 함수도 아니고 클래스도 아니라 link하지 못해, 기계어로 변환하지  x 이렇게 구체화 시켜주어야한다.
// 보통 템플릿들은 헤더파일에 모여서 구현시켜놓는다