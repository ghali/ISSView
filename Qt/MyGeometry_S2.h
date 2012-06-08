#ifndef MYGEOMETRY_S2_H
#define MYGEOMETRY_S2_H

#include "Qt/MyGeoGraphicsScene.h"
#include "Qt/MyGeoGraphicsView.h"

#include "geometry/S2/geometry_s2.h"
#include "geometry/S2/interpolation_s2.h"
#include "geometry/S2/intersection_s2.h"
#include "geometry/S2/predicates_s2.h"

#include "geometry/S3/quaternion.h"

#include <cmath>
using std::sqrt;

template<typename NT>
class MyGeometry_S2 : public Geometry_S2<NT>
{
public:
    typedef MyGeoGraphicsScene<MyGeometry_S2<NT> > MyGraphicsScene;
    typedef MyGeoGraphicsView<MyGeometry_S2<NT> >  MyGraphicsView;

    typedef typename Geometry_S2<NT>::Number_Type Number_Type;

    typedef typename Geometry_S2<NT>::Point Point;
    typedef typename Geometry_S2<NT>::Hyperplane Line;
    typedef typename Geometry_S2<NT>::Transformation Transformation;
    typedef typename Geometry_S2<NT>::Point_Polygon Point_Polygon;
    typedef typename Geometry_S2<NT>::Line_Polygon Line_Polygon;
    typedef typename Geometry_S2<NT>::Segment Segment;

    static const char * get_window_title() { return "S2"; }

    static QRectF
    get_default_SceneRect()
    {
        return QRectF(QPointF(-1.1,-1.1), QSizeF(2.2,2.2));
    }

    static QPointF to_QPointF(const Point & P)
    {
        return QPointF(P.x(), P.y());
    }
    // MyGeometry_H2 and MyGeometry_E2 also provide from_QPointF(..).
    static Point from_QPointF(const QPointF & P)
    {
        qreal x = P.x(); qreal y = P.y();
        qreal r = x*x + y*y;
        qreal z;
        if(r > 1.0) {
            r = sqrt(r);
            x /= r;
            y /= r;
            z = 0.0;
        }
        else
            z = std::sqrt(1.0 - r);
        return Point(x, y, z);
    }

    // Only MyGeometry_S2 provides from_Longitude_Latitude(..).
    static Point from_Longitude_Latitude(const double longitude_in_degrees, const double latitude_in_degrees)
    {
        double longitude_in_radians = longitude_in_degrees * M_PI / 180.0;
        double latitude_in_radians  = latitude_in_degrees  * M_PI / 180.0;
        double x = cos(latitude_in_radians) * cos(longitude_in_radians );
        double y = cos(latitude_in_radians) * sin(longitude_in_radians );
        double z = sin(latitude_in_radians);
        return Point(x, y, z);
    }

    static Point
    normalize(const Point & p) {
        NT d = (NT)( sqrt( p.x()*p.x() + p.y()*p.y() + p.z()*p.z() ) );
        return Point(p.x()/d, p.y()/d, p.z()/d);
    }

    static void draw_line(const Line & line,
                          const QPolygonF & /*polygonf*/,
                          QPainterPath & path)
    {
        // polygonf is only needed in E2.
        Point base1 = normalize(line.base1());
        Point base2 = normalize(line.base2());
        draw_segment( base1,  base2, path);
        draw_segment( base2, -base1, path);
        draw_segment(-base1, -base2, path);
        draw_segment(-base2,  base1, path);

        // // Draw scaled unit circle.
        // path->addEllipse( QRectF(QPointF(-1,-1), QSize(2,2)) );
    }

    static void draw_segment(const Segment & segment,
                             QPainterPath & path)
    {
        draw_segment(segment.source(), segment.target(), path);
    }
    static void draw_segment(const Point & source,
                             const Point & target,
                             QPainterPath & path)
    {
        const QPointF qpsource = to_QPointF(source);
        path.moveTo(qpsource);

        const qreal MAX_SEGMENT_DIVISIONS = 60.0;

        qreal xx = source.x() - target.x();
        qreal yy = source.y() - target.y();
        const qreal dist = std::sqrt(xx*xx+yy*yy);

        if(dist > 1.0 / MAX_SEGMENT_DIVISIONS) {
            qreal increment = 1.0 / MAX_SEGMENT_DIVISIONS / dist;

            for(qreal f=increment; f<1.0; f+=increment) {
                Point p = interpolate(source, target, f);
                QPointF qp = to_QPointF(p);
                path.lineTo(qp);
            }
        }
        const QPointF qptarget = to_QPointF(target);
        path.lineTo(qptarget);
    }
    static void draw_segment(const Point & source,
                             const Point & target,
                             QVector<QPointF> & path)
    {
        const QPointF qpsource = to_QPointF(source);
        path.push_back(qpsource);

        const qreal MAX_SEGMENT_DIVISIONS = 60.0;

        qreal xx = source.x() - target.x();
        qreal yy = source.y() - target.y();
        const qreal dist = std::sqrt(xx*xx+yy*yy);

        if(dist > 1.0 / MAX_SEGMENT_DIVISIONS) {
            qreal increment = 1.0 / MAX_SEGMENT_DIVISIONS / dist;

            for(qreal f=increment; f<1.0; f+=increment) {
                Point p = interpolate(source, target, f);
                QPointF qp = to_QPointF(p);
                path.push_back(qp);
            }
        }
        const QPointF qptarget = to_QPointF(target);
        path.push_back(qptarget);
    }

    static Transformation
    calc_current_transformation(const Point & P0,
                                const Point & P1)
    {
        double qx, qy, qz;
        cross_product(P0.x(), P0.y(), P0.z(),
                      P1.x(), P1.y(), P1.z(),
                      qx, qy, qz);
        double qw = inner_product(P1, P0);
        Quaternion<NT> q(qw, qx, qy, qz);
        Transformation rot(q);
        return rot;
    }
    static void drawBackground(QPainter * painter, const QRectF & rect)
    {
        painter->setRenderHint(default_hints);
        painter->setPen( QPen(Qt::gray, LINE_WIDTH) );
        painter->drawLine(QPointF(rect.left(),0), QPointF(rect.right(),0)); // X
        painter->drawLine(QPointF(0,rect.bottom()), QPointF(0,rect.top())); // Y
        painter->drawEllipse( QRectF(QPointF(-1,-1), QSize(2,2)) ); // unit circle

//        draw_segment( Point(1.0, 0.0, 0.0), Point(0.0, 1.0, 0.0) )
    }
};

#endif // MYGEOMETRY_S2_H
