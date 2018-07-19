import sys
from PyQt5.QtGui import QCursor, QPixmap
from PyQt5.QtWidgets import QApplication
import global_const
from GameWindow import GameWindow


def run_normal():
    app = QApplication(sys.argv)
    mygameWindow = GameWindow()
    mycursor = QCursor(QPixmap(global_const.CURSOR_PATH), 0, 0)
    mygameWindow.setCursor(mycursor)
    mygameWindow.show()
    sys.exit(app.exec_())

if __name__ == '__main__':
    run_normal()