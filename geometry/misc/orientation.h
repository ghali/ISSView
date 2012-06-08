/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef ORIENTATION_H
#define ORIENTATION_H

enum Orientation
{
    RIGHT_TURN = -1,
    COLINEAR,
    LEFT_TURN
};

enum Oriented_side
{
    ON_NEGATIVE_SIDE = -1,
    ON_ORIENTED_BOUNDARY,
    ON_POSITIVE_SIDE
};

enum Orientation_to_circle
{
    OUTSIDE_CIRCLE = -1,
    COCIRCULAR,
    INSIDE_CIRCLE
};

enum Set_membership
{
    INSIDE_SET = -1,
    ON_SET_BOUNDARY,
    OUTSIDE_SET
};

template<typename T>
Oriented_side
enum_Oriented_side(const T& d)
{
    if(d > 0)
        return ON_POSITIVE_SIDE; // in the plane: LEFT_TURN;
    else if(d < 0)
        return ON_NEGATIVE_SIDE; // in the plane: RIGHT_TURN;
    else
        return ON_ORIENTED_BOUNDARY; // COLINEAR;
}

#endif // ORIENTATION_H
