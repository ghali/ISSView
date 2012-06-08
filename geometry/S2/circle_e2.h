/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef CIRCLE_E2_H
#define CIRCLE_E2_H

#include "geometry/E2/point_e2.h"
#include "geometry/misc/determinant.h"

#include <iostream>
using std::ostream;
using std::istream;
using std::cout;
using std::endl;

template<typename NT>
class Circle_E2;

template<typename NT>
ostream & operator<< (ostream & os, const Circle_E2<NT> & C);

template<typename NT>
istream & operator>> (istream & is, Circle_E2<NT> & C);

template<typename NT>
class Circle_E2
{
private:
    Point_E2<NT> _center;
    NT _radius;
public:
    Circle_E2() : _center(NT(0),NT(0)), _radius(NT(1)) {}

    Circle_E2(const Point_E2<NT> & center, const NT & radius)
        : _center(center), _radius(radius)
    {}

    Circle_E2(const Point_E2<NT> & p1,
              const Point_E2<NT> & p2,
              const Point_E2<NT> & p3)
    {
        const NT p1s = p1.x() * p1.x() + p1.y() * p1.y();
        const NT p2s = p2.x() * p2.x() + p2.y() * p2.y();
        const NT p3s = p3.x() * p3.x() + p3.y() * p3.y();

        const NT A = determinant<NT>(p1.x(), p1.y(), 1,
                                     p2.x(), p2.y(), 1,
                                     p3.x(), p3.y(), 1);
        const NT B = - determinant<NT>(p1s, p1.y(), 1,
                                       p2s, p2.y(), 1,
                                       p3s, p3.y(), 1);
        const NT C = determinant<NT>(p1s, p1.x(), 1,
                                     p2s, p2.x(), 1,
                                     p3s, p3.x(), 1);
        const NT D = - determinant<NT>(p1s, p1.x(), p1.y(),
                                       p2s, p2.x(), p2.y(),
                                       p3s, p3.x(), p3.y());

        const NT xc = B / -2.0 / A;
        const NT yc = C / -2.0 / A;
        _center = Point_E2<NT>(xc, yc);

        const NT r2 = (B * B + C * C) / 4.0 / A / A  -  D / A;
        if(r2 > 0.0)
            _radius = sqrt(r2);
        else
            _radius = sqrt(-r2);
    }

    Circle_E2<NT>& operator=(const Circle_E2<NT>& rs)
    {
        if(this != &rs) {
            _center = rs._center;
            _radius = rs._radius;
        }
        return *this;
    }

    Point_E2<NT> center() const { return _center; }
    NT radius() const { return _radius; }

    bool operator==(const Circle_E2<NT> & c) const {
        return (this == &c) ||
            (_center == c._center) && (_radius == c._radius);
    }

    bool operator!=(const Circle_E2<NT> & c) const {
        return ! operator==(c);
    }

    friend ostream & operator<< <>(ostream& os, const Circle_E2<NT>& C);

    friend istream & operator>> <>(istream& is, Circle_E2<NT>& C);
};

template<typename NT>
ostream& operator<< (ostream& os, const Circle_E2<NT>& C)
{
    return os << C._center << "  " << C._radius;
}

template<typename NT>
istream& operator>> (istream& is, Circle_E2<NT>& C)
{
    return is >> C._center >> C._radius;
}

#endif // CIRCLE_E2_H
