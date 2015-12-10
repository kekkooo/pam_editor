#pragma once

#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <QString>
#include <QFile>
#include <QMap>
#include <Eigen/Dense>

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

namespace Mesh
{

namespace Importer
{

// Adaptation from Marco Livesu's old code.
static void from_obj( std::string filename, std::vector< double >&pts, std::vector< std::vector< u_long > >& polygons)
{
        typedef boost::char_separator<char>     CharSeparator;
        typedef boost::tokenizer<CharSeparator> Tokenizer;
        typedef Tokenizer::iterator             TokenizerIterator;

        CharSeparator space_separator(" ");
        CharSeparator slash_separator("/");

        static std::string vertex = "v";
        static std::string face   = "f";

        std::ifstream file(filename.c_str());
        std::string   line;

        if(!file.is_open()) { return; }
        pts.clear();;
        polygons.clear();

        while(getline(file,line))
        {
            Tokenizer space_tokenizer(line, space_separator);

            if (space_tokenizer.begin() == space_tokenizer.end()) continue;

            TokenizerIterator token = space_tokenizer.begin();
            std::string header = *token;

            // Handle
            //
            // v 0.123 0.234 0.345
            // v 0.123 0.234 0.345 1.0

            if ( strcmp( header.c_str(), vertex.c_str()) == 0)
            {
                std::string x = *(++token);
                std::string y = *(++token);
                std::string z = *(++token);

                pts.push_back( atof( x.c_str( )));
                pts.push_back( atof( y.c_str( )));
                pts.push_back( atof( z.c_str( )));
            }

            else

            // Handle
            //
            // f 1 2 3
            // f 3/1 4/2 5/3
            // f 6/4/1 3/5/3 7/6/5
            //
            // NOTE: 6/4/1 => only 6 (vertex id) will be stored in the mesh

            if (strcmp(header.c_str(), face.c_str()) == 0)
            {
                polygons.push_back(std::vector< u_long >());

                for(Tokenizer::iterator it=++(space_tokenizer.begin()); it!=space_tokenizer.end(); ++it)
                {
                    Tokenizer slash_tokenizer(*it, slash_separator);
                    std::string str_nid = *slash_tokenizer.begin();
                    int int_nid = atoi(str_nid.c_str());
                    polygons.back().push_back(int_nid - 1);
//                    poly.vertices.push_back(int_nid - 1);
                }
//                m.polygons.push_back(poly);                
            }
        }
}

//static void from_off( RMesh::mesh &m, QString filename)
//
//    typedef boost::char_separator<char>     CharSeparator;
//    typedef boost::tokenizer<CharSeparator> Tokenizer;
//    typedef Tokenizer::iterator             TokenizerIterator;

//    CharSeparator space_separator(" ");

//    ifstream file(filename.toStdString().c_str());
//    string   line;

//    if(!file.is_open())
//    {
//        return;
//    }

//    getline(file,line);
//    boost::algorithm::trim(line);

//    assert( line.compare("OFF") == 0 );
//    while(getline(file,line)) { boost::algorithm::trim(line); if( line.find('#') >= line.length()) break;  }

//    cout << line << endl;
//    int vs, fs, hes;
//    sscanf(line.c_str(), "%d %d %d", &vs, &fs, &hes );

//    m.vertices.reserve(vs);
//    m.polygons.reserve(fs);


//    for( int i = 0; i < vs; ++i)
//    {
//        getline(file,line);
//        double x,y,z;
//        sscanf(line.c_str(), "%lf %lf %lf", &x, &y, &z );
////        cout << i << ") " << x << ", " << y << ", " << z << endl;
//        Primitives::Point3d p( x, y, z );
//        m.vertices.push_back(p);
//    }
//    for( int i = 0; i < fs; ++i)
//    {
//        getline(file,line);
//        MeshPolygon f;
//        Tokenizer space_tokenizer(line, space_separator);
//        if ( space_tokenizer.begin() == space_tokenizer.end( )) continue;
//        TokenizerIterator token = space_tokenizer.begin();
//        string nf = *token;
//        int num_of_vertices = atoi( nf.c_str( ));
//        assert( num_of_vertices > 2 );
//        ++token;
//        f.vertices.reserve( num_of_vertices );
//        while( token != space_tokenizer.end())
//        {
//            string vertex = *(token);
//            f.vertices.push_back( atoi( vertex.c_str( )));
//            ++token;
//        }
//        m.polygons.push_back(f);

//    }
//    m.bbox.Set(m.vertices);
//    file.close();
//}

}
}
