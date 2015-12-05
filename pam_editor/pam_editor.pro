#-------------------------------------------------
#
# Project created by QtCreator 2015-12-04T21:43:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -stdlib=libc++ -std=c++11
QMAKE_CXXFLAGS += -mmacosx-version-min=10.9

TARGET = pam_editor
TEMPLATE = app

INCLUDEPATH += /Users/francescousai/Documents/Libs/eigen/
INCLUDEPATH += /Users/francescousai/Documents/Libs/gsl-lite/include/


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    basics/point.h \
    basics/coord.h \
    R3/coord.h \
    R3/point.h \
    R3/vec3d.h \
    mesh/mesh_base.h

FORMS    += mainwindow.ui