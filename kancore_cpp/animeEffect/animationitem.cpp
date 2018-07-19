#include "animationitem.h"


/**
 * @brief item动画构造函数
 *
 * @param parent       父
 * @param inputItem    加特效的item
 * @param animeGeomOn  是否开启几何动画
 * @param animeOpacOn  是否开启透明度动画
 */
AnimationItem::AnimationItem(QObject *parent, PicGraphic *inputItem,
                             bool animeGeomOn, bool animeOpacOn) :
    QObject(parent)
{
    item=inputItem;
    /*动画初始化*/
    animeGeomIsOn=false;
    animeOpacIsOn=false;
    setAnimation_OnOff(animeGeomOn,animeOpacOn);
}

AnimationItem::~AnimationItem()
{
    if(animeGeomIsOn)
    {
        delete animeGeom;
        delete timeLineItem;
    }
    if(animeOpacIsOn)
    {
        delete animeOpacity;
    }
}



/**
 * @brief 各种动画开启或关闭,可以重复调用,已集成内存管理,不会内存泄露
 *
 * @param animeGeomOn 使能或关闭几何动画
 * @param animeOpacOn 使能或关闭透明度动画
 */
void AnimationItem::setAnimation_OnOff(bool animeGeomOn, bool animeOpacOn)
{
    /*几何动画开关*/
    if(!animeGeomIsOn && animeGeomOn)
    {
        animeGeom    = new QGraphicsItemAnimation(this);
        timeLineItem = new QTimeLine(1000,this);
        animeGeom->setItem(item);
        animeGeom->setTimeLine(timeLineItem);
        timeLineItem->setFrameRange(0,100);
        timeLineItem->setUpdateInterval(25);
        connect(timeLineItem,SIGNAL(finished()),this,SLOT(animeFinishedGeom()));
        //connect(timeLineItem,SIGNAL(frameChanged(int)),this,SLOT(scaleAnimation(int)));
        animeGeomIsOn=true;
    }else if(animeGeomIsOn && !animeGeomOn)
    {
        delete animeGeom;
        disconnect(timeLineItem,SIGNAL(finished()),this,SLOT(animeFinishedGeom()));
        animeGeomIsOn=false;
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
 * @param loopTime    循环次数(0为无限循环)
 */
void AnimationItem::gradualPos(QPointF startPos, QPointF endPos, int msec,
                               const QEasingCurve &aTyte, int animeHandle,int loopTime)
{
    animeGeom->clear();
    animeGeom->setPosAt(0,startPos);
    //animeGeom->setPosAt(0.5,midPos); //关键帧:中间
    animeGeom->setPosAt(1,endPos);
    timeLineItem->setDuration(msec);
    timeLineItem->setEasingCurve(aTyte);
    timeLineItem->setLoopCount(loopTime);
    timeLineItem->start();
    handlerCurGeom=animeHandle;
    emit signAnimeStartGeom(animeHandle);
}

/**
 * @brief 大小动画
 *
 * @param startScale 起始比例
 * @param endScale   结束比例
 * @param msec       时长
 * @param aTyte      曲线
 * @param animeHandle句柄
 * @param loopTime    循环次数(0为无限循环)
 */
void AnimationItem::gradualScale(qreal startScale,qreal endScale,int msec,
                                 const QEasingCurve &aTyte,int animeHandle,int loopTime)
{
    animeGeom->clear();
    animeGeom->setScaleAt(0,startScale,startScale);
    animeGeom->setScaleAt(1,endScale,endScale);
    timeLineItem->setDuration(msec);
    timeLineItem->setEasingCurve(aTyte);
    timeLineItem->setLoopCount(loopTime);
    timeLineItem->start();
    handlerCurGeom=animeHandle;
    emit signAnimeStartGeom(animeHandle);
}

/**
 * @brief 旋转动画
 *
 * @param startAngle  起始角度
 * @param endAngle    结束角度
 * @param msec        时长
 * @param aTyte       曲线
 * @param animeHandle 句柄
 * @param loopTime    循环次数(0为无限循环)
 */
void AnimationItem::gradualRotate(qreal startAngle, qreal endAngle, int msec,
                                  const QEasingCurve &aTyte, int animeHandle,int loopTime)
{
    animeGeom->clear();
    animeGeom->setRotationAt(0,startAngle);
    animeGeom->setRotationAt(1,endAngle);
    timeLineItem->setDuration(msec);
    timeLineItem->setEasingCurve(aTyte);
    timeLineItem->setLoopCount(loopTime);
    timeLineItem->start();
    handlerCurGeom=animeHandle;
    emit signAnimeStartGeom(animeHandle);
}

/**
 * @brief 几何动画
 *
 * @param startPos    起始位置
 * @param endPos      结束位置
 * @param startScale  起始大小
 * @param endScale    结束大小
 * @param startAngle  起始角度
 * @param endAngle    结束角度
 * @param msec        时长
 * @param aTyte       曲线
 * @param animeHandle 句柄
 * @param loopTime    循环次数(0为无限循环)
 */
void AnimationItem::gradualGeometry(QPointF startPos, QPointF endPos,
                                    qreal   startScale,qreal  endScale,
                                    qreal   startAngle, qreal endAngle,
                                    int msec, const QEasingCurve &aTyte,int animeHandle,int loopTime)
{
    animeGeom->clear();
    animeGeom->setPosAt(0,startPos);
    animeGeom->setPosAt(1,endPos);
    animeGeom->setScaleAt(0,startScale,startScale);
    animeGeom->setScaleAt(1,endScale,endScale);
    animeGeom->setRotationAt(0,startAngle);
    animeGeom->setRotationAt(1,endAngle);

    timeLineItem->setDuration(msec);
    timeLineItem->setEasingCurve(aTyte);
    timeLineItem->setLoopCount(loopTime);
    timeLineItem->start();
    handlerCurGeom=animeHandle;
    emit signAnimeStartGeom(animeHandle);
}


/**
 * @brief 透明度动画
 *
 * @param startOpac  起始透明度
 * @param endOpac    结束透明度
 * @param msec       时长
 * @param aTyte      曲线
 * @param animeHandle句柄
 */
void AnimationItem::gradualOpac(qreal startOpac, qreal endOpac, int msec,
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
void AnimationItem::animeFinishedGeom()
{
    emit signAnimeStartGeom(handlerCurGeom);
}
void AnimationItem::animeFinishedOpac()
{
    emit signAnimeStartOpac(handlerCurOpac);
}



void AnimationItem::scaleAnimation(int frame)
{
    QPointF pt =item->boundingRect().center();
    qreal scaleX_Y = (frame+50) / 100.0;
    QTransform tran;
    tran.translate(pt.x(), pt.y());
    tran.scale(scaleX_Y, scaleX_Y);
    item->setTransform(tran);
    QTransform t;
    t.translate(-pt.x(), -pt.y());
    item->setTransform(t, true);
}
