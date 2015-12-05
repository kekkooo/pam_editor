#include "mainwindow.h"
#include <QApplication>

#include <iostream>

#include <R3/coord.h>
#include <R3/point.h>
#include <R3/vec3d.h>


int main(int argc, char *argv[])
{
    R3::Coord c(1,1,1), c2(1,1,1);
    R3::Point p(1,1,1), p2(1,1,1);
    R3::Vec3d v(1,1,1), v2(1,1,1);

    R3::Coord cr = c + c2;
    R3::Point pr = p + p2;
    R3::Vec3d vr = v + v2;

//    std::cout << cr << std::endl;
//    std::cout << vr << std::endl;
//    std::cout << pr << std::endl;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
