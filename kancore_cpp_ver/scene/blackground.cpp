#include "blackground.h"

Blackground::Blackground(QFrame *parent) :
    QFrame(parent)
{
    this->setAttribute(Qt::WA_DeleteOnClose);//clsoe时自动delete
    this->setFixedSize(SCREEN_WIDTH,SCREEN_HEIGHT);
    this->setStyleSheet("Blackground{background-image:url(./GameData/UI1/mainD2/black.jpg)}");

    imageShip=new PicLabel(this,QPixmap(QString(URL_UI1)+"mainD2/mainD2_3.png"),370,200);
    connect(imageShip->animeEffect,SIGNAL(signAnimeFinishGeom(int)),this,SLOT(animeGeomEnd(int)));

    /*渐变特效*/
    effectOpacity=new QGraphicsOpacityEffect;
    animeOpacity =new QPropertyAnimation(effectOpacity,"opacity");//透明度动画必须借助QGraphicsOpacityEffect
    this->setGraphicsEffect(effectOpacity);

    startPosShip=imageShip->pos();
    endPosShip=QPoint(imageShip->x(),imageShip->y()+SHIP_OFFSET);
    curveShip=QEasingCurve::InOutQuad;
}
Blackground::~Blackground()
{
    delete effectOpacity;
    delete animeOpacity;
}

/**
 * @brief blackWindow渐变出现,里面的各种动画开始
 *
 */
void Blackground::display()
{
    /*window的动画*/
    animeOpacity->setDuration(1500);
    animeOpacity->setEasingCurve(QEasingCurve::Linear);
    animeOpacity->setStartValue(0);      	//动画属性起始值
    animeOpacity->setEndValue(1);       	//动画属性结束值
    animeOpacity->start();                 //开始动画
    /*ship的动画*/
    imageShip->animeEffect->gradualPos_Geom(startPosShip,endPosShip,SHIP_TIMELAST,
                                            curveShip,ANIME_HANDLER_SHIP_1);

}


/**
 * @brief 几何动画slot
 *
 * @param handler
 */
void Blackground::animeGeomEnd(int handler)
{
    if(handler==ANIME_HANDLER_SHIP_1)
    {
        imageShip->animeEffect->gradualPos_Geom(endPosShip,startPosShip,SHIP_TIMELAST,
                                                curveShip,ANIME_HANDLER_SHIP_2);
    }
    else if(handler==ANIME_HANDLER_SHIP_2)
    {
        imageShip->animeEffect->gradualPos_Geom(startPosShip,endPosShip,SHIP_TIMELAST,
                                                curveShip,ANIME_HANDLER_SHIP_1);
    }
}
