#include "textitem.h"

/**
 * @brief item文字结构体,字体初始化为"微软雅黑"
 *
 * @param parent 父
 * @param text   文字
 * @param pos    位置
 * @param fontsize 字体号
 * @param color    颜色
 */
TextItem::TextItem(const QString &text, const QPointF &pos,
                   int fontsize, const QColor &color,QGraphicsItem *parent) :
    QGraphicsTextItem(text,parent)
{
    this->setPos(pos);
    textFont.setFamily("微软雅黑");
    textFont.setPointSize(fontsize);
    this->setFont(textFont);
    this->setDefaultTextColor(color);
}
TextItem::~TextItem()
{

}

/**********************************public***************************************/

/**
 * @brief 设置颜色
 *
 * @param color 如 Qt::white
 */
void TextItem::setTextColor(const QColor &color)
{
    this->setDefaultTextColor(color);
}

/**
 * @brief 设置字体
 *
 * @param font    字体如"微软雅黑"
 * @param isBold  加粗
 */
void TextItem::setTextFont(const QString &font, bool isBold,bool isItalic)
{
    textFont.setFamily(font);
    textFont.setBold(isBold);
    textFont.setItalic(isItalic);
    this->setFont(textFont);
}

/**
 * @brief 设置字体大小
 *
 * @param fontsize
 */
void TextItem::setTextSize(int fontsize)
{
    textFont.setPointSize(fontsize);
    this->setFont(textFont);
}

/**
 * @brief 将 textFont设置进去
 *
 */
void TextItem::updateFont()
{
    this->setFont(textFont);
}

/**
 * @brief 获取其字符串
 *
 * @return QString
 */
QString TextItem::text()
{
    return this->toPlainText();
}

/**
 * @brief 设字符串
 *
 * @param str
 */
void TextItem::setText(const QString &str)
{
    this->setPlainText(str);
}
