#ifndef MESH_BASE_H
#define MESH_BASE_H

#include "R3/point.h"

#include <boost/serialization/strong_typedef.hpp>

#include <vector>
#include <string>

namespace Mesh{

#define SIGNED_INVALID_ID -1

/* ID's are defined as separate structs in order to be not substitutable */
BOOST_STRONG_TYPEDEF(u_long, VertexID)
BOOST_STRONG_TYPEDEF(u_long, HalfEdgeID)
BOOST_STRONG_TYPEDEF(u_long, FaceID)

static const VertexID InvalidVertexID(       ULLONG_MAX );
static const HalfEdgeID InvalidHalfEdgeID(   ULLONG_MAX );
static const FaceID InvalidFaceID(           ULLONG_MAX );

inline bool isValid( VertexID id)   { return id != InvalidVertexID; }
inline bool isValid( HalfEdgeID id) { return id != InvalidHalfEdgeID; }
inline bool isValid( FaceID id)     { return id != InvalidFaceID; }

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
    HalfEdgeID  edge = InvalidHalfEdgeID;
};

}

#endif // MESH_BASE_H
