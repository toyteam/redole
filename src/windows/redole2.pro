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
    pdfpage.cpp \
    configreader.cpp \
    bookmarkreader.cpp \
    bookinfo.cpp \
    logindialog.cpp

HEADERS  += mainwindow.h \
    pdffile.h \
    pdfview.h \
    pdfpage.h \
    configreader.h \
    bookmarkreader.h \
    bookinfo.h \
    logindialog.h

FORMS    += mainwindow.ui \
    logindialog.ui

QT += printsupport

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/poppler/ -llibpoppler.dll
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/poppler/ -llibpoppler.dll
else:unix: LIBS += -L$$PWD/poppler/ -llibpoppler.dll

INCLUDEPATH += $$PWD/poppler
DEPENDPATH += $$PWD/poppler

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/poppler/ -llibpoppler-qt5.dll
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/poppler/ -llibpoppler-qt5.dll
else:unix: LIBS += -L$$PWD/poppler/ -llibpoppler-qt5.dll

INCLUDEPATH += $$PWD/poppler
DEPENDPATH += $$PWD/poppler
