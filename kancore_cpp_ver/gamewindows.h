#ifndef GAMEWINDOWS_H
#define GAMEWINDOWS_H

#include "./scene/startmenu.h"
#include "./scene/blackgroundview.h"
#include "./scene/mainsceneview.h"

#define ANIME_HANDLER_FIRSTSHOW  0

class GameWindows : public QFrame
{
    Q_OBJECT
public:
    explicit GameWindows(QFrame *parent = 0);
    ~GameWindows();
    /*开头界面和过渡动画用QWidget体系*/
    StartMenu *mystartMenu;     //开场Menu窗口
    BlackgroundView *myBlackground; //过渡动画黑窗口

    /*主界面以及其他游戏场景用QgraphicWidget体系*/
    MainSceneView *maingameView;

private:
    void showMainScene();


signals:

public slots:
    void show_BlackWindow();
    void close_MenuWindow(int numOfOverMusic);
    void maingameView_animeFinish(int handler);

};

#endif // GAMEWINDOWS_H
