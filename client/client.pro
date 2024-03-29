#-------------------------------------------------
#
# Project created by QtCreator 2019-06-18T23:55:38
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp \
    studenthome.cpp \
    register.cpp \
    modifypersonalinfo.cpp \
    teacherhome.cpp \
    modifypassword.cpp \
    modifyclassinfo.cpp \
    jsontools.cpp \
    deanhome.cpp \
    course.cpp \
    classdata.cpp
HEADERS += \
        widget.h \
    studenthome.h \
    register.h \
    customtabstyle.h \
    modifypersonalinfo.h \
    personalinfo.h \
    teacherhome.h \
    modifypassword.h \
    modifyclassinfo.h \
    jsontools.h \
    deanhome.h \
    course.h \
    classdata.h

FORMS += \
        widget.ui \
    studenthome.ui \
    register.ui \
    modifypersonalinfo.ui \
    teacherhome.ui \
    modifypassword.ui \
    modifyclassinfo.ui \
    deanhome.ui \
    course.ui \
    classdata.ui
