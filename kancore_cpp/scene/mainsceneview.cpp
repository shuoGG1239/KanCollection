#include "mainsceneview.h"

MainSceneView::MainSceneView(QWidget *parent) :
    QGraphicsView(parent)
{
    /*去掉view的横纵滚动条*/
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //这行很重要,没这行则背景默认是白色,会出很多问题(不同于Qwidget体系默认透明)
    this->setStyleSheet("background: transparent;border:0px");
    this->setWindowFlags(Qt::FramelessWindowHint);
    //kanmusumeCur必须在myscene前面实体化,不然析构会出错.原因:scene销毁时被add的item也会被销毁
    kanmusumeCur=new KanMusume("054川内","5",this);
    /*scene设置*/
    myscene=new QGraphicsScene(this);
    this->setScene(myscene);
    this->setSceneRect(QRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT));
    /*透明度动画*/
    this->setAnimeOpacOn(true);
    connect(animeOpacity,SIGNAL(finished()),this,SLOT(opacAnimeFinish()));

    clock=new Clock(this);
    connect(clock,SIGNAL(secTimeout()),this,SLOT(updateClock()));
    connect(clock,SIGNAL(minTimeout()),this,SLOT(updateSrc()));
    this->initGamePara();
    this->initItem();
}
MainSceneView::~MainSceneView()
{
    /*delete所有的图片和文字等等*/
}

/**
 * @brief 游戏参数的初始化
 *
 */
void MainSceneView::initGamePara()
{
    oilNum=3000;
    steelNum=6500;
    bulletNum=8800;
    alNum=2536;
}


/**
 * @brief item的初始化
 *
 */
void MainSceneView::initItem()
{
    int x_fightButt=120;
    int y_fightButt=180;

    int offsetXSupStr=100;
    int offsetYSupStr=15;
    int offsetXRepFat=60;
    int offsetYRepFat=120;
    int figButtWidth;

    int topButtBaseX=120;
    int topButtBaseY=30;
    int topButtOffsetX=80;

    textMyName    =new TextItem("shuoGG",QPointF(115,0),11,Qt::white);
    textNumOil    =new TextItem(QString::number(oilNum),QPointF(670,30),9,Qt::white);
    textNumSteel  =new TextItem(QString::number(steelNum),QPointF(740,30),9,Qt::white);
    textNumBullet =new TextItem(QString::number(bulletNum),QPointF(670,48),9,Qt::white);
    textNumAl     =new TextItem(QString::number(alNum),QPointF(740,48),9,Qt::white);
    textCapLevel  =new TextItem("41",QPointF(410,5),11,Qt::white);
    textCapRank   =new TextItem("[少将]",QPointF(440,5),10,Qt::white);
    textkanseatNum=new TextItem("4",QPointF(560,5),10,Qt::white);
    textKanmuNum  =new TextItem("91",QPointF(650,5),10,Qt::white);
    textBucketNum =new TextItem("88",QPointF(715,5),10,Qt::white);
    textBuildSrcNum =new TextItem("30",QPointF(775,5),10,Qt::white);

    textDate      =new TextItem(clock->getCurrentDate(),QPointF(14,405),13,Qt::white);
    textTime      =new TextItem(clock->getCurrentTime(Clock::typetime3),QPointF(0,430),15,Qt::white);

    picFloor       =new PicGraphic(QPixmap(QString(URL_HOME_FLOOR)+"001.png"),0,275);
    picBackground  =new PicGraphic(QPixmap(QString(URL_HOME_WALL)+"001.png"),0,0);
    picStick_x0    =new PicGraphic(QPixmap(QString(URL_PORTMAIN)+"image 160.png"),0,0);
    picStick_x1    =new PicGraphic(QPixmap(QString(URL_PORTMAIN)+"image 168.png"),300,0);
    picStick_x2    =new PicGraphic(QPixmap(QString(URL_PORTMAIN)+"image 236_L.png"),250,470);
    picStick_x3    =new PicGraphic(QPixmap(QString(URL_PORTMAIN)+"image 235.png"),-15,470);
    picStick_y1    =new PicGraphic(QPixmap(QString(URL_PORTMAIN)+"image 232.png"),0,30);
    picGearCir     =new PicGraphic(QPixmap(QString(URL_PORTMAIN)+"image 281.png"),0,0);
    picGearGray    =new PicGraphic(QPixmap(QString(URL_PORTMAIN)+"image 233.png"),1,-12);
    picGearWhite   =new PicGraphic(QPixmap(QString(URL_PORTMAIN)+"image 300.png"),-15,-20);
    picGearRotate  =new PicGraphic(QPixmap(QString(URL_PORTMAIN)+"image 157.png"),-32,-35,true,false);
    picClock       =new PicGraphic(QPixmap(QString(URL_PORTMAIN)+"clock.png"),-10,390);
    picOil         =new PicGraphic(QPixmap(QString(URL_PORTMAIN)+"image 141.png"),650,30);
    picSteel       =new PicGraphic(QPixmap(QString(URL_PORTMAIN)+"image 166.png"),720,30);
    picBullet      =new PicGraphic(QPixmap(QString(URL_PORTMAIN)+"image 165.png"),650,50);
    picAl          =new PicGraphic(QPixmap(QString(URL_PORTMAIN)+"image 175.png"),720,50);
    picCapLevel    =new PicGraphic(QPixmap(QString(URL_PORTMAIN)+"image 167.png"),300,12);
    pickanseatNum  =new PicGraphic(QPixmap(QString(URL_PORTMAIN)+"image 223.png"),500,13);
    picKanmuNum    =new PicGraphic(QPixmap(QString(URL_PORTMAIN)+"image 222.png"),590,13);
    picBucketNum   =new PicGraphic(QPixmap(QString(URL_PORTMAIN)+"image 161.png"),680,10);
    picBuildSrcNum =new PicGraphic(QPixmap(QString(URL_PORTMAIN)+"image 171.png"),740,10);


    buttFight=new ImageButtonGraphics(QPixmap(QString(URL_PORTMAIN)+"fight1.png"),
                                      x_fightButt,y_fightButt,true,true);
    buttFight->setAllButtImage(QPixmap(QString(URL_PORTMAIN)+"fight1.png"),
                               QPixmap(QString(URL_PORTMAIN)+"fight2.png"),
                               PicGraphic::getScaledPixmap(QPixmap(QString(URL_PORTMAIN)+"fight2.png"),0.95));
    figButtWidth=buttFight->sizePixmapOrig.width()*0.5-30;

    buttFomation=new ImageButtonGraphics(QPixmap(QString(URL_PORTMAIN)+"image 434.png"),
                                         x_fightButt+15,y_fightButt-100,true,true);
    buttFomation->setAllButtImage(QPixmap(QString(URL_PORTMAIN)+"image 434.png"),
                                  QPixmap(QString(URL_PORTMAIN)+"image 441.png"),
                                  PicGraphic::getScaledPixmap(QPixmap(QString(URL_PORTMAIN)+"image 441.png"),0.95));

    buttStrengthen=new ImageButtonGraphics(QPixmap(QString(URL_PORTMAIN)+"image 385.png"),
                                           x_fightButt+offsetXSupStr+figButtWidth,y_fightButt-offsetYSupStr,true,true);
    buttStrengthen->setAllButtImage(QPixmap(QString(URL_PORTMAIN)+"image 385.png"),
                                    QPixmap(QString(URL_PORTMAIN)+"image 392.png"),
                                    PicGraphic::getScaledPixmap(QPixmap(QString(URL_PORTMAIN)+"image 392.png"),0.95));

    buttSupply=new ImageButtonGraphics(QPixmap(QString(URL_PORTMAIN)+"image 454.png"),
                                       x_fightButt-offsetXSupStr,y_fightButt-offsetYSupStr,true,true);
    buttSupply->setAllButtImage(QPixmap(QString(URL_PORTMAIN)+"image 454.png"),
                                QPixmap(QString(URL_PORTMAIN)+"image 461.png"),
                                PicGraphic::getScaledPixmap(QPixmap(QString(URL_PORTMAIN)+"image 461.png"),0.95));

    buttRepair=new ImageButtonGraphics(QPixmap(QString(URL_PORTMAIN)+"image 444.png"),
                                       x_fightButt-offsetXRepFat,y_fightButt+offsetYRepFat,true,true);
    buttRepair->setAllButtImage(QPixmap(QString(URL_PORTMAIN)+"image 444.png"),
                                QPixmap(QString(URL_PORTMAIN)+"image 451.png"),
                                PicGraphic::getScaledPixmap(QPixmap(QString(URL_PORTMAIN)+"image 451.png"),0.95));

    buttFactory=new ImageButtonGraphics(QPixmap(QString(URL_PORTMAIN)+"image 395.png"),
                                        x_fightButt+offsetXRepFat+figButtWidth,y_fightButt+offsetYRepFat,true,true);
    buttFactory->setAllButtImage(QPixmap(QString(URL_PORTMAIN)+"image 395.png"),
                                 QPixmap(QString(URL_PORTMAIN)+"image 402.png"),
                                 PicGraphic::getScaledPixmap(QPixmap(QString(URL_PORTMAIN)+"image 402.png"),0.95));

    buttConfig=new ImageButtonGraphics(QPixmap(QString(URL_PORTMAIN)+"image 81.png"),
                                       750,430,true,false);
    buttConfig->setAllButtImage(QPixmap(QString(URL_PORTMAIN)+"image 81.png"),
                                QPixmap(QString(URL_PORTMAIN)+"image 81_1.png"),
                                PicGraphic::getScaledPixmap(QPixmap(QString(URL_PORTMAIN)+"image 81_1.png"),0.95));
    /*顶行的一排文字按键*/
    buttTextBattleMark=new ImageButtonGraphics(QPixmap(QString(URL_PORTMAIN)+"image 180.png"),
                                               topButtBaseX,topButtBaseY,false,false);
    buttTextBattleMark->setAllButtImage(QPixmap(QString(URL_PORTMAIN)+"image 180.png"),
                                        QPixmap(QString(URL_PORTMAIN)+"image 182.png"),
                                        PicGraphic::getScaledPixmap(QPixmap(QString(URL_PORTMAIN)+"image 182.png"),0.95));

    buttTextFriend=new ImageButtonGraphics(QPixmap(QString(URL_PORTMAIN)+"image 180.png"),
                                           topButtBaseX+topButtOffsetX,topButtBaseY,false,false);
    buttTextFriend->setAllButtImage(QPixmap(QString(URL_PORTMAIN)+"image 185.png"),
                                    QPixmap(QString(URL_PORTMAIN)+"image 190.png"),
                                    PicGraphic::getScaledPixmap(QPixmap(QString(URL_PORTMAIN)+"image 190.png"),0.95));

    buttTextPicBook=new ImageButtonGraphics(QPixmap(QString(URL_PORTMAIN)+"image 202.png"),
                                            topButtBaseX+topButtOffsetX*2,topButtBaseY,false,false);
    buttTextPicBook->setAllButtImage(QPixmap(QString(URL_PORTMAIN)+"image 202.png"),
                                     QPixmap(QString(URL_PORTMAIN)+"image 204.png"),
                                     PicGraphic::getScaledPixmap(QPixmap(QString(URL_PORTMAIN)+"image 204.png"),0.95));

    buttTextItem=new ImageButtonGraphics(QPixmap(QString(URL_PORTMAIN)+"image 207.png"),
                                         topButtBaseX+topButtOffsetX*3,topButtBaseY,false,false);
    buttTextItem->setAllButtImage(QPixmap(QString(URL_PORTMAIN)+"image 207.png"),
                                  QPixmap(QString(URL_PORTMAIN)+"image 209.png"),
                                  PicGraphic::getScaledPixmap(QPixmap(QString(URL_PORTMAIN)+"image 209.png"),0.95));

    buttTextBackground=new ImageButtonGraphics(QPixmap(QString(URL_PORTMAIN)+"image 212.png"),
                                               topButtBaseX+topButtOffsetX*4,topButtBaseY,false,false);
    buttTextBackground->setAllButtImage(QPixmap(QString(URL_PORTMAIN)+"image 212.png"),
                                        QPixmap(QString(URL_PORTMAIN)+"image 214.png"),
                                        PicGraphic::getScaledPixmap(QPixmap(QString(URL_PORTMAIN)+"image 214.png"),0.95));

    buttTextTask=new ImageButtonGraphics(QPixmap(QString(URL_PORTMAIN)+"image 194.png"),
                                         topButtBaseX+topButtOffsetX*5,topButtBaseY,false,false);
    buttTextTask->setAllButtImage(QPixmap(QString(URL_PORTMAIN)+"image 194.png"),
                                  QPixmap(QString(URL_PORTMAIN)+"image 196.png"),
                                  PicGraphic::getScaledPixmap(QPixmap(QString(URL_PORTMAIN)+"image 196.png"),0.95));

    buttTextBuyItem=new ImageButtonGraphics(QPixmap(QString(URL_PORTMAIN)+"image 217.png"),
                                            topButtBaseX+topButtOffsetX*6,topButtBaseY,false,false);
    buttTextBuyItem->setAllButtImage(QPixmap(QString(URL_PORTMAIN)+"image 217.png"),
                                     QPixmap(QString(URL_PORTMAIN)+"image 219.png"),
                                     PicGraphic::getScaledPixmap(QPixmap(QString(URL_PORTMAIN)+"image 219.png"),0.95));


    buttColorcircle=new ImageButtonGraphics(QPixmap(QString(URL_PORTMAIN)+"image 283.png"),-15,-20,true,true);
    buttColorcircle->setAllButtImage(QPixmap(QString(URL_PORTMAIN)+"image 283.png"),
                                     QPixmap(QString(URL_PORTMAIN)+"image 283.png"),
                                     PicGraphic::getScaledPixmap(QPixmap(QString(URL_PORTMAIN)+"image 283.png"),0.98));


    myscene->addItem(picFloor);
    myscene->addItem(picBackground);

    myscene->addItem(kanmusumeCur->picBodyHalf);

    myscene->addItem(picGearRotate);
    myscene->addItem(picStick_y1);
    myscene->addItem(picStick_x0);
    myscene->addItem(picStick_x1);
    myscene->addItem(picStick_x2);
    myscene->addItem(picStick_x3);
    myscene->addItem(picGearWhite);
    myscene->addItem(picGearCir);
    myscene->addItem(picGearGray);
    myscene->addItem(picClock);
    myscene->addItem(buttFight);
    myscene->addItem(buttStrengthen);
    myscene->addItem(buttSupply);
    myscene->addItem(buttFomation);
    myscene->addItem(buttRepair);
    myscene->addItem(buttFactory);
    myscene->addItem(buttConfig);
    myscene->addItem(textMyName);
    myscene->addItem(buttTextBattleMark);
    myscene->addItem(buttTextFriend);
    myscene->addItem(buttTextPicBook);
    myscene->addItem(buttTextItem);
    myscene->addItem(buttTextBackground);
    myscene->addItem(buttTextTask);
    myscene->addItem(buttTextBuyItem);
    myscene->addItem(picOil);
    myscene->addItem(picSteel);
    myscene->addItem(picBullet);
    myscene->addItem(picAl);
    myscene->addItem(textNumOil);
    myscene->addItem(textNumSteel);
    myscene->addItem(textNumBullet);
    myscene->addItem(textNumAl);
    myscene->addItem(picCapLevel);
    myscene->addItem(textCapLevel);
    myscene->addItem(textCapRank);
    myscene->addItem(pickanseatNum);
    myscene->addItem(picKanmuNum);
    myscene->addItem(textkanseatNum);
    myscene->addItem(textKanmuNum);
    myscene->addItem(picBucketNum);
    myscene->addItem(picBuildSrcNum);
    myscene->addItem(textBucketNum);
    myscene->addItem(textBuildSrcNum);
    myscene->addItem(textDate);
    myscene->addItem(textTime);
    myscene->addItem(buttColorcircle);

    /*舰娘属性初始化*/
    kanmusumeCur->picBodyHalf->setPos(500,50);
    kanmusumeCur->show_hide(true,KanMusume::Pic_bodyHalf);
    /*各种item的动画*/
    picGearRotate->animeEffect->gradualRotate(0,360,20000,QEasingCurve::Linear,0,-1);
    buttColorcircle->animeEffect->gradualRotate(0,360,20000,QEasingCurve::Linear,0,-1);

}

/**
 * @brief 是否使能view的透明度动画功能
 *
 * @param animeOn
 */
void MainSceneView::setAnimeOpacOn(bool animeOn)
{
    if(animeOn)
    {
        effectOpacity=new QGraphicsOpacityEffect;
        animeOpacity =new QPropertyAnimation(effectOpacity,"opacity");//透明度动画必须借助QGraphicsOpacityEffect
        this->setGraphicsEffect(effectOpacity);
    }
}
/**
 * @brief 出现或消失(透明度型)
 *
 * @param isToShow     出现还是消失
 * @param msec         动画持续时间
 * @param aTyte        缓和曲线
 * @param animeHandle  动画句柄
 */
void MainSceneView::gradualShowHide_Opac(bool isToShow, int msec, QEasingCurve::Type aTyte,int handler)
{
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
    animeOpacity->start();
    curHandler=handler;
    emit animeStartSignal(handler);
}

/******************************************private slots******************************************************/
/**
 * @brief 每过一秒都会更新一下时钟和日期
 *
 */
void MainSceneView::updateClock()
{
    textDate->setPlainText(clock->getCurrentDate());
    textTime->setPlainText(clock->getCurrentTime(Clock::typetime3));
}

/**
 * @brief 油钢弹铝资源更新
 *
 */
void MainSceneView::updateSrc()
{
    /*每3分钟更新一次资源的数量*/
    if((clock->minNum)%3 ==0)
    {
        oilNum   +=OIL_INCREASE;
        steelNum +=STEEL_INCREASE;
        bulletNum+=BULLET_INCREASE;
        alNum    +=AL_INCREASE;
        textNumOil->setText(QString::number(oilNum));
        textNumSteel->setText(QString::number(steelNum));
        textNumBullet->setText(QString::number(bulletNum));
        textNumAl->setText(QString::number(alNum));
    }
}

/**
 * @brief view透明度动画结束,发个信号
 *
 */
void MainSceneView::opacAnimeFinish()
{
    emit animeFinishSignal(curHandler);
}
