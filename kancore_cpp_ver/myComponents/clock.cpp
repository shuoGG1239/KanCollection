#include "clock.h"

Clock::Clock(QObject *parent) :
    QObject(parent)
{
    secNum=0;
    minNum=0;
    hourNum=0;
    dayNum=0;
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(clockTimeout()));
    timer->start(1000);
}

Clock::~Clock()
{

}


/**
 * @brief 获得当前的日期,有多种返回格式
 *
 * @param type 格式看头文件解释
 * @return QString 返回字符串
 */
QString Clock::getCurrentDate(TypeDate type)
{
    switch (type) {
    case typedate1:
        return QDateTime::currentDateTime().toString("MM/dd");
    case typedate2:
        return QDateTime::currentDateTime().toString("MM dd");
    case typedate3:
        return QDateTime::currentDateTime().toString("yyyy/MM/dd");
    default:
        return QDateTime::currentDateTime().toString("MM/dd");
    }
}

/**
 * @brief 获得当前的时间,有多种返回格式
 *
 * @param type 格式看头文件解释
 * @return QString 返回字符串
 */
QString Clock::getCurrentTime(TypeTime type)
{
    switch (type) {
    case typetime1:
        return QDateTime::currentDateTime().toString("hh:mm");
    case typetime2:
        return QDateTime::currentDateTime().toString("hh mm");
    case typetime3:
        return QDateTime::currentDateTime().toString("hh:mm:ss");
    default:
        return QDateTime::currentDateTime().toString("hh:mm");
    }

}



/******************************slots******************************************/
/**
 * @brief 1s时间到
 *
 */
void Clock::clockTimeout()
{
    emit secTimeout();
    if(secNum<60)
    {
        secNum++;
    }
    else
    {
        secNum=0;
        minNum++;
        emit minTimeout();
        if(minNum<60)
        {
            minNum++;
        }
        else
        {
            minNum=0;
            hourNum++;
            emit hourTimeout();
            if(hourNum<24)
            {
                hourNum++;
            }
            else
            {
                hourNum=0;
                dayNum++;
                if(dayNum>=24)
                    dayNum=0;
            }

        }

    }

}
