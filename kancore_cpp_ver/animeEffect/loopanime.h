#ifndef LOOPANIME_H
#define LOOPANIME_H

#include "animation.h"
#define ANIME_HANDLER_OPAC_1   1
#define ANIME_HANDLER_OPAC_2   2

#define ANIME_HANDLER_GEOM_1   1
#define ANIME_HANDLER_GEOM_2   2


class LoopAnime : public Animation
{
    Q_OBJECT
public:
    explicit LoopAnime(QObject *parent,QWidget *inputItem);
    ~LoopAnime();
    void setLoopOpac(bool startWithShow, int msec, QEasingCurve::Type curve=QEasingCurve::Linear);
    void startLoopOpac();
    void stopLoopOpac();

    void setLoopPos(QPoint startPos,QPoint endPos,int msec,QEasingCurve::Type curve=QEasingCurve::Linear);
    void startLoopPos();
    void stopLoopPos();

private:
    int timeLastOpac;
    int timeLastGeom;
    QPoint startPos;
    QPoint endPos;

    bool isShowOrHide;

    QEasingCurve::Type curveOpac;
    QEasingCurve::Type curveGeom;


signals:

public slots:
    void loopOpacSlot(int handler);
    void loopPosSlot(int handler);

};

#endif // LOOPANIME_H
