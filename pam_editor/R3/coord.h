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


    Coord operator +  ( const Coord  in ) const   { return Coord( GetX() + in.GetX(),
                                                                  GetY() + in.GetY(),
                                                                  GetZ() + in.GetZ());  }

    Coord operator -  ( const Coord  in ) const   { return Coord( GetX() - in.GetX(),
                                                                  GetY() - in.GetY(),
                                                                  GetZ() - in.GetZ());  }

    Coord operator *  ( double scale ) const   { return Coord( GetX() * scale,
                                                               GetY() * scale,
                                                               GetZ() * scale);  }

    virtual Coord operator /  ( double scale ) const   { assert( scale != 0 );
                                                 return Coord( GetX() / scale,
                                                               GetY() / scale,
                                                               GetZ() / scale);  }

    Coord& operator +=  ( const Coord  in ) { Set(  GetX() + in.GetX(),
                                                    GetY() + in.GetY(),
                                                    GetZ() + in.GetZ());
                                              return *this;
                                            }

    Coord& operator -=  ( const Coord  in ) { Set(  GetX() - in.GetX(),
                                                    GetY() - in.GetY(),
                                                    GetZ() - in.GetZ());
                                              return *this;
                                            }

    Coord& operator *=  ( double scale ) { Set( GetX() * scale,
                                                GetY() * scale,
                                                GetZ() * scale);
                                           return *this;
                                         }

    Coord operator /=  ( double scale ) { assert( scale != 0 );
                                          Set( GetX() / scale,
                                               GetY() / scale,
                                               GetZ() / scale);
                                          return *this;
                                        }

    friend std::ostream& operator<<( std::ostream& os, const Coord& in);

};


// IMPLEMENTATION
inline std::ostream& operator<<( std::ostream& os, const Coord& in ){
    return os << "[" << in.GetX() << ", " << in.GetY() << "," << in.GetZ() << "]";
}

}


#endif // COORD_H
