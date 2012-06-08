#ifndef LINE_POLYGON_S2_H
#define LINE_POLYGON_S2_H

#include <cassert>

#include "geometry/S2/point_s2.h"
// #include "geometry/S2/line_s2.h"
#include "geometry/S2/line_s2.h"
#include "geometry/S2/triangle_s2.h"
#include "geometry/S2/predicates_s2.h"

// The differences between Line_Polygon_S2 and Point_Polygon_S2 are:
//   1- Point_Polygon_S2 stores the bounding vertices.
//   2- Line_Polygon_S2 may represent the empty set.
//   3- Line_Polygon_S2 stores whether each boundary is open or closed.

//================================================================
// A Line_Polygon_S2 would consist of *two* disjoint sets.
// We consider, implicitly, tha the polygon on the side of z>0 
// is the one captured.
//================================================================

template<typename NT>
class Line_Polygon_S2
{
    bool is_empty_var;

    std::vector<Line_S2<NT> >  lines;
    std::vector<bool>  line_is_closed;

    // For consistency with 3D solids:
    // Interior of polygon lies on the right (negative side) of boundary.
    // Exterior lies on the left (positive side).
    // The polygon is oriented clockwise.

public:
    Line_Polygon_S2() { is_empty_var = true; }
    // The Universe:
    Line_Polygon_S2(bool /*b*/)
    {
	is_empty_var = false;
    }

    Line_Polygon_S2(const Line_S2<NT> & line, bool closed)
    {
	is_empty_var = false;

	lines.push_back(line);
	line_is_closed.push_back(closed);
    }

#if 0
    template<typename Point_Iterator>
    Line_Polygon_S2(Point_Iterator b, Point_Iterator e)
    {
        const size_t sz = e - b;
        std::fill_n(std::back_inserter(line_is_closed), sz, true);

        lines.push_back(Line_S2<NT>(*(e-1), *b));
        for(Point_Iterator i=b; i!=e-1; ++i)
            lines.push_back(Line_S2<NT>(*i, *(i+1)));
    }
#endif
    template<typename Line_Iterator>
    Line_Polygon_S2(Line_Iterator b, Line_Iterator e)
        : lines(b, e)
    {
        const size_t sz = e - b;
        std::fill_n(std::back_inserter(line_is_closed), sz, true);
    }

    Line_Polygon_S2(const Point_Polygon_S2<NT> & point_polygon)
    {
	typedef typename Point_Polygon_S2<NT>::Point_const_iterator Pit;
	Pit first = point_polygon.end() - 1;
	for(Pit second = point_polygon.begin(); second != point_polygon.end(); ++second)
	{
	    lines.push_back( Line_S2<NT>(*first, *second) );
	    first = second;
	}
        line_is_closed = std::vector<bool>(point_polygon.size(), true);
    }

    Line_Polygon_S2(const std::vector<Line_S2<NT> >& lines_in, 
		    const std::vector<bool>& line_is_closed_in)
        : is_empty_var(false),
          lines(lines_in), line_is_closed(line_is_closed_in)
    {}

    Line_Polygon_S2( const Triangle_S2<NT>& triangle )
        : is_empty_var(false)
    {
        const Point_S2<NT>& p0 = triangle.P0();
        const Point_S2<NT>& p1 = triangle.P1();
        const Point_S2<NT>& p2 = triangle.P2();

        lines.push_back(Line_S2<NT>(p0, p1));
        lines.push_back(Line_S2<NT>(p1, p2));
        lines.push_back(Line_S2<NT>(p2, p0));

        line_is_closed = std::vector<bool>(3, true);

        // Confirm:
        //   p0, p1, p2 is a negative (right/clockwise) turn
        assert( oriented_side(p0, p1, p2) == ON_NEGATIVE_SIDE );
    }

    std::vector<Line_S2<NT> >
    get_lines() const
    {
        return lines;
    }

    std::vector<Line_S2<NT> >
    get_free_bounding_lines() const
    {
        std::vector<Line_S2<NT> > returned_lines;

        typedef typename std::vector<Line_S2<NT> >::const_iterator Line_it;
        typedef typename std::vector<bool>::const_iterator         Bool_it;

        Line_it line_it = lines.begin();
        Bool_it  bool_it = line_is_closed.begin();

        while(bool_it != line_is_closed.end()) {

            if(*bool_it)
                returned_lines.push_back(*line_it);

            ++line_it;
            ++bool_it;
        }
        return returned_lines;
    }

    unsigned int size() const { return lines.size(); }
    bool is_empty() const { return is_empty_var; }

    Line_S2<NT> get_line(int i) const { return lines[i]; }
    bool is_line_closed(int i) const { return line_is_closed[i]; }

    std::vector<bool>
    get_line_is_closed() const {
        return line_is_closed;
    }
};

#endif // LINE_POLYGON_S2_H
