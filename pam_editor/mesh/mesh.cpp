#include <mesh/mesh.h>

namespace  Mesh {
    void Mesh::Mesh::BuildFromVectors( Eigen::MatrixXd vertices, Eigen::MatrixXi faces ){
        // data structures fro twin connectiity
        typedef std::pair<VertexID, VertexID> VPair;
        typedef std::map<VPair, HalfEdgeID>   VertexToHalfedge;

        VertexToHalfedge vpair_to_he;

        //TODO : create twin connectivity, maybe this can go on a cpp file.
        this->Clear();
        // Actually it should be more performant to iterate column-wise, instead of row-wise
        // STEP 1 - copy vertices
        for( size_t r = 0; r< vertices.rows(); ++r ){
            Vertex vert;
            vert.pos.Set( vertices(r, 0), vertices(r, 1),  vertices(r, 2));
            vs.Items().push_back( vert );
        }
        // STEP 2 - a) create faces;  b) create halfedges; c) create next, prev connectivity
        for( size_t r = 0; r< faces.rows(); ++r ){
            // a) create faces
            Face face;
            bool last = false;
            for( size_t c = 0; c < faces.cols() && !last; ++c ){
                if( faces( r, c ) == SIGNED_INVALID_ID ){
                    last = true;
                    continue;
                }
                face.verts.push_back( VertexID(faces( r,c )));
            }
            FaceID fid( fs.size() );
            fs.Items().push_back( face );
            // b) create halfedges
            HalfEdgeID anchor( hs.size( ));
            for( size_t i = 1; i < face.verts.size(); ++i ){
                HalfEdge h;
                h.face = fid;
                h.from = VertexID( face.verts[i-1] );
                h.to   = VertexID( face.verts[i] );
                HalfEdgeID hid( hs.Items().size());
                hs.Items().push_back( h );
                vs.at( h.from ).out = hid;
                vs.at( h.to).in     = hid;
                vpair_to_he[ std::make_pair(h.from, h.to)] = hid;
            }
            HalfEdge last_h;
            last_h.face = fid;
            last_h.from = VertexID( face.verts.back() );
            last_h.to   = VertexID( face.verts.front() );
            HalfEdgeID hid( hs.Items().size());
            hs.Items().push_back( last_h );
            fs.at( last_h.face ).edge = hid;
            vs.at( last_h.from ).out = hid;
            vs.at( last_h.to).in     = hid;
            vpair_to_he[ std::make_pair(last_h.from, last_h.to)] = hid;
            // c) create next, prev connectivity
            HalfEdgeID curr = anchor, prev = anchor;
            ++curr;
            for( size_t i= 1; i < face.verts.size(); ++i ){
                hs.at( prev ).next = curr;
                hs.at( curr ).prev= prev;
                ++prev;
                ++curr;
            }
            hs.at( prev ).next = anchor;
            hs.at( anchor ).prev= prev;
        }
        for( const auto& item : vpair_to_he ){// item is a pair< Vpair, HalfEdgeID>
            assert( item.second.isValid() );
            // if the twin has been set, this item can be skipped.
            if(  hs.at(item.second).twin.isValid( )) { continue; }
            VPair twin_pair = std::make_pair( item.first.second, item.first.first );
            assert(vpair_to_he.count( twin_pair ) > 0 );
            HalfEdgeID twin_id = vpair_to_he.at( twin_pair );
            hs.at( item.second).twin = twin_id;
            hs.at( twin_id ).twin = item.second;
        }
    }
    HalfEdgeWalker  Mesh::getWalker( const HalfEdgeID& halfedge ){
        return HalfEdgeWalker( *this, halfedge );
    }
    VertexWalker  Mesh::getWalker( const VertexID& vertex ){
        return VertexWalker( *this, vertex );
    }
    FaceWalker  Mesh::getWalker( const FaceID& face ){
        return FaceWalker( *this, face );
    }

}
