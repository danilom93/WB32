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

INCLUDEPATH += ..\..\mplabx\include

SOURCES += main.cpp\
        MTempClient.cpp \
    MTempCommons.cpp \
    NetworkConfig.cpp \
    MClient.cpp \
    Loader.cpp

HEADERS  += MTempClient.h \
    MTempDefs.h \
    MTempCommons.h \
    NetworkConfig.h \
    MClient.h \
    Loader.h

FORMS    += MTempClient.ui \
    NetworkConfig.ui \
    Loader.ui

RESOURCES += \
    resource.qrc
