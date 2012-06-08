#ifndef MYGEOGRAPHICSSCENE_H
#define MYGEOGRAPHICSSCENE_H

#include <QtGui>

template<typename MyGeometry>
class MyGeoGraphicsScene : public QGraphicsScene
{
public:
    MyGeoGraphicsScene()
    {
        // setSceneRect is necessary even when MyGraphicsView::worldHint is overriden.
        this->setSceneRect(MyGeometry::get_default_SceneRect());
    }
};

#endif // MYGEOGRAPHICSSCENE_H
