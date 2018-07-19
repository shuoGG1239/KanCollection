#ifndef KANMUSUME_H
#define KANMUSUME_H

#include <QObject>
#include <QPixmap>
#include "../myComponents/picgraphic.h"
#include "publicConstData.h"
#include "../musicUtils/musicplayer.h"

#define URL_KANPIC  "./GameData/kanPic/"
#define KAN_PIC1    "image 5"
#define KAN_PIC2    "image 7"
#define KAN_PIC3    "image 9"
#define KAN_PIC4    "image 11"
#define KAN_PIC5    "image 17"
#define KAN_PIC6    "image 19"
#define KAN_PIC7    "image 13"
#define KAN_PIC8    "image 15"
#define KAN_PIC9    "image 21"
#define KAN_PIC10   "image 23"
#define KAN_PIC11   "image 1"
#define KAN_PIC12   "image 3"
#define KAN_PIC13   "image 27"
#define KAN_PIC14   "image 29"
#define KAN_PIC15   "image 25"

namespace KanEnum {
enum Speed
{
    slowSp,
    normalSp,
    fastSp
};

enum Gunshot
{
    shortShot,
    normalShot,
    longShot
};
enum BrokenLevel
{
    brokenLow,
    brokenNorm,
    brokenHigh
};
}


typedef struct
{
    int durAbility;
    int firePower;
    int armor;
    int torpedo;
    int avoid;
    int airPower;
    int plateAfford;
    int divAnti;
    KanEnum::Speed speed;
    int explore;
    KanEnum::Gunshot gunshot;
    int luck;
} KanProperty;


class KanMusume : public QObject
{
    Q_OBJECT
public:
    enum PicSelect
    {
        Pic_cardNorm,
        Pic_cardBroken,
        Pic_bodyHalf,
        Pic_bodyHalfBroken,
        Pic_bodyBigAll,
        Pic_bodyBigAllBroken,
        Pic_bodySmaAll,
        Pic_bodySmaAllBroken,
        Pic_bodyPart,
        Pic_bodyPartBroken,
        Pic_tip,
        Pic_tipBroken,
        Pic_supply,
        Pic_supplyBroken,
        Pic_text,
    };
    explicit KanMusume(const QString &kanNameFolder, const QString &voiceFolder, QObject *parent = 0);
    ~KanMusume();
    void setKanpic(const QPixmap &cardNorm,
                   const QPixmap &cardBroken,
                   const QPixmap &bodyHalf,
                   const QPixmap &bodyHalfBroken,
                   const QPixmap &bodyBigAll,
                   const QPixmap &bodyBigAllBroken,
                   const QPixmap &bodySmaAll,
                   const QPixmap &bodySmaAllBroken,
                   const QPixmap &bodyPart,
                   const QPixmap &bodyPartBroken,
                   const QPixmap &tip,
                   const QPixmap &tipBroken,
                   const QPixmap &supply,
                   const QPixmap &supplyBroken,
                   const QPixmap &text);
    void setKanvalue(
            int durAbility,
            int firePower,
            int armor,
            int torpedo,
            int avoid,
            int airPower,
            int plateAfford,
            int divAnti,
            KanEnum::Speed speed,
            int explore,
            KanEnum::Gunshot gunshot,
            int luck,
            int Hp,
            int level,
            int exp,
            int loveValue);

    void loadKanpic(const QString &kanNameFolder);
    void loadKanvalue();
    void show_hide(bool isShow,PicSelect pic);

    PicGraphic  *picCardNorm;
    PicGraphic  *picCardBroken;
    PicGraphic  *picBodyHalf;
    PicGraphic  *picBodyHalfBroken;
    PicGraphic  *picBodyBigAll;
    PicGraphic  *picBodyBigAllBroken;
    PicGraphic  *picBodySmaAll;
    PicGraphic  *picBodySmaAllBroken;
    PicGraphic  *picBodyPart;
    PicGraphic  *picBodyPartBroken;
    PicGraphic  *picTip;
    PicGraphic  *picTipBroken;
    PicGraphic  *picSupply;
    PicGraphic  *picSupplyBroken;
    PicGraphic  *picText;

    KanProperty  kanpro;
    int          Hp;
    int          level;
    int          exp;
    int          loveValue;
    KanEnum::BrokenLevel brokenlevel;

    MusicPlayer *voiceplayer;


private:
    void loadVoice(const QString &kanVoiceFolder);


signals:

public slots:
    void onClickedVoice();

};

#endif // KANMUSUME_H
