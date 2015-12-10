#-------------------------------------------------
#
# Project created by QtCreator 2015-12-04T21:43:52
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS += -stdlib=libc++
QMAKE_CXXFLAGS += -mmacosx-version-min=10.9
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9

TARGET = pam_editor
TEMPLATE = app

INCLUDEPATH += /Users/francescousai/Documents/Libs/eigen/
INCLUDEPATH += /Users/francescousai/Documents/Libs/gsl-lite/include/
INCLUDEPATH += /usr/local/include/
LIBS    += -L/usr/local/lib/ -lboost_system



SOURCES += main.cpp\
        mainwindow.cpp \
    mesh/mesh.cpp

HEADERS  += mainwindow.h \
    basics/point.h \
    basics/coord.h \
    R3/coord.h \
    R3/point.h \
    R3/vec3d.h \
    mesh/mesh_base.h \
    color.h \
    mesh/mesh.h \
    mesh/import.h \
    mesh/drawable.h \
    mesh/BBox.h \
    mesh/bsphere.h \
    utilities/GLutils.h

FORMS    += mainwindow.ui
