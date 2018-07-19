#ifndef IMAGEBUTTONGRAPHICS_H
#define IMAGEBUTTONGRAPHICS_H

#include "picgraphic.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>

class ImageButtonGraphics : public PicGraphic
{
    Q_OBJECT
public:
    enum ButtStyle
    {
        ButtNorm,
        ButtPress,
        ButtRelease,
        ButtEnter,
        ButtLeave
    };
    explicit ImageButtonGraphics(const QPixmap &buttNormPic, int x, int y,
                                 bool animeGeomOn=false,bool animeOpacOn=false, QGraphicsItem *parent=0);
    ~ImageButtonGraphics();
    void setButtonPicture(QPixmap pic);
    void setPressPicture(QPixmap pic);
    void setReleasePicture(QPixmap pic);
    void setEnterPicture(QPixmap pic);
    void setLeavePicture(QPixmap pic);
    void setAllButtImage(const QPixmap &buttNorm,const QPixmap &buttEnter,
                         const QPixmap &buttPress);

    ButtStyle currentButtStyle;

protected:
    /*按钮事件函数*/
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
    /*按钮图片对象*/
    QPixmap *buttonPicture;
    QPixmap *pressPicture ;
    QPixmap *releasePicture;
    QPixmap *enterPicture;
    QPixmap *leavePicture;

    QPixmap *buttonPictureOrigin;
    QPixmap *pressPictureOrigin ;
    QPixmap *releasePictureOrigin;
    QPixmap *enterPictureOrigin;
    QPixmap *leavePictureOrigin;

    bool isAnimateEnable;

signals:
    void leftclick(); //左击信号,按键release才发送
    void rightclick();

public slots:

};

#endif // IMAGEBUTTONGRAPHICS_H
