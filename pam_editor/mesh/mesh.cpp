#include <mesh/mesh.h>

namespace  Mesh {
    //void Mesh::Mesh::BuildFromVectors( Eigen::MatrixXd vertices, Eigen::MatrixXi faces ){
    void Mesh::BuildFromVectors( std::vector< double >& verts,  std::vector< std::vector< u_long > >& faces ){
        // data structures fro twin connectiity
        typedef std::pair<VertexID, VertexID> VPair;
        typedef std::map<VPair, HalfEdgeID>   VertexToHalfedge;

        VertexToHalfedge vpair_to_he;

        //TODO : create twin connectivity, maybe this can go on a cpp file.
        this->Clear();
        // Actually it should be more performant to iterate column-wise, instead of row-wise
        // STEP 1 - copy vertices

        for( size_t i = 0; i < verts.size(); i+=3 ){
            Vertex vert;
            vert.pos.Set( verts.at(i), verts.at(i+1), verts.at(i+2));
            vs.push_back( vert );
        }
        // STEP 2 - a) create faces;  b) create halfedges; c) create next, prev connectivity
        for( const auto& item: faces ){
            // a) create faces
            Face face;
            for( const auto& vert_id: item){
                face.verts.push_back( VertexID( vert_id ));
            }
            FaceID fid( fs.size() );
            fs.push_back( face );
            // b) create halfedges
            HalfEdgeID anchor( hs.size( ));
            for( size_t i = 1; i < face.verts.size(); ++i ){
                HalfEdge h;
                h.face = fid;
                h.from = VertexID( face.verts[i-1] );
                h.to   = VertexID( face.verts[i] );
                HalfEdgeID hid( hs.size());
                hs.push_back( h );
                vs.at( h.from ).out = hid;
                vs.at( h.to).in     = hid;
                vpair_to_he[ std::make_pair(h.from, h.to)] = hid;
            }
            HalfEdge last_h;
            last_h.face = fid;
            last_h.from = VertexID( face.verts.back() );
            last_h.to   = VertexID( face.verts.front() );
            HalfEdgeID hid( hs.size());
            hs.push_back( last_h );
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
            assert( isValid(item.second) );
            // if the twin has been set, this item can be skipped.
            if(  isValid(hs.at(item.second).twin) ) { continue; }
            VPair twin_pair = std::make_pair( item.first.second, item.first.first );
            assert(vpair_to_he.count( twin_pair ) > 0 );
            HalfEdgeID twin_id = vpair_to_he.at( twin_pair );
            hs.at( item.second).twin = twin_id;
            hs.at( twin_id ).twin = item.second;
        }
    }
    HalfEdgeWalker  Mesh::getWalker( const HalfEdgeID& halfedge ) const {
        return HalfEdgeWalker( *this, halfedge );
    }
    VertexWalker  Mesh::getWalker( const VertexID& vertex ) const {
        return VertexWalker( *this, vertex );
    }
    FaceWalker  Mesh::getWalker( const FaceID& face ) const {
        return FaceWalker( *this, face );
    }

}
