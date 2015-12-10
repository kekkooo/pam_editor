#ifndef VEC3D_H
#define VEC3D_H

#include "coord.h"

/**
 * @file vec3d.h
 * @author Francesco Usai (fr.usai1@gmail.com)
 * @brief Simple vector in R3
 */

namespace R3{

class Vec3d : public Coord{

public :
    Vec3d( double x=0.0, double y=0.0, double z=0.0) : Coord( x, y, z ) {}
    Vec3d( const Coord& coordinates ) { Set( coordinates.GetX(), coordinates.GetY(), coordinates.GetZ() ); }    

    double    LengthSquared()       const   { return this->coord.squaredNorm();     }
    double    Length()              const   { return sqrt( this->LengthSquared());  }
    double    Normalize()                   { double len = Length(); this->coord /=len; return len; }

    Vec3d     Normalized()          const   { double len = this->Length();
                                              return *this / len; }
    double    Dot(const Vec3d in)   const   { return this->coord.dot(in.coord); }


    Vec3d     Cross(const Vec3d in) const   { auto temp = this->coord.cross(in.coord);
                                              return Vec3d( temp(0), temp(1), temp(2) );  }

    bool Parallel( const Vec3d in ) const { return fabs( 1.0 - fabs( this->Dot( in ))) < R3_EPS; }
    bool Opposite( const Vec3d in ) const { return fabs( 1.0 + this->Dot( in )) < R3_EPS; }
    bool ParallelAndOpposite( const Vec3d in ) const
                                          { double dot = this->Dot( in );
                                            return (fabs( 1.0 - fabs(dot) ) < R3_EPS)&&(( 1.0 + dot ) < R3_EPS );
                                          }    

/* STATIC */
    static double Angle ( const Vec3d &left, const Vec3d &right )
                                            { double cos = left.Normalized().Dot( right.Normalized( ));
                                              return acos( cos ); }



};
}

#endif // VEC3D_H
