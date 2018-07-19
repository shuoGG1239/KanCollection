#include "loopanime.h"

LoopAnime::LoopAnime(QObject *parent, QWidget *inputItem) :
    Animation(parent,inputItem)
{

}
LoopAnime::~LoopAnime()
{

}

/***********************************出现消失_透明度循环动画系列**************************************/
/**
 * @brief 出现消失循环动画设置
 *
 * @param startWithShow 第一次动画是消失还是出现
 * @param msec 循环的一半时间
 * @param curve 动画曲线
 */
void LoopAnime::setLoopOpac(bool startWithShow,int msec,QEasingCurve::Type curve)
{
    isShowOrHide=startWithShow;
    timeLastOpac=msec;
    curveOpac=curve;
    connect(this,SIGNAL(signAnimeFinishOpac(int)),this,SLOT(loopOpacSlot(int)));
}
void LoopAnime::startLoopOpac()
{
    this->gradualShowHide_Opac(isShowOrHide,timeLastOpac,curveOpac,ANIME_HANDLER_OPAC_1);
}
void LoopAnime::stopLoopOpac()
{
    this->animeOpacity->stop();
}
void LoopAnime::loopOpacSlot(int handler)
{
    if(handler==ANIME_HANDLER_OPAC_1)
    {
        this->gradualShowHide_Opac(!isShowOrHide,timeLastOpac,curveOpac,ANIME_HANDLER_OPAC_2);
    }
    else if(handler==ANIME_HANDLER_OPAC_2)
    {
        this->gradualShowHide_Opac(isShowOrHide,timeLastOpac,curveOpac,ANIME_HANDLER_OPAC_1);
    }
}


/********************************************位移循环动画系列**************************************/
/**
 * @brief 位移循环动画
 *
 * @param startPos 起始位置
 * @param endPos 结束位置
 * @param msec 循环的一半时间
 * @param curve 动画曲线
 */
void LoopAnime::setLoopPos(QPoint startPos,QPoint endPos,int msec,QEasingCurve::Type curve)
{
    this->startPos=startPos;
    this->endPos=endPos;
    timeLastGeom=msec;
    curveGeom=curve;
    connect(this,SIGNAL(signAnimeFinishGeom(int)),this,SLOT(loopPosSlot(int)));
}
void LoopAnime::startLoopPos()
{
    this->gradualPos_Geom(startPos,endPos,timeLastGeom,curveGeom,ANIME_HANDLER_GEOM_1);
}
void LoopAnime::stopLoopPos()
{
    this->animeGeometry->stop();
}
void LoopAnime::loopPosSlot(int handler)
{
    if(handler==ANIME_HANDLER_GEOM_1)
    {
        this->gradualPos_Geom(endPos,startPos,timeLastGeom,curveGeom,ANIME_HANDLER_GEOM_2);
    }
    else if(handler==ANIME_HANDLER_GEOM_2)
    {
        this->gradualPos_Geom(startPos,endPos,timeLastGeom,curveGeom,ANIME_HANDLER_GEOM_1);
    }
}
