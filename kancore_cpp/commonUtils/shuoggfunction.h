#ifndef SHUOGGFUNCTION_H
#define SHUOGGFUNCTION_H

#include <QTime>
#include <QApplication>
#include <qglobal.h>
#include <time.h>

class ShuoGGFunction
{
public:
    ShuoGGFunction();
    static int getRandomNum(int min, int max, int seedOffset=0, int partitions=10);
    static void sleepShuoGG(unsigned int msec);
};

#endif // SHUOGGFUNCTION_H
