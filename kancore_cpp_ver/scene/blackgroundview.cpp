#include "blackgroundview.h"

BlackgroundView::BlackgroundView(QWidget *parent) :
    QGraphicsView(parent)
{
    this->setAttribute(Qt::WA_DeleteOnClose);//clsoe时自动delete
    /*去掉view的横纵滚动条*/
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //这行很重要,没这行则背景默认是白色,会出很多问题(不同于Qwidget体系默认透明)
    this->setStyleSheet("background: transparent;border:0px");
    this->setWindowFlags(Qt::FramelessWindowHint);
    /*scene设置*/
    myscene=new QGraphicsScene(this);
    this->setScene(myscene);
    this->setSceneRect(QRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT));
    this->initItem();

    animeEffect=new Animation(this,this,false,true);
}
BlackgroundView::~BlackgroundView()
{
    delete picBackground;
    delete picShip;
}



/**
 * @brief item的初始化
 *
 */
void BlackgroundView::initItem()
{
    picBackground=new PicGraphic(QPixmap("./GameData/UI1/mainD2/black.jpg"),0,0,false,false);
    picShip=new PicGraphic(QPixmap(QString(URL_UI1)+"mainD2/mainD2_3.png"),370,200,true,false);
    picCircle1=new PicGraphic(QPixmap("./GameData/UI1/mainD2/circle.png"),365,225,true,true);
    picCircle2=new PicGraphic(QPixmap("./GameData/UI1/mainD2/circle.png"),365,225,true,true);

    myscene->addItem(picBackground);
    myscene->addItem(picCircle1);
    myscene->addItem(picCircle2);
    myscene->addItem(picShip);

    connect(picShip->animeEffect,SIGNAL(signAnimeFinishPos(int)),this,SLOT(animeGeomEnd(int)));
}

/**
 * @brief 船和波浪的动画
 *
 */
void BlackgroundView::playAnime()
{
    curveShip=QEasingCurve::InOutQuad;
    startPosShip=picShip->pos();
    endPosShip=QPointF(startPosShip.x(),(startPosShip.y()+SHIP_OFFSET));
    //船的来回双循环动画使用了曲线,所以没法用loopcount的循环
    picShip->animeEffect->gradualPos(startPosShip,endPosShip,SHIP_TIMELAST,
                                     curveShip,ANIME_HANDLER_SHIP_1);

    picCircle1->animeEffect->gradualScale(0,1.5,CIRCLE1_TIMELAST,QEasingCurve::Linear,0,-1);
    picCircle1->animeEffect->gradualOpac(1,0,CIRCLE1_TIMELAST,QEasingCurve::Linear,0,-1);
    picCircle2->animeEffect->gradualScale(0,1,CIRCLE2_TIMELAST,QEasingCurve::Linear,0,-1);
    picCircle2->animeEffect->gradualOpac(1,0,CIRCLE2_TIMELAST,QEasingCurve::Linear,0,-1);
}


/**
 * @brief 该过渡界面淡出出现
 *
 */
void BlackgroundView::display()
{
    this->show();
    this->animeEffect->gradualShowHide_Opac(true,1500);
}


/**
 * @brief 几何动画slot
 *
 * @param handler
 */
void BlackgroundView::animeGeomEnd(int handler)
{
    if(handler==ANIME_HANDLER_SHIP_1)
    {
        picShip->animeEffect->gradualPos(endPosShip,startPosShip,SHIP_TIMELAST,
                                         curveShip,ANIME_HANDLER_SHIP_2);
    }
    else if(handler==ANIME_HANDLER_SHIP_2)
    {
        picShip->animeEffect->gradualPos(startPosShip,endPosShip,SHIP_TIMELAST,
                                         curveShip,ANIME_HANDLER_SHIP_1);
    }
}

