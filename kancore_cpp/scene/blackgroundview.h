#ifndef BLACKGROUNDVIEW_H
#define BLACKGROUNDVIEW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include "./animeEffect/animation.h"
#include "./myComponents/picgraphic.h"
#include "publicConstData.h"

#define SHIP_OFFSET         10
#define SHIP_TIMELAST       800
#define CIRCLE1_TIMELAST    900
#define CIRCLE2_TIMELAST    700

#define ANIME_HANDLER_SHIP_1  1
#define ANIME_HANDLER_SHIP_2  2

class BlackgroundView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit BlackgroundView(QWidget *parent = 0);
    ~BlackgroundView();
    void playAnime();
    void display();

    QGraphicsScene *myscene;
    Animation      *animeEffect;

    PicGraphic    *picBackground;
    PicGraphic    *picShip;
    PicGraphic    *picCircle1;
    PicGraphic    *picCircle2;

private:
    void initItem();
    QPointF        startPosShip;
    QPointF        endPosShip;
    QEasingCurve   curveShip;
signals:

public slots:
    void animeGeomEnd(int handler);

};

#endif // BLACKGROUNDVIEW_H
