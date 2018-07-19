from PyQt5.QtWidgets import QFrame

from global_const import *
from scene.StartMenu import StartMenu


class GameWindow(QFrame):
    mystartMenu = None
    def __init__(self):
        self.setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT)
        self.mystartMenu = StartMenu(self)
        self.mystartMenu.setFocus()
        self.mystartMenu.show()

