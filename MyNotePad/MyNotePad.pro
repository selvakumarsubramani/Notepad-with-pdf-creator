#-------------------------------------------------
#
# Project created by QtCreator 2016-12-27T14:54:10
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyNotePad
TEMPLATE = app


SOURCES += main.cpp\
        mynotepad.cpp \
    mydialog.cpp

HEADERS  += mynotepad.h \
    mydialog.h

FORMS    += mynotepad.ui \
    mydialog.ui

RESOURCES += \
    resources.qrc
