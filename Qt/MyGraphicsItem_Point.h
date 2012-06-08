#ifndef MYGRAPHICSITEM_POINT_H
#define MYGRAPHICSITEM_POINT_H

#include "Qt/Qt_Geo_Types.h"

#include <QtGui>

// The coordinates are stored in MyGeometry::Point and also, implicitly,
// in QGraphicsEllipseItem, hence the need for sync().
template<typename MyGeometry>
class MyGraphicsItem_Point
    : public QGraphicsEllipseItem,
      public MyGeometry::Point
{
public:
    typedef typename MyGeometry::Point Point;
    typedef typename MyGeometry::Transformation Transformation;
    typedef typename MyGeometry::MyGraphicsView MyGraphicsView;

    MyGraphicsItem_Point(qreal _point_radius = POINT_RADIUS)
        : QGraphicsEllipseItem(0),
          point_radius(_point_radius)
    {
        setZValue(POINT_Z);
    }

    // todo: QGraphicsItem * parent should be last.
    // leaving the interface like this at this time to avoid breaking existing code.
    MyGraphicsItem_Point(const Point & point,
                         QGraphicsItem * parent = 0,
                         qreal _point_radius = POINT_RADIUS)
        : QGraphicsEllipseItem(parent), Point(point), point_radius(_point_radius)
    {
        setZValue(POINT_Z);
        sync();
    }

    void item_is_about_to_change()
    {
        QGraphicsItem::prepareGeometryChange();
    }

    void set_radius(qreal r) {
        point_radius = r;
    }

protected:
    void sync(const Transformation & transformation = Transformation())
    {
        Point p = transformation.transform(*this);
        QPointF qtp = MyGeometry::to_QPointF(p);

        setRect(QRectF(qtp.x() - point_radius, qtp.y() - point_radius,
                       2.0 * point_radius, 2.0 * point_radius));
    }

    // QAbstractGraphicsShapeItem::paint
    virtual void paint(QPainter * painter,
                       const QStyleOptionGraphicsItem * style,
                       QWidget * widget = 0)
    {
        Transformation transformation;
        if(widget && widget->parent()) {
            MyGraphicsView * qgw = static_cast<MyGraphicsView *>(widget->parent());
            transformation = qgw->get_transformation();
        } // Otherwise we're printing to pdf/svg.

        sync(transformation);

        QGraphicsEllipseItem::paint(painter, style, widget);
    }

    int type() const
    {
        return Point_Item_Type;
    }

    qreal point_radius;

};

#endif // MYGRAPHICSITEM_POINT_H
