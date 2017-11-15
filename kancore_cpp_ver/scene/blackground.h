#ifndef BLACKGROUND_H
#define BLACKGROUND_H

#include <QFrame>
#include "./myComponents/piclabel.h"
#include "publicConstData.h"

#define ANIME_HANDLER_SHIP_1  1
#define ANIME_HANDLER_SHIP_2  2

#define SHIP_OFFSET         20
#define SHIP_TIMELAST       1000
#define CIRCLE1_TIMELAST    500

/**
 * @brief 开始界面过渡动画界面,QWidget体系版本
 *
 */
class Blackground : public QFrame
{
    Q_OBJECT
public:
    explicit Blackground(QFrame *parent = 0);
    ~Blackground();
    void display();

    PicLabel    *imageShip;
    PicLabel    *imageCircle;
    QGraphicsOpacityEffect *effectOpacity;
    QPropertyAnimation *animeOpacity;

private:
    QPoint startPosShip;
    QPoint endPosShip;
    QEasingCurve curveShip;

signals:


public slots:
    void animeGeomEnd(int handler);

};

#endif // BLACKGROUND_H
