#ifndef BBOX_H
#define BBOX_H

#include <R3/coord.h>
#include <R3/point.h>
#include <R3/vec3d.h>

namespace Mesh
{

class BBox{
private:
    R3::Point min, max;
public:

    BBox() { min.Set( std::numeric_limits<double>::max(), numeric_limits<double>::max(), numeric_limits<double>::max() ); }

    void Set( const  std::vector< R3::Point > &points ){
        for ( const R3::Point& p : points)
        {
            if( p.GetX() < min.GetX() ) min.SetX( p.GetX());
            if( p.GetY() < min.GetY() ) min.SetY( p.GetY());
            if( p.GetZ() < min.GetZ() ) min.SetZ( p.GetZ());

            if( p.GetX() > max.GetX() ) max.SetX( p.GetX() );
            if( p.GetY() > max.GetY() ) max.SetY( p.GetY() );
            if( p.GetZ() > max.GetZ() ) max.SetZ( p.GetZ() );
        }
    }

    void Set( const  std::vector< const R3::Point* > &points ){
        for ( const R3::Point* p : points){
            if( p->GetX() < min.GetX() ) min.SetX( p->GetX());
            if( p->GetY() < min.GetY() ) min.SetY( p->GetY());
            if( p->GetZ() < min.GetZ() ) min.SetZ( p->GetZ());

            if( p->GetX() > max.GetX() ) max.SetX( p->GetX() );
            if( p->GetY() > max.GetY() ) max.SetY( p->GetY() );
            if( p->GetZ() > max.GetZ() ) max.SetZ( p->GetZ() );
        }
    }

    void Reset(){
        min = R3::Point();
        max = R3::Point();
    }

    inline double       Diagonal()  const { return min.Distance( max ); }
    inline R3::Point    Center()    const { return R3::Point::MidPoint( min, max );  }
    BBox operator +  (const BBox  in) const{
        BBox b_new;
        vector< R3::Point> ps;
        ps.push_back( this->min );
        ps.push_back( this->max );
        ps.push_back( in.min );
        ps.push_back( in.max );
        b_new.Set( ps );
        return b_new;
    }

    R3::Point Min() const { return this->min; }
    R3::Point Max() const { return this->min; }
};

}

#endif // BBOX_H
