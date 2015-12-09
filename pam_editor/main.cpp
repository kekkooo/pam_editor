#include "mainwindow.h"
#include <QApplication>

#include <iostream>

#include <Eigen/Dense>

#include <R3/coord.h>
#include <R3/point.h>
#include <R3/vec3d.h>
#include <mesh/mesh_base.h>
#include <mesh/mesh.h>




int main(int argc, char *argv[])
{
    R3::Coord c(1,1,1), c2(1,1,1);
    R3::Point p(1,1,1), p2(1,1,1);
    R3::Vec3d v(1,1,1), v2(1,1,1);

    R3::Coord cr = c + c2;
    R3::Point pr = p + p2;
    R3::Vec3d vr = v + v2;

    Eigen::MatrixXd verts(4, 3);
    Eigen::MatrixXi faces(4, 3);

    verts << 0, 0,  0,
             1, 0,  0,
             0, 0,  1,
             0.5, 1, 0.5;

    faces <<
         1, 0, 2,
         1, 3, 0,
         1, 2, 3,
         2, 0, 3;


    Mesh::Mesh mesh;
    mesh.BuildFromVectors( verts, faces );
    Mesh::FaceID fid( 0 );
    Mesh::FaceWalker fw = mesh.getWalker( fid );
    Mesh::HalfEdgeWalker hew = mesh.getWalker( fw.GetFace().edge );
    Mesh::VertexWalker vw = mesh.getWalker( hew.GetHalfEdge().from );

    std::cout << "FACES!" << std::endl;
    size_t iters = 0;
    while( !fw.done( )){

        std::cout << iters++ << ") " << fw.GetFaceID() << " : done? " << fw.done()  << std::endl;
        Mesh::FaceWalker n = fw.Next();
        fw = n;
        std::cout << "fw done ? " << fw.done() << "   #    n done? " << n.done() << std::endl;
        //fw = fw.Next();


    }


//    std::cout << cr << std::endl;
//    std::cout << vr << std::endl;
//    std::cout << pr << std::endl;


    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
