#ifndef STARTMENU_H
#define STARTMENU_H

#include <QFrame>
#include <QLabel>
#include <QTime>
#include <QKeyEvent>
#include <qglobal.h>
#include "publicConstData.h"
#include "./myComponents/imagebutton.h"
#include "./myComponents/piclabel.h"
#include "./musicUtils/musicplayer.h"

#define  VOICE_VOLUME  60
#define  STAR_TIME_MIN 500
#define  STAR_TIME_MAX 1500
/*星星们的闪烁时间间隔*/
#define  STAR1_TIMELAST 500
#define  STAR2_TIMELAST 600
#define  STAR3_TIMELAST 800
#define  STAR4_TIMELAST 700
#define  STAR5_TIMELAST 900
/*星星动画的handler*/
#define ANIME_HANDLER_STAR1_1       500
#define ANIME_HANDLER_STAR1_2       501
#define ANIME_HANDLER_STAR2_1       502
#define ANIME_HANDLER_STAR2_2       503
#define ANIME_HANDLER_STAR3_1       504
#define ANIME_HANDLER_STAR3_2       505
#define ANIME_HANDLER_STAR4_1       506
#define ANIME_HANDLER_STAR4_2       507
#define ANIME_HANDLER_STAR5_1       508
#define ANIME_HANDLER_STAR5_2       509

#define ANIME_HANDLER_GAMEBUTT_GEOM    0
#define ANIME_HANDLER_LOGO_OPAC        0
#define ANIME_HANDLER_GAMEBUTT_DISPLAY 1
#define ANIME_HANDLER_BLACK_SHOW       2


class StartMenu : public QFrame
{
    Q_OBJECT

public:
    explicit StartMenu(QFrame *parent = 0);
    ~StartMenu();

    ImageButton *gameStartButt;
    PicLabel    *imageLogo;
    PicLabel    *imageStar1;
    PicLabel    *imageStar2;
    PicLabel    *imageStar3;
    PicLabel    *imageStar4;
    PicLabel    *imageStar5;
    MusicPlayer *musicplayTitle;

protected:
    virtual void keyPressEvent(QKeyEvent *e);

private:
    void voiceInit(int volume);
    void starImage_init();
    int timeStarLast;

signals:
    void musicAllOver();
    void gameStartButtClicked();


public slots:
    void on_buttonGameStart_clicked();
    void buttAnimeGeomEnd(int handler);
    void animeOpacEnd(int handler);
    void starAnimeOpacEnd(int handler);
};

#endif // STARTMENU_H
