#ifndef QT_GEO_TYPES_H
#define QT_GEO_TYPES_H

#include <QtGui>

const qreal LINE_WIDTH = 0.01;
const qreal BEZIER_CURVE_LINE_WIDTH = 10.0 * LINE_WIDTH;
const qreal POINT_RADIUS = 0.02;

// Z values are set through setZValue(..). Higher values are painted on top.
// The colors have some transparency.
const qreal POINT_Z   = 4.0;
const qreal SEGMENT_Z = 3.0;
const qreal LINE_Z    = 2.0;
const qreal POLYGON_Z = 1.0;

const double BEZIER_SEGMENT_INCREMENT = 0.01;
// const double BEZIER_SEGMENT_INCREMENT = 0.1;

const QPainter::RenderHint default_hints = QPainter::Antialiasing;

enum {
    Point_Item_Type = QGraphicsItem::UserType + 1,
    Line_Item_Type,
    Segment_Item_Type,
    Circle_Item_Type,
    Point_Polygon_Item_Type,
    Bezier_Segment_Item_Type
};

#endif // QT_GEO_TYPES_H
