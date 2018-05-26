#-------------------------------------------------
#
# Project created by QtCreator 2018-05-17T18:44:07
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Telemetrie_0_1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += qwt

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    plot.cpp \
    mainwindow.cpp \
    curvedata.cpp \
    signaldata.cpp \
    Datenaufbereitung.cpp \
    datenlogger.cpp \
    Datensatz.cpp \
    Datenverarbeitung.cpp

HEADERS += \
    plot.h \
    mainwindow.h \
    curvedata.h \
    signaldata.h \
    Datenaufbereitung.h \
    datenlogger.h \
    Datensatz.h \
    Datenverarbeitung.h

FORMS += \
        mainwindow.ui \
    mainwindow.ui

RESOURCES += \
    ressourcenbilder.qrc
