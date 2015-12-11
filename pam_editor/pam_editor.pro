#-------------------------------------------------
#
# Project created by QtCreator 2015-12-04T21:43:52
#
#-------------------------------------------------

QT       += core gui opengl xml widgets
CONFIG   +=  qt core opengl thread

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
INCLUDEPATH += /Users/francescousai/Documents/Libs/libQGLViewer-2.6.3/QGLViewer/
LIBS    += -L/Users/francescousai/Documents/Libs/libQGLViewer-2.6.3/QGLViewer/ -lQGLViewer
LIBS    += -L/usr/local/lib/ -lboost_system



SOURCES += main.cpp\
        mainwindow.cpp \
    mesh/mesh.cpp \
    mesh/drawable_mesh.cpp \
    GUI/viewer.cpp

HEADERS  += mainwindow.h \
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
    utilities/GLutils.h \
    mesh/drawable_mesh.h \
    GUI/viewer.h

FORMS    += mainwindow.ui
