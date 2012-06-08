/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef DIRECTION_E3_H
#define DIRECTION_E3_H

#include <cmath>
using std::sqrt;
#include "geometry/E3/vector_e3.h"

template<typename NT>
class Direction_E3;

template<class NT>
std::ostream&
operator<<(std::ostream& os, const Direction_E3<NT>& d);

template<class NT>
std::istream&
operator>>(std::istream& is, Direction_E3<NT>& d);

template<typename NT>
class Direction_E3
{
    Vector_E3<NT> V;

    void
    normalize() {
        NT d = static_cast<NT>( sqrt( V.length2() ) );
        V = Vector_E3<NT>(V.x()/d, V.y()/d, V.z()/d);
    }

public:
    Direction_E3() : V() {}
    Direction_E3(const NT& x, const NT& y, const NT& z) : V(x,y,z) {
        normalize();
    }
    Direction_E3(const Vector_E3<NT>& V) : V(V) {
        normalize();
    }
    Direction_E3(const Point_E3<NT>& source,
                 const Point_E3<NT>& target)
    {
        V = target - source;
        normalize();
    }

    NT x() const { return V.x(); }
    NT y() const { return V.y(); }
    NT z() const { return V.z(); }

    Vector_E3<NT> getVector_E3() const { return V; }

    Direction_E3 operator-() const { return Direction_E3(-V); }

    Direction_E3<NT> operator+(const Direction_E3<NT>& D2)
    {
        return Direction_E3<NT>(V + D2.V);
    }

    bool operator==(const Direction_E3<NT>& d) const {
        return (V == d.V);
    }

    template<class S>
    friend std::ostream&
    operator<<(std::ostream& os, const Direction_E3<S>& d);

    template<class S>
    friend std::istream&
    operator>>(std::istream& is, Direction_E3<S>& d);
};

template<class S>
std::ostream&
operator<<(std::ostream& os, const Direction_E3<S>& d)
{
    return os << d.V;
}

template<class S>
std::istream&
operator>>(std::istream& is, Direction_E3<S>& d)
{
    return is >> d.V;
}

template<typename NT>
Vector_E3<NT>
operator*(const Direction_E3<NT> D, const NT& k)
{
    return Vector_E3<NT>(D.x()*k, D.y()*k, D.z()*k);
}

template<class NT>
NT
dot_product(const Direction_E3<NT>& d1, const Direction_E3<NT>& d2)
{
    return dot_product(d1.getVector_E3(), d2.getVector_E3());
}

template<class NT>
Direction_E3<NT>
cross_product(const Direction_E3<NT>& v1, const Direction_E3<NT>& v2)
{
    return Direction_E3<NT>(+ determinant(v1.y(), v2.y(), v1.z(), v2.z()),
                            - determinant(v1.x(), v2.x(), v1.z(), v2.z()),
                            + determinant(v1.x(), v2.x(), v1.y(), v2.y()));
}

#endif // DIRECTION_E3_H
