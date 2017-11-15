#ifndef ANIMATIONITEM_H
#define ANIMATIONITEM_H

#include <QPropertyAnimation>
#include <QGraphicsItemAnimation>
#include <QGraphicsPixmapItem>
#include <QTimeLine>
#include <QPointF>
#include <QTransform>
#include "../myComponents/picgraphic.h"

class PicGraphic;

/**
 * @brief 专为PicGraphic(继承了QObject的QGraphicsPixmapItem)设计的动画类,new完就可以直接使用gradual函数
 * 关键帧自定义动画示例:
 *   animeGeom->clear();
     animeGeom->setPosAt(0,startPos);
     animeGeom->setPosAt(0.5,midPos1);
     animeGeom->setPosAt(0.8,midPos2);
     animeGeom->setPosAt(1,endPos);
     timeLineItem->setDuration(5000);
     timeLineItem->setEasingCurve(QEasingCurve::Linear);
     timeLineItem->setLoopCount(0);
     timeLineItem->start();
 *
 */
class AnimationItem : public QObject
{
    Q_OBJECT
public:
    explicit AnimationItem(QObject *parent, PicGraphic *inputItem,
                           bool animeGeomOn=true, bool animeOpacOn=true);
    ~AnimationItem();

    void setAnimation_OnOff(bool animeGeomOn, bool animeOpacOn);
    /*gradual动画系列都自带clear和start的,带关键帧的定制动画不要用到gradual系列动画函数*/
    void gradualPos(QPointF startPos, QPointF endPos, int msec,
                    const QEasingCurve &aTyte=QEasingCurve::Linear, int animeHandle=0, int loopTime=1);
    void gradualScale(qreal startScale,qreal endScale,int msec,
                      const QEasingCurve &aTyte=QEasingCurve::Linear,int animeHandle=0, int loopTime=1);
    void gradualRotate(qreal startAngle, qreal endAngle, int msec,
                       const QEasingCurve &aTyte=QEasingCurve::Linear,int animeHandle=0, int loopTime=1);
    void gradualGeometry(QPointF startPos, QPointF endPos,
                         qreal   startScale,qreal  endScale,
                         qreal   startAngle, qreal endAngle,
                        int msec, const QEasingCurve &aTyte=QEasingCurve::Linear,
                        int animeHandle=0,int loopTime=1);

    void gradualOpac(qreal startOpac, qreal endOpac, int msec,
                     const QEasingCurve &aTyte=QEasingCurve::Linear,int animeHandle=0,int loopTime=1);

    /*当前动画句柄,供动画结束slots发送signal时使用*/
    int handlerCurGeom;
    int handlerCurOpac;
    QGraphicsItemAnimation  *animeGeom;
    QPropertyAnimation      *animeOpacity; //QGraphicsItemAnimation不支持透明度
    QTimeLine               *timeLineItem;

protected:
    PicGraphic              *item; //指向被附加动画特效的对象

private:
    bool animeGeomIsOn;
    bool animeOpacIsOn;
signals:
    void signAnimeStartGeom(int handle);
    void signAnimeStartOpac(int handle);


public slots:
    /*为了接受finished()信号的slots*/
    void animeFinishedGeom();
    void animeFinishedOpac();
private slots:
    void scaleAnimation(int frame);

};

#endif // ANIMATIONITEM_H
