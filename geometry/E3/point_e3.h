/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef POINT_E3_H
#define POINT_E3_H

#include <iostream>

template<typename NT>
class Point_E3;
template<typename NT>
class Vector_E3;
template<typename NT>
class Point_T3;

template<class S>
std::ostream&
operator<<(std::ostream& os, const Point_E3<S>& p);

template<class S>
std::istream&
operator>>(std::istream& is, Point_E3<S>& p);

template<typename NT>
class Point_E3
{
    NT _x, _y, _z;
public:
    typedef NT NumberType;
    typedef Point_E3<NT> value_type;
    typedef Point_T3<NT> T3_equivalent;

    Point_E3() : _x(),_y(),_z() {}
    Point_E3(const NT& x, const NT& y, const NT& z) : _x(x), _y(y), _z(z) {}

    NT x() const { return _x; }
    NT y() const { return _y; }
    NT z() const { return _z; }

    bool operator==(const Point_E3<NT>& p) const {
        return (this == &p) ||
            (_x == p.x()) && (_y == p.y()) && (_z == p.z());
    }

    bool operator!=(const Point_E3<NT>& p) const {
        return ! operator==(p);
    }

    Point_E3<NT> operator+=(const Vector_E3<NT> & v);
    Point_E3<NT> operator-=(const Vector_E3<NT> & v);

    template<class S>
    friend std::ostream&
    operator<<(std::ostream& os, const Point_E3<S>& p);

    template<class S>
    friend std::istream&
    operator>>(std::istream& is, Point_E3<S>& p);
};

template<class S>
std::ostream&
operator<<(std::ostream& os, const Point_E3<S>& p)
{
    return os << p._x << " " << p._y << " " << p._z;
}

template<class S>
std::istream&
operator>>(std::istream& is, Point_E3<S>& p)
{
    return is >> p._x >> p._y >> p._z;
}

template<typename NT>
NT
squared_distance(const Point_E3<NT>& P, const Point_E3<NT>& Q)
{
    NT x = P.x() - Q.x();
    NT y = P.y() - Q.y();
    NT z = P.z() - Q.z();
    return x*x + y*y + z*z;
}

#endif // POINT_E3_H
