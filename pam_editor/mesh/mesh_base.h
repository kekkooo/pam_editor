#ifndef MESH_BASE_H
#define MESH_BASE_H

#include "R3/point.h"
#include <vector>
#include <string>

namespace Mesh{

struct VertexID     { size_t id; bool operator == (VertexID r)  { return this->id == r.id; } };
struct HalfEdgeID   { size_t id; bool operator == (HalfEdgeID r){ return this->id == r.id; } };
struct FaceID       { size_t id; bool operator == (FaceID r)    { return this->id == r.id; } };

enum class Polygon : char{
    Triangle = 'T', Quad = 'Q', Penta = 'P', Hexa = 'H',
};

struct Vertex{
    R3::Point pos;
public :
    HalfEdgeID in, out;
    const R3::Point Pos() const { return pos; }
    R3::Point Pos()             { return pos; }
};

class HalfEdge{
public :
    VertexID    from, to;
    HalfEdgeID  next, prev, twin;
    FaceID      face;
};

struct Face{
public :
    std::vector<VertexID> verts;
    HalfEdgeID  edge;
};

}

#endif // MESH_BASE_H
