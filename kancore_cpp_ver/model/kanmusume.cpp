#include "kanmusume.h"

KanMusume::KanMusume(const QString &kanNameFolder,const QString &voiceFolder,QObject *parent) :
    QObject(parent)
{
    picCardNorm         =new PicGraphic();
    picCardBroken       =new PicGraphic();
    picBodyHalf         =new PicGraphic();
    picBodyHalfBroken   =new PicGraphic();
    picBodyBigAll       =new PicGraphic();
    picBodyBigAllBroken =new PicGraphic();
    picBodySmaAll       =new PicGraphic();
    picBodySmaAllBroken =new PicGraphic();
    picBodyPart         =new PicGraphic();
    picBodyPartBroken   =new PicGraphic();
    picTip              =new PicGraphic();
    picTipBroken        =new PicGraphic();
    picSupply           =new PicGraphic();
    picSupplyBroken     =new PicGraphic();
    picText             =new PicGraphic();
    picCardNorm->hide();
    picCardBroken->hide();
    picBodyHalf->hide();
    picBodyHalfBroken->hide();
    picBodyBigAll->hide();
    picBodyBigAllBroken->hide();
    picBodySmaAll->hide();
    picBodySmaAllBroken->hide();
    picBodyPart->hide();
    picBodyPartBroken->hide();
    picTip->hide();
    picTipBroken->hide();
    picSupply->hide();
    picSupplyBroken->hide();
    picText->hide();

    this->loadKanpic(kanNameFolder);
    this->loadVoice(voiceFolder);
    this->loadKanvalue();

    connect(picBodyHalf,SIGNAL(leftclick()),this,SLOT(onClickedVoice()));

}

KanMusume::~KanMusume()
{
    delete  picCardNorm;
    delete  picCardBroken;
    delete  picBodyHalf;
    delete  picBodyHalfBroken;
    delete  picBodyBigAll;
    delete  picBodyBigAllBroken;
    delete  picBodySmaAll;
    delete  picBodySmaAllBroken;
    delete  picBodyPart;
    delete  picBodyPartBroken;
    delete  picTip;
    delete  picTipBroken;
    delete  picSupply;
    delete  picSupplyBroken;
    delete  picText;
}


void KanMusume::setKanvalue(int durAbility,
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
                            int loveValue)
{
    this->kanpro.durAbility=durAbility;
    this->kanpro.firePower=firePower;
    this->kanpro.armor=armor;
    this->kanpro.torpedo=torpedo;
    this->kanpro.avoid=avoid;
    this->kanpro.airPower=airPower;
    this->kanpro.plateAfford=plateAfford;
    this->kanpro.divAnti=divAnti;
    this->kanpro.speed=speed;
    this->kanpro.explore=explore;
    this->kanpro.gunshot=gunshot;
    this->kanpro.luck=luck;
    this->Hp=Hp;
    this->level=level;
    this->exp=exp;
    this->loveValue=loveValue;
}



/**
 * @brief 设置舰娘的所有picGraphics
 *
 * @param cardNorm
 * @param cardBroken
 * @param bodyHalf
 * @param bodyHalfBroken
 * @param bodyBigAll
 * @param bodyBigAllBroken
 * @param bodySmaAll
 * @param bodySmaAllBroken
 * @param bodyPart
 * @param bodyPartBroken
 * @param tip
 * @param tipBroken
 * @param supply
 * @param supplyBroken
 * @param text
 */
void KanMusume::setKanpic(const QPixmap &cardNorm,
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
                          const QPixmap &text)
{
    picCardNorm->setPixmap(cardNorm);
    picCardBroken->setPixmap(cardBroken);
    picBodyHalf->setPixmap(bodyHalf);
    picBodyHalfBroken->setPixmap(bodyHalfBroken);
    picBodyBigAll->setPixmap(bodyBigAll);
    picBodyBigAllBroken->setPixmap(bodyBigAllBroken);
    picBodySmaAll->setPixmap(bodySmaAll);
    picBodySmaAllBroken->setPixmap(bodySmaAllBroken);
    picBodyPart->setPixmap(bodyPart);
    picBodyPartBroken->setPixmap(bodyPartBroken);
    picTip->setPixmap(tip);
    picTipBroken->setPixmap(tipBroken);
    picSupply->setPixmap(supply);
    picSupplyBroken->setPixmap(supplyBroken);
    picText->setPixmap(text);
}




void KanMusume::loadKanvalue()
{
    setKanvalue(30,12,11,34,50,99,12,12,KanEnum::fastSp,93,KanEnum::longShot,9,50,1,60,0);
}



/**
 * @brief 输入一个舰娘的文件夹名即可初始化所有的picGraphics
 *
 * @param kanNameFolder 舰娘的文件夹名字
 */
void KanMusume::loadKanpic(const QString &kanNameFolder)
{
    QPixmap tempPic1;
    QPixmap tempPic2;
    QPixmap tempPic3;
    QPixmap tempPic4;
    QPixmap tempPic5;
    QPixmap tempPic6;
    QPixmap tempPic7;
    QPixmap tempPic8;
    QPixmap tempPic9;
    QPixmap tempPic10;
    QPixmap tempPic11;
    QPixmap tempPic12;
    QPixmap tempPic13;
    QPixmap tempPic14;
    QPixmap tempPic15;
    if(!(tempPic1.load(QString(URL_KANPIC)+kanNameFolder+QString("/")+QString(KAN_PIC1)+FORM_PNG)))
        tempPic1.load(QString(URL_KANPIC)+kanNameFolder+QString("/")+QString(KAN_PIC1)+FORM_JPG);
    if(!(tempPic2.load(QString(URL_KANPIC)+kanNameFolder+QString("/")+QString(KAN_PIC2)+FORM_PNG)))
        tempPic2.load(QString(URL_KANPIC)+kanNameFolder+QString("/")+QString(KAN_PIC2)+FORM_JPG);
    if(!(tempPic3.load(QString(URL_KANPIC)+kanNameFolder+QString("/")+QString(KAN_PIC3)+FORM_PNG)))
        tempPic3.load(QString(URL_KANPIC)+kanNameFolder+QString("/")+QString(KAN_PIC3)+FORM_JPG);
    if(!(tempPic4.load(QString(URL_KANPIC)+kanNameFolder+QString("/")+QString(KAN_PIC4)+FORM_PNG)))
        tempPic5.load(QString(URL_KANPIC)+kanNameFolder+QString("/")+QString(KAN_PIC4)+FORM_JPG);
    if(!(tempPic5.load(QString(URL_KANPIC)+kanNameFolder+QString("/")+QString(KAN_PIC5)+FORM_PNG)))
        tempPic5.load(QString(URL_KANPIC)+kanNameFolder+QString("/")+QString(KAN_PIC5)+FORM_JPG);
    if(!(tempPic6.load(QString(URL_KANPIC)+kanNameFolder+QString("/")+QString(KAN_PIC6)+FORM_PNG)))
        tempPic6.load(QString(URL_KANPIC)+kanNameFolder+QString("/")+QString(KAN_PIC6)+FORM_JPG);
    if(!(tempPic7.load(QString(URL_KANPIC)+kanNameFolder+QString("/")+QString(KAN_PIC7)+FORM_PNG)))
        tempPic7.load(QString(URL_KANPIC)+kanNameFolder+QString("/")+QString(KAN_PIC7)+FORM_JPG);
    if(!(tempPic8.load(QString(URL_KANPIC)+kanNameFolder+QString("/")+QString(KAN_PIC8)+FORM_PNG)))
        tempPic8.load(QString(URL_KANPIC)+kanNameFolder+QString("/")+QString(KAN_PIC8)+FORM_JPG);
    if(!(tempPic9.load(QString(URL_KANPIC)+kanNameFolder+QString("/")+QString(KAN_PIC9)+FORM_PNG)))
        tempPic9.load(QString(URL_KANPIC)+kanNameFolder+QString("/")+QString(KAN_PIC9)+FORM_JPG);
    if(!(tempPic10.load(QString(URL_KANPIC)+kanNameFolder+QString("/")+QString(KAN_PIC10)+FORM_PNG)))
        tempPic10.load(QString(URL_KANPIC)+kanNameFolder+QString("/")+QString(KAN_PIC10)+FORM_JPG);
    if(!(tempPic11.load(QString(URL_KANPIC)+kanNameFolder+QString("/")+QString(KAN_PIC11)+FORM_PNG)))
        tempPic11.load(QString(URL_KANPIC)+kanNameFolder+QString("/")+QString(KAN_PIC11)+FORM_JPG);
    if(!(tempPic12.load(QString(URL_KANPIC)+kanNameFolder+QString("/")+QString(KAN_PIC12)+FORM_PNG)))
        tempPic12.load(QString(URL_KANPIC)+kanNameFolder+QString("/")+QString(KAN_PIC12)+FORM_JPG);
    if(!(tempPic13.load(QString(URL_KANPIC)+kanNameFolder+QString("/")+QString(KAN_PIC13)+FORM_PNG)))
        tempPic13.load(QString(URL_KANPIC)+kanNameFolder+QString("/")+QString(KAN_PIC13)+FORM_JPG);
    if(!(tempPic14.load(QString(URL_KANPIC)+kanNameFolder+QString("/")+QString(KAN_PIC14)+FORM_PNG)))
        tempPic14.load(QString(URL_KANPIC)+kanNameFolder+QString("/")+QString(KAN_PIC14)+FORM_JPG);
    if(!(tempPic15.load(QString(URL_KANPIC)+kanNameFolder+QString("/")+QString(KAN_PIC15)+FORM_PNG)))
        tempPic15.load(QString(URL_KANPIC)+kanNameFolder+QString("/")+QString(KAN_PIC15)+FORM_JPG);

    this->setKanpic(tempPic1,
                    tempPic2,
                    tempPic3,
                    tempPic4,
                    tempPic5,
                    tempPic6,
                    tempPic7,
                    tempPic8,
                    tempPic9,
                    tempPic10,
                    tempPic11,
                    tempPic12,
                    tempPic13,
                    tempPic14,
                    tempPic15);

}


/**
 * @brief show或者hide某张
 *
 * @param isShow true:show  false:hide
 * @param pic    枚举值
 */
void KanMusume::show_hide(bool isShow, PicSelect pic)
{
    if(isShow)
    {
        switch (pic) {
        case Pic_cardNorm:
            picCardNorm->show();break;
        case Pic_cardBroken:
            picCardBroken->show();break;
        case Pic_bodyHalf:
            picBodyHalf->show();break;
        case Pic_bodyHalfBroken:
            picBodyHalfBroken->show();break;
        case Pic_bodyBigAll:
            picBodyBigAll->show();break;
        case Pic_bodyBigAllBroken:
            picBodyBigAllBroken->show();break;
        case Pic_bodySmaAll:
            picBodySmaAll->show();break;
        case Pic_bodySmaAllBroken:
            picBodySmaAllBroken->show();break;
        case Pic_bodyPart:
            picBodyPart->show();break;
        case Pic_bodyPartBroken:
            picBodyPartBroken->show();break;
        case Pic_tip:
            picTip->show();break;
        case Pic_tipBroken:
            picTipBroken->show();break;
        case Pic_supply:
            picSupply->show();break;
        case Pic_supplyBroken:
            picSupply->show();break;
        case Pic_text:
            picText->show();break;
        default:
            break;
        }
    }
    else
    {
        switch (pic) {
        case Pic_cardNorm:
            picCardNorm->hide();break;
        case Pic_cardBroken:
            picCardBroken->hide();break;
        case Pic_bodyHalf:
            picBodyHalf->hide();break;
        case Pic_bodyHalfBroken:
            picBodyHalfBroken->hide();break;
        case Pic_bodyBigAll:
            picBodyBigAll->hide();break;
        case Pic_bodyBigAllBroken:
            picBodyBigAllBroken->hide();break;
        case Pic_bodySmaAll:
            picBodySmaAll->hide();break;
        case Pic_bodySmaAllBroken:
            picBodySmaAllBroken->hide();break;
        case Pic_bodyPart:
            picBodyPart->hide();break;
        case Pic_bodyPartBroken:
            picBodyPartBroken->hide();break;
        case Pic_tip:
            picTip->hide();break;
        case Pic_tipBroken:
            picTipBroken->hide();break;
        case Pic_supply:
            picSupply->hide();break;
        case Pic_supplyBroken:
            picSupply->hide();break;
        case Pic_text:
            picText->hide();break;
        default:
            break;
        }
    }
}


/**
 * @brief 加载某个舰娘所有语音
 *
 * @param kanNameFolder 语音文件夹
 */
void KanMusume::loadVoice(const QString &kanVoiceFolder)
{
    QString urlbase(URL_VOICE);
    voiceplayer=new MusicPlayer(this);
    for(quint8 i=1;i<=27;i++)
    {
        if(i != 24) //24为空曲
        {
            voiceplayer->addMusic(urlbase+kanVoiceFolder+"/"+QString::number(i)+FORM_MP3);
        }
    }

}

/******************************************private slots*******************************************************/

/**
 * @brief 点击人物随机发出呻吟
 *
 */
void KanMusume::onClickedVoice()
{
    //一共26首 0~25里面随便挑一首放
    this->voiceplayer->playOneRandomMusic(0,25);
}
