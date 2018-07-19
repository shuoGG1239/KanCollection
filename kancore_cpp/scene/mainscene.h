#ifndef MAINSCENE_H
#define MAINSCENE_H
#include <QGraphicsScene>
#include <QGraphicsWidget>
#include "./myComponents/picgraphic.h"
#include "publicConstData.h"

class MainScene:public QGraphicsScene
{
    Q_OBJECT
public:
    MainScene(QObject *parent=0);

    PicGraphic *picBackground;


private:

signals:

public slots:


};

#endif // MAINSCENE_H
