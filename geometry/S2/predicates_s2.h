/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef PREDICATES_S2_H
#define PREDICATES_S2_H

#include <iostream>
using namespace std;

#include "geometry/S2/point_s2.h"
#include "geometry/S2/segment_s2.h"
#include "geometry/S2/triangle_s2.h"

#include "geometry/misc/orientation.h"
#include "geometry/misc/determinant.h"

// Line-based sidedness predicate
// On which side of L3 does intersection(L1,L2) lie?
template<typename NT>
Oriented_side
oriented_side(const Line_S2<NT> & L1,
              const Line_S2<NT> & L2,
              const Line_S2<NT> & L3)
{
    std::cerr << "not quite right..." << std::endl;
    NT s = sign(determinant<NT>(L1.x(), L1.y(),
                                L2.x(), L2.y()));

    NT d = determinant<NT>(L1.x(), L1.y(), L1.z(),
                           L2.x(), L2.y(), L2.z(),
                           L3.x(), L3.y(), L3.z());

    return enum_Oriented_side(s * d);
}

//----------------S2_oriented_side_Begin----------------
template<typename NT>
Oriented_side
oriented_side(
              const Point_S2<NT>& p1,
              const Point_S2<NT>& p2,
              const Point_S2<NT>& p3)
{
    NT d = determinant(
                       p1.x(), p1.y(), p1.z(),
                       p2.x(), p2.y(), p2.z(),
                       p3.x(), p3.y(), p3.z());

    return enum_Oriented_side(d);
}
//----------------S2_oriented_side_End----------------

template<typename NT>
Oriented_side
oriented_side(
              const Line_S2<NT>& circle,
              const Point_S2<NT>& point)
{
    NT d = inner_product(circle, point);
    return enum_Oriented_side(d);
}

template<typename NT>
Oriented_side
oriented_side(
              const Segment_S2<NT>& segment,
              const Point_S2<NT>& point)
{
    NT d = inner_product(segment.get_Line_S2(), point);
    return enum_Oriented_side(d);
}

template<typename NT>
Orientation_to_circle
inside_circle(const Point_S2<NT>& p0,
              const Point_S2<NT>& p1,
              const Point_S2<NT>& p2,
              const Point_S2<NT>& p3)
{
    // Precondition: the four points must be normalized.
    NT d1 = determinant(p0.x() * p0.x() + p0.y() * p0.y() + p0.z() * p0.z(), p0.x(), p0.y(), p0.z(),
                        p1.x() * p1.x() + p1.y() * p1.y() + p1.z() * p1.z(), p1.x(), p1.y(), p1.z(),
                        p2.x() * p2.x() + p2.y() * p2.y() + p2.z() * p2.z(), p2.x(), p2.y(), p2.z(),
                        p3.x() * p3.x() + p3.y() * p3.y() + p3.z() * p3.z(), p3.x(), p3.y(), p3.z());
    NT d2 = determinant(p1.x(), p1.y(), p1.z(), 
                        p2.x(), p2.y(), p2.z(), 
                        p3.x(), p3.y(), p3.z());
    NT d = d1 * d2;

    if(d < 0)
        return INSIDE_CIRCLE;
    else if(d > 0)
        return OUTSIDE_CIRCLE;
    else
        return COCIRCULAR;
}

template<typename NT>
bool
is_inside(const Triangle_S2<NT>& T,
          const Point_S2<NT>& P)
{
    Oriented_side o1 = oriented_side(T.P0(), T.P1(), P);
    Oriented_side o2 = oriented_side(T.P1(), T.P2(), P);
    Oriented_side o3 = oriented_side(T.P2(), T.P0(), P);

    return
        o1 != ON_NEGATIVE_SIDE &&
        o2 != ON_NEGATIVE_SIDE &&
        o3 != ON_NEGATIVE_SIDE;
}

#endif // PREDICATES_S2_H
