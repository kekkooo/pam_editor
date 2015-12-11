#ifndef DRAWABLE_H
#define DRAWABLE_H

namespace Mesh{

//enum DrawMode : int{
//  FLAT = 0x01, SMOOTH = 0x02, WIREFRAME = 0x04, POINTS = 0x08,
//  TRANSPARENT = 0x10, SOLID = 0x20,
//};

struct DrawMode{
private :
    bool flat        = false;
    bool smooth      = true;
    bool wireFrame   = true;
    bool points      = false;
    bool transparent = false;
    bool solid       = true;
    bool highLight   = true;
    bool faceColor   = true;
    bool vertexColor = true;
    bool edgeColor   = true;
public :
    void SetFlat(){           flat = true; smooth = false; }
    void SetSmooth(){         flat = false;  smooth = true; }
    void SetSolid(){          solid = true; transparent = false; }
    void SetTransparent(){    solid = false; transparent = true; }
    void SetPoints(){         points = true; }
    void SetWireframe(        bool set = true) {  wireFrame     = set; }
    void SetFaceColor(        bool set = true) {  faceColor     = set; }
    void SetVertexColor(      bool set = true) {  vertexColor   = set; }
    void SetEdgeColor(        bool set = true) {  edgeColor     = set; }
};

class Drawable{
protected:
    bool isVisible = true;
public:
    virtual void Draw() const = 0;
    virtual void SetVisibility( bool visibility ) { isVisible = visibility; }
    virtual bool IsVisible() const { return isVisible; }

    /* ATTRIBUTES */
    DrawMode draw_mode;
};

}

#endif // DRAWABLE_H
