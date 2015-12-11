#ifndef VIEWER_H
#define VIEWER_H

#include <QGLViewer/qglviewer.h>
#include <QGLViewer/vec.h>
#include <QGLViewer/manipulatedFrame.h>
#include <QString>
#include <QObject>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPair>
#include <QListWidgetItem>

class Viewer : public QGLViewer
{
//    Q_OBJECT

protected :
  virtual void draw();
  virtual void init();
  virtual QString helpString() const;

public:

    //Viewer();
    explicit Viewer( QWidget *parent = 0 );
};

#endif // VIEWER_H
