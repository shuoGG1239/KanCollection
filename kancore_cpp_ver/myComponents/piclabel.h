#ifndef PICLABEL_H
#define PICLABEL_H

#include <QLabel>
#include <QPixmap>
#include <QMouseEvent>
#include "./animeEffect/animation.h"
class Animation;

class PicLabel: public QLabel
{
    Q_OBJECT
public:
    explicit PicLabel(QWidget *parent,const QPixmap &pic,int x,int y,bool animeOn=true);
    ~PicLabel();
    Animation *animeEffect;


protected:
    virtual void mousePressEvent(QMouseEvent * e);
    virtual void mouseReleaseEvent(QMouseEvent * e);

private:

signals:
    void leftclick(); //左击信号,按键release才发送
    void rightclick();
};

#endif // PICLABEL_H
