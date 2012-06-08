#ifndef MYGRAPHICSITEM_POINT_POLYGON_H
#define MYGRAPHICSITEM_POINT_POLYGON_H

#include "Qt/Qt_Geo_Types.h"

#include <QtGui>

template<typename MyGeometry>
class MyGraphicsItem_Point_Polygon
    : public QGraphicsPolygonItem,
      public MyGeometry::Point_Polygon
{
public:
    typedef typename MyGeometry::Point Point;
    typedef typename MyGeometry::Point_Polygon Point_Polygon;
    typedef typename MyGeometry::Transformation Transformation;
    typedef typename MyGeometry::MyGraphicsView MyGraphicsView;

    MyGraphicsItem_Point_Polygon() {}

    template<typename iterator>
    MyGraphicsItem_Point_Polygon(iterator b, iterator e)
        : Point_Polygon(b,e)
    {
        setZValue(POLYGON_Z);
        typedef typename Point_Polygon::Point_iterator It;
        for(It i = MyGeometry::Point_Polygon::begin();
            i != MyGeometry::Point_Polygon::end(); ++i)
            *i = MyGeometry::normalize(*i);
    }

    MyGraphicsItem_Point_Polygon(const Point_Polygon & polygon,
                                 QGraphicsItem * parent = 0)
        : QGraphicsPolygonItem(parent), Point_Polygon(polygon)
    {
        setZValue(POLYGON_Z);
    }

    void item_is_about_to_change()
    {
        QGraphicsItem::prepareGeometryChange();
    }

protected:
    void sync(const Transformation & transformation = Transformation())
    {
        const Point_Polygon transformed_polygon = transformation.transform(*this);

        QVector<QPointF> path;
        typedef typename Point_Polygon::Point_const_iterator It;
        for(It i = transformed_polygon.begin();
            i != transformed_polygon.end()-1; ++i)
            MyGeometry::draw_segment(*i, *(i+1), path);
        MyGeometry::draw_segment(*(transformed_polygon.end()-1),
                                 *(transformed_polygon.begin()), path);
        QGraphicsPolygonItem::setPolygon(QPolygonF(path));
    }

    virtual void paint(QPainter * painter,
                       const QStyleOptionGraphicsItem * style,
                       QWidget * widget = 0)
    {
        Transformation transformation;
        if(widget && widget->parent()) {
            MyGraphicsView * qgw;
            qgw = (MyGraphicsView *)(widget->parent());
            transformation = qgw->get_transformation();
        } // Otherwise we're printing to pdf/svg.

        // if(MyGeometry::Point_Polygon::size())
        {
            sync(transformation);

            QGraphicsPolygonItem::paint(painter, style, widget);
        }
    }

    int type() const
    {
        // The Qt way to enable us to tell the type of this item.
        return Point_Polygon_Item_Type;
    }
};

#endif // MYGRAPHICSITEM_POINT_POLYGON_H
