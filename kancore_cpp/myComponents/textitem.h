#ifndef TEXTITEM_H
#define TEXTITEM_H

#include <QGraphicsTextItem>
#include <QFont>
#include <QColor>

class TextItem : public QGraphicsTextItem
{
    Q_OBJECT
public:
    explicit TextItem(const QString &text, const QPointF &pos,int fontsize=10,
                      const QColor &color=Qt::black, QGraphicsItem *parent=0);
    ~TextItem();
    void setTextFont(const QString &font, bool isBold=false, bool isItalic=false);
    void setTextColor(const QColor &color);
    void setTextSize(int fontsize);
    void updateFont();
    void setText(const QString &str);
    QString text();

    QFont textFont; //开放出来供用户使用更多设置,如字体间隔等,设完在使用updateFont即可

private:

signals:

public slots:

};

#endif // TEXTITEM_H
