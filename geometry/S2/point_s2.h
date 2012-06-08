/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef POINT_S2_H
#define POINT_S2_H

#include <iostream>
using std::ostream;
using std::istream;

#include "geometry/E3/direction_e3.h"
#include "geometry/misc/determinant.h"

#include <cmath>

template<typename NT>
class Point_S2;

template<typename NT>
ostream& operator<< (ostream& os, const Point_S2<NT>& p);

//----------------Point_S2_Begin----------------
template<typename NT>
class Point_S2
{
    NT _x, _y, _z;
public:
    typedef NT NumberType;
    typedef NT number_type;
    typedef Point_S2<NT> value_type;

    Point_S2() : _x(1), _y(0), _z(0) {}
    Point_S2(const NT& x, const NT& y, const NT& z) : _x(x), _y(y), _z(z) {}
    Point_S2(const Direction_E3<NT>& D) : _x(D.x()), _y(D.y()), _z(D.z()) {}
    Point_S2(const Point_E3<NT>& source, const Point_E3<NT>& target)
        : _x(target.x() - source.x()),
          _y(target.y() - source.y()),
          _z(target.z() - source.z())
    {}

    Direction_E3<NT> get_Direction_E3() const {
        return Direction_E3<NT>(_x,_y,_z);
    }

    NT x() const { return _x; }
    NT y() const { return _y; }
    NT z() const { return _z; }

    const Point_S2<NT> antipode() const { return Point_S2(-_x, -_y, -_z); }

    Point_S2 operator-() const { return antipode(); }
//----------------Point_S2_End----------------

//----------------Point_S2_Equality_Begin----------------
    bool operator==(const Point_S2<NT>& p) const {
        return (this == &p) ||
            ( are_dependent(_x, _y, _z,  p._x, p._y, p._z) &&
              inner_product(_x, _y, _z, p._x, p._y, p._z) > 0 );
    }
//----------------Point_S2_Equality_End----------------
    bool operator!=(const Point_S2<NT>& p) const { return !operator==(p); }

    // to align a cylinder with this spherical point, we rotate by
    // -getXangle() followed by -getZangle(). gluCylinder is
    // originally aligned with the Z-axis.

    NT getXangle() const
    {
        //            Z     .
        //            |    /
        //            |   / |
        //            |  /  |
        //            | /   |
        //            |/    |    
        //             ---------- Y
        //           /\     |
        //          /  \    |
        //         /    \   |
        //        /      \  |
        //       /     pL \ |
        //      X           .

        double projlength = sqrt(_x * _x + _y * _y);
        double Xangle = atan2(projlength, _z);
        return 180.0 / M_PI * Xangle;
    }

    NT getZangle() const
    {
        double Zangle = atan2(_x, _y);
        return 180.0 / M_PI * Zangle;
    }

    friend ostream& operator<< <>(ostream& os, const Point_S2<NT>& p);
};

template<typename NT>
ostream&
operator<<(ostream& os, const Point_S2<NT>& p) {
    return os << p._x << " , " << p._y << " , " << p._z;
}

template<typename NT>
Point_S2<NT>
operator*(const Point_S2<NT> p, const NT& d)
{
    return Point_S2<NT>(p.x()*d, p.y()*d, p.z()*d);
}

template<typename NT>
Point_S2<NT>
operator+(const Point_S2<NT>& p1, const Point_S2<NT>& p2)
{
    return Point_S2<NT>(p1.x()+p2.x(), p1.y()+p2.y(), p1.z()+p2.z());
}

template<typename NT>
NT
inner_product(const Point_S2<NT>& p1, const Point_S2<NT>& p2)
{
    return inner_product(p1.x(), p1.y(), p1.z(), p2.x(), p2.y(), p2.z());
}

#endif // POINT_S2_H
