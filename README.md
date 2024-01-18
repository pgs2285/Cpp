# Cpp
Cpp 
## Unreal, DirectX 를 위한 CPP 연습

### 학습한 내용은 cpp파일에 주석으로 정리
0. c_basic 폴더에 있음
1. 1_DataBasic C++의 기초
2. 2_modernCpp ModernC++ 
3. C++Match3Game[ - 애니팡과 같은 Match3Game을 제작해보기](https://github.com/pgs2285/Cpp_MatchThreePuzzle_Qt)

## 보완 
C++20 이후로 추가된 spaceship operator은 c++20 을 자세히 알아볼때 다시 학습예정.

## 다시 해볼것
operator를 사용해서 python의 range함수 구현해보기(해더파일 분리하고.)


## C++20 Module 
gcc로 컴파일시 -fmodules-ts 옵션을 넣어주여야 한다.
현재까지는 실험적인 기능이라 이런게 있다고 생각하고 넘어가자.
* (실제로 std.core 에서 std::cout 사용시 integer은 받지못하지만 character는 받는다)

## qt를 통한 애니팡과 같은 Match Three Puzzle 을 제작해보자
Qt선정 이유
Unreal - 간단한 2d게임을 만들긴 너무 과하다
OpenGL, Vulkan 과 같은 그래픽 API -  너무 밑단부터 제작해야하고, 그전에 그래픽스의 과정 자체를 이해해야한다. 
Qt를 사용해 제작하면 멀티플랫폼에 유리하고, 개발도 쉬우므로 적당하다. 즉 Win32나 MFC도 알맞지 않았다.

### Qt란?
C++을 주로 사용하는 GUI프레임워크이다.
초기에는 크로스플랫폼 GUI 라이브러리로 시작했고 UI 개발 도구, 번역 작업을 위한 도구와 C++ 개발에 필요한 많은 기능(UI, XML, 네트워크, SVG, Animation, Container Class 등등)을 제공하는 범용적인 응용프로그램 프레임워크가 되었다
