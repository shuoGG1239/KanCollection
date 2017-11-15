#ifndef ANIMATIONGRAPHIC_H
#define ANIMATIONGRAPHIC_H

#include <QPropertyAnimation>
#include <QPointF>
#include "../myComponents/picgraphic.h"
class PicGraphic; //不要用include,会出现互相包含的状况

/**
 * @brief 动画类,直接new一个出来就可以使用特效了(只适用于PicGraphic及其子类)
 * 缩放不会降图像质量;
 * 缩放和旋转中心的设置可以用PicGraphics类的setGeomCenter方法;
 */
class AnimationGraphic : public QObject
{
    Q_OBJECT
public:
    enum animeType{
        TypePos,
        TypeScale,
        TypeRotate,
        TypeOpacity
    };
    explicit AnimationGraphic(QObject *parent, PicGraphic *inputItem,
                              bool animePosOn=true,bool animeScaleOn=true,
                              bool animeRotateOn=true,bool animeOpacOn=true);
    ~AnimationGraphic();

    void setAnimation_OnOff(bool animePosOn, bool animeScaleOn,
                                        bool animeRotateOn, bool animeOpacOn);
    void gradualPos(QPointF startPos, QPointF endPos, int msec,
                    const QEasingCurve &aTyte=QEasingCurve::Linear, int animeHandle=0, int loopTime=1);
    void gradualScale(qreal startScale, qreal endScale, int msec,
                      const QEasingCurve &aTyte=QEasingCurve::Linear, int animeHandle=0, int loopTime=1);
    void gradualRotate(qreal startAngle, qreal endAngle, int msec,
                       const QEasingCurve &aTyte=QEasingCurve::Linear, int animeHandle=0, int loopTime=1);
    void gradualOpac(qreal startOpac, qreal endOpac, int msec,
                     const QEasingCurve &aTyte=QEasingCurve::Linear,int animeHandle=0,int loopTime=1);

    /*当前动画句柄,供动画结束slots发送signal时使用*/
    int handlerCurPos;
    int handlerCurScale;
    int handlerCurRotate;
    int handlerCurOpac;
    /*这些动画public出来是为了方便定制,keyValue关键帧的添加*/
    QPropertyAnimation *animeOpacity;
    QPropertyAnimation *animePos;
    QPropertyAnimation *animeScale;
    QPropertyAnimation *animeRotate;


protected:
    PicGraphic *item; //指向被附加动画特效的对象

private:
    bool animePosIsOn;
    bool animeScaleIsOn;
    bool animeRotateIsOn;
    bool animeOpacIsOn;

signals:
    void signAnimeStartPos(int handle);
    void signAnimeStartScale(int handle);
    void signAnimeStartRotate(int handle);
    void signAnimeStartOpac(int handle);

    void signAnimeFinishPos(int handle);
    void signAnimeFinishScale(int handle);
    void signAnimeFinishRotate(int handle);
    void signAnimeFinishOpac(int handle);

public slots:
    /*为了接受finished()信号的slots*/
    void animeFinishedPos();
    void animeFinishedScale();
    void animeFinishedRotate();
    void animeFinishedOpac();

};
#endif // ANIMATIONGRAPHIC_H

