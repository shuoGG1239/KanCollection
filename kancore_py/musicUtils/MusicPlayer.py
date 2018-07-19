from PyQt5.QtMultimedia import QMediaPlayer, QMediaPlaylist
from PyQt5.QtCore import QObject, QUrl, pyqtSignal, pyqtSlot
import random

VOLUME_INIT = 50


class MusicPlayer(QMediaPlayer):
    curPlayList = QMediaPlaylist()
    oneSoundOverSignal = pyqtSignal(int)

    def __init__(self, parent):
        super(MusicPlayer, self).__init__(parent)
        self.setPlaylist(self.curPlayList)
        self.setVolume(VOLUME_INIT)
        self.mediaStatusChanged.connect(self.music_status_change)

    def addMusic(self, url):
        self.curPlayList.addMedia(QUrl(url))

    def setMusicMode(self, playMode, startNum):
        self.curPlayList.setPlaybackMode(playMode)
        self.curPlayList.setCurrentIndex(startNum)

    def clearMusicList(self):
        self.curPlayList.clear()

    def setCurrentMusic(self, num):
        self.curPlayList.setCurrentIndex(num)

    def getMusicCount(self):
        return self.curPlayList.mediaCount()

    def playOneMusic(self, num, isLoop):
        if True == isLoop:
            self.curPlayList.setPlaybackMode(QMediaPlaylist.CurrentItemInLoop)
        else:
            self.curPlayList.setPlaybackMode(QMediaPlaylist.CurrentItemOnce)
        self.curPlayList.setCurrentIndex(num)
        self.play()

    def playOneRandomMusic(self, min, max):
        self.playOneMusic(random.randint(min, max), False)

    def getRandomNumStr(self, min, max, strlen):
        return str(random.randint(min, max)).zfill(strlen)

    @pyqtSlot(int)
    def music_status_change(self, status):
        if status == QMediaPlayer.EndOfMedia:
            self.oneSoundOverSignal.emit(self.curPlayList.currentIndex())
