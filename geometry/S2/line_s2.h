/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef LINE_S2_H
#define LINE_S2_H

#include "geometry/S2/point_s2.h"

#include "geometry/E3/dominant_e3.h"

template<typename NT>
class Line_S2;

template<typename NT>
std::ostream & operator<< (std::ostream & os, const Line_S2<NT> & l);

//----------------Line_S2_Begin----------------
template<typename NT>
class Line_S2
{
    NT _x, _y, _z;
public:
    Line_S2() : _x(1), _y(0), _z(0) {}
    Line_S2(const NT& x, const NT& y, const NT& z) : _x(x), _y(y), _z(z) {}
//----------------Line_S2_End----------------
    explicit Line_S2(const Point_S2<NT>& p) : _x(p.x()), _y(p.y()), _z(p.z()) {}

//----------------S2_Circle_from_points_Begin----------------
    Line_S2(const Point_S2<NT>& p1, const Point_S2<NT>& p2)
    {
        cross_product(
                      p1.x(), p1.y(), p1.z(),
                      p2.x(), p2.y(), p2.z(),
                      _x, _y, _z);
    }
//----------------S2_Circle_from_points_End----------------

#if 0
    Line_S2(const Segment_S2<NT>& seg)
    {
        cross_product(
                      seg.source().x(), seg.source().y(), seg.source().z(),
                      seg.target().x(), seg.target().y(), seg.target().z(),
                      _x, _y, _z);
    }
#endif

    NT x() const { return _x; }
    NT y() const { return _y; }
    NT z() const { return _z; }

    bool is_valid() const {
        return ( _x != NT(0) ) || ( _y != NT(0) ) || ( _z != NT(0) );
    }

    Line_S2 get_reverse_orientation() const {
        return Line_S2( -_x, -_y, -_z );
    }

    Line_S2<NT>& operator=(const Line_S2<NT>& rs)
    {
        if(this != &rs) {
            _x = rs._x;
            _y = rs._y;
            _z = rs._z;
        }
        return *this;
    }

    bool operator==(const Line_S2<NT>& L) const {
	std::cerr << "confirm/test" << std::endl;
        return (this == &L) ||
            are_dependent(_x, _y, _z, L._x, L._y, L._z) &&
            inner_product(_x, _y, _z, L._x, L._y, L._z) > 0;
    }

    bool operator!=(const Line_S2<NT>& L) const {
        return ! operator==(L);
    }

    Point_S2<NT> get_Point_S2() const { return Point_S2<NT>(_x, _y, _z); }

//----------------Line_S2_base1_Begin----------------
    Point_S2<NT> base1() const {
        Dominant_E3 least_dom = least_dominant(_x, _y, _z);
        Vector_E3<NT> least = get_Vector_E3<NT>(least_dom);

        Vector_E3<NT> b1 = cross_product(least, Vector_E3<NT>(_x,_y,_z));
        return Point_S2<NT>(b1.x(), b1.y(), b1.z());
    }
//----------------Line_S2_base1_End----------------

//----------------Line_S2_base2_Begin----------------
    Point_S2<NT> base2() const {
        NT b2x,b2y,b2z;
        Point_S2<NT> b1 = base1();
        cross_product(_x,_y,_z, b1.x(), b1.y(), b1.z(), b2x, b2y, b2z);
        return Point_S2<NT>(b2x, b2y, b2z);
    }
//----------------Line_S2_base2_End----------------

//----------------S2_incidence_Begin----------------
    bool contains(const Point_S2<NT>& p)
    {
        return (dot_product(_x,_y,_z, p.x(),p.y(),p.z()) == 0);
    }
//----------------S2_incidence_End----------------

    std::pair<Point_S2<NT>, Point_S2<NT> >
    get_two_points() const
    {
        return std::make_pair(base1(), base2());
    }

    friend std::ostream & operator<< <>(std::ostream & os, const Line_S2<NT> & l);
};


template<typename NT>
std::ostream &
operator<<(std::ostream & os, const Line_S2<NT> & p) {
    return os << p._x << " , " << p._y << " , " << p._z;
}

template<typename NT>
NT
inner_product(const Line_S2<NT>& c, const Point_S2<NT>& p)
{
    return inner_product(c.x(), c.y(), c.z(),  p.x(), p.y(), p.z());
}

#endif // LINE_S2_H
