#ifndef MESH_H
#define MESH_H

#include "mesh_base.h"
#include "R3/vec3d.h"
#include <vector>
#include <map>
#include <Eigen/Dense>
#include "gsl/gsl-lite.h"
#include <iostream>

namespace Mesh{

typedef std::vector<Vertex>         VertexVector;
typedef std::vector<HalfEdge>       HalfEdgeVector;
typedef std::vector<Face>           FaceVector;
typedef std::vector< R3::Vec3d>     VertexNormalsVector;
typedef std::vector< R3::Vec3d>     FaceNormalsVector;

class Walker;
class HalfEdgeWalker;
class FaceWalker;
class VertexWalker;

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
        vs.clear();
        fs.clear();
        hs.clear();
        vns.clear();
        fns.clear();
    }

//    void BuildFromVectors( Eigen::MatrixXd vertices,  Eigen::MatrixXi faces );
    void BuildFromVectors( std::vector< double >& verts,  std::vector< std::vector< u_long > >& faces );


    /*********************************/
    /*              Items            */
    /*********************************/
    const VertexVector&     Vertices()  const { return vs; }
    const HalfEdgeVector&   Hafledges() const { return hs; }
    const FaceVector&       Faces()     const { return fs; }

    VertexVector&     Vertices()  { return vs; }
    HalfEdgeVector&   Hafledges() { return hs; }
    FaceVector&       Faces()     { return fs; }

    const Face&     FaceAt      ( FaceID id )       const { assert( isValid(id)); return fs.at( id ); }
    const HalfEdge& HalfEdgeAt  ( HalfEdgeID id )   const { assert( isValid(id)); return hs.at( id ); }
    const Vertex&   VertexAt    ( VertexID id )     const { assert( isValid(id)); return vs.at( id ); }

    Face&     FaceAt      ( FaceID id )       { assert( isValid(id)); return fs.at( id ); }
    HalfEdge& HalfEdgeAt  ( HalfEdgeID id )   { assert( isValid(id)); return hs.at( id ); }
    Vertex&   VertexAt    ( VertexID id )     { assert( isValid(id)); return vs.at( id ); }

    const R3::Vec3d&   NormalAt    ( FaceID id )    const { assert( isValid(id) ); return fns.at( id ); }
    const R3::Vec3d&   NormalAt    ( VertexID id )  const { assert( isValid(id) ); return vns.at( id ); }

    R3::Vec3d&   NormalAt    ( FaceID id )    { assert( isValid(id)); return fns.at( id ); }
    R3::Vec3d&   NormalAt    ( VertexID id )  { assert( isValid(id)); return vns.at( id ); }

    bool Exists( const HalfEdgeID& id ) const { return hs.size() > id ; }
    bool Exists( const VertexID&   id ) const { return vs.size() > id ; }
    bool Exists( const FaceID&     id ) const { return fs.size() > id ; }

    size_t NoVertices( )    const { return vs.size(); }
    size_t NoHalfEdges( )   const { return hs.size(); }
    size_t NoFaces( )       const { return fs.size(); }

    /*********************************/
    /*              Walkers          */
    /*********************************/
    HalfEdgeWalker  getWalker( const HalfEdgeID& halfedge) const;
    VertexWalker    getWalker( const VertexID& vertex ) const;
    FaceWalker      getWalker( const FaceID& face ) const;
};

/*********************************/
/*   HalfEdgeWalker declaration  */
/*********************************/

class Walker{

protected :

    size_t counter      = 0;
    bool  already_done  = false;
    const Mesh* mesh;   // this could have been a weak_ptr to const mesh, but I want errors if the mesh becoms null
    HalfEdgeID starter = InvalidHalfEdgeID;
    HalfEdgeID current = InvalidHalfEdgeID;

    void setIfDone(){
        this->already_done = ( this->counter > 0 ) && ( this->current == this->starter );
    }

    void assertMeshNotNull()        const { assert(mesh != NULL ); }
    HalfEdgeID _getHalfEdgeID()     const { return current; }
    HalfEdgeID _getOppHalfEdgeID()  const { return _getHalfEdge().twin; }
    FaceID _getStarterFaceID()      const { return mesh->HalfEdgeAt(starter).face; }
    FaceID _getPointedFaceID()      const { return _getOppHalfEdge().face; }
    VertexID _getFromVertexID()     const { return _getHalfEdge().from; }
    VertexID _getToVertexID()       const { return _getHalfEdge().to; }

    const HalfEdge& _getHalfEdge()  const { assertMeshNotNull(); return mesh->HalfEdgeAt( current             ); }
    HalfEdge _getOppHalfEdge()      const { assertMeshNotNull(); return mesh->HalfEdgeAt( _getOppHalfEdgeID() ); }
    const Face& _getStarterFace()   const { assertMeshNotNull(); return mesh->FaceAt(     _getStarterFaceID() ); }
    const Face& _getPointedFace()   const { assertMeshNotNull(); return mesh->FaceAt(     _getPointedFaceID() ); }
    const Vertex& _getFromVertex()  const { assertMeshNotNull(); return mesh->VertexAt(   _getFromVertexID()  ); }
    const Vertex& _getToVertex()    const { assertMeshNotNull(); return mesh->VertexAt(   _getToVertexID()    ); }


public :

    Walker( const Mesh& m, const HalfEdgeID& halfedge ) : mesh(&m){
        assert( mesh->Exists( halfedge) );
        this->starter = halfedge;
        this->current = this->starter;
    }
    ~Walker(){ }

    bool done() const { return already_done; }
};


class HalfEdgeWalker : public Walker{
public :
    /* MOVE ALONG EDGES */
    HalfEdgeWalker Next() const {
        assertMeshNotNull();
        auto _next = mesh->HalfEdgeAt( current ).next;
        HalfEdgeWalker w( *mesh, _next );
        w.starter = this->starter;
        w.counter++;
        w.setIfDone();
        return w;
    }

    HalfEdgeWalker Opp() const {
        assertMeshNotNull();
        auto _opp = mesh->HalfEdgeAt( current ).twin;
        HalfEdgeWalker w( *mesh, _opp );
        w.starter = this->starter;
        w.counter++;
        w.setIfDone();
        return w;
    }

    HalfEdgeWalker Prev() const {
        assertMeshNotNull();
        auto _prev = mesh->HalfEdgeAt( current ).prev;
        HalfEdgeWalker w( *mesh, _prev );
        w.starter = this->starter;
        w.counter++;
        w.setIfDone();
        return w;
    }

    HalfEdgeWalker(const Mesh& m, const HalfEdgeID& halfedge ) : Walker( m, halfedge ){ }
    HalfEdgeID GetHalfEdgeID()          const { return _getHalfEdgeID();    }
    HalfEdgeID GetOppHalfEdgeID()       const { return _getOppHalfEdgeID();  }
    const HalfEdge& GetHalfEdge()       const { return _getHalfEdge();      }
    const HalfEdge& GetOppHalfEdge()    const { return  _getOppHalfEdge();  }
};

class FaceWalker : public Walker{
protected :
    FaceWalker(const Mesh& m, const HalfEdgeID& halfedge ) : Walker( m, halfedge){ }
public :
    FaceWalker(const Mesh& m, const FaceID& face ) : Walker( m, m.FaceAt(face).edge){ }
    FaceID GetStarterFaceID()    const { return this->_getStarterFaceID(); }
    FaceID GetFaceID()           const { return this->_getPointedFaceID(); }
    const Face& GetStarterFace() const { return this->_getStarterFace(); }
    const Face& GetFace()        const { return this->_getPointedFace(); }

    /* MOVE ALONG FACE 1-RING CCW */
    FaceWalker Next() const {
        assertMeshNotNull();
        auto _next = mesh->HalfEdgeAt(current).next;
        FaceWalker w( *mesh, _next );
        w.starter = this->starter;
        w.counter++;
        w.setIfDone();        
        return w;
    }

    FaceWalker Prev() const {
        assertMeshNotNull();
        auto _prev = mesh->HalfEdgeAt(current).prev;
        FaceWalker w( *mesh, _prev );
        w.starter = this->starter;
        w.counter++;
        w.setIfDone();        
        return w;
    }
};

class VertexWalker : public Walker{
protected:
    VertexWalker(const Mesh& m, const HalfEdgeID& halfedge) : Walker( m, halfedge ){ }
public :
    VertexWalker(const Mesh& m, const VertexID& vertex) : Walker( m, m.VertexAt(vertex).out ){ }
    VertexID GetVertexID()     const { return this->_getToVertexID(); }
    const Vertex& GetVertex()  const { return this->_getToVertex(); }

    /* MOVE ALONG VERTEX 1-RING CCW */
    VertexWalker Next() const {
        assertMeshNotNull();
        auto _next =
                mesh->HalfEdgeAt(
                mesh->HalfEdgeAt(current).twin).next;

        VertexWalker w( *mesh, _next );
        w.starter = this->starter;
        w.counter++;
        w.setIfDone();
        assert(w._getFromVertexID() == this->_getFromVertexID());
        return w;
    }

    VertexWalker Prev() const {
        assertMeshNotNull();
        auto _prev =
                mesh->HalfEdgeAt(
                mesh->HalfEdgeAt(current).prev ).twin;

        VertexWalker w( *mesh, _prev );
        w.starter = this->starter;
        w.counter++;
        w.setIfDone();
        assert(w._getFromVertexID() == this->_getFromVertexID());
        return w;
    }
};



}

#endif // MESH_H
