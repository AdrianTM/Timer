QT += core gui widgets
CONFIG += c++11

TARGET        = timer

HEADERS       = \
    mainwindow.h \
    timer.h \
    settings.h \
    help.h
SOURCES       = \
    main.cpp \
    mainwindow.cpp \
    timer.cpp \
    settings.cpp \
    help.cpp

FORMS += \
    mainwindow.ui \
    settings.ui \
    help.ui

