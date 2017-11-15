#-------------------------------------------------
#
# Project created by QtCreator 2016-10-09T08:11:24
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KanCollection
TEMPLATE = app


SOURCES += main.cpp\
        scene/startmenu.cpp \
    gamewindows.cpp \
    myComponents/imagebutton.cpp \
    myComponents/piclabel.cpp \
    musicUtils/musicplayer.cpp \
    animeEffect/animation.cpp \
    commonUtils/shuoggfunction.cpp \
    scene/blackground.cpp \
    animeEffect/loopanime.cpp \
    myComponents/picgraphic.cpp \
    scene/mainsceneview.cpp \
    animeEffect/animationgraphic.cpp \
    myComponents/imagebuttongraphics.cpp \
    animeEffect/animationitem.cpp \
    scene/blackgroundview.cpp \
    myComponents/textitem.cpp \
    model/kanmusume.cpp \
    myComponents/clock.cpp \
    scene/mainscene.cpp

HEADERS  += scene/startmenu.h \
    gamewindows.h \
    publicConstData.h \
    myComponents/imagebutton.h \
    myComponents/piclabel.h \
    musicUtils/musicplayer.h \
    animeEffect/animation.h \
    commonUtils/shuoggfunction.h \
    scene/blackground.h \
    animeEffect/loopanime.h \
    myComponents/picgraphic.h \
    scene/mainsceneview.h \
    animeEffect/animationgraphic.h \
    myComponents/imagebuttongraphics.h \
    animeEffect/animationitem.h \
    scene/blackgroundview.h \
    myComponents/textitem.h \
    model/kanmusume.h \
    myComponents/clock.h \
    scene/mainscene.h

FORMS    +=

OTHER_FILES += \
    ico_set.rc

RC_FILE = ico_set.rc
