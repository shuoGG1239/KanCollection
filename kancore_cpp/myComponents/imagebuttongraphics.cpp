#include "imagebuttongraphics.h"

ImageButtonGraphics::ImageButtonGraphics(const QPixmap &buttNormPic, int x, int y, bool animeGeomOn, bool animeOpacOn,
                                         QGraphicsItem *parent)
    :PicGraphic(buttNormPic,x,y,animeGeomOn,animeOpacOn,parent)
{
    //使能hover事件
    this->setAcceptHoverEvents(true);
    this->setAcceptDrops(true);
    /*一开始所有按钮状态均为buttNormPic*/
    buttonPicture   = new QPixmap(buttNormPic);
    pressPicture    = new QPixmap(buttNormPic);
    releasePicture  = new QPixmap(buttNormPic);
    enterPicture    = new QPixmap(buttNormPic);
    leavePicture    = new QPixmap(buttNormPic);
    currentButtStyle=ButtNorm;

}

ImageButtonGraphics::~ImageButtonGraphics()
{

}

/**
 * @brief 一次性设置所有按钮图片,方便
 *
 * @param buttNorm
 * @param buttEnter
 * @param buttPress
 */
void ImageButtonGraphics::setAllButtImage(const QPixmap &buttNorm,const QPixmap &buttEnter,
                                          const QPixmap &buttPress)
{
    //设置按钮图片
    this->setButtonPicture(buttNorm);
    this->setEnterPicture(buttEnter);
    this->setLeavePicture(buttNorm);
    this->setPressPicture(buttPress);
    this->setReleasePicture(buttEnter);
}

/**
 * @brief 设置按钮图片,可以随时使用,可用于中途改变按键图片,灵活
 *
 * @param pic 输入的pximap按钮图片
 */
void ImageButtonGraphics::setButtonPicture(QPixmap pic)
{
    *buttonPicture=pic;
}
void ImageButtonGraphics::setEnterPicture(QPixmap pic)
{
    *enterPicture=pic;

}
void ImageButtonGraphics::setLeavePicture(QPixmap pic)
{
    *leavePicture=pic;

}
void  ImageButtonGraphics::setPressPicture(QPixmap pic)
{
    *pressPicture=pic;
}
void  ImageButtonGraphics::setReleasePicture(QPixmap pic)
{
    *releasePicture=pic;
}



/***********************************protected****************************************/
/**
 * @brief 鼠标事件
 *
 * @param e 鼠标事件类型
 */
void ImageButtonGraphics::mousePressEvent (QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        this->setPixmap(*pressPicture);
        currentButtStyle=ButtPress;
    }
}
void ImageButtonGraphics::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //响应左击事件
    if((event->button()&Qt::LeftButton)==1)
    {
        emit leftclick();
        this->setPixmap(*enterPicture);
        currentButtStyle=ButtRelease;
    }
    //响应右击事件
    else if((event->button()&Qt::RightButton)==1)
        emit rightclick();
}
void ImageButtonGraphics::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsPixmapItem::hoverEnterEvent(event);
    this->setPixmap(*enterPicture);
    event=event;
    currentButtStyle=ButtEnter;
}
void ImageButtonGraphics::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsPixmapItem::hoverLeaveEvent(event);
    this->setPixmap(*leavePicture);
    event=event;
    currentButtStyle=ButtLeave;
}

