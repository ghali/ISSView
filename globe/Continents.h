#ifndef CONTINENTS_H
#define CONTINENTS_H

// Todo: Abstract continents in a class.

struct LatLong
{
    double latitude, longitude, time;
};

extern LatLong south_america_longitude_latitude[];
extern LatLong africa_longitude_latitude[];

extern int sizeof_south_america();
extern int sizeof_africa();

#endif // CONTINENTS_H
