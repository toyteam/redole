#-------------------------------------------------
#
# Project created by QtCreator 2016-09-08T09:10:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = redole2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    pdffile.cpp \
    pdfview.cpp \
    pdfpage.cpp

HEADERS  += mainwindow.h \
    pdffile.h \
    pdfview.h \
    pdfpage.h

FORMS    += mainwindow.ui

INCLUDEPATH += $$PWD/poppler
win32: LIBS += -L$$PWD/poppler -llibpoppler
win32: LIBS += -L$$PWD/poppler -llibpoppler-qt5
