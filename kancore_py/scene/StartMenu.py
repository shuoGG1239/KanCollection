from PyQt5.QtCore import QObject, QSize, Qt, pyqtSignal, pyqtSlot
from PyQt5.QtWidgets import QGraphicsPixmapItem, QFrame
from PyQt5.Qt import QEasingCurve, QRect
from animeEffect.AnimationGraphic import AnimationGraphic
from PyQt5.QtGui import QPixmap
from global_const import *
from musicUtils.MusicPlayer import MusicPlayer
from myComponents.ImageButtonGraphics import ImageButtonGraphics, ButtStyle
from myComponents.PicGraphic import PicGraphic

VOICE_VOLUME = 60
STAR_TIME_MIN = 500
STAR_TIME_MAX = 1500
ANIME_HANDLER_GAMEBUTT_GEOM = 0
ANIME_HANDLER_LOGO_OPAC = 0
ANIME_HANDLER_GAMEBUTT_DISPLAY = 1
ANIME_HANDLER_BLACK_SHOW = 2


class StartMenu(QFrame):
    musicAllOver = pyqtSignal()
    gameStartButtClicked = pyqtSignal()
    musicplayTitle = None
    gameStartButt = None
    imageLogo = None

    def __init__(self):
        super(StartMenu, self).__init__()
        self.setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT)
        self.voiceInit(VOICE_VOLUME)
        self.setStyleSheet("StartMenu{background-image:url(./GameData/UI1/TitleMain/image 1.jpg)}")
        mainPicUrl = RESOURCE_PATH + "/GameData/UI1/TitleMain/"
        self.gameStartButt = ImageButtonGraphics(self, QPixmap(mainPicUrl + "image 23.png"),
                                                 QPixmap(mainPicUrl + "image 24.png"),
                                                 QPixmap(mainPicUrl + "image 25.png"),
                                                 420, 360)
        self.gameStartButt.leftclick.connect(self.on_buttonGameStart_clicked)
        logoImage = QPixmap(URL_UI1 + "logo.png")
        self.imageLogo = PicGraphic(self, logoImage, 500, 50)
        self.imageLogo.animeEffect.gradualShowHide_Opac(True, 2500,
                                                        QEasingCurve.InOutCubic, ANIME_HANDLER_LOGO_OPAC)  # logo淡入
        self.imageLogo.animeEffect.signAnimeFinishOpac.connnect(self.animeOpacEnd)

        self.gameStartButt.setAnimationEable(True)
        self.gameStartButt.setEnabled(False)
        self.gameStartButt.currentButtStyle = ButtStyle.ButtPress  # 一开始按钮暗的(遵照原作)
        self.gameStartButt.animeEffect.gradualShowHide_Opac(True, 3500, QEasingCurve.InCirc)
        self.gameStartButt.animeEffect.gradualGeometry(QRect(self.gameStartButt.x(), self.gameStartButt.y() + 200,
                                                             self.gameStartButt.width(), self.gameStartButt.height()),
                                                       self.gameStartButt.geometry(), 3500,
                                                       QEasingCurve.Linear, ANIME_HANDLER_GAMEBUTT_GEOM)
        # 几何动画的信号与槽的连接
        self.gameStartButt.animeEffect.signAnimeFinishGeom.connect(self.buttAnimeGeomEnd)

    def voiceInit(self, volume):
        musicplayTitle = MusicPlayer(self)
        voiceUrl = URL_TITILE_SE
        numStr = musicplayTitle.getRandomNumStr(1, 20, 2)
        musicplayTitle.addMusic(voiceUrl + "a/" + numStr + FORM_MP3)
        numStr = musicplayTitle.getRandomNumStr(1, 12, 2)
        musicplayTitle.addMusic(voiceUrl + "b/" + numStr + FORM_MP3)
        numStr = musicplayTitle.getRandomNumStr(1, 10, 2)
        musicplayTitle.addMusic(voiceUrl + "c/" + numStr + FORM_MP3)
        musicplayTitle.setVolume(volume)
        musicplayTitle.playOneMusic(0, False)

    def keyPressEvent(self, e):
        if self.gameStartButt.isEnabled():
            if e.key() == Qt.Key_Space:
                self.on_buttonGameStart_clicked()
