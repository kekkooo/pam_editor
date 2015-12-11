#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mesh/drawable.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    viewer = new Viewer(this);
    viewer->setFocusPolicy(Qt::StrongFocus);
}

MainWindow::~MainWindow()
{
    delete ui;
}
