#include "viewer.h"



Viewer::Viewer(QWidget *parent) : QGLViewer(parent) {}

void Viewer::draw() {}
void Viewer::init() {}
QString Viewer::helpString() const{ return QString("ciao"); }
