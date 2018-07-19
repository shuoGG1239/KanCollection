#include "animation.h"

/**
 * @brief 构造函数
 *
 * @param parent 父
 * @param inputItem 将被附加动画特效的对象
 */
Animation::Animation(QObject *parent, QWidget *inputItem,
                     bool animeGeomOn, bool animeOpacOn)
    :QObject(parent)
{
    item=inputItem;
    /*动画初始化*/
    animeGeomIsOn=false;
    animeOpacIsOn=false;
    this->setAnimation_OnOff(animeGeomOn,animeOpacOn);
}

Animation::~Animation()
{
    if(animeGeomIsOn)
        delete animeGeometry;
    if(animeOpacIsOn)
    {
        delete animeOpacity;
        delete effectOpacity;
    }
}


/**
 * @brief 各种动画开启或关闭,可以重复调用,已集成内存管理,不会内存泄露
 *
 * @param animeGeomOn 几何类动画是否使能
 * @param animeOpacOn 透明度类动画是否使能
 */
void Animation::setAnimation_OnOff(bool animeGeomOn, bool animeOpacOn)
{
    /*几何动画开关*/
    if(!animeGeomIsOn && animeGeomOn)
    {
        animeGeometry=new QPropertyAnimation(item,"geometry");
        connect(animeGeometry,SIGNAL(finished()),this,SLOT(animeFinishedGeom()));
        animeGeomIsOn=true;
    }else if(animeGeomIsOn && !animeGeomOn)
    {
        delete animeGeometry;
        disconnect(animeGeometry,SIGNAL(finished()),this,SLOT(animeFinishedGeom()));
        animeGeomIsOn=false;
    }

    /*透明度动画开关*/
    if(!animeOpacIsOn && animeOpacOn)
    {
        effectOpacity=new QGraphicsOpacityEffect;
        //透明度动画必须借助QGraphicsOpacityEffect
        animeOpacity =new QPropertyAnimation(effectOpacity,"opacity");
        connect(animeOpacity,SIGNAL(finished()),this,SLOT(animeFinishedOpac()));
        animeOpacIsOn=true;
    }else if(animeOpacIsOn && !animeOpacOn)
    {
        delete effectOpacity;
        delete  animeOpacity;
        disconnect(animeOpacity,SIGNAL(finished()),this,SLOT(animeFinishedOpac()));
        animeOpacIsOn=false;
    }
}


/***************************************gradual系列动画函数********************************************/

/**
 * @brief 透明度渐变动画
 *
 * @param startOpac 起始透明度
 * @param endOpac   结束透明度
 * @param msec      动画持续时间
 * @param aTyte     缓和曲线
 * @param animeHandle 动画句柄
 * @param loopTime    循环次数(-1为无限循环,区别于timeline的0为无限循环)
 */
void Animation::gradualOpacity(qreal startOpac, qreal endOpac, int msec,
                               const QEasingCurve &aTyte, int animeHandle, int loopTime)
{
    handlerCurOpac=animeHandle;
    item->setGraphicsEffect(effectOpacity);
    animeOpacity->setEasingCurve(aTyte);
    animeOpacity->setDuration(msec);
    animeOpacity->setStartValue(startOpac);
    animeOpacity->setEndValue(endOpac);
    animeOpacity->setLoopCount(loopTime);
    animeOpacity->start();
    emit signAnimeStartOpac(animeHandle);
}

/**
 * @brief 出现或消失(透明度型)
 *
 * @param isToShow 出现还是消失
 * @param msec     动画持续时间
 * @param aTyte    缓和曲线
 * @param animeHandle 动画句柄
 * @param loopTime    循环次数(-1为无限循环,区别于timeline的0为无限循环)
 */
void Animation::gradualShowHide_Opac(bool isToShow, int msec,
                                     const QEasingCurve &aTyte, int animeHandle,int loopTime)
{
    handlerCurOpac=animeHandle;
    item->setGraphicsEffect(effectOpacity);
    animeOpacity->setDuration(msec);
    animeOpacity->setEasingCurve(aTyte);
    if(isToShow)//逐渐出现
    {
        animeOpacity->setStartValue(0);
        animeOpacity->setEndValue(1.0);
    }
    else//逐渐消失
    {
        animeOpacity->setStartValue(1.0);
        animeOpacity->setEndValue(0);
    }
    animeOpacity->setLoopCount(loopTime);
    animeOpacity->start();
    emit signAnimeStartOpac(animeHandle);
}

/**
 * @brief 几何动画:位置和大小的变化
 *
 * @param startGeom 起始几何状态
 * @param endGeom   结束几何状态
 * @param msec      动画持续时间
 * @param aTyte     缓和曲线
 * @param animeHandle 动画句柄
 * @param loopTime    循环次数(-1为无限循环,区别于timeline的0为无限循环)
 */
void Animation::gradualGeometry(QRect startGeom, QRect endGeom, int msec,
                                const QEasingCurve &aTyte, int animeHandle, int loopTime)
{
    handlerCurGeom=animeHandle;
    animeGeometry->setEasingCurve(aTyte);
    animeGeometry->setDuration(msec);
    animeGeometry->setStartValue(startGeom);
    animeGeometry->setEndValue(endGeom);
    animeGeometry->setLoopCount(loopTime);
    animeGeometry->start();
    emit signAnimeStartGeom(animeHandle);
}


/**
 * @brief 大小逐渐变化,缩放中心为几何中心
 *        算法核心: Rect1(x_1,y_1,w_1,h_1) Rect2(x_2,y_2,w_2,h_2)
 *                 则 x_2 = x_1+(w1-w2)*0.5
 *                    y_2 = y_1+(h1-h2)*0.5
 *
 * @param startSize
 * @param endSize
 * @param msec   动画持续时间
 * @param aTyte  缓和曲线
 * @param animeHandle 动画句柄
 * @param loopTime    循环次数(-1为无限循环,区别于timeline的0为无限循环)
 */
void Animation::gradualSize_Geom(QSize startSize, QSize endSize, int msec,
                                 const QEasingCurve &aTyte, int animeHandle, int loopTime)
{
    int x=item->x();
    int y=item->y();
    int w=item->width();
    int h=item->height();
    int startX=x+0.5*(w-startSize.width());
    int startY=y+0.5*(h-startSize.height());
    int gapX=(startSize.width()-endSize.width())*0.5;
    int gapY=(startSize.height()-endSize.height())*0.5;
    QRect rectStart(startX,startY,startSize.width(),startSize.height());
    QRect rectEnd(startX+gapX,startY+gapY,endSize.width(),endSize.height());
    gradualGeometry(rectStart,rectEnd,msec,aTyte,animeHandle,loopTime);
}

/**
 * @brief 位移变化,大小不变
 *
 * @param startPos 起始地点
 * @param endPoint 结束地点
 * @param msec     持续时间
 * @param aTyte    缓和曲线
 * @param animeHandle 动画句柄
 * @param loopTime    循环次数(-1为无限循环,区别于timeline的0为无限循环)
 */
void Animation::gradualPos_Geom(QPoint startPos, QPoint endPoint, int msec,
                                const QEasingCurve &aTyte, int animeHandle, int loopTime)
{
    int w=item->width();
    int h=item->height();
    QRect rectStart(startPos.x(),startPos.y(),w,h);
    QRect rectEnd(endPoint.x(),endPoint.y(),w,h);
    gradualGeometry(rectStart,rectEnd,msec,aTyte,animeHandle,loopTime);
}

/**
 * @brief 出现或消失(几何型)
 *
 * @param isToShow 出现还是消失
 * @param msec     动画持续时间
 * @param aTyte    缓和曲线
 * @param animeHandle 动画句柄
 * @param loopTime    循环次数(-1为无限循环,区别于timeline的0为无限循环)
 */
void Animation::gradualShowHide_Geom(bool isToShow, int msec,
                                     const QEasingCurve &aTyte,int animeHandle,int loopTime)
{
    int x=item->x();
    int y=item->y();
    int w=item->width();
    int h=item->height();
    QRect rect0(x+w*0.5,y+h*0.5,0,0);
    if(isToShow)//出现
        gradualGeometry(rect0,item->geometry(),msec,aTyte,animeHandle,loopTime);
    else//消失
        gradualGeometry(item->geometry(),rect0,msec,aTyte,animeHandle,loopTime);
}


/*******************************************slots**************************************************/
/**
 * @brief 动画结束slot
 *
 */
void Animation::animeFinishedGeom()
{
    emit signAnimeFinishGeom(handlerCurGeom);
}
void Animation::animeFinishedOpac()
{
    emit signAnimeFinishOpac(handlerCurOpac);
}
