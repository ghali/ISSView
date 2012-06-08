#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QMainWindow>
#include <QPrinter>
#include <QtGui>

#include <QStringBuilder>       // defines QString % QString

class Image_Viewer : public QMainWindow
{
    Q_OBJECT

public:
    Image_Viewer(QString filename)
    {
        imageLabel = new QLabel;
        imageLabel->setBackgroundRole(QPalette::Base);
        imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        imageLabel->setScaledContents(true);

        scrollArea = new QScrollArea;
        scrollArea->setBackgroundRole(QPalette::Dark);
        scrollArea->setWidget(imageLabel);
        setCentralWidget(scrollArea);

        setWindowTitle( filename );
        // resize(400, 300);

        const QString full_filename = QString("images/") + filename + QString(".JPG");
        QImage image( full_filename );
        if( image.isNull() ) {
            QMessageBox::information(this, tr("Image Viewer"),
                                     tr("Cannot load %1.").arg(filename));
            return;
        }

        imageLabel->setPixmap(QPixmap::fromImage(image));
        imageLabel->adjustSize();
    }

private:
    QLabel *imageLabel;
    QScrollArea *scrollArea;

};

#endif // IMAGEVIEWER_H
