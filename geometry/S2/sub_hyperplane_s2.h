/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef SUB_HYPERPLANE_S2_H
#define SUB_HYPERPLANE_S2_H

#include <ostream>

#include "geometry/S2/point_s2.h"
#include "geometry/S2/line_s2.h"
#include "geometry/S2/line_polygon_s2.h"
#include "geometry/S2/intersection_s2.h"

template<typename NT>
class Sub_hyperplane_S2;

template<typename NT>
std::ostream &
operator<< ( std::ostream & out, const Sub_hyperplane_S2<NT> & s );

template<typename NT>
class Sub_hyperplane_S2
{
private:
    Line_S2<NT>          _carrying_line;
    Line_Polygon_S2<NT>  _bounding_cell;

    mutable bool _source_and_target_are_ready;
    mutable bool _clipped_out;
    mutable Segment_S2<NT> _segment;

public:
    Sub_hyperplane_S2() {}

    Sub_hyperplane_S2( const Line_S2<NT>& hyperplane,
		       const Line_Polygon_S2<NT>& convex_polytope )
        : _carrying_line( hyperplane ),
          _bounding_cell( convex_polytope ),
          _source_and_target_are_ready(false)
    {}

    Line_S2<NT> carrying_line() const { return _carrying_line; }
    Line_Polygon_S2<NT> bounding_cell() const { return _bounding_cell; }

    void determine_source_and_target() const
    {
        typedef std::pair<bool,Segment_S2<NT> > Bool_and_Segment;
        Bool_and_Segment s = clip_line_to_convex_region( _carrying_line,
							 _bounding_cell.get_lines() );
        _clipped_out = !s.first;
        if( !_clipped_out )
            _segment = s.second;
    }

    // precondition for source() and target():
    //   _bounding_cell is finite
    Point_S2<NT> source() const {
        if( ! _source_and_target_are_ready ) {
            determine_source_and_target();
            _source_and_target_are_ready = true;
        }
        return _segment.source();
    }

    Point_S2<NT> target() const {
        if( ! _source_and_target_are_ready ) {
            determine_source_and_target();
            _source_and_target_are_ready = true;
        }
        return _segment.target();
    }

    friend std::ostream & operator<< <>( ostream & out, const Sub_hyperplane_S2<NT> & s );
};

template<typename NT>
std::ostream &
operator<<( std::ostream & out, const Sub_hyperplane_S2<NT> & s )
{
    out << s._carrying_line;
    return out;
}

#endif // SUB_HYPERPLANE_S2_H
