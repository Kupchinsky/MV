#-------------------------------------------------
#
# Project created by QtCreator 2015-10-01T18:35:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = gauss
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    qcustomplot.cpp

HEADERS  += widget.h \
    qcustomplot.h

FORMS    += widget.ui
