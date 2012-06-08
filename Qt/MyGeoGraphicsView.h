#ifndef MYGEOGRAPHICSVIEW_H
#define MYGEOGRAPHICSVIEW_H

#include "Qt/My_Printing_GraphicsView.h"
#include "Qt/Qt_Geo_Types.h"
#include "Qt/MyGeoGraphicsScene.h"

#include <QtGui>

template<typename MyGeometry>
class MyGeoGraphicsView : public My_Printing_GraphicsView
{
public:

    typedef typename MyGeometry::Point Point;
    typedef typename MyGeometry::Transformation Transformation;

    MyGeoGraphicsView(MyGeoGraphicsScene<MyGeometry> * myscene,
                      bool _enable_magnification = true)
        : My_Printing_GraphicsView(myscene),
          dragging(false),
          enable_magnification(_enable_magnification),
          cumulative_scale(1.0)
    {
        scale(1, -1);
        fitInView(scene()->sceneRect() , Qt::KeepAspectRatio);
        setRenderHint(default_hints);
        setWindowTitle(MyGeometry::get_window_title());

        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        // setDragMode(QGraphicsView::ScrollHandDrag);
    }

    Transformation get_transformation() const
    {
        return transformation;
    }

    virtual QString get_geometry_name() const
    {
        return QString(MyGeometry::get_window_title());
    }

    qreal get_cumulative_scale() {
        return cumulative_scale;
    }

protected:
    void resizeEvent(QResizeEvent *)
    {
        if( !enable_magnification )
            fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
    }

    virtual void wheelEvent(QWheelEvent* event)
    {
        const double scale_factor = (event->delta() > 0) ? 1.08 : 1.0/1.08;
        QGraphicsView::scale(scale_factor, scale_factor);

        cumulative_scale *= scale_factor;
    }

    void mousePressEvent(QMouseEvent * mouseEvent)
    {
        if(mouseEvent->modifiers() == Qt::ControlModifier) 
        {
            dragging = true;

            // Notice that whereas in QWidget we used widget_to_world.map(event->posF()),
            // in QGraphicsView/Scene we use mapToScene(mouseEvent->pos()).
            P0 = P1 = mapToScene(mouseEvent->pos());
            P0_H2d = P1_H2d = MyGeometry::from_QPointF(P0);
            update();
        }
    }

    void mouseMoveEvent(QMouseEvent * mouseEvent)
    {
        if(dragging && (mouseEvent->modifiers() == Qt::ControlModifier))
        {
            P1 = mapToScene(mouseEvent->pos());
            P1_H2d = MyGeometry::from_QPointF(P1);

            transformation = calc_current_transformation(); // ( must follow QGraphicsView::mouseMoveEvent(..) ? )
            transformation = transformation * accumulation_of_previous_transformations;

            update();
        }
    }

    void mouseReleaseEvent(QMouseEvent * mouseEvent)
    {
        if(dragging || (mouseEvent->modifiers() == Qt::ControlModifier))
        {
            dragging = false;

            P1 = mapToScene(mouseEvent->pos());

            accumulation_of_previous_transformations = calc_current_transformation() * accumulation_of_previous_transformations;
            // accumulation_of_previous_transformations = calc_current_transformation();

            P0 = P1;
            P0_H2d = P1_H2d;

            update();
        }
    }

    Transformation get_accumulation() const
    {
        return accumulation_of_previous_transformations;
    }
    Transformation calc_current_transformation()
    {
        return MyGeometry::calc_current_transformation(P0_H2d, P1_H2d);
    }

    void drawBackground(QPainter * painter, const QRectF & rect)
    {
        My_Printing_GraphicsView::drawBackground(painter, rect);
        MyGeometry::drawBackground(painter, rect);

        // Draw the translation-manipulation segment.
        if(dragging) {
            painter->setPen(QPen(Qt::lightGray, LINE_WIDTH, Qt::SolidLine, Qt::RoundCap));
            QPainterPath path;
            MyGeometry::draw_segment(P0_H2d, P1_H2d, path);
            painter->drawPath(path);
        }
    }

    QPointF P0; QPointF P1;
    Point P0_H2d; Point P1_H2d;
    bool dragging;

    bool enable_magnification;

    Transformation accumulation_of_previous_transformations;
    Transformation transformation;

    qreal cumulative_scale;
};

#endif // MYGEOGRAPHICSVIEW_H
