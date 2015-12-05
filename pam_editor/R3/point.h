#ifndef POINT_H
#define POINT_H

#include "coord.h"

/**
 * @file point.h
 * @author Francesco Usai (fr.usai1@gmail.com)
 * @brief Simple point in R3
 */

namespace R3{

class Point : public Coord{

public :
    Point( const Coord& coordinates ) { Set( coordinates.GetX(), coordinates.GetY(), coordinates.GetZ() ); }
    Point( double x=0.0, double y=0.0, double z=0.0) : Coord( x, y, z ) {}

    double DistanceSquared( const Point& in )   { return ( this->coord - in.coord).squaredNorm(); }
    double Distance( const Point& in )          { return sqrt(this->DistanceSquared( in )); }

    static Point  MidPoint( const Point& left, const Point& right )
                                                { return Point(( left.GetX() + right.GetX())  / 2.0,
                                                               ( left.GetY() + right.GetY()) / 2.0,
                                                               ( left.GetZ() + right.GetZ()) / 2.0 );}

};
}
// IMPLEMENTATION

#endif // POINT_H
