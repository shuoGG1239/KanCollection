#include "musicplayer.h"

MusicPlayer::MusicPlayer(QObject *parent) :
    QMediaPlayer(parent)
{
    curPlayList=new QMediaPlaylist(this);
    this->setPlaylist(curPlayList);
    //初始化音量
    this->setVolume(VOLUME_INIT);
    connect(this,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),
            this,SLOT(music_status_change(QMediaPlayer::MediaStatus)));
}


/**
 * @brief 歌单中加入音乐
 *
 * @param url 路径
 */
void MusicPlayer::addMusic(QString url)
{
    curPlayList->addMedia(QUrl(url));
}
/**
 * @brief 音乐模式和播放第几首,设置完后this->play()即可播
 *
 * @param playMode 播放模式
 * @param startNum 设置播放第几首
 */
void MusicPlayer::setMusicMode(QMediaPlaylist::PlaybackMode playMode,int startNum)
{
    curPlayList->setPlaybackMode(playMode);
    curPlayList->setCurrentIndex(startNum);

}
/**
 * @brief 清歌单
 *
 */
void MusicPlayer::clearMusicList()
{
    curPlayList->clear();
}
void MusicPlayer::setCurrentMusic(int num)
{
    curPlayList->setCurrentIndex(num);
}
int  MusicPlayer::getMusicCount()
{
    return curPlayList->mediaCount();
}
/**
 * @brief 播放一首曲子,可选择播放一次或循环播放
 *
 * @param num    曲子的序号
 * @param isLoop 是否循环
 */
void MusicPlayer::playOneMusic(int num,bool isLoop)
{
    if(true==isLoop)
        curPlayList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    else
        curPlayList->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    curPlayList->setCurrentIndex(num);
    this->play();
}

/**
 * @brief 随机播放一首
 *
 * @param min 最小list序号
 * @param max 最大list序号
 */
void MusicPlayer::playOneRandomMusic(int min,int max)
{
    this->playOneMusic(getRandomNum(min,max),false);
}

/**
 * @brief 在某个区间内获得一个随机数(字符串)
 *
 * @param min 最小小
 * @param max 最大数
 * @param strlen 几位数: 个位数为1,十位数为2,百位数为3,不够则自动补零
 * @return QString
 */
QString MusicPlayer::getRandomNumStr(int min,int max,int strlen)
{
    if(max <= min && strlen<=0)
        return QString("");
    QString numStr;
    QTime   time1=QTime::currentTime();
    qsrand(time1.msec()+time1.second()*1000);
    int num=(qrand()%max)+min;
    numStr=QString("%1").arg(num,strlen,10,QLatin1Char('0'));
    return numStr;
}

/**
 * @brief 在某个区间内获得一个随机数
 *
 * @param min 最小小
 * @param max 最大数
 * @return int
 */
int MusicPlayer::getRandomNum(int min,int max)
{
    if(max <= min)
        return 0;
    QTime   time1=QTime::currentTime();
    qsrand(time1.msec()+time1.second()*1000);
    int num=(qrand()%max)+min;
    return num;
}


/**
 * @brief 音乐播放状态改变slot
 *
 * @param status
 */
void MusicPlayer::music_status_change(QMediaPlayer::MediaStatus status)
{
    if(status==QMediaPlayer::EndOfMedia)
        emit oneSoundOverSignal(curPlayList->currentIndex());
}
