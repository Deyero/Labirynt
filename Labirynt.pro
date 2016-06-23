#-------------------------------------------------
#
# Project created by QtCreator 2015-11-02T21:50:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Labirynt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    maze.cpp \
    labirynth.cpp \
    solver.cpp \
    generator.cpp \
    randommapdialog.cpp

HEADERS  += mainwindow.h \
    maze.h \
    labirynth.h \
    solver.h \
    map2d.h \
    generator.h \
    randommapdialog.h

FORMS    += mainwindow.ui \
    randommapdialog.ui

CONFIG += c++11
