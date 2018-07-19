import random
from PyQt5.QtCore import QTime, QCoreApplication, QEventLoop


def getRandomNum(min, max):
    return random.randint(min, max)


def sleepShuoGG(msec):
    reachTime = QTime.currentTime().addMSecs(msec)
    while QTime.currentTime() < reachTime:
        QCoreApplication.processEvents(QEventLoop.AllEvents, 100)
