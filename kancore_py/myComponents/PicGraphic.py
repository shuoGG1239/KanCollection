from PyQt5.QtCore import QObject, QSize, Qt, pyqtSignal
from PyQt5.QtWidgets import QGraphicsPixmapItem
from animeEffect.AnimationGraphic import AnimationGraphic
from PyQt5.QtGui import QPixmap


class PicGraphic(QObject, QGraphicsPixmapItem):
    sizePixmapOrig = QSize()
    leftclick = pyqtSignal()
    rightclick = pyqtSignal()
    def __init__(self, pic, x, y, animeGeomOn, animeOpacOn, parent):
        QGraphicsPixmapItem.__init__(pic, parent)
        # 改变几何中心, 默认在重心
        self.sizePixmapOrig.setWidth(pic.width())
        self.sizePixmapOrig.setHeight(pic.height())
        self.setTransformOriginPoint(pic.width() * 0.5, pic.height() * 0.5)
        self.setPos(x, y)
        self.setOpacity(1)
        self.setScale(1)
        self.show()
        self.setAnimeAll_OnOff(animeGeomOn, animeOpacOn)

    def setAnimeAll_OnOff(self, animeGeomOn, animeOpacOn):
        if animeGeomOn and animeOpacOn:
            animeEffect = AnimationGraphic(self, self, True, True, True, True)
        elif animeGeomOn and not animeOpacOn:
            animeEffect = AnimationGraphic(self, self, True, True, True, False)
        elif not animeGeomOn and animeOpacOn:
            animeEffect = AnimationGraphic(self, self, False, False, False, True)

    def setGeomCenter(self, x_percent, y_percent):
        """
        设置几何中心
        :param x_percent:
        :param y_percent:
        :return:
        """
        self.setTransformOriginPoint(self.scale() * (self.sizePixmapOrig.width()) * x_percent,
                                     self.scale() * (self.sizePixmapOrig.height()) * y_percent)

    def getScaledPixmap(self, inputPic, scale):
        """
        缩放
        :param inputPic:
        :param scale:
        :return:
        """
        rePic = inputPic.scaled(inputPic.width() * scale, inputPic.height() * scale)
        return rePic

    def mouseReleaseEvent(self, e):
        # 响应左击事件
        if (e.button() & Qt.LeftButton) == 1:
            self.leftclick.emit()
        # 响应右击事件
        elif (e.button() & Qt.RightButton) == 1:
            self.rightclick.emit()
