from enum import Enum
from PyQt5.QtCore import QObject, pyqtSignal, pyqtSlot
from PyQt5.QtCore import QPropertyAnimation


class animeType(Enum):
    TypePos = 0
    TypeScale = 1
    TypeRotate = 2
    TypeOpacity = 3


class AnimationGraphic(QObject):
    signAnimeStartPos = pyqtSignal(int)
    signAnimeStartScale = pyqtSignal(int)
    signAnimeStartRotate = pyqtSignal(int)
    signAnimeStartOpac = pyqtSignal(int)
    signAnimeFinishPos = pyqtSignal(int)
    signAnimeFinishScale = pyqtSignal(int)
    signAnimeFinishRotate = pyqtSignal(int)
    signAnimeFinishOpac = pyqtSignal(int)
    animePosIsOn = True
    animeScaleIsOn = True
    animeRotateIsOn = True
    animeOpacIsOn = True
    handlerCurPos = 0
    handlerCurScale = 0
    handlerCurRotate = 0
    handlerCurOpac = 0
    animeOpacity = None
    animePos = None
    animeScale = None
    animeRotate = None
    item = None

    def __init__(self, parent, inputItem, animePosOn, animeScaleOn, animeRotateOn, animeOpacOn):
        super(AnimationGraphic, self).__init__(parent)
        self.item = inputItem
        self.animePosIsOn = False
        self.animeScaleIsOn = False
        self.animeRotateIsOn = False
        self.animeOpacIsOn = False
        self.setAnimation_OnOff(animePosOn, animeScaleOn, animeRotateOn, animeOpacOn)


def setAnimation_OnOff(self, animePosOn, animeScaleOn, animeRotateOn, animeOpacOn):
    if not self.self.animePosIsOn and animePosOn:
        self.animePos = QPropertyAnimation(self.item, "pos")
        self.animePos.finished.connect(self.animeFinishedPos)
        self.animePosIsOn = True
    elif self.animePosIsOn and not animePosOn:
        self.animePos.finished.disconnect(self.animeFinishedPos)
        self.animePosIsOn = False

    if not self.animeScaleIsOn and animeScaleOn:
        self.animeScale = QPropertyAnimation(self.item, "scale")
        self.animeScale.finished.connect(self.animeFinishedScale)
        self.animeScaleIsOn = True
    elif self.animeScaleIsOn and not animeScaleOn:
        self.animeScale.finished.disconnect(self.animeFinishedScale)
        self.animeScaleIsOn = False

    if not self.animeRotateIsOn and animeRotateOn:
        self.animeRotate = QPropertyAnimation(self.item, "rotation")
        self.animeRotate.finished.connect(self.animeFinishedRotate)
        self.animeRotateIsOn = True
    elif self.animeRotateIsOn and not animeRotateOn:
        self.animeRotate.finished.disconnect(self.animeFinishedRotate)
        self.animeRotateIsOn = False

    if not self.animeOpacIsOn and animeOpacOn:
        self.animeOpacity = QPropertyAnimation(self.item, "opacity")
        self.animeOpacity.finished.connect(self.animeFinishedOpac)
        self.animeOpacIsOn = True
    elif self.animeOpacIsOn and not animeOpacOn:
        self.animeOpacity.finished.disconnect(self.animeFinishedOpac)
        self.animeOpacIsOn = False

    def gradualPos(self, startPos, endPos, msec, aTyte, animeHandle, loopTime):
        self.handlerCurPos = animeHandle
        self.animePos.setEasingCurve(aTyte)
        self.animePos.setDuration(msec)
        self.animePos.setStartValue(startPos)
        self.animePos.setEndValue(endPos)
        self.animePos.setLoopCount(loopTime)
        self.animePos.start()
        self.signAnimeStartPos.emit(animeHandle)

    def gradualScale(self, startScale, endScale, msec, aTyte, animeHandle, loopTime):
        self.handlerCurScale = animeHandle
        self.animeScale.setEasingCurve(aTyte)
        self.animeScale.setDuration(msec)
        self.animeScale.setStartValue(startScale)
        self.animeScale.setEndValue(endScale)
        self.animeScale.setLoopCount(loopTime)
        self.animeScale.start()
        self.signAnimeStartScale.emit(animeHandle)

    def gradualRotate(self, startAngle, endAngle, msec, aTyte, animeHandle, loopTime):
        self.handlerCurRotate = animeHandle
        self.animeRotate.setEasingCurve(aTyte)
        self.animeRotate.setDuration(msec)
        self.animeRotate.setStartValue(startAngle)
        self.animeRotate.setEndValue(endAngle)
        self.animeRotate.setLoopCount(loopTime)
        self.animeRotate.start()
        self.signAnimeStartRotate.emit(animeHandle)

    def gradualOpac(self, startOpac, endOpac, msec, aTyte, animeHandle, loopTime):
        self.handlerCurOpac = animeHandle
        self.animeOpacity.setEasingCurve(aTyte)
        self.animeOpacity.setDuration(msec)
        self.animeOpacity.setStartValue(startOpac)
        self.animeOpacity.setEndValue(endOpac)
        self.animeOpacity.setLoopCount(loopTime)
        self.animeOpacity.start()
        self.signAnimeStartOpac.emit(animeHandle)

    @pyqtSlot()
    def animeFinishedPos(self):
        self.signAnimeFinishPos.emit(self.handlerCurPos)

    @pyqtSlot()
    def animeFinishedScale(self):
        self.signAnimeFinishScale.emit(self.handlerCurScale)

    @pyqtSlot()
    def animeFinishedRotate(self):
        self.signAnimeFinishRotate.emit(self.handlerCurRotate)

    @pyqtSlot()
    def animeFinishedOpac(self):
        self.signAnimeFinishOpac.emit(self.handlerCurOpac)
