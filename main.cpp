
#include "globe/Globe_View.h"

#include <QtGui>
#include <cmath>

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);
    QVBoxLayout * layout = new QVBoxLayout;
    {
        MyGeometry::MyGraphicsScene * scene = new MyGeometry::MyGraphicsScene;
        Globe_View * scw = new Globe_View( QPoint(700, 25), scene );
        layout->addWidget(scw);

        QSlider * slider = new QSlider(Qt::Horizontal);
        slider->setRange( scw->get_earliest_time(), scw->get_latest_time() ); // Remember that QSlider uses integers.

        slider->setValue(scw->get_latest_time());
        // slider->setTickInterval(100);
        slider->setTickPosition(QSlider::TicksBelow);
        layout->addWidget( slider );

        QObject::connect(slider, SIGNAL(sliderMoved(int)), scw, SLOT(new_current_time(int)));
    }
    QWidget * view_and_slider_widget = new QWidget;
    view_and_slider_widget->setLayout(layout);
    view_and_slider_widget->show();

    return app.exec();
}
