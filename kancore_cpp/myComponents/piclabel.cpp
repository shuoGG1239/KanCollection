#include "piclabel.h"

PicLabel::PicLabel(QWidget *parent, const QPixmap &pic, int x, int y, bool animeOn):QLabel(parent)
{
    this->setPixmap(pic);
    this->setScaledContents(true); //label图片随label自身的大小变化而跟着变化
    this->setGeometry(x,y,pic.width(),pic.height());
    this->show();
    /*动画初始化*/
    if(animeOn)
        animeEffect=new Animation(this,(QWidget*)this);
}
PicLabel::~PicLabel()
{

}


/**
 * @brief 鼠标事件
 *
 * @param e 鼠标事件类型
 */
void PicLabel::mouseReleaseEvent(QMouseEvent *e)
{
    //响应左击事件
    if((e->button()&Qt::LeftButton)==1)
        emit leftclick();
    //响应右击事件
    else if((e->button()&Qt::RightButton)==1)
        emit rightclick();
}
void PicLabel::mousePressEvent(QMouseEvent *e)
{
    e=e;
}
