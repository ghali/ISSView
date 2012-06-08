/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef VECTOR_E3_H
#define VECTOR_E3_H

#include <iostream>
#include <cmath>

#include "geometry/E3/point_e3.h"
#include "geometry/misc/determinant.h"

template<typename NT>
class Vector_E3
{
    NT _x, _y, _z;

public:
    Vector_E3() : _x(),_y(),_z()  {}

    Vector_E3(const NT& x, const NT& y, const NT& z) :_x(x),_y(y),_z(z)     {}

    Vector_E3(Point_E3<NT> & source, Point_E3<NT> & target);

    NT x() const { return _x; }
    NT y() const { return _y; }
    NT z() const { return _z; }

    NT length2() const {
        return _x*_x + _y*_y + _z*_z;
    }
    void rotateY(double d)
    {
        double c = cos(d);
        double s = sin(d);
        double nx =   _x * c + _z * s;
        double nz = - _x * s + _z * c;
        _x = nx;
        _z = nz;
    }

    bool operator==(const Vector_E3<NT>& v) const
    {
        return (_x == v._x && _y == v._y && _z == v._z);
    }

    Vector_E3<NT>
    operator-() const
    {
        return Vector_E3(-_x, -_y, -_z);
    }

    template<class S>
    friend std::ostream&
    operator<<(std::ostream& os, const Vector_E3<S>& v);
};

template<typename NT>
Vector_E3<NT>
operator*(const Vector_E3<NT> v, const NT& d)
{
    return Vector_E3<NT>(v.x()*d, v.y()*d, v.z()*d);
}

template<typename NT>
Vector_E3<NT>
operator/(const Vector_E3<NT> v, const NT& d)
{
    return Vector_E3<NT>(v.x()/d, v.y()/d, v.z()/d);
}

template<typename NT>
Vector_E3<NT>
operator+(const Vector_E3<NT>& v1, const Vector_E3<NT>& v2)
{
    return Vector_E3<NT>(v1.x()+v2.x(), v1.y()+v2.y(), v1.z()+v2.z());
}

template<typename NT>
Vector_E3<NT>
operator-(const Vector_E3<NT>& v1, const Vector_E3<NT>& v2)
{
    return Vector_E3<NT>(v1.x()-v2.x(), v1.y()-v2.y(), v1.z()-v2.z());
}


template<typename NT>
Point_E3<NT>
operator+(const Point_E3<NT>& p, const Vector_E3<NT>&  v)
{
    return Point_E3<NT>(p.x()+v.x(), p.y()+v.y(), p.z()+v.z());
}

template<typename NT>
Point_E3<NT>
operator-(const Point_E3<NT>& p, const Vector_E3<NT>&  v)
{
    return Point_E3<NT>(p.x()-v.x(), p.y()-v.y(), p.z()-v.z());
}

template<typename NT>
Point_E3<NT>
Point_E3<NT>::operator+=(const Vector_E3<NT> & v)
{
    this->_x += v.x();
    this->_y += v.y();
    this->_z += v.z();
    return *this;
}

template<typename NT>
Point_E3<NT>
Point_E3<NT>::operator-=(const Vector_E3<NT> & v)
{
    this->_x -= v.x();
    this->_y -= v.y();
    this->_z -= v.z();
    return *this;
}

template<typename NT>
Point_E3<NT>
operator+=(const Point_E3<NT>& p, const Vector_E3<NT>&  v)
{
    return Point_E3<NT>(p.x()+v.x(), p.y()+v.y(), p.z()+v.z());
}

template<typename NT>
Vector_E3<NT>
operator-(const Point_E3<NT>& p1, const Point_E3<NT>& p2)
{
    return Vector_E3<NT>(p1.x()-p2.x(), p1.y()-p2.y(), p1.z()-p2.z());
}

template<typename NT>
Vector_E3<NT>::Vector_E3(Point_E3<NT> & source, Point_E3<NT> & target)
{
    *this = target - source;
}

template<class S>
std::ostream&
operator<<(std::ostream& os, const Vector_E3<S>& v)
{
    return os << v._x << " " << v._y << " " << v._z;
}

template<class S>
S
dot_product(const Vector_E3<S>& v1, const Vector_E3<S>& v2)
{
    return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}

template<class S>
Vector_E3<S>
cross_product(const Vector_E3<S>& v1, const Vector_E3<S>& v2)
{
    return Vector_E3<S>(+ determinant(v1.y(), v2.y(), v1.z(), v2.z()),
                        - determinant(v1.x(), v2.x(), v1.z(), v2.z()),
                        + determinant(v1.x(), v2.x(), v1.y(), v2.y()));
}

#endif // VECTOR_E3_H
