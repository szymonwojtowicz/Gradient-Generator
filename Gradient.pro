#-------------------------------------------------
#
# Project created by QtCreator 2013-11-09T15:42:54
#
#-------------------------------------------------

QT       += core gui
CONFIG += static
CONFIG+=release
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Gradient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    generator.cpp \
    author.cpp

HEADERS  += mainwindow.h \
    generator.h \
    author.h

FORMS    += mainwindow.ui \
    author.ui

RESOURCES += \
    AuthorPhoto.qrc
