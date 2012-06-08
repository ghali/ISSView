#ifndef MY_PRINTING_GRAPHICSVIEW_H
#define MY_PRINTING_GRAPHICSVIEW_H

// #define OPTION_TO_GENERATE_SVG

#include "display_sizes.h"

#include <QtGui>
#include <QStringBuilder>       // needed for QString::operator%
#ifdef OPTION_TO_GENERATE_SVG
#include <QSvgGenerator>
#endif

class My_Printing_GraphicsView : public QGraphicsView
{
public:
    My_Printing_GraphicsView(QGraphicsScene * scene,
                             QWidget * parent = 0)
        : QGraphicsView(scene, parent)
    {
        move(50,70);
    }

    virtual QString get_geometry_name() const=0;

    QString get_filename()
    {
        QDateTime datetime = QDateTime::currentDateTime();
        QString sdatetime = datetime.toString("yyyy.MM.dd--hh:mm:ss--");
        return sdatetime;
    }

    void pdf_save()
    {
        QString filename = get_filename() % get_geometry_name() % ".pdf"; // % is more efficient than +

        QPrinter printer;
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(filename);
        printer.setFullPage(true);

        // QWidget::size() will report the current size.
        printer.setPaperSize( size(), QPrinter::Point );

        QPainter painter(&printer);
        this->render(&painter);
        QMessageBox::information(this, "Print", QString("Pdf Saved"), QMessageBox::Ok);
    }

#ifdef OPTION_TO_GENERATE_SVG
    void
    svg_save()
    {
        QSvgGenerator svg;

        QString filename = get_filename() % get_geometry_name() % ".svg"; // % is more efficient than +

        svg.setFileName(filename);
        svg.setSize(QSize(320, 240));
        //svg.setViewBox(QRect(0, 0, 1100, 850));
        svg.setTitle(windowTitle());
    
        QPainter painter(&svg);
        this->render(&painter);
        QMessageBox::information(this, "SVG", "SVG saved", QMessageBox::Ok);
    }
#endif

protected:
    QSize sizeHint() const { return Display_Size__VGA; }
    // QSize sizeHint() const { return QSize(32,32); }

    void keyPressEvent(QKeyEvent * event)
    {
        switch(event->key()) {
        case Qt::Key_P: pdf_save(); break;
#ifdef OPTION_TO_GENERATE_SVG
        case Qt::Key_S: svg_save(); break;
#endif
        }
    }
};

#endif // MY_PRINTING_GRAPHICSVIEW_H
