#include "imagebutton.h"

ImageButton::ImageButton(QWidget *parent,const QPixmap &buttNorm,const QPixmap &buttEnter,
                         const QPixmap &buttPress, int x, int y,bool isAnimeEnable):QPushButton(parent)
{
    //保存图片成员初始化
    buttonPicture   = new QPixmap();
    pressPicture    = new QPixmap();
    releasePicture  = new QPixmap();
    enterPicture    = new QPixmap();
    leavePicture    = new QPixmap();
    //原始图片成员初始化,多次scaled一个图片会严重降质,所以需要原图辅助
    buttonPictureOrigin   = new QPixmap(buttNorm);
    pressPictureOrigin    = new QPixmap(buttPress);
    releasePictureOrigin  = new QPixmap(buttEnter);
    enterPictureOrigin    = new QPixmap(buttEnter);
    leavePictureOrigin    = new QPixmap(buttNorm);
    //背景透明
    this->setFlat(true);
    //设置按钮图片
    setButtonPicture(buttNorm);
    setEnterPicture(buttEnter);
    setLeavePicture(buttNorm);
    setPressPicture(buttPress);
    setReleasePicture(buttEnter);
    //自适应大小和设置位置
    set_X_Y_width_height(x,y,buttNorm.width(),buttNorm.height());
    //默认关闭动画效果
    this->setAnimationEable(isAnimeEnable);

    this->show();
}

ImageButton::~ImageButton()
{
    delete buttonPicture;
    buttonPicture =NULL;
    delete pressPicture;
    pressPicture  =NULL;
    delete releasePicture;
    releasePicture=NULL;
    delete enterPicture;
    enterPicture  =NULL;
    delete leavePicture;
    leavePicture  =NULL;
}


/**
 * @brief 设置按钮图片
 *
 * @param pic 输入的pximap按钮图片
 */
void  ImageButton::setButtonPicture(QPixmap pic)
{
    *buttonPicture=pic;
    this->setIcon(QIcon(*buttonPicture));
    currentButtStyle=ButtNorm;
}
void ImageButton::setEnterPicture(QPixmap pic)
{
    *enterPicture=pic;
}
void ImageButton::setLeavePicture(QPixmap pic)
{
    *leavePicture=pic;
}
void  ImageButton::setPressPicture(QPixmap pic)
{
    *pressPicture=pic;
}
void  ImageButton::setReleasePicture(QPixmap pic)
{
    *releasePicture=pic;
}

/**
 * @brief 使能动画功能,没调用此函数使用动画会挂
 *
 * @param isEnble
 */
void ImageButton::setAnimationEable(bool isEnble)
{
    /*加个==NULL的条件是为了避免重复new的情况*/
    if(isEnble==true)
        animeEffect=new Animation(this,(QWidget*)this);
}

/**
 * @brief 设置按钮的大小和位置
 *
 * @param x 横坐标
 * @param y 纵坐标
 * @param width  宽度
 * @param height 高度
 */
void  ImageButton::set_X_Y_width_height(int x, int y, int width, int height)
{
    this -> setIconSize(QSize(width, height));
    this -> setGeometry(x, y, width, height);
}


/**
 * @brief 各种按钮事件
 *
 * @param event 事件
 */
void  ImageButton::mouseReleaseEvent (QMouseEvent *event)
{
    //只响应左击事件
    if((event->button()&Qt::LeftButton)==1)
    {
        this->setIcon(QIcon(*releasePicture));
        emit leftclick();
        currentButtStyle=ButtRelease;
    }
}
void  ImageButton::mousePressEvent (QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        this->setIcon(QIcon(*pressPicture));
        currentButtStyle=ButtPress;
    }
}
void ImageButton::enterEvent(QEvent *event)
{
    this-> setIcon(QIcon(*enterPicture));
    event=event;
    currentButtStyle=ButtEnter;
}
void ImageButton::leaveEvent(QEvent *event)
{
    this-> setIcon(QIcon(*leavePicture));
    event=event;
    currentButtStyle=ButtLeave;
}


/**
 * @brief butt大小变化时里面的icon也随之变
 *
 * @param event resize事件
 */
void ImageButton::resizeEvent(QResizeEvent *event)
{
    //调用父类的源函数
    QPushButton::resizeEvent(event);
    /*图标随着butt的大小改变而改变size  注意:对一张图迭代多次scaled会严重失真*/
    *buttonPicture  =buttonPictureOrigin->scaled(this->size());
    *pressPicture   =pressPictureOrigin->scaled(this->size());
    *releasePicture =releasePictureOrigin->scaled(this->size());
    *enterPicture   =enterPictureOrigin->scaled(this->size());
    *leavePicture   =leavePictureOrigin->scaled(this->size());
    /*判断当前butt是属于什么状态*/
    switch (currentButtStyle) {
    case ButtNorm:
        this->setIcon(QIcon(*buttonPicture));break;
    case ButtPress:
        this->setIcon(QIcon(*pressPicture));break;
    case ButtEnter:
        this->setIcon(QIcon(*enterPicture));break;
    case ButtRelease:
        this->setIcon(QIcon(*releasePicture));break;
    case ButtLeave:
        this->setIcon(QIcon(*leavePicture));break;
    }
}
