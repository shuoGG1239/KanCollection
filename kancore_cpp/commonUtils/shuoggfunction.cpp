#include "shuoggfunction.h"

ShuoGGFunction::ShuoGGFunction()
{
}



/**
 * @brief 在某个区间获得一个随机数
 *
 * @param min 最小值
 * @param max 最大值
 * @param seedOffset 偏移算子
 * @param partitions 分割数
 * @return int
 */
int ShuoGGFunction::getRandomNum(int min,int max,int seedOffset,int partitions)
{
    if(max <= min)
        return 0;
    QTime time1=QTime::currentTime();
    //当有几个随机数是在同一时间取的,这个时候就需要另外加偏移量
    int offsetValue=seedOffset*((max-min)/partitions);
    qsrand(time1.msec()+time1.second()*1000+offsetValue);
    //qsrand(x); 对应一个伪随机数: qsrand(1)==qsrand(1); qsrand(1)!=qsrand(2);
    int num=(qrand()%max)+min;
    return num;
}

/**
 * @brief 延时函数,让当前进程sleep n毫秒
 *
 * @param msec 延时时间毫秒
 */
void ShuoGGFunction::sleepShuoGG(unsigned int msec)
{
    QTime reachTime =QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime() <reachTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}
