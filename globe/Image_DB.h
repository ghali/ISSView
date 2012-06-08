#ifndef IMAGE_DB_H
#define IMAGE_DB_H

#include "geometry/S2/point_s2.h"

#include <QtGui>

typedef Point_S2<double> Point_S2d;

struct Image
{
    QString Mission_Roll_Frame;
    QString Region;
    double latitude;
    double longitude;
    int YYYYMMDD;

    Point_S2d point_s2;
};

extern Image images[];

extern int number_of_images();

class Image_DB
{
public:
    Image_DB()
    {
        sz = number_of_images();
    }

    Image * begin() { return images + 0;  }
    Image * end()   { return images + sz; }

protected:
    size_t sz;
};

#endif // IMAGE_DB_H
