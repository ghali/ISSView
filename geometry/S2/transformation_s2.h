/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef TRANSFORMATION_S2_H
#define TRANSFORMATION_S2_H

#include <cmath>
#include <utility>
using std::cos; using std::sin;
#include <iostream>
using namespace std;
#include "geometry/S3/quaternion.h"

#include "geometry/E3/direction_e3.h"
#include "geometry/S2/point_s2.h"
#include "geometry/S2/point_polygon_s2.h"

template<typename NT>
class Transformation_S2;

template<typename NT>
ostream & operator<< (ostream & os, const Transformation_S2<NT> & p);

template<typename NT>
class Transformation_S2
{
    Quaternion<NT> _unitq;
public:
    Transformation_S2()
    {
        init_with_angle_and_direction(0, Direction_E3<NT>(1,0,0));
    }
    Transformation_S2(const Quaternion<NT>& q)
    {
        NT n = q.norm();
        _unitq = Quaternion<NT>(q.r()/n, q.vi()/n, q.vj()/n, q.vk()/n);
    }
    Transformation_S2(const NT& angleInRadians, const Direction_E3<NT>& axis)
    {
        init_with_angle_and_direction(angleInRadians, axis);
    }

private:
    void init_with_angle_and_direction(const NT & angleInRadians, const Direction_E3<NT> & axis)
    {
        NT c = cos(angleInRadians/2.0);
        NT s = sin(angleInRadians/2.0);
        _unitq = Quaternion<NT>(c, s * axis.x(), s * axis.y(), s * axis.z());
    }

public:
    Quaternion<NT> unitq() const { return _unitq; }

    Transformation_S2<NT> inverse() const {
        return Transformation_S2<NT>( _unitq.inverse() );
    }

    bool operator==(const Transformation_S2<NT> & T) const {
        return (this == &T) ||
            (_unitq == T._unitq);
    }

    Point_S2<NT>
    transform(const Point_S2<NT>& p) const
    {
        Quaternion<NT> pq(0, p.x(), p.y(), p.z());
        Quaternion<NT> transformedQ = _unitq * pq * _unitq.conjugate();
        // assert(transformedQ.r() == 0);
        return Point_S2<NT>(transformedQ.vi(), transformedQ.vj(), transformedQ.vk());
    }
    Line_S2<NT>
    transform(const Line_S2<NT>& l) const
    {
        Quaternion<NT> lq(0, l.x(), l.y(), l.z());
        Quaternion<NT> transformedQ = _unitq * lq * _unitq.conjugate();
        // assert(transformedQ.r() == 0);
        return Line_S2<NT>(transformedQ.vi(), transformedQ.vj(), transformedQ.vk());
    }
    Segment_S2<NT>
    transform(const Segment_S2<NT>& s) const
    {
        return Segment_S2<NT>(transform(s.source()),
                              transform(s.target()));
    }
    Point_Polygon_S2<NT>
    transform(const Point_Polygon_S2<NT>& polygon) const
    {
        Point_Polygon_S2<NT> transformed_polygon;

        typedef typename Point_Polygon_S2<NT>::Point_const_iterator It;
        for(It i = polygon.begin(); i != polygon.end(); ++i)
            transformed_polygon.push_back(transform(*i));

        return transformed_polygon;
    }

    std::pair<double,Direction_E3<NT> >
    getAngleAndAxis()
    {
        NT two(static_cast<NT>(2));
        NT a = acos(_unitq.r());
        NT s = sin(a);

        NT angle = two * a;
        Direction_E3<NT> axis( _unitq.vi() / s, _unitq.vj() / s, _unitq.vk() / s );
        return make_pair(angle, axis);
    }
    Transformation_S2<NT> operator*(const Transformation_S2<NT>& R2) const
    // R2 will be applied before *this.
    {
        return Transformation_S2<NT>( _unitq * R2._unitq );
    }

    friend ostream & operator<< <>(ostream & os, const Transformation_S2<NT> & rot);
};

template<typename NT>
ostream & operator<< (ostream & os, const Transformation_S2<NT> & rot)
{
    return os << rot._unitq;
}

#endif // TRANSFORMATION_S2_H
