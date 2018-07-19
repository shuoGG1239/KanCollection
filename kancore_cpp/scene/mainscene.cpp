#include "mainscene.h"


MainScene::MainScene(QObject *parent):QGraphicsScene(parent)
{
    picBackground=new PicGraphic(QPixmap(QString(URL_HOME_WALL)+"001.png"),0,0,0,true);
    this->addItem(picBackground);
}
