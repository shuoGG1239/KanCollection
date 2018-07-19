#include "startmenu.h"
#include <qthread.h>

StartMenu::StartMenu(QFrame *parent) :
    QFrame(parent)
{
    this->setAttribute(Qt::WA_DeleteOnClose);//clsoe时自动delete
    this->setFixedSize(SCREEN_WIDTH,SCREEN_HEIGHT);
    //音效音乐初始化
    voiceInit(VOICE_VOLUME);
    //设置背景图片
    this->setStyleSheet("StartMenu{background-image:url(./GameData/UI1/TitleMain/image 1.jpg)}");
    QString mainPicUrl="./GameData/UI1/TitleMain/";
    /*注意:若为QPixmap&,则无法使用QPixmap("...")作为输入对象;要为const QPixmap& 才行*/
    gameStartButt=new ImageButton(this,QPixmap(mainPicUrl+"image 23.png"),
                                  QPixmap(mainPicUrl+"image 24.png"),
                                  QPixmap(mainPicUrl+"image 25.png"),
                                  420,360);
    connect(gameStartButt,SIGNAL(leftclick()),this,SLOT(on_buttonGameStart_clicked()));
    //logo的放置
    QPixmap logoImage(QString(URL_UI1)+"logo.png");
    imageLogo=new PicLabel(this,logoImage,500,50);
    imageLogo->animeEffect->gradualShowHide_Opac(true,2500,QEasingCurve::InOutCubic,ANIME_HANDLER_LOGO_OPAC);//logo淡入
    connect(imageLogo->animeEffect,SIGNAL(signAnimeFinishOpac(int)),this,SLOT(animeOpacEnd(int)));

    gameStartButt->setAnimationEable(true);
    gameStartButt->setEnabled(false);
    gameStartButt->currentButtStyle=ImageButton::ButtPress;//一开始按钮暗的(遵照原作)
    gameStartButt->animeEffect->gradualShowHide_Opac(true,3500,QEasingCurve::InCirc);
    gameStartButt->animeEffect->gradualGeometry(QRect(gameStartButt->x(),gameStartButt->y()+200,
                                                      gameStartButt->width(),gameStartButt->height()),
                                                gameStartButt->geometry(),3500,QEasingCurve::Linear,ANIME_HANDLER_GAMEBUTT_GEOM);
    //几何动画的信号与槽的连接
    connect(gameStartButt->animeEffect,SIGNAL(signAnimeFinishGeom(int)),this,SLOT(buttAnimeGeomEnd(int)));

}

StartMenu::~StartMenu()
{
}

void StartMenu::starImage_init()
{
    //star是在logo周围闪的;而logo的位置为 (500,50)
    imageStar1=new PicLabel(this,QPixmap(QString(URL_UI1)+"TitleMain/star.png"),650,120);
    imageStar2=new PicLabel(this,QPixmap(QString(URL_UI1)+"TitleMain/star.png"),600,60);
    imageStar3=new PicLabel(this,QPixmap(QString(URL_UI1)+"TitleMain/star.png"),510,100);
    imageStar4=new PicLabel(this,QPixmap(QString(URL_UI1)+"TitleMain/star.png"),700,200);
    imageStar5=new PicLabel(this,QPixmap(QString(URL_UI1)+"TitleMain/star.png"),520,210);

    connect(imageStar1->animeEffect,SIGNAL(signAnimeFinishOpac(int)),this,SLOT(starAnimeOpacEnd(int)));
    connect(imageStar2->animeEffect,SIGNAL(signAnimeFinishOpac(int)),this,SLOT(starAnimeOpacEnd(int)));
    connect(imageStar3->animeEffect,SIGNAL(signAnimeFinishOpac(int)),this,SLOT(starAnimeOpacEnd(int)));
    connect(imageStar4->animeEffect,SIGNAL(signAnimeFinishOpac(int)),this,SLOT(starAnimeOpacEnd(int)));
    connect(imageStar5->animeEffect,SIGNAL(signAnimeFinishOpac(int)),this,SLOT(starAnimeOpacEnd(int)));
    /*开始进行闪烁动画*/
    timeStarLast=STAR1_TIMELAST;
    imageStar1->animeEffect->gradualShowHide_Opac(true,timeStarLast,QEasingCurve::Linear,ANIME_HANDLER_STAR1_1);
    timeStarLast=STAR2_TIMELAST;
    imageStar2->animeEffect->gradualShowHide_Opac(true,timeStarLast,QEasingCurve::Linear,ANIME_HANDLER_STAR2_1);
    timeStarLast=STAR3_TIMELAST;
    imageStar3->animeEffect->gradualShowHide_Opac(true,timeStarLast,QEasingCurve::Linear,ANIME_HANDLER_STAR3_1);
    timeStarLast=STAR4_TIMELAST;
    imageStar4->animeEffect->gradualShowHide_Opac(true,timeStarLast,QEasingCurve::Linear,ANIME_HANDLER_STAR4_1);
    timeStarLast=STAR5_TIMELAST;
    imageStar5->animeEffect->gradualShowHide_Opac(true,timeStarLast,QEasingCurve::Linear,ANIME_HANDLER_STAR5_1);
}
/**
 * @brief 音效播放初始化
 *
 */
void StartMenu::voiceInit(int volume)
{
    musicplayTitle=new MusicPlayer(this);
    QString voiceUrl;
    QString numStr;
    voiceUrl=QString(URL_TITILE_SE);
    /*20首开场a音效,随机产生一个数字*/
    numStr=musicplayTitle->getRandomNumStr(1,20,2);
    /*添加音效*/
    musicplayTitle->addMusic(voiceUrl+"a/"+numStr+FORM_MP3);
    numStr=musicplayTitle->getRandomNumStr(1,12,2);
    musicplayTitle->addMusic(voiceUrl+"b/"+numStr+FORM_MP3);
    numStr=musicplayTitle->getRandomNumStr(1,10,2);
    musicplayTitle->addMusic(voiceUrl+"c/"+numStr+FORM_MP3);
    musicplayTitle->setVolume(volume);
    /*播第一首,不循环*/
    musicplayTitle->playOneMusic(0,false);
}

/*********************************slots***************************************/
/**
 * @brief GameStart按钮
 *
 */
void StartMenu::on_buttonGameStart_clicked()
{
    musicplayTitle->playOneMusic(2);
    gameStartButt->setEnabled(false);
    gameStartButt->animeEffect->gradualShowHide_Opac(false,500,QEasingCurve::OutCubic,ANIME_HANDLER_GAMEBUTT_DISPLAY);
    emit gameStartButtClicked();
}

/**
 * @brief 透明度变化结束的slot(除了星星)
 *
 * @param hanlder 动画句柄
 */
void StartMenu::animeOpacEnd(int handler)
{
    //logo淡入之后
    if(handler==ANIME_HANDLER_LOGO_OPAC)
    {
        //星星图片和动画的开始
        starImage_init();
    }
}

/**
 * @brief 按钮出现动画结束的slot
 *
 * @param hanlder 动画句柄
 */
void StartMenu::buttAnimeGeomEnd(int handler)
{
    //gameStart按键升起来之后
    if(handler==ANIME_HANDLER_GAMEBUTT_GEOM)
    {
        musicplayTitle->playOneMusic(1);
        gameStartButt->currentButtStyle=ImageButton::ButtNorm;//按钮变亮
        gameStartButt->setEnabled(true);
        gameStartButt->animeEffect->gradualSize_Geom(QSize(gameStartButt->width()*0.9,gameStartButt->height()*0.9),
                                                     gameStartButt->size(),800,QEasingCurve::OutBounce,1);
    }
}

/**
 * @brief 星星循环动画slot
 *
 * @param handler
 */
void StartMenu::starAnimeOpacEnd(int handler)
{
    if(handler==ANIME_HANDLER_STAR1_1)
    {
        timeStarLast=STAR1_TIMELAST;
        imageStar1->animeEffect->gradualShowHide_Opac(false,timeStarLast,QEasingCurve::Linear,ANIME_HANDLER_STAR1_2);
    }
    else if(handler==ANIME_HANDLER_STAR1_2)
    {
        timeStarLast=STAR1_TIMELAST;
        imageStar1->animeEffect->gradualShowHide_Opac(true,timeStarLast,QEasingCurve::Linear,ANIME_HANDLER_STAR1_1);
    }
    else if(handler==ANIME_HANDLER_STAR2_1)
    {
        timeStarLast=STAR2_TIMELAST;
        imageStar2->animeEffect->gradualShowHide_Opac(false,timeStarLast,QEasingCurve::Linear,ANIME_HANDLER_STAR2_2);
    }
    else if(handler==ANIME_HANDLER_STAR2_2)
    {
        timeStarLast=STAR2_TIMELAST;
        imageStar2->animeEffect->gradualShowHide_Opac(true,timeStarLast,QEasingCurve::Linear,ANIME_HANDLER_STAR2_1);
    }
    else if(handler==ANIME_HANDLER_STAR3_1)
    {
        timeStarLast=STAR3_TIMELAST;
        imageStar3->animeEffect->gradualShowHide_Opac(false,timeStarLast,QEasingCurve::Linear,ANIME_HANDLER_STAR3_2);
    }
    else if(handler==ANIME_HANDLER_STAR3_2)
    {
        timeStarLast=STAR3_TIMELAST;
        imageStar3->animeEffect->gradualShowHide_Opac(true,timeStarLast,QEasingCurve::Linear,ANIME_HANDLER_STAR3_1);
    }
    else if(handler==ANIME_HANDLER_STAR4_1)
    {
        timeStarLast=STAR4_TIMELAST;
        imageStar4->animeEffect->gradualShowHide_Opac(false,timeStarLast,QEasingCurve::Linear,ANIME_HANDLER_STAR4_2);
    }
    else if(handler==ANIME_HANDLER_STAR4_2)
    {
        timeStarLast=STAR4_TIMELAST;
        imageStar4->animeEffect->gradualShowHide_Opac(true,timeStarLast,QEasingCurve::Linear,ANIME_HANDLER_STAR4_1);
    }
    else if(handler==ANIME_HANDLER_STAR5_1)
    {
        timeStarLast=STAR5_TIMELAST;
        imageStar5->animeEffect->gradualShowHide_Opac(false,timeStarLast,QEasingCurve::Linear,ANIME_HANDLER_STAR5_2);
    }
    else if(handler==ANIME_HANDLER_STAR5_2)
    {
        timeStarLast=STAR5_TIMELAST;
        imageStar5->animeEffect->gradualShowHide_Opac(true,timeStarLast,QEasingCurve::Linear,ANIME_HANDLER_STAR5_1);
    }

}



/**
 * @brief 快捷键系列
 *
 * @param e
 */
void StartMenu::keyPressEvent(QKeyEvent *e)
{
    if(gameStartButt->isEnabled())
    {
        if (e->key() == Qt::Key_Space)
        {
            this->on_buttonGameStart_clicked();
        }
    }
}

