#-------------------------------------------------
#
# Project created by QtCreator 2016-06-21T10:31:53
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MTempClient
TEMPLATE = app


SOURCES += main.cpp\
        MTempClient.cpp \
    MT_Client.cpp \
    MTempCommons.cpp

HEADERS  += MTempClient.h \
    MT_Client.h \
    MTempDefs.h \
    MTempCommons.h

FORMS    += MTempClient.ui
