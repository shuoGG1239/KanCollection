#ifndef PICGRAPHIC_H
#define PICGRAPHIC_H
//两种动画体系的选择
#define USE_ANIME_ITEM   0

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#if USE_ANIME_ITEM
#include "animationitem.h"
class AnimationItem;
#else
#include "./animeEffect/animationgraphic.h"
class AnimationGraphic;
#endif



class PicGraphic:public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
    /*其实这些属性定义在QGraphicsPixmapItem已经有了,这里写这些当教程*/
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    Q_PROPERTY(qreal scale READ scale WRITE setScale)
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)
public:
    explicit PicGraphic(const QPixmap &pic, int x, int y,
                        bool animeGeomOn=false, bool animeOpacOn=false, QGraphicsItem *parent=0);
    PicGraphic(bool animeGeomOn=false, bool animeOpacOn=false, QGraphicsItem *parent=0);
    ~PicGraphic();
    void setGeomCenter(qreal x_percent,qreal y_percent);
    static QPixmap getScaledPixmap(const QPixmap &inputPic,qreal scale);

#if USE_ANIME_ITEM
    AnimationItem *animeEffect;
#else
    AnimationGraphic *animeEffect;
#endif
    QSize sizePixmapOrig;

protected:
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *e);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *e);
private:
    void setAnimeAll_OnOff(bool animeGeomOn, bool animeOpacOn);

signals:
    void leftclick(); //左击信号,按键release才发送
    void rightclick();

};

#endif // PICGRAPHIC_H
