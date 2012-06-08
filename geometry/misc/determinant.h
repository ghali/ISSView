/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef DETERMINANT_H
#define DETERMINANT_H

template<typename NT>
inline
NT
determinant(const NT & a, const NT & b,
            const NT & c, const NT & d)
{
    return a * d - b * c;
}

template<typename NT>
inline
NT
determinant(const NT & a, const NT & b, const NT & c,
            const NT & d, const NT & e, const NT & f,
            const NT & g, const NT & h, const NT & i)
{
    return a * determinant(e,f,h,i)
        -  b * determinant(d,f,g,i)
        +  c * determinant(d,e,g,h);
}

template<typename NT>
inline
NT
determinant(const NT & a, const NT & b, const NT & c, const NT & d,
            const NT & e, const NT & f, const NT & g, const NT & h,
            const NT & i, const NT & j, const NT & k, const NT & l,
            const NT & m, const NT & n, const NT & o, const NT & p)
{
    return a * determinant(f,g,h, j,k,l, n,o,p)
        -  b * determinant(e,g,h, i,k,l, m,o,p)
        +  c * determinant(e,f,h, i,j,l, m,n,p)
        -  d * determinant(e,f,g, i,j,k, m,n,o);
}

template<typename NT>
inline
NT
inner_product(const NT & x1, const NT & y1,
              const NT & x2, const NT & y2)
{
    return x1 * x2 + y1 * y2;
}

template<typename NT>
inline
NT
inner_product(const NT & x1, const NT & y1, const NT & z1,
              const NT & x2, const NT & y2, const NT & z2)
{
    return x1 * x2 + y1 * y2 + z1 * z2;
}

template<typename NT>
inline
NT
inner_product(const NT & x1, const NT & y1, const NT & z1, const NT & w1,
              const NT & x2, const NT & y2, const NT & z2, const NT & w2)
{
    return x1 * x2 + y1 * y2 + z1 * z2 + w1 * w2;
}

template<typename NT>
inline
bool
are_dependent(
              const NT & a1, const NT & b1, const NT & c1,
              const NT & a2, const NT & b2, const NT & c2 )
{
    NT zero = static_cast<NT>(0);
    return (
            determinant(a1, b1, a2, b2) == zero &&
            determinant(a1, c1, a2, c2) == zero &&
            determinant(b1, c1, b2, c2) == zero );
}

template<typename NT>
inline
bool
are_dependent(
              const NT & a1, const NT & b1, const NT & c1, const NT & d1,
              const NT & a2, const NT & b2, const NT & c2, const NT & d2 )
{
    NT zero = static_cast<NT>(0);
    return (
            determinant(a1, b1, a2, b2) == zero &&
            determinant(a1, c1, a2, c2) == zero &&
            determinant(a1, d1, a2, d2) == zero &&
            determinant(b1, c1, b2, c2) == zero &&
            determinant(b1, d1, b2, d2) == zero &&
            determinant(c1, d1, c2, d2) == zero );
}

template<class NT>
inline
void
cross_product(const NT & v1x, const NT & v1y, const NT & v1z,
              const NT & v2x, const NT & v2y, const NT & v2z,
              NT & vx, NT & vy, NT & vz)
{
    vx = + determinant( v1y, v2y, v1z, v2z );
    vy = - determinant( v1x, v2x, v1z, v2z );
    vz = + determinant( v1x, v2x, v1y, v2y );
}

#endif // DETERMINANT_H
