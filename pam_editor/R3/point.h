#ifndef POINT_H
#define POINT_H

#include "coord.h"
#include "vec3d.h"

/**
 * @file point.h
 * @author Francesco Usai (fr.usai1@gmail.com)
 * @brief Simple point in R3
 */

namespace R3{

class Point{
private:
    Coord coord;

public :
    Point( const Coord& coordinates ) { coord = coordinates; }
    Point( double x, double y, double z) { coord = Coord( x, y, z ); }
    Point( ){ Coord( 0.0, 0.0, 0.0 ); }

    double DistanceSquared( const Point& in ) const  { return ( this->coord.getCoord() - in.coord.getCoord()).squaredNorm(); }
    double Distance( const Point& in )        const  { return sqrt(this->DistanceSquared( in )); }

    static Point  MidPoint( const Point& left, const Point& right ) {
        return Point(( left.coord.GetX() + right.coord.GetX()) / 2.0,
                     ( left.coord.GetY() + right.coord.GetY()) / 2.0,
                     ( left.coord.GetZ() + right.coord.GetZ()) / 2.0 );}

    Point operator +  ( const Point  in ) const   {  return Point( this->coord + in.coord ); }
    Vec3d operator -  ( const Point  in ) const   {  return Vec3d( this->coord - in.coord ); }
    Point operator *  ( double  scale ) const     {  return Point( this->coord * scale );    }
    Point operator /  ( double  scale ) const     {  assert( scale != 0 );  return Point( this->coord / scale );    }

    Point& operator +=  ( const Point  in ) { this->coord = this->coord + in.coord; return *this; }

    void Set( double x, double y, double z ){ coord.Set(x, y, z); }
    void SetX( double x ){ coord.SetX( x ); }
    void SetY( double y ){ coord.SetX( y ); }
    void SetZ( double z ){ coord.SetX( z ); }

    double GetX() const { return coord.GetX(); }
    double GetY() const { return coord.GetY(); }
    double GetZ() const { return coord.GetZ(); }
};



}
// IMPLEMENTATION

#endif // POINT_H
