/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef SEGMENT_S2_H
#define SEGMENT_S2_H

#include "geometry/E3/direction_e3.h"

#include "geometry/S2/point_s2.h"
#include "geometry/S2/line_s2.h"

#include <iostream>
#include <cassert>

template<typename NT>
class Segment_S2;

template<typename NT>
ostream& operator<< (ostream& os, const Segment_S2<NT>& seg);

//----------------Segment_S2_Begin----------------
template<typename NT>
class Segment_S2
{
    Point_S2<NT> _source, _target;
    Line_S2<NT> _circle;
public:
    Segment_S2() : _source(), _target() {}
private:
    void set_circle()
    {
        Direction_E3<NT> D;
        if(_source!=_target && _source!=-_target)
            D = cross_product(
                              _source.get_Direction_E3(),
                              _target.get_Direction_E3());
        else
            if(_source==Point_S2<NT>(1,0,0) || _source==Point_S2<NT>(-1,0,0))
                D = cross_product(
                                  _source.get_Direction_E3(),
                                  Direction_E3<NT>(0,1,0));
            else
                D = cross_product(
                                  _source.get_Direction_E3(),
                                  Direction_E3<NT>(1,0,0));
        _circle = Line_S2<NT>(D);
    }
public:
    Segment_S2(
               const Point_S2<NT>& source,
               const Point_S2<NT>& target)
        : _source(source), _target(target)
    {
        set_circle();
    }
    Segment_S2(
               const Point_S2<NT>& source,
               const Point_S2<NT>& target,
               const Line_S2<NT>& circle)
        : _source(source), _target(target), _circle(circle)
    {
        assert(_circle.contains(_source) && _circle.contains(_target));
    }
//----------------Segment_S2_End----------------

    Point_S2<NT> source() const { return _source; }
    Point_S2<NT> target() const { return _target; }

    void set_source(const Point_S2<NT> & s) { _source = s; set_circle(); }
    void set_target(const Point_S2<NT> & t) { _target = t; set_circle(); }

    Line_S2<NT> get_Line_S2() const { return _circle; }

    bool operator==(const Segment_S2<NT>& s) const {
        return (this == &s) ||
            (_source == s._source && _target == s._target && _circle == s._circle);
    }

    NT getAngle() const {
        // Precondition: segment is no larger than half a circle
        // Calculate angle between the two spherical points P1 and P2.
        double angle =  acos(dot_product(_source.get_Direction_E3(),
                                         _target.get_Direction_E3()));
        return angle;
    }

    Point_S2<NT>
    get_midpoint() const {
        // Precondition: segment is shorter than half a circle
        return (_source.get_Direction_E3() + _target.get_Direction_E3());
    }
public:
    typedef NT              eNT;
    typedef Point_S2<NT> ePoint;

    friend ostream& operator<< <>(ostream& os, const Segment_S2<NT>& seg);
};

template<typename NT>
ostream&
operator<<(ostream& os, const Segment_S2<NT>& seg)
{
    return os << seg._source << " <-> " << seg._target;
}

#endif // SEGMENT_S2_H
