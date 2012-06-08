/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef DOMINANT_E3_H
#define DOMINANT_E3_H

#include <cassert>
#include "geometry/E3/vector_e3.h"

enum Dominant_E3 { E3_POSX, E3_NEGX, E3_POSY, E3_NEGY, E3_POSZ, E3_NEGZ };
//----------------------------------------------------------------
template<typename T>
Dominant_E3
dominant(const T& dx, const T& dy, const T& dz)
{
    const T zero(0);
    T dxabs = dx >= zero ? dx : (-dx);
    T dyabs = dy >= zero ? dy : (-dy);
    T dzabs = dz >= zero ? dz : (-dz);

    if(dxabs >= dyabs && dxabs >= dzabs)
        return ((dx > zero) ? E3_POSX : E3_NEGX);
    else if(dyabs >= dzabs)
        return ((dy > zero) ? E3_POSY : E3_NEGY);
    else
        return ((dz > zero) ? E3_POSZ : E3_NEGZ);
}
//----------------------------------------------------------------
template<typename T>
Dominant_E3
least_dominant(const T& dx, const T& dy, const T& dz)
{
    const T zero(0);
    T dxabs = dx >= zero ? dx : -dx;
    T dyabs = dy >= zero ? dy : -dy;
    T dzabs = dz >= zero ? dz : -dz;

    if(dxabs <= dyabs && dxabs <= dzabs)
        return ((dx >= zero) ? E3_POSX : E3_NEGX);
    else if(dyabs <= dzabs)
        return ((dy >= zero) ? E3_POSY : E3_NEGY);
    else
        return ((dz >= zero) ? E3_POSZ : E3_NEGZ);
}

template<typename T>
Vector_E3<T>
get_Vector_E3(const Dominant_E3& d)
{
    switch( d )
    {
    case E3_POSX: return Vector_E3<T>( 1, 0, 0);
    case E3_NEGX: return Vector_E3<T>(-1, 0, 0);
    case E3_POSY: return Vector_E3<T>( 0, 1, 0);
    case E3_NEGY: return Vector_E3<T>( 0,-1, 0);
    case E3_POSZ: return Vector_E3<T>( 0, 0, 1);
    case E3_NEGZ: return Vector_E3<T>( 0, 0,-1);
    default: assert(false);
    };
}

#endif // DOMINANT_E3_H
