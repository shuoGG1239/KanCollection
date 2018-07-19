#include "picgraphic.h"

PicGraphic::PicGraphic(const QPixmap &pic, int x, int y, bool animeGeomOn,bool animeOpacOn, QGraphicsItem *parent)
    :QGraphicsPixmapItem(pic,parent)
{
    //改变几何中心,默认在重心
    sizePixmapOrig.setWidth(pic.width());
    sizePixmapOrig.setHeight(pic.height());
    this->setTransformOriginPoint(pic.width()*0.5,pic.height()*0.5);

    this->setPos(x,y);
    this->setOpacity(1);
    this->setScale(1);
    this->show();

    setAnimeAll_OnOff(animeGeomOn,animeOpacOn);
}

PicGraphic::PicGraphic(bool animeGeomOn, bool animeOpacOn, QGraphicsItem *parent)
    :QGraphicsPixmapItem(parent)
{
    setAnimeAll_OnOff(animeGeomOn,animeOpacOn);
    this->show();
}


PicGraphic::~PicGraphic()
{

}


/**
 * @brief 开启或关闭动画效果(给构造函数用的)
 *
 * @param animeOn
 */
void PicGraphic::setAnimeAll_OnOff(bool animeGeomOn,bool animeOpacOn)
{
#if USE_ANIME_ITEM
    if(animeGeomOn && animeOpacOn)
        animeEffect=new AnimationItem(this,this,true,true);
    else if(animeGeomOn  && !animeOpacOn)
        animeEffect=new AnimationItem(this,this,true,false);
    else if(!animeGeomOn && animeOpacOn)
        animeEffect=new AnimationItem(this,this,false,true);
#else
    if(animeGeomOn && animeOpacOn)
        animeEffect=new AnimationGraphic(this,this,true,true,true,true);
    else if(animeGeomOn  && !animeOpacOn)
        animeEffect=new AnimationGraphic(this,this,true,true,true,false);
    else if(!animeGeomOn && animeOpacOn)
        animeEffect=new AnimationGraphic(this,this,false,false,false,true);
#endif
}


/**
 * @brief 设置几何中心
 *
 * @param x_percent x方向上的比例位置(从左往右)
 * @param y_percent y方向上的比例位置(从上往下)
 */
void PicGraphic::setGeomCenter(qreal x_percent,qreal y_percent)
{
    this->setTransformOriginPoint(this->scale()*(sizePixmapOrig.width())*x_percent,
                                  this->scale()*(sizePixmapOrig.height())*y_percent);
}

/**
 * @brief 获得缩放完的pixmap
 *
 * @param inputPic
 * @param scale
 * @return QPixmap
 */
QPixmap PicGraphic::getScaledPixmap(const QPixmap &inputPic,qreal scale)
{
    QPixmap rePic=inputPic.scaled(inputPic.width()*scale,inputPic.height()*scale);
    return rePic;
}

/**
 * @brief 鼠标事件
 *
 * @param e 鼠标事件类型
 */
void PicGraphic::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    //响应左击事件
    if((e->button()&Qt::LeftButton)==1)
        emit leftclick();
    //响应右击事件
    else if((e->button()&Qt::RightButton)==1)
        emit rightclick();
}
void PicGraphic::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    e=e;
}
