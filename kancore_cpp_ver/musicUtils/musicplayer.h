#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTime>
#include <qglobal.h>
#include "publicConstData.h"

#define VOLUME_INIT  50

/**
 * @brief 音乐播放器
 * 使用方法1:
 *       new -- addMusic -- setMusicMode -- play
 * 使用方法2:
 *       new -- addMusic -- playOneMusic
 *
 * 音量设置为 setVolume
 */
class MusicPlayer : public QMediaPlayer
{
    Q_OBJECT
public:
    explicit MusicPlayer(QObject *parent = 0);
    QString getRandomNumStr(int min,int max,int strlen);

    void addMusic(QString url);
    void setMusicMode(QMediaPlaylist::PlaybackMode playMode,int startNum);
    void playOneMusic(int num,bool isLoop=false);
    void playOneRandomMusic(int min,int max);
    void clearMusicList();
    void setCurrentMusic(int num);
    int  getMusicCount();

    QMediaPlaylist *curPlayList;

private:
    int getRandomNum(int min,int max);
signals:
    void oneSoundOverSignal(int numOfmusic);

private slots:
    void music_status_change(QMediaPlayer::MediaStatus status);

};

#endif // MUSICPLAYER_H
