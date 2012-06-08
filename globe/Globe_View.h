#ifndef GLOBE_VIEW_H
#define GLOBE_VIEW_H

#include "globe/Image_DB.h"
#include "globe/Continents.h"
#include "globe/Image_Viewer.h"

#include "Qt/MyGraphicsItem_Point.h"
#include "Qt/MyGraphicsItem_Point_Polygon.h"
#include "Qt/MyGeometry_S2.h"

#include <limits>               // use limits for g++ v4; climits for g++ v3.

typedef MyGeometry_S2<double> MyGeometry;

struct Image_and_its_Point
{
    Image * image;
    MyGraphicsItem_Point<MyGeometry> * point;
};

class Globe_View : public MyGeometry::MyGraphicsView
{
    Q_OBJECT

public:
    Globe_View(const QPoint & window_location,
               MyGeometry::MyGraphicsScene * scene)
        : MyGeometry_S2<double>::MyGraphicsView(scene)
    {
        // typedef MyGeometry_S2<double> Geometry;

        typedef MyGeometry::Point Point;
        typedef MyGeometry::Hyperplane Line;
        typedef MyGeometry::Segment Segment;
        typedef MyGeometry::Point_Polygon Point_Polygon;
        typedef MyGeometry::MyGraphicsScene MyGraphicsScene;
        typedef MyGeometry::MyGraphicsView MyGraphicsView;

        // MyGraphicsView * view = new MyGraphicsView(scene);

        // North Pole
        MyGraphicsItem_Point<MyGeometry> * north_pole_point_item;
        Point north(MyGeometry::from_Longitude_Latitude(0, 90));
        north_pole_point_item = new MyGraphicsItem_Point<MyGeometry>(north);
        north_pole_point_item->setPen(QPen(QBrush(Qt::red), LINE_WIDTH, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        scene->addItem(north_pole_point_item);

        // QGraphicsTextItem * item = new QGraphicsTextItem("North");
        // item->scale(1, -1);
        // scene->addItem(item);
        // item->setPos(MyGeometry::to_QPointF(north));

        // South Pole
        MyGraphicsItem_Point<MyGeometry> * south_pole_point_item;
        Point south(MyGeometry::from_Longitude_Latitude(0, -90));
        south_pole_point_item = new MyGraphicsItem_Point<MyGeometry>(south);
        south_pole_point_item->setPen(QPen(QBrush(Qt::blue), LINE_WIDTH, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        scene->addItem(south_pole_point_item);

        QColor c(255, 255, 0, 127);

        // South America
        Point_Polygon south_america_polygon;
        // size_t south_america_sz = sizeof(south_america_longitude_latitude) / sizeof(LatLong);
        size_t south_america_sz = sizeof_south_america();
        for(LatLong * myll = south_america_longitude_latitude + 0;
            myll != south_america_longitude_latitude + south_america_sz; ++myll)
            south_america_polygon.push_back( Point(MyGeometry::from_Longitude_Latitude(myll->longitude, myll->latitude)) );

        MyGraphicsItem_Point_Polygon<MyGeometry> * south_america_polygon_item;
        south_america_polygon_item = new MyGraphicsItem_Point_Polygon<MyGeometry>( south_america_polygon );
        south_america_polygon_item->setPen(QPen(c.darker().darker(), LINE_WIDTH));
        south_america_polygon_item->setBrush(c);
        scene->addItem(south_america_polygon_item);

        // Africa
        Point_Polygon africa_polygon;
        // size_t africa_sz = sizeof(africa_longitude_latitude) / sizeof(LatLong);
        size_t africa_sz = sizeof_africa();
        for(LatLong * myll = africa_longitude_latitude + 0;
            myll != africa_longitude_latitude + africa_sz; ++myll)
            africa_polygon.push_back( Point(MyGeometry::from_Longitude_Latitude(myll->longitude, myll->latitude)) );

        MyGraphicsItem_Point_Polygon<MyGeometry> * africa_polygon_item;
        africa_polygon_item = new MyGraphicsItem_Point_Polygon<MyGeometry>( africa_polygon );
        africa_polygon_item->setPen(QPen(c.darker().darker(), LINE_WIDTH));
        africa_polygon_item->setBrush(c);
        scene->addItem(africa_polygon_item);

        earliest_time = std::numeric_limits<int>::max();
        latest_time   = std::numeric_limits<int>::min();

        for( Image * image = image_db.begin(); image != image_db.end(); ++image )
        {
            image->point_s2 = MyGeometry::from_Longitude_Latitude(image->longitude, image->latitude);

            MyGraphicsItem_Point<MyGeometry> * point_item;
            point_item = new MyGraphicsItem_Point<MyGeometry>(image->point_s2);
            point_item->setPen(QPen(QBrush(Qt::darkGray), LINE_WIDTH, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            point_item->setBrush(Qt::darkGray);
            scene->addItem(point_item);

            Image_and_its_Point i;
            i.image = image;    // Careful: This is only safe as long as Image_DB uses static arrays.
            i.point = point_item;
            images_and_their_points.push_back(i);

            if( image->YYYYMMDD < earliest_time )
                earliest_time = image->YYYYMMDD;
            if( image->YYYYMMDD > latest_time )
                latest_time = image->YYYYMMDD;
        }

        this->move(window_location);
        this->show();
        // view->pdf_save();
    }

    int get_earliest_time() {
        return earliest_time;
    }
    int get_latest_time() {
        return latest_time;
    }

public slots:
    void new_current_time(int now)
    {
        for( std::vector<Image_and_its_Point>::iterator ip = images_and_their_points.begin();
             ip != images_and_their_points.end(); ++ip )
        {
            QColor c = Qt::darkGray;
            const qreal ratio = qreal( abs(ip->image->YYYYMMDD - now) ) / qreal( (latest_time - earliest_time) / 10 );
            c.setAlpha( 255 * (1.0 - ratio) );

            ip->point->setPen(QPen(QBrush(c), LINE_WIDTH, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            ip->point->setBrush(c);
        }
        update();
    }

protected:

    // Scale the points when zooming in/out.
    virtual void wheelEvent(QWheelEvent* event)
    {
        MyGeometry::MyGraphicsView::wheelEvent(event);

        for( std::vector<Image_and_its_Point>::iterator ip = images_and_their_points.begin();
             ip != images_and_their_points.end(); ++ip )
            ip->point->set_radius( POINT_RADIUS / get_cumulative_scale() );

        update();
    }

    void mousePressEvent(QMouseEvent * mouseEvent)
    {
        MyGeometry::MyGraphicsView::mousePressEvent(mouseEvent);

        if(mouseEvent->modifiers() == Qt::NoModifier) {
            QPointF qtp = this->mapToScene(mouseEvent->pos());

            for( std::vector<Image_and_its_Point>::iterator ip = images_and_their_points.begin();
                 ip != images_and_their_points.end(); ++ip )
                if( ip->point->contains( qtp ) ) {
                    // std::cout << ip->image->latitude << "  " << ip->image->longitude << std::endl;
                    Image_Viewer * image_viewer = new Image_Viewer( ip->image->Mission_Roll_Frame );
                    image_viewer->show();
                    break;
                }
        }

        // MyGeometry::MyGraphicsView::update();
    }

protected:
    Image_DB image_db;

    std::vector<Image_and_its_Point> images_and_their_points;

    int earliest_time;
    int latest_time;
    double datetime;

};

#endif // GLOBE_VIEW_H
