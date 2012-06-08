/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef INTERPOLATION_S2_H
#define INTERPOLATION_S2_H

#include "geometry/S2/transformation_s2.h"

template<typename NT>
Point_S2<NT>
interpolate(const Point_S2<NT>& P1, const Point_S2<NT>& P2, const NT& u)
{
    if(P1 == P2)
        return P1;
    else {
        NT costheta = dot_product(P1.get_Direction_E3(), P2.get_Direction_E3());
        NT theta = std::acos(costheta);
        NT sintheta = std::sin(theta);
        Vector_E3<NT> v1 = Vector_E3<NT>(P1.x(), P1.y(), P1.z()) * (std::sin((1-u) * theta) / sintheta);
        Vector_E3<NT> v2 = Vector_E3<NT>(P2.x(), P2.y(), P2.z()) * (std::sin(u * theta)     / sintheta);
        Point_S2<NT> ret = Direction_E3<NT>(v1 + v2);
        return ret;
    }
}

template<typename NT>
Point_S2<NT>
slerp(const Point_S2<NT>& P1, const Point_S2<NT>& P2, const NT& u)
{
    return interpolate( P1, P2, u );
}

template<typename NT>
Transformation_S2<NT>
slerp(const Transformation_S2<NT>& R1, Transformation_S2<NT>& R2, const NT& u)
{
    if(R1 == R2)
        return R1;
    else {
        NT costheta = dot_product(R1.unitq(), R2.unitq());
        NT theta = std::acos(costheta);
        NT sintheta = std::sin(theta);
        Quaternion<NT> retq = R1.unitq() * (std::sin((1-u) * theta) / sintheta)
            +                 R2.unitq() * (std::sin(u * theta)     / sintheta);

        return Transformation_S2<NT>(retq);
    }
}

template<typename NT>
Transformation_S2<NT>
lerp(const Transformation_S2<NT>& R1, Transformation_S2<NT>& R2, const NT& t)
{
    Quaternion<NT> Q1 = R1.unitq();
    Quaternion<NT> Q2 = R2.unitq();

    NT unity(static_cast<NT>(1));
    NT r = Q1.r()  * (unity-t) + Q2.r()  * t;
    NT x = Q1.vi() * (unity-t) + Q2.vi() * t;
    NT y = Q1.vj() * (unity-t) + Q2.vj() * t;
    NT z = Q1.vj() * (unity-t) + Q2.vk() * t;
    return Transformation_S2<NT>(r, Direction_E3<NT>(x, y, z));
}

#endif // INTERPOLATION_S2_H
