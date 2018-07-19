#include "animationgraphic.h"

/**
 * @brief 动画构造函数
 *
 * @param parent        父
 * @param inputItem     加特效的对象
 * @param animePosOn    位移特效是否开(默认开)
 * @param animeScaleOn  缩放特效是否开(默认开)
 * @param animeRotateOn 旋转特效是否开(默认开)
 * @param animeOpacOn   透明度特效是否开(默认开)
 */
AnimationGraphic::AnimationGraphic(QObject *parent, PicGraphic *inputItem, bool animePosOn,
                                   bool animeScaleOn, bool animeRotateOn, bool animeOpacOn) :
    QObject(parent)
{
    item=inputItem;
    /*动画初始化*/
    animePosIsOn   =false;
    animeScaleIsOn =false;
    animeRotateIsOn=false;
    animeOpacIsOn  =false;
    setAnimation_OnOff(animePosOn,animeScaleOn,animeRotateOn,animeOpacOn);
}

AnimationGraphic::~AnimationGraphic()
{
    if(animePosIsOn)
        delete animePos;
    if(animeScaleIsOn)
        delete animeScale;
    if(animeRotateIsOn)
        delete animeRotate;
    if(animeOpacIsOn)
        delete animeOpacity;
}


/**
 * @brief 各种动画开启或关闭,可以重复调用,已集成内存管理,不会内存泄露
 *
 * @param animePosOn    位移动画是否使能
 * @param animeScaleOn  大小动画是否使能
 * @param animeRotateOn 旋转动画是否使能
 * @param animeOpacOn   透明动画是否使能
 */
void AnimationGraphic::setAnimation_OnOff(bool animePosOn, bool animeScaleOn,
                                          bool animeRotateOn, bool animeOpacOn)
{
    /*位移动画开关*/
    if(!animePosIsOn && animePosOn)
    {
        animePos=new QPropertyAnimation(item,"pos");
        connect(animePos,SIGNAL(finished()),this,SLOT(animeFinishedPos()));
        animePosIsOn=true;
    }else if(animePosIsOn && !animePosOn)
    {
        delete animePos;
        disconnect(animePos,SIGNAL(finished()),this,SLOT(animeFinishedPos()));
        animePosIsOn=false;
    }
    /*缩放动画开关*/
    if(!animeScaleIsOn && animeScaleOn)
    {
        animeScale=new QPropertyAnimation(item,"scale");
        connect(animeScale,SIGNAL(finished()),this,SLOT(animeFinishedScale()));
        animeScaleIsOn=true;
    }else if(animeScaleIsOn && !animeScaleOn)
    {
        delete animeScale;
        disconnect(animeScale,SIGNAL(finished()),this,SLOT(animeFinishedScale()));
        animeScaleIsOn=false;
    }
    /*旋转动画开关*/
    if(!animeRotateIsOn && animeRotateOn)
    {
        animeRotate=new QPropertyAnimation(item,"rotation");
        connect(animeRotate,SIGNAL(finished()),this,SLOT(animeFinishedRotate()));
        animeRotateIsOn=true;
    }else if(animeRotateIsOn && !animeRotateOn)
    {
        delete animeRotate;
        disconnect(animeRotate,SIGNAL(finished()),this,SLOT(animeFinishedRotate()));
        animeRotateIsOn=false;
    }
    /*透明度动画开关*/
    if(!animeOpacIsOn && animeOpacOn)
    {
        animeOpacity=new QPropertyAnimation(item,"opacity");
        connect(animeOpacity,SIGNAL(finished()),this,SLOT(animeFinishedOpac()));
        animeOpacIsOn=true;
    }else if(animeOpacIsOn && !animeOpacOn)
    {
        delete animeOpacity;
        disconnect(animeOpacity,SIGNAL(finished()),this,SLOT(animeFinishedOpac()));
        animeOpacIsOn=false;
    }

}






/****************************Public******************************/

/**
 * @brief 位移动画
 *
 * @param startPos    起始点
 * @param endPoint    结束点
 * @param msec        时长
 * @param aTyte       曲线
 * @param animeHandle 句柄
 * @param loopTime    循环次数(-1为无限循环,区别于timeline的0为无限循环)
 */
void AnimationGraphic::gradualPos(QPointF startPos, QPointF endPos, int msec,
                                  const QEasingCurve &aTyte, int animeHandle, int loopTime)
{
    handlerCurPos=animeHandle;
    animePos->setEasingCurve(aTyte);
    animePos->setDuration(msec);
    animePos->setStartValue(startPos);
    animePos->setEndValue(endPos);
    animePos->setLoopCount(loopTime);
    animePos->start();
    emit signAnimeStartPos(animeHandle);
}

/**
 * @brief 大小动画
 *
 * @param startScale 起始比例
 * @param endScale   结束比例
 * @param msec       时长
 * @param aTyte      曲线
 * @param animeHandle句柄
 * @param loopTime    循环次数(-1为无限循环,区别于timeline的0为无限循环)
 */
void AnimationGraphic::gradualScale(qreal startScale,qreal endScale,int msec,
                                    const QEasingCurve &aTyte,int animeHandle,int loopTime)
{
    handlerCurScale=animeHandle;
    animeScale->setEasingCurve(aTyte);
    animeScale->setDuration(msec);
    animeScale->setStartValue(startScale);
    animeScale->setEndValue(endScale);
    animeScale->setLoopCount(loopTime);
    animeScale->start();
    emit signAnimeStartScale(animeHandle);
}

/**
 * @brief 旋转动画
 *
 * @param startAngle  起始角度
 * @param endAngle    结束角度
 * @param msec        时长
 * @param aTyte       曲线
 * @param animeHandle 句柄
 * @param loopTime    循环次数(-1为无限循环,区别于timeline的0为无限循环)
 */
void AnimationGraphic::gradualRotate(qreal startAngle, qreal endAngle, int msec,
                                     const QEasingCurve &aTyte, int animeHandle,int loopTime)
{
    handlerCurRotate=animeHandle;
    animeRotate->setEasingCurve(aTyte);
    animeRotate->setDuration(msec);
    animeRotate->setStartValue(startAngle);
    animeRotate->setEndValue(endAngle);
    animeRotate->setLoopCount(loopTime);
    animeRotate->start();
    emit signAnimeStartRotate(animeHandle);
}

/**
 * @brief 透明度动画
 *
 * @param startOpac  起始透明度
 * @param endOpac    结束透明度
 * @param msec       时长
 * @param aTyte      曲线
 * @param animeHandle句柄
 * @param loopTime    循环次数(-1为无限循环,区别于timeline的0为无限循环)
 */
void AnimationGraphic::gradualOpac(qreal startOpac, qreal endOpac, int msec,
                                   const QEasingCurve &aTyte, int animeHandle,int loopTime)
{
    handlerCurOpac=animeHandle;
    animeOpacity->setEasingCurve(aTyte);
    animeOpacity->setDuration(msec);
    animeOpacity->setStartValue(startOpac);
    animeOpacity->setEndValue(endOpac);
    animeOpacity->setLoopCount(loopTime);
    animeOpacity->start();
    emit signAnimeStartOpac(animeHandle);
}



/*******************************************slots**************************************************/
/**
 * @brief 动画结束slot
 *
 */
void AnimationGraphic::animeFinishedPos()
{
    emit signAnimeFinishPos(handlerCurPos);
}
void AnimationGraphic::animeFinishedScale()
{
    emit signAnimeFinishScale(handlerCurScale);
}
void AnimationGraphic::animeFinishedRotate()
{
    emit signAnimeFinishRotate(handlerCurRotate);
}
void AnimationGraphic::animeFinishedOpac()
{
    emit signAnimeFinishOpac(handlerCurOpac);
}
