#ifndef MESH_BASE_H
#define MESH_BASE_H

#include "R3/point.h"
//#include "R3/vec3d.h"
#include <vector>
#include <string>

namespace Mesh{

#define SIGNED_INVALID_ID -1

struct VertexID{
    size_t id;
    VertexID( )             { id = ULONG_MAX; }
    VertexID( size_t v )    { id = v; }
    bool operator == (const VertexID r)       { return this->id == r.id; }
    bool operator < ( const VertexID r)        { return this->id < r.id; }
    bool operator > ( const VertexID r)        { return this->id > r.id; }
    VertexID& operator<<(size_t r)      { this->id = r; return *this; }
    VertexID& operator = (VertexID r)   { this->id =r.id; return *this; }
    VertexID& operator++()              { this->id++; return *this; }
    VertexID& operator--()              { this->id--; return *this; }
    bool isValid() const                { return this->id != ULLONG_MAX; }
};

struct HalfEdgeID{
    size_t id;
    HalfEdgeID( )           { id = ULONG_MAX; }
    HalfEdgeID( size_t h )  { id = h; }
    bool operator == (HalfEdgeID r)         { return this->id == r.id; }
    bool operator < (HalfEdgeID r)          { return this->id < r.id; }
    bool operator > (HalfEdgeID r)          { return this->id > r.id; }
    HalfEdgeID& operator << (size_t r)      { this->id = r; return *this; }
    HalfEdgeID& operator =  (HalfEdgeID r)  { this->id = r.id; return *this; }
    HalfEdgeID& operator ++ ()              { this->id++; return *this; }
    HalfEdgeID& operator -- ()              { this->id--; return *this; }
    bool isValid() const                    { return this->id != ULLONG_MAX; }
};
struct FaceID{
    size_t id;
    FaceID( )           { id = ULONG_MAX; }
    FaceID( size_t f )  { id = f; }
    bool operator       == (FaceID r)   { return this->id == r.id; }
    bool operator < (FaceID r)          { return this->id < r.id; }
    bool operator > (FaceID r)          { return this->id > r.id; }
    FaceID& operator    << (size_t r)   { this->id = r; return *this; }
    FaceID& operator    =  (FaceID r)   { this->id = r.id; return *this; }
    FaceID& operator    ++ ()           { this->id++; return *this; }
    FaceID& operator    -- ()           { this->id--; return *this; }
    bool isValid() const                { return this->id != ULLONG_MAX; }
};

inline bool operator < ( const VertexID l, const VertexID r)        { return l.id < r.id; }
inline bool operator < ( const HalfEdgeID l, const HalfEdgeID r)    { return l.id < r.id; }
inline bool operator < ( const FaceID l, const FaceID r)            { return l.id < r.id; }


static const VertexID InvalidVertexID(       ULLONG_MAX );
static const HalfEdgeID InvalidHalfEdgeID(   ULLONG_MAX );
static const FaceID InvalidFaceID(           ULLONG_MAX );

enum class Polygon : char{
    Triangle = 'T', Quad = 'Q', Penta = 'P', Hexa = 'H',
};

enum class MeshType: char{
    TriangleMesh = 'T', QuadMesh = 'Q', QuadDominantMesh = 'D',
};

struct Vertex{
    R3::Point pos;
public :
    HalfEdgeID in = InvalidHalfEdgeID, out = InvalidHalfEdgeID;
    const R3::Point Pos() const { return pos; }
    R3::Point Pos()             { return pos; }
};

class HalfEdge{
public :
    VertexID    from = InvalidVertexID, to = InvalidVertexID;
    HalfEdgeID  next = InvalidHalfEdgeID, prev = InvalidHalfEdgeID, twin = InvalidHalfEdgeID;
    FaceID      face = InvalidFaceID;
};

struct Face{
public :
    std::vector<VertexID> verts;
    HalfEdgeID  edge;
};

}

#endif // MESH_BASE_H
