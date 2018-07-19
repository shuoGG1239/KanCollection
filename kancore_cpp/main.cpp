#include <QApplication>
#include "gamewindows.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWindows mygameWindow;
    mygameWindow.setWindowTitle("舰队collection");
    //mygameWindow.setWindowFlags(Qt::FramelessWindowHint);
    QCursor mycursor(QPixmap("./GameData/UI1/cursor1.png"),0,0);
    mygameWindow.setCursor(mycursor);
    mygameWindow.show();
    return a.exec();
}
