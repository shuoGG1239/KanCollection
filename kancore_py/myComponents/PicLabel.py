from PyQt5.QtCore import QObject, QSize, Qt, pyqtSignal
from PyQt5.QtWidgets import QGraphicsPixmapItem, QLabel, QWidget
from PyQt5.QtGui import QPixmap



class PicLabel(QLabel):
    leftclick = pyqtSignal()
    rightclick = pyqtSignal()
    animeEffect = None
    def __int__(self,parent,pic,x,y,animeOn=True):
        super(PicLabel, self).__int__(parent)
        self.setPixmap(pic)
        self.setScaledContents(True)
        self.setGeometry(x, y, pic.width(), pic.height())
        self.show()
        if animeOn:
            pass
            # self.animeEffect = Animation(self,self)
            
    def mouseReleaseEvent(self, e):
        if (e.button() & Qt.LeftButton)==1:
            self.leftclick.emit()
        elif (e.button()&Qt.RightButton)==1:
            self.rightclick.emit()