#ifndef MESH_H
#define MESH_H

#include "mesh_base.h"
#include "R3/vec3d.h"
#include <vector>
#include <map>
#include <Eigen/Dense>
#include "gsl/gsl-lite.h"

namespace Mesh{

template <typename ITEM, typename INDEX>
class ItemVector{
private:
    std::vector<ITEM> items;
public:
    const std::vector<ITEM>& Items() const { return items; }
          std::vector<ITEM>& Items()       { return items; }

    const ITEM& at( INDEX idx ) const{
        return items.at( idx.id );
    }

    ITEM& at( INDEX idx ){
        return items.at( idx.id );
    }

    size_t size() const{
        return items.size();
    }

    inline bool Exists( const INDEX& idx ) const { return idx.id < items.size(); }
};

typedef ItemVector< Vertex,     VertexID>   VertexVector;
typedef ItemVector< HalfEdge,   HalfEdgeID> HalfEdgeVector;
typedef ItemVector< Face,       FaceID>     FaceVector;
typedef ItemVector< R3::Vec3d,  VertexID>   VertexNormalsVector;
typedef ItemVector< R3::Vec3d,  FaceID>     FaceNormalsVector;

class Mesh{
private :
    VertexVector        vs;
    HalfEdgeVector      hs;
    FaceVector          fs;
    VertexNormalsVector vns;
    FaceNormalsVector   fns;

public:

    Mesh(){
        vs = VertexVector();
        hs = HalfEdgeVector();
        fs = FaceVector();
        vns = VertexNormalsVector();
        fns = FaceNormalsVector();
    };
    ~Mesh(){ this->Clear(); }

    void Clear(){
        vs.Items().clear();
        fs.Items().clear();
        hs.Items().clear();
        vns.Items().clear();
        fns.Items().clear();
    }

    void BuildFromVectors( Eigen::MatrixXd vertices,  Eigen::MatrixXi faces );//{
//        // data structures fro twin connectiity
//        typedef std::pair<VertexID, VertexID> VPair;
//        typedef std::map<VPair, HalfEdgeID>   VertexToHalfedge;

//        VertexToHalfedge vpair_to_he;

//        //TODO : create twin connectivity, maybe this can go on a cpp file.
//        this->Clear();
//        // Actually it should be more performant to iterate column-wise, instead of row-wise
//        // STEP 1 - copy vertices
//        for( size_t r = 0; r< vertices.rows(); ++r ){
//            Vertex vert;
//            vert.pos.Set( vertices(r, 0), vertices(r, 1),  vertices(r, 2));
//            vs.Items().push_back( vert );
//        }
//        // STEP 2 - a) create faces;  b) create halfedges; c) create next, prev connectivity
//        for( size_t r = 0; r< faces.rows(); ++r ){
//            // a) create faces
//            Face face;
//            FaceID fid;
//            bool last = false;
//            for( size_t c = 0; c < faces.cols() && !last; ++c ){
//                if( faces( r, c ) == SIGNED_INVALID_ID ){
//                    last = true;
//                    continue;
//                }
//                face.verts.push_back( VertexID(faces( r,c )));
//            }
//            fid.id = fs.size();
//            fs.Items().push_back( face );
//            // b) create halfedges
//            HalfEdgeID anchor( hs.size( ));
//            for( size_t i = i; i < face.verts.size(); ++i ){
//                HalfEdge h;
//                h.face = fid;
//                h.from = VertexID( face.verts[i-1] );
//                h.to   = VertexID( face.verts[i] );
//                HalfEdgeID hid( hs.Items().size());
//                hs.Items().push_back( h );
//                vs.at( h.from ).out = hid;
//                vs.at( h.to).in     = hid;
//                vpair_to_he[ std::make_pair(h.from, h.to)] = hid;
//            }
//            HalfEdge last_h;
//            last_h.face = fid;
//            last_h.from = VertexID( face.verts.back() );
//            last_h.to   = VertexID( face.verts.front() );
//            HalfEdgeID hid( hs.Items().size());
//            hs.Items().push_back( last_h );
//            vs.at( last_h.from ).out = hid;
//            vs.at( last_h.to).in     = hid;
//            vpair_to_he[ std::make_pair(last_h.from, last_h.to)] = hid;
//            // c) create next, prev connectivity
//            HalfEdgeID curr = anchor, prev = anchor;
//            ++curr;
//            for( int i= 1; i < face.verts.size(); ++i ){
//                hs.at( prev ).next = curr;
//                hs.at( curr ).prev= prev;
//                ++prev;
//                ++curr;
//            }
//            hs.at( prev ).next = anchor;
//            hs.at( anchor ).prev= prev;
//        }
//        for( const auto& item : vpair_to_he ){// item is a pair< Vpair, HalfEdgeID>
//            assert( item.second.isValid() );
//            // if the twin has been set, this item can be skipped.
//            if(  !hs.at(item.second).twin.isValid( )) { continue; }
//            VPair twin_pair = std::make_pair( item.first.second, item.first.first );
//            assert(vpair_to_he.count( twin_pair ) > 0 );
//            HalfEdgeID twin_id = vpair_to_he.at( twin_pair );
//            hs.at( item.second).twin = twin_id;
//            hs.at( twin_id ).twin = item.second;
//        }
    //}


    /*********************************/
    /*              Items            */
    /*********************************/
    const VertexVector&     Vertices()  const { return vs; }
    const HalfEdgeVector&   Hafledges() const { return hs; }
    const FaceVector&       Faces()     const { return fs; }

    VertexVector&     Vertices()  { return vs; }
    HalfEdgeVector&   Hafledges() { return hs; }
    FaceVector&       Faces()     { return fs; }

    const Face&     FaceAt      ( FaceID id )       const { assert( id.isValid()); return fs.at( id ); }
    const HalfEdge& HalfEdgeAt  ( HalfEdgeID id )   const { assert( id.isValid()); return hs.at( id ); }
    const Vertex&   VertexAt    ( VertexID id )     const { assert( id.isValid()); return vs.at( id ); }

    Face&     FaceAt      ( FaceID id )       { assert( id.isValid()); return fs.at( id ); }
    HalfEdge& HalfEdgeAt  ( HalfEdgeID id )   { assert( id.isValid()); return hs.at( id ); }
    Vertex&   VertexAt    ( VertexID id )     { assert( id.isValid()); return vs.at( id ); }

    const R3::Vec3d&   NormalAt    ( FaceID id )    const { assert( id.isValid() ); return fns.at( id ); }
    const R3::Vec3d&   NormalAt    ( VertexID id )  const { assert( id.isValid() ); return vns.at( id ); }

    R3::Vec3d&   NormalAt    ( FaceID id )    { assert( id.isValid()); return fns.at( id ); }
    R3::Vec3d&   NormalAt    ( VertexID id )  { assert( id.isValid()); return vns.at( id ); }

    bool Exists( const HalfEdgeID& id ) const { return hs.Exists( id ); }
    bool Exists( const VertexID&   id ) const { return vs.Exists( id ); }
    bool Exists( const FaceID&     id ) const { return fs.Exists( id ); }

    /*********************************/
    /*              Walkers          */
    /*********************************/

};

/*********************************/
/*   HalfEdgeWalker declaration  */
/*********************************/

class Walker{

protected :

    size_t counter = 0;
    bool  already_done = false;
    const Mesh& mesh;
    HalfEdgeID starter;
    HalfEdgeID current;

    void setIfDone(){ already_done = counter > 0 && this->current == this->starter; }

    /* MOVE ALONG EDGES */
    Walker& nextHE() const {
        auto _next = mesh.HalfEdgeAt( current ).next;
        Walker* w = new Walker( mesh, _next );
        w->starter = this->starter;
        w->setIfDone();
        w->counter++;
        return *w;
    }

    Walker& oppHE() const {
        auto _opp = mesh.HalfEdgeAt( current ).twin;
        Walker* w = new Walker( mesh, _opp );
        w->starter = this->starter;
        w->setIfDone();
        w->counter++;
        return *w;
    }

    Walker& prevHE() const {
        auto _prev = mesh.HalfEdgeAt( current ).prev;
        Walker* w = new Walker( mesh, _prev );
        w->starter = this->starter;
        w->setIfDone();
        w->counter++;
        return *w;
    }

    /* MOVE ALONG FACE 1-RING CCW */
    Walker& nextFace() const {
        // next->opp->face
        auto _next =
                mesh.HalfEdgeAt(
                mesh.HalfEdgeAt(current).next ).twin;

        Walker* w = new Walker( mesh, _next );
        w->starter = this->starter;
        w->setIfDone();
        w->counter++;
        return *w;
    }

    Walker& prevFace() const {
        auto _prev =
                mesh.HalfEdgeAt(
                mesh.HalfEdgeAt(current).prev ).twin;

        Walker* w = new Walker( mesh, _prev );
        w->starter = this->starter;
        w->setIfDone();
        w->counter++;
        return *w;
    }

    /* MOVE ALONG VERTEX 1-RING CCW */
    Walker& nextVertex() const {
        // next->opp->face
        auto _next =
                mesh.HalfEdgeAt(
                mesh.HalfEdgeAt(current).prev).twin;

        Walker* w = new Walker( mesh, _next );
        w->starter = this->starter;
        w->setIfDone();
        w->counter++;
        return *w;
    }

    Walker& prevVertex() const {
        auto _prev =
                mesh.HalfEdgeAt(
                mesh.HalfEdgeAt(current).twin ).next;

        Walker* w = new Walker( mesh, _prev );
        w->starter = this->starter;
        w->setIfDone();
        w->counter++;
        return *w;
    }

    HalfEdgeID _getHalfEdgeID()     const { return current; }
    HalfEdgeID _getOppHalfEdgeID()  const { return HalfEdge().twin; }
    FaceID _getFaceID()             const { return _getHalfEdge().face; }
    FaceID _getOppFaceID()          const { return _getOppHalfEdge().face; }
    VertexID _getFromVertexID()     const { return _getHalfEdge().from; }
    VertexID _getToVertexID()       const { return _getHalfEdge().to; }

    const HalfEdge& _getHalfEdge()  const { return mesh.HalfEdgeAt( current             ); }
    HalfEdge _getOppHalfEdge()      const { return mesh.HalfEdgeAt( _getOppHalfEdgeID() ); }
    const Face& _getFace()          const { return mesh.FaceAt(     _getHalfEdge().face ); }
    const Face& _getOppFace()       const { return mesh.FaceAt(     _getOppFaceID()     ); }
    const Vertex& _getFromVertex()  const { return mesh.VertexAt(   _getFromVertexID()  ); }
    const Vertex& _getToVertex()    const { return mesh.VertexAt(   _getToVertexID()    ); }


public :

    Walker( const Mesh& m, const HalfEdgeID& halfedge ) : mesh(m){
        assert( mesh.Exists( halfedge) );
        this->starter = halfedge;
        this->current = this->starter;
    }
    ~Walker(){ }

    inline Walker operator =(const Walker& w)
    {
        current = w.current;
        counter = w.counter;
        return *this;
    }

    bool done() const { return already_done; }

};


class HalfEdgeWalker : public Walker{

public :
    Walker& Next() const { return this->nextHE();}
    Walker& Prev() const { return this->prevHE();}
    Walker& Opp()  const { return this->oppHE();}
    HalfEdgeID GetHalfEdgeID()     const { return this->_getHalfEdgeID(); }
    const HalfEdge& GetHalfEdge()  const { return this->_getHalfEdge(); }
};

class FaceWalker : public Walker{

public :
    Walker& Next() const { return this->nextFace(); }
    Walker& Prev() const { return this->prevFace(); }
    FaceID GetFaceID()     const { return this->_getFaceID(); }
    const Face& GetFace()  const { return this->_getFace(); }
};

class VertexWalker : public Walker{

public :
    Walker& Next() const { return this->nextVertex(); }
    Walker& Prev() const { return this->prevVertex(); }
    FaceID GetFaceID()     const { return this->_getFaceID(); }
    const Face& GetFace()  const { return this->_getFace(); }
};



}

#endif // MESH_H
