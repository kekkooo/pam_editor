#ifndef BSPHERE_H
#define BSPHERE_H

#include <R3/coord.h>
#include <R3/point.h>
#include <R3/vec3d.h>
#include "BBox.h"

namespace Mesh
{

class BSphere{
private:
    BBox b;
public:

    BSphere() {  }

    void Set( const  std::vector< R3::Point > &points ){
        b.Set(points);
    }
    void Set( const  std::vector< const R3::Point* > &points ){
        b.Set(points);
    }

    void Reset(){
        b.Reset();
    }

    inline double       Radius()  const { return b.Diagonal()/2.0; }
    inline R3::Point    Center()  const { return b.Center();  }
    BBox operator +  (const BBox  in) const
    {
        BBox b_new;
        vector< R3::Point> ps;
        ps.push_back( b.Min() );
        ps.push_back( b.Max() );
        ps.push_back( in.Min());
        ps.push_back( in.Max());
        b_new.Set( ps );
        return b_new;
    }

    R3::Point Min() const { return this->min; }
    R3::Point Max() const { return this->min; }
};

}


#endif // BSPHERE_H
