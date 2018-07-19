#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <QPushButton>
#include <QPixmap>
#include <QLabel>
#include <QMouseEvent>
#include "./animeEffect/animation.h"

class ImageButton : public QPushButton
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
    explicit ImageButton(QWidget *parent, const QPixmap &buttNorm,
                         const QPixmap &buttEnter, const QPixmap &buttPress, int x, int y, bool isAnimeEnable=false);
    ~ImageButton();
    /*设置按钮图片*/
    void setButtonPicture(QPixmap pic);
    void setPressPicture(QPixmap pic);
    void setReleasePicture(QPixmap pic);
    void setEnterPicture(QPixmap pic);
    void setLeavePicture(QPixmap pic);
    /*按钮位置大小设置*/
    void set_X_Y_width_height(int x, int y, int width, int height);
    void setAnimationEable(bool isEnble);

    Animation *animeEffect;
    ButtStyle currentButtStyle;


protected:
    /*按钮事件函数*/
    void mousePressEvent (QMouseEvent *event);
    void mouseReleaseEvent (QMouseEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void resizeEvent(QResizeEvent *event);

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

};

#endif // IMAGEBUTTON_H
