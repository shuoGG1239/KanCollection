#include "gamewindows.h"

GameWindows::GameWindows(QFrame *parent) :
    QFrame(parent)
{
    this->setFixedSize(SCREEN_WIDTH,SCREEN_HEIGHT);
    /*开头菜单*/
    mystartMenu=new StartMenu(this);
    mystartMenu->setFocus(); //focus后才能使用快捷键
    mystartMenu->show();
    /*过渡船界面*/
    myBlackground=new BlackgroundView(this);
    myBlackground->hide();

    connect(mystartMenu,SIGNAL(gameStartButtClicked()),this,SLOT(show_BlackWindow()));
    connect(mystartMenu->musicplayTitle,SIGNAL(oneSoundOverSignal(int)),this,SLOT(close_MenuWindow(int)));

    /*游戏主界面*/
    maingameView=new MainSceneView(this);
    connect(maingameView,SIGNAL(animeFinishSignal(int)),this,SLOT(maingameView_animeFinish(int)));
    maingameView->hide();
}

GameWindows::~GameWindows()
{

}

/**
 * @brief 游戏主界面出现的动画特效和音乐特效
 *
 */
void GameWindows::showMainScene()
{
    maingameView->show();
    /*整个界面渐变出现*/
    maingameView->gradualShowHide_Opac(true,1000,QEasingCurve::Linear,ANIME_HANDLER_FIRSTSHOW);
    /*按钮的出现动画*/
    maingameView->buttFight->animeEffect->gradualScale(0,1,1500,QEasingCurve::OutBounce,1);
    maingameView->buttFomation->animeEffect->gradualScale(0,1,1500,QEasingCurve::OutCubic,2);
    maingameView->buttStrengthen->animeEffect->gradualScale(0,1,1500,QEasingCurve::OutCubic,3);
    maingameView->buttSupply->animeEffect->gradualScale(0,1,1500,QEasingCurve::OutCubic,4);
    maingameView->buttRepair->animeEffect->gradualScale(0,1,1500,QEasingCurve::OutCubic,5);
    maingameView->buttFactory->animeEffect->gradualScale(0,1,1500,QEasingCurve::OutCubic,6);
    /*看板舰娘的第一句挨SaTsU~*/
    maingameView->kanmusumeCur->voiceplayer->playOneMusic(0);
}

/**********************************slots*************************************/
/**
 * @brief gameStart按钮按下时blackWindow出现
 *
 */
void GameWindows::show_BlackWindow()
{
    myBlackground->display();
    myBlackground->playAnime();
}

/**
 * @brief title的最后一首音乐结束时,titleWindow就可以关掉delete了
 *
 * @param numOfOverMusic
 */
void GameWindows::close_MenuWindow(int numOfOverMusic)
{
    if(numOfOverMusic==2)
    {
        mystartMenu->close();
        //主游戏页面渐变出现
        showMainScene();
    }
}

/**
 * @brief 主游戏界面的出现消失动画结束的slot
 *
 * @param handler 动画句柄
 */
void GameWindows::maingameView_animeFinish(int handler)
{
    if(handler==ANIME_HANDLER_FIRSTSHOW)
    {
        myBlackground->close();
    }
}
