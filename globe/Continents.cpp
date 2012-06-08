
#include "globe/Continents.h"

#include <cstdlib>

LatLong south_america_longitude_latitude[] = {
    {   10, -70 , 999  },
    {   -5, -35 , 999  },
    {  -55, -70 , 999  },
    {  -20, -70 , 999  },
    {   -5, -80 , 999  },
};

LatLong africa_longitude_latitude[] = {
    {   30 , -10 , 999  },
    {   30 ,  35 , 999  },
    {   10 ,  45 , 999  },
    {   12 ,  50 , 999  },
    {  -35 ,  20 , 999  },
    {    5 ,  10 , 999  },
    {    5 , -10 , 999  },
    {   20 , -15 , 999  }
};

int sizeof_south_america()
{
    size_t south_america_sz = sizeof(south_america_longitude_latitude) / sizeof(LatLong);
    return south_america_sz;
}

int sizeof_africa()
{
    size_t africa_sz = sizeof(africa_longitude_latitude) / sizeof(LatLong);
    return africa_sz;
}
