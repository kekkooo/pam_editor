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
        vs.Items().clear();
        fs.Items().clear();
        hs.Items().clear();
        vns.Items().clear();
        fns.Items().clear();
    }

    void BuildFromVectors( Eigen::MatrixXd vertices,  Eigen::MatrixXi faces );


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
    HalfEdgeWalker  getWalker( const HalfEdgeID& halfedge);
    VertexWalker    getWalker( const VertexID& vertex );
    FaceWalker      getWalker( const FaceID& face );


};

/*********************************/
/*   HalfEdgeWalker declaration  */
/*********************************/

class Walker{

protected :

    size_t counter      = 0;
    bool  already_done;//  = false;
    const Mesh& mesh;
    const Mesh* mesh_pointer;
    std::shared_ptr<const Mesh> const_mesh;
    HalfEdgeID starter;
    HalfEdgeID current;

    void setIfDone(){
        bool comparison = this->current == this->starter;
        bool countercomp = this->counter > 0;
        this->already_done = ( this->counter > 0 ) && ( comparison);
        std::cout << "internal : has done?" << this->already_done << std::endl;
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
//        mesh = w.mesh ;
        const_mesh = w.const_mesh;
        mesh_pointer = w.mesh_pointer;
        starter = w.starter;
        current = w.current;
        counter = w.counter;
        already_done = w.already_done;
        return *this;
    }

    bool done() const { return already_done; }

};


class HalfEdgeWalker : public Walker{
public :
    /* MOVE ALONG EDGES */
    HalfEdgeWalker Next() const {
        auto _next = mesh.HalfEdgeAt( current ).next;
        HalfEdgeWalker w( mesh, _next );
        w.starter = this->starter;
        w.counter++;
        w.setIfDone();
        return w;
    }

    HalfEdgeWalker Opp() const {
        auto _opp = mesh.HalfEdgeAt( current ).twin;
        HalfEdgeWalker w( mesh, _opp );
        w.starter = this->starter;
        w.counter++;
        w.setIfDone();
        return w;
    }

    HalfEdgeWalker Prev() const {
        auto _prev = mesh.HalfEdgeAt( current ).prev;
        HalfEdgeWalker w( mesh, _prev );
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
    FaceID GetFaceID()          const { return this->_getFaceID(); }
    FaceID GetOppFaceID()       const { return this->_getOppFaceID(); }
    const Face& GetFace()       const { return this->_getFace(); }
    const Face& GetOppFace()    const { return this->_getOppFace(); }

    /* MOVE ALONG FACE 1-RING CCW */
    FaceWalker Next() const {
        // next->opp->face
        auto _next =
                mesh.HalfEdgeAt(
                mesh.HalfEdgeAt(current).next ).twin;

        FaceWalker w( mesh, _next );
        w.starter = this->starter;
        w.counter++;
        w.setIfDone();
        std::cout << "internal : has done?" << w.done() << std::endl;
        return w;
    }

    FaceWalker Prev() const {
        auto _prev =
                mesh.HalfEdgeAt(
                mesh.HalfEdgeAt(current).prev ).twin;

        FaceWalker w( mesh, _prev );
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
        // next->opp->face
        auto _next =
                mesh.HalfEdgeAt(
                mesh.HalfEdgeAt(current).prev).twin;

        VertexWalker w( mesh, _next );
        w.starter = this->starter;
        w.counter++;
        w.setIfDone();
        return w;
    }

    VertexWalker Prev() const {
        auto _prev =
                mesh.HalfEdgeAt(
                mesh.HalfEdgeAt(current).twin ).next;

        VertexWalker w( mesh, _prev );
        w.starter = this->starter;
        w.counter++;
        w.setIfDone();
        return w;
    }
};



}

#endif // MESH_H
