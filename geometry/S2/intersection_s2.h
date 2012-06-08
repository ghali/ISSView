#ifndef INTERSECTION_S2_H
#define INTERSECTION_S2_H

#include "geometry/misc/determinant.h"

#include "geometry/S2/point_s2.h"
#include "geometry/S2/line_s2.h"
#include "geometry/S2/segment_s2.h"
#include "geometry/S2/predicates_s2.h"
//#include "geometry/S2/projection_s2.h"

#include <iostream>

template<typename NT>
class Point_S2;

template<typename NT>
class Segment_S2;

template<typename NT>
class Line_S2;

//----------------------------------------------------------------
template<typename NT>
Point_S2<NT>
intersection(const Line_S2<NT> & l1, const Line_S2<NT> & l2)
// precondition: lines are distinct
{
    NT detx = + determinant(l1.y(), l1.z(), l2.y(), l2.z());
    NT dety = - determinant(l1.x(), l1.z(), l2.x(), l2.z());
    NT detw = + determinant(l1.x(), l1.y(), l2.x(), l2.y());

    return Point_S2<NT>( detx, dety, detw);
    // return Point_S2<NT>(-detx, -dety, -detw);

    //----------------------------------------------------------------
    // According to:
    //    /Users/me/ghali/gcb/tex/book1/chaps/code-solution/geometry/S2/intersection_s2.h
    // we should return the antipode.
    // We negate because we use clockwise spherical polygons.
    // //     return Point_S2<NT>(- detx, - dety, - detz);



    // NT denom = determinant(l1.x(), l1.y(), l2.x(), l2.y());
    // assert(denom != 0);
    // 
    // NT detx = + determinant(l1.y(), l1.z(), l2.y(), l2.z());
    // NT dety = - determinant(l1.x(), l1.z(), l2.x(), l2.z());
    // 
    // return Point_S2<NT>(detx/denom, dety/denom);
}

//----------------------------------------------------------------
template<typename NT>
Point_S2<NT>
intersection(const Line_S2<NT> & l1, const Segment_S2<NT> & seg2)
// precondition: segment does not lie on line.
{
    const Line_S2<NT> l2 = Line_S2<NT>(seg2.source(), seg2.target());
    return intersection(l1, l2);
}

//----------------------------------------------------------------
template<typename NT>
Point_S2<NT>
intersection_of_lines(const Line_S2<NT> & l1, const Line_S2<NT> & l2)
// precondition: circles are not parallel
{
    return intersection(l1, l2);
}

//----------------------------------------------------------------
// The following function is used by Point_Polytope_Splitter_by_Segment.
// 
template<typename NT>
Point_S2<NT>
intersection_of_lines(const Segment_S2<NT> & seg1, const Segment_S2<NT> & seg2)
{
    Line_S2<NT> l1(seg1.source(), seg1.target());
    Line_S2<NT> l2(seg2.source(), seg2.target());


    const Point_S2<NT> p = intersection(l1, l2);
    const Point_S2<NT> s = seg1.source();
    const Point_S2<NT> t = seg1.target();

    NT dp1 = inner_product(p.x(),p.y(),p.z(), s.x(),s.y(),s.z() );
    NT dp2 = inner_product(p.x(),p.y(),p.z(), t.x(),t.y(),t.z() );

    const Direction_E3<NT> direc = p.get_Direction_E3();
    const Point_S2<NT> normalized_p(direc);

    if(dp1 > 0 && dp2 > 0)
        return normalized_p;
    else
        return -normalized_p;
}

#endif // INTERSECTION_S2_H
