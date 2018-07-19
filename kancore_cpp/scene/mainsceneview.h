#ifndef MAINSCENEVIEW_H
#define MAINSCENEVIEW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include "./animeEffect/animation.h"
#include "./myComponents/picgraphic.h"
#include "publicConstData.h"
#include "./myComponents/imagebuttongraphics.h"
#include "./myComponents/textitem.h"
#include "./myComponents/clock.h"
#include "./model/kanmusume.h"
/*油钢弹铝每分钟的增长数量*/
#define  OIL_INCREASE      3
#define  STEEL_INCREASE    3
#define  BULLET_INCREASE   3
#define  AL_INCREASE       1


class MainSceneView : public QGraphicsView
{
    Q_OBJECT
public:
    MainSceneView(QWidget *parent = 0);
    ~MainSceneView();
    void gradualShowHide_Opac(bool isToShow, int msec,
                              QEasingCurve::Type aTyte=QEasingCurve::Linear, int handler=0);
    void setAnimeOpacOn(bool animeOn);

    QGraphicsScene *myscene;
    QGraphicsOpacityEffect *effectOpacity;
    QPropertyAnimation *animeOpacity;

    TextItem   *textMyName;
    TextItem   *textCapLevel;
    TextItem   *textCapRank;
    TextItem   *textKanmuNum;
    TextItem   *textkanseatNum;
    TextItem   *textBucketNum;
    TextItem   *textBuildSrcNum;

    ImageButtonGraphics *buttConfig;
    ImageButtonGraphics *buttFight;
    ImageButtonGraphics *buttFomation;
    ImageButtonGraphics *buttFactory;
    ImageButtonGraphics *buttSupply;
    ImageButtonGraphics *buttStrengthen;
    ImageButtonGraphics *buttRepair;

    ImageButtonGraphics *buttTextBattleMark;
    ImageButtonGraphics *buttTextFriend;
    ImageButtonGraphics *buttTextPicBook;
    ImageButtonGraphics *buttTextItem;
    ImageButtonGraphics *buttTextBackground;
    ImageButtonGraphics *buttTextTask;
    ImageButtonGraphics *buttTextBuyItem;

    ImageButtonGraphics *buttColorcircle;

    KanMusume *kanmusumeCur;


private:
    void initItem();
    void initGamePara();

    PicGraphic *picGearRotate;
    PicGraphic *picGearCir;
    PicGraphic *picGearGray;
    PicGraphic *picGearWhite;

    PicGraphic *picClock;

    PicGraphic *picFloor;
    PicGraphic *picBackground;
    PicGraphic *picStick_y1;
    PicGraphic *picStick_x0;
    PicGraphic *picStick_x1;
    PicGraphic *picStick_x2;
    PicGraphic *picStick_x3;
    PicGraphic *picStick_x4;

    PicGraphic *picOil;
    PicGraphic *picSteel;
    PicGraphic *picBullet;
    PicGraphic *picAl;
    TextItem   *textNumOil;
    TextItem   *textNumSteel;
    TextItem   *textNumBullet;
    TextItem   *textNumAl;
    PicGraphic *picCapLevel;
    PicGraphic *picKanmuNum;
    PicGraphic *pickanseatNum;
    PicGraphic *picBucketNum;
    PicGraphic *picBuildSrcNum;

    TextItem   *textDate;
    TextItem   *textTime;
    Clock      *clock;

    uint oilNum    ;
    uint steelNum  ;
    uint bulletNum ;
    uint alNum     ;

    int curHandler;

signals:
    void animeFinishSignal(int handler);
    void animeStartSignal(int handler);

public slots:


private slots:
    void updateClock();
    void updateSrc();
    void opacAnimeFinish();


};

#endif // MAINSCENEVIEW_H
