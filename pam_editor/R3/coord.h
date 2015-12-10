#ifndef COORD_H
#define COORD_H

#include <ostream>
#include <Eigen/Dense>

#define R3_EPS 0.000001

/**
 * @file coord.h
 * @author Francesco Usai (fr.usai1@gmail.com)
 * @brief Simple coordinates in R3. Relies on Eigen classes for data representation
 */

namespace R3{
class Coord{

private:
    Coord( Eigen::Vector3d eigen_vec ){ coord = eigen_vec; }

protected :
    Eigen::Vector3d coord;

public:
     Coord( double x=0.0, double y=0.0, double z=0.0) {
         Set( x, y, z );
     }

    void Set( double x=0.0, double y=0.0, double z=0.0) {
        coord(0) = x;
        coord(1) = y;
        coord(2) = z;
    }

    void SetX( double x ){ coord(0) = x; }
    void SetY( double y ){ coord(1) = y; }
    void SetZ( double z ){ coord(2) = z; }

    double GetX() const { return coord(0); }
    double GetY() const { return coord(1); }
    double GetZ() const { return coord(2); }


    Coord operator +  ( const Coord  in ) const   {  return Coord( this->coord + in.coord ); }
    Coord operator -  ( const Coord  in ) const   {  return Coord( this->coord - in.coord ); }
    Coord operator *  ( double  scale ) const     {  return Coord( this->coord * scale );    }
    Coord operator /  ( double  scale ) const     {  assert( scale != 0 );  return Coord( this->coord / scale );    }

    Coord& operator +=  ( const Coord  in ) { this->coord = this->coord + in.coord; return *this; }
    Coord& operator -=  ( const Coord  in ) { this->coord = this->coord - in.coord; return *this; }
    Coord& operator *=  ( double scale )    { this->coord = this->coord * scale; return *this; }
    Coord& operator /=  ( double scale )    { assert( scale != 0 ); this->coord = this->coord / scale; return *this; }

    friend std::ostream& operator<<( std::ostream& os, const Coord& in);
    const Eigen::Vector3d& getCoord() const { return coord; }

};


// IMPLEMENTATION
inline std::ostream& operator<<( std::ostream& os, const Coord& in ){
    return os << "[" << in.GetX() << ", " << in.GetY() << "," << in.GetZ() << "]";
}

}


#endif // COORD_H
