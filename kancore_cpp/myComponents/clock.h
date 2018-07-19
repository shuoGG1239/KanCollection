#ifndef CLOCK_H
#define CLOCK_H

#include <QObject>
#include <QString>
#include <QTimer>
#include <QTime>

class Clock : public QObject
{
    Q_OBJECT
public:
    enum TypeDate{  // 格式举例:
        typedate1,  // 12/25
        typedate2,  // 12 25
        typedate3   // 2016/12/25

    };
    enum TypeTime{ //格式举例:
        typetime1, //  18:00
        typetime2, //  18 00
        typetime3  //  18:00:20
    };
    explicit Clock(QObject *parent = 0);
    ~Clock();
    QString  getCurrentDate(TypeDate type=typedate1);
    QString  getCurrentTime(TypeTime type=typetime1);

    QTimer *timer;
    uchar secNum;
    uchar minNum;
    uchar hourNum;
    uchar dayNum;

private:

signals:
    void secTimeout();
    void minTimeout();
    void hourTimeout();

private slots:
    void clockTimeout();

};

#endif // CLOCK_H
