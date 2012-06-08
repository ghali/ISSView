// geometry_s2.h

#ifndef GEOMETRY_S2_H
#define GEOMETRY_S2_H

#include "geometry/S2/point_s2.h"
#include "geometry/S2/line_s2.h"
#include "geometry/S2/segment_s2.h"
#include "geometry/S2/point_polygon_s2.h"
#include "geometry/S2/line_polygon_s2.h"
#include "geometry/S2/sub_hyperplane_s2.h"
#include "geometry/S2/transformation_s2.h"

template<typename NT>
struct Geometry_S2
{
    typedef NT NumberType;      // todo: delete this line.
    typedef NT Number_Type;

    typedef Point_S2<NT>           Point;
    typedef Line_S2<NT>            Hyperplane;
    typedef Segment_S2<NT>         Segment;

    typedef Line_S2<NT>            Line; // for convenience

    typedef Point_Polygon_S2<NT>   Point_Polygon; // more convenient in non-dimension-free code
    typedef Point_Polygon_S2<NT>   Point_Polytope;

    // We provide two aliases. Line_Polygon improves readability in systems restricted to dimension 2.
    // Hyperplane_Polytope is necessary for dimension-free code (such as BSP) to be meaningful.
    typedef Line_Polygon_S2<NT>    Line_Polygon;
    typedef Line_Polygon_S2<NT>    Hyperplane_Polytope;

    typedef Sub_hyperplane_S2<NT>  Sub_hyperplane;

    typedef Transformation_S2<NT>  Transformation;
};

#endif // GEOMETRY_S2_H
