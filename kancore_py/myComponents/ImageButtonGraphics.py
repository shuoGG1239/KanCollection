from enum import Enum
from PyQt5.QtCore import Qt, pyqtSignal
from PyQt5.QtGui import QPixmap
from PyQt5.QtWidgets import QGraphicsPixmapItem
from myComponents.PicGraphic import PicGraphic


class ButtStyle(Enum):
    ButtNorm = 0,
    ButtPress = 1,
    ButtRelease = 2,
    ButtEnter = 3,
    ButtLeave = 4,


class ImageButtonGraphics(PicGraphic):
    leftclick = pyqtSignal()
    rightclick = pyqtSignal()
    buttonPicture = None
    pressPicture = None
    releasePicture = None
    enterPicture = None
    leavePicture = None
    buttonPictureOrigin = None
    pressPictureOrigin = None
    releasePictureOrigin = None
    enterPictureOrigin = None
    leavePictureOrigin = None
    isAnimateEnable = False
    currentButtStyle = None

    def __init__(self, buttNormPic, x, y, animeGeomOn, animeOpacOn, parent):
        super(ImageButtonGraphics, self).__init__(buttNormPic, x, y, animeGeomOn, animeOpacOn, parent)
        self.setAcceptHoverEvents(True)
        self.setAcceptDrops(True)
        self.buttonPicture = QPixmap(buttNormPic)
        self.pressPicture = QPixmap(buttNormPic)
        self.releasePicture = QPixmap(buttNormPic)
        self.enterPicture = QPixmap(buttNormPic)
        self.leavePicture = QPixmap(buttNormPic)
        self.currentButtStyle = ButtStyle.ButtNorm

    def setAllButtImage(self, buttNorm, buttEnter, buttPress):
        self.setButtonPicture(buttNorm)
        self.setEnterPicture(buttEnter)
        self.setLeavePicture(buttNorm)
        self.setPressPicture(buttPress)
        self.setReleasePicture(buttEnter)

    def setButtonPicture(self, pic):
        self.buttonPicture = pic

    def setEnterPicture(self, pic):
        self.enterPicture = pic

    def setLeavePicture(self, pic):
        self.leavePicture = pic

    def setPressPicture(self, pic):
        self.pressPicture = pic

    def setReleasePicture(self, pic):
        self.releasePicture = pic

    def mousePressEvent(self, event):
        if event.button() == Qt.LeftButton:
            self.setPixmap(self.pressPicture)
            self.currentButtStyle = ButtStyle.ButtPress

    def mouseReleaseEvent(self, event):
        if (event.button() & Qt.LeftButton) == 1:
            self.leftclick.emit()
            self.setPixmap(self.enterPicture)
            self.currentButtStyle = ButtStyle.ButtRelease
        elif (event.button() & Qt.RightButton) == 1:
            self.rightclick.emit()

    def hoverEnterEvent(self, event):
        QGraphicsPixmapItem.hoverEnterEvent(event)
        self.setPixmap(self.enterPicture)
        self.currentButtStyle = ButtStyle.ButtEnter

    def hoverLeaveEvent(self, event):
        QGraphicsPixmapItem.hoverLeaveEvent(event)
        self.setPixmap(self.leavePicture)
        self.currentButtStyle = ButtStyle.ButtLeave
