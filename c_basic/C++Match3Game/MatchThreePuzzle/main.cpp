
#include <QtWidgets/QApplication>       // Application
#include <QtWidgets/QGraphicsScene>     // Object를 띄우기 위한 Scene
#include <QtWidgets/QGraphicsRectItem>  // Item
#include <QtWidgets/QGraphicsView>      // 화면 floating 하기 위함

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);         // Application
    QGraphicsScene scene;               // 여기에 만든 오브젝트들이 담긴다.

    QGraphicsRectItem rect(0,0,300,100);// (x,y,width,height)
    scene.addItem(&rect);               // pointer로 넘겨받는다. 복사방지

    // 현재 scene안에 rect가 포함되어 있으나 viewing역할은 없다. 이상태면 백그라운드로만 돌아감
    QGraphicsView view(&scene);         //
    view.showFullScreen();
    // 비로소 화면에 넘겨졌다. Cpp는 메모리 절약을 위해 주소값을 넘겨주는 경우가 많으므로 익숙해지자.
    
    return a.exec();
}
