/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef SCENE_S2_H
#define SCENE_S2_H

#include <vector>

#include "geometry/S2/point_s2.h"
#include "geometry/S2/line_s2.h"
#include "geometry/S2/segment_s2.h"
#include "geometry/S2/triangle_s2.h"

template<typename NT>
struct Scene_S2
{
    vector<Triangle_S2<NT> > V;

    // Triangles in Scene_S2 face _inside_ the sphere
    Scene_S2()
    {}

    void
    add_triangle(const Triangle_S2<NT>& tri)
    {
        V.push_back(tri);
    }
    int number_of_triangles() const { return V.size(); }
    void
    recursive_subdivide()
    {
        vector<Triangle_S2<NT> > newV;
        typedef typename vector<Triangle_S2<NT> >::iterator VIT;
        for(VIT vit = V.begin(); vit != V.end(); ++vit) {
            vector<Triangle_S2<NT> > newtriangles;
            newtriangles = vit->get_recursive_subdivision();
            newV.insert(newV.end(), newtriangles.begin(), newtriangles.end());
        }
        V = newV;
    }
};

#endif // SCENE_S2_H
