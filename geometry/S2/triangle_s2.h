/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef TRIANGLE_S2_H
#define TRIANGLE_S2_H

#include <vector>
using std::vector;

#include "geometry/E3/point_e3.h"
#include "geometry/S2/point_s2.h"
#include "geometry/S2/segment_s2.h"

template<typename NT>
class Triangle_S2
{
    Point_S2<NT> p0;
    Point_S2<NT> p1;
    Point_S2<NT> p2;

public:
    Triangle_S2() {}

    Triangle_S2(const Point_E3<NT>& p0,
                const Point_E3<NT>& p1,
                const Point_E3<NT>& p2)
        : p0(p0), p1(p1), p2(p2)
    {}

    Triangle_S2(const Point_S2<NT>& p0,
                const Point_S2<NT>& p1,
                const Point_S2<NT>& p2)
        : p0(p0), p1(p1), p2(p2)
    {}

    Point_S2<NT> P0() const { return p0; }
    Point_S2<NT> P1() const { return p1; }
    Point_S2<NT> P2() const { return p2; }

    vector<Triangle_S2<NT> > get_recursive_subdivision() const
    {
        Segment_S2<NT> s01(p0,p1);
        Segment_S2<NT> s12(p1,p2);
        Segment_S2<NT> s20(p2,p0);

        Point_S2<NT> p01 = s01.get_midpoint();
        Point_S2<NT> p12 = s12.get_midpoint();
        Point_S2<NT> p20 = s20.get_midpoint();

        vector<Triangle_S2<NT> > V;
        V.push_back(Triangle_S2<NT>( p0, p01, p20));
        V.push_back(Triangle_S2<NT>( p1, p12, p01));
        V.push_back(Triangle_S2<NT>( p2, p20, p12));
        V.push_back(Triangle_S2<NT>(p01, p12, p20));

        return V;
    }
};

#endif // TRIANGLE_S2_H
