#ifndef ANIMATION_H
#define ANIMATION_H

#include <QObject>
#include <QWidget>
#include <QPropertyAnimation>
#include <QGraphicsEffect>
#include <QGraphicsOpacityEffect>

/**
 * @brief 动画类,直接new一个出来就可以使用特效了(只适用于QWidget及其子类)
 * 有一个无法解决的问题:图片缩小后再放大会严重降质量,其不可逆性导致做大小循环缩放的动画会无法进行.
 *
 */
class Animation : public QObject
{
    Q_OBJECT
public:
    explicit Animation(QObject *parent,QWidget *inputItem,
                       bool animeGeomOn=true,bool animeOpacOn=true);
    ~Animation();

    void setAnimation_OnOff(bool animeGeomOn, bool animeOpacOn);
    void gradualShowHide_Opac(bool isToShow, int msec,
                              const QEasingCurve &aTyte=QEasingCurve::Linear, int animeHandle=0, int loopTime=1);
    void gradualGeometry(QRect startGeom, QRect endGeom, int msec,
                         const QEasingCurve &aTyte=QEasingCurve::Linear,int animeHandle=0,int loopTime=1);
    void gradualOpacity(qreal startOpac, qreal endOpac, int msec,
                         const QEasingCurve &aTyte=QEasingCurve::Linear,int animeHandle=0,int loopTime=1);
    void gradualSize_Geom(QSize startSize,QSize endSize,int msec,
                          const QEasingCurve &aTyte=QEasingCurve::Linear,int animeHandle=0,int loopTime=1);
    void gradualPos_Geom(QPoint startPos,QPoint endPoint,int msec,
                         const QEasingCurve &aTyte=QEasingCurve::Linear,int animeHandle=0,int loopTime=1);
    void gradualShowHide_Geom(bool isToShow, int msec,
                              const QEasingCurve &aTyte=QEasingCurve::Linear,int animeHandle=0,int loopTime=1);

    int handlerCurGeom;
    int handlerCurOpac;
    /*这些动画public出来是为了方便定制,keyValue关键帧的添加*/
    QGraphicsOpacityEffect *effectOpacity;
    QPropertyAnimation *animeOpacity;
    QPropertyAnimation *animeGeometry;

protected:
    QWidget *item; //指向被附加动画特效的对象

private:
    bool animeGeomIsOn;
    bool animeOpacIsOn;
signals:
    void signAnimeStartGeom(int handle);
    void signAnimeStartOpac(int handle);
    void signAnimeFinishGeom(int handle);
    void signAnimeFinishOpac(int handle);

public slots:
    void animeFinishedGeom();
    void animeFinishedOpac();

};

#endif // ANIMATION_H
