#include "mainwindow.h"
#include <QApplication>

#include <iostream>

#include <Eigen/Dense>

#include <R3/coord.h>
#include <R3/point.h>
#include <R3/vec3d.h>
#include <mesh/mesh_base.h>
#include <mesh/mesh.h>
#include <mesh/import.h>



int main(int argc, char *argv[])
{
    R3::Coord c(1,1,1), c2(1,1,1);
    R3::Point p(1,1,1), p2(1,1,1);
    R3::Vec3d v(1,1,1), v2(1,1,1);

    R3::Coord cr = c + c2;
    R3::Point pr = p + p2;
    R3::Vec3d vr = v + v2;

    std::vector< double > verts;
    std::vector< std::vector< u_long > > faces;

    static const double arr[] = { 0, 0, 0,
                               1, 0, 0,
                               0, 0, 1,
                               0.5, 1, 0.5};

    verts.assign(arr, arr + 12);


    faces.push_back( {1, 0,  2} );
    faces.push_back( {1, 3,  0} );
    faces.push_back( {1, 2,  3} );
    faces.push_back( {2, 0,  3} );


    Mesh::Mesh mesh;
    //mesh.BuildFromVectors( verts, faces );
    Mesh::Importer::from_obj("/Users/francescousai/Documents/Sviluppo/igl_viewer/data/warrior.obj", verts, faces);

    std::cout << verts.size() << ", " << faces.size() << std::endl;

//    std::cout << "VERTICES" <<std::endl;
//    for( int i = 0; i < verts.size(); i+=3 ){
//        std::cout<< verts[i] << ", " << verts[i+1] << ", " << verts[i+2] << std::endl;
//    }
//    std::cout << "FACES" <<std::endl;
//    for(const auto& face : faces){
//        for(u_long fv : face){
//            std::cout<< fv << ", ";
//        }
//        std::cout << std::endl;
//    }

    mesh.BuildFromVectors(verts, faces);


    Mesh::FaceID fid( 0 );
    Mesh::FaceWalker fw = mesh.getWalker( fid );
    Mesh::HalfEdgeID hid = fw.GetFace().edge;
    Mesh::HalfEdgeWalker hew = mesh.getWalker( hid );
    Mesh::VertexWalker vw = mesh.getWalker( hew.GetHalfEdge().from );

    std::cout << "FACES! start at " << fw.GetFaceID() << std::endl;
    while( !fw.done( )){

        fw = fw.Next();
        std::cout <<  fw.GetFaceID() << " : done? " << fw.done()  << std::endl;
    }

    std::cout << "EDGES! start at " << hew.GetHalfEdgeID() << std::endl;
    while( !hew.done( )){
        std::cout << hew.GetHalfEdgeID() << " : done? " << hew.done()  << std::endl;
        hew = hew.Next();
    }

    std::cout << "VERTICES! start at " << vw.GetVertexID() << std::endl;
    while( !vw.done( )){
        std::cout << vw.GetVertexID() << " : done? " << vw.done()  << std::endl;
        vw = vw.Next();
    }


    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
