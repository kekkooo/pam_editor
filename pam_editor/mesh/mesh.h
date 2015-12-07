#ifndef MESH_H
#define MESH_H

#include "mesh_base.h"
#include <vector>

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

    bool Exists( const INDEX& idx ) const { return idx.id < items.size(); }
};

typedef ItemVector< Vertex,     VertexID>   VertexVector;
typedef ItemVector< HalfEdge,   HalfEdgeID> HalfEdgeVector;
typedef ItemVector< Face,       FaceID>     FaceVector;


class Mesh{
private :
    VertexVector    vs;
    HalfEdgeVector  hs;
    FaceVector      fs;

public:
    const VertexVector&     Vertices()  const { return vs; }
    const HalfEdgeVector&   Hafledges() const { return hs; }
    const FaceVector&       Faces()     const { return fs; }

    VertexVector&     Vertices()  { return vs; }
    HalfEdgeVector&   Hafledges() { return hs; }
    FaceVector&       Faces()     { return fs; }

    const Face&     FaceAt      ( FaceID id )       const { return fs.at( id ); }
    const HalfEdge& HalfEdgeAt  ( HalfEdgeID id )   const { return hs.at( id ); }
    const Vertex&   VertexAt    ( VertexID id )     const { return vs.at( id ); }

    Face&     FaceAt      ( FaceID id )       { return fs.at( id ); }
    HalfEdge& HalfEdgeAt  ( HalfEdgeID id )   { return hs.at( id ); }
    Vertex&   VertexAt    ( VertexID id )     { return vs.at( id ); }

    bool Exists( const HalfEdgeID& id ) const { return hs.Exists( id ); }
    bool Exists( const VertexID&   id ) const { return vs.Exists( id ); }
    bool Exists( const FaceID&     id ) const { return fs.Exists( id ); }

};


class Walker{
protected :
//          bool  already_done;
//    const Mesh& mesh;

    virtual void setIfDone() = 0;

public :
//    Walker( const Mesh& m ) : mesh(m) {  }
    virtual ~Walker(){};
    virtual Walker& next() const = 0;
//    virtual Walker& prev() const = 0;
    virtual bool   done()  const = 0;
};

class HalfEdgeWalker : public Walker{

protected :
          bool  already_done;
    const Mesh& mesh;

    HalfEdgeID starter;
    HalfEdgeID current;

    void setIfDone();

public :

    HalfEdgeWalker( const Mesh& m, const HalfEdgeID& halfedge ) : mesh(m), Walker(){
        assert( mesh.Exists( halfedge) );
        this->starter = halfedge;
        this->current = this->starter;
    }
    ~HalfEdgeWalker(){ Walker::~Walker(); }

    Walker& next() const;
//    virtual Walker& prev() const;
    bool   done()  const;
};

/* HalfEdgeWalker implementation */


Walker& HalfEdgeWalker::next() const {
    const HalfEdgeID& _next = mesh.HalfEdgeAt( current ).next;
    HalfEdgeWalker* w = new HalfEdgeWalker( mesh, _next );
    w->starter = this->starter;
    w->setIfDone();
    return *w;
}

//Walker& HalfEdgeWalker::prev() const {
//    auto _prev = mesh.HalfEdgeAt( current ).prev;
//    HalfEdgeWalker* w = new HalfEdgeWalker( mesh, _prev );
//    w->starter = this->starter;
//    w->setIfDone();
//    return *w;
//}

void HalfEdgeWalker::setIfDone(){ already_done = already_done || this->current == this->starter; }
bool HalfEdgeWalker::done() const { return already_done; }

}

#endif // MESH_H
