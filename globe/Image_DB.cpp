
#include "globe/Image_DB.h"

#include <cstdlib>

Image images[] =
{
    // LatLong data are from:
    // http://eol.jsc.nasa.gov/scripts/sseop/clickmap.pl?hashnumber=3217&fieldlist=GEON,FEAT,LAT,LON,PDATE&options=none
    { "ISS030-E-5114" , "ARGENTINA",  -35.0,   -57.5,   20111122, Point_S2d(1,0,0)  },
    { "ISS030-E-5116" , "ARGENTINA",  -35.0,   -57.0,   20111122, Point_S2d(1,0,0)  },
    { "ISS026-E-26890", "URUGUAY"  ,  -34.9,   -56.1,   20110214, Point_S2d(1,0,0)  },
    { "ISS026-E-26893", "URUGUAY"  ,  -34.9,   -56.2,   20110214, Point_S2d(1,0,0)  },
    { "ISS026-E-10424", "URUGUAY"  ,  -34.5,   -56.0,   20101216, Point_S2d(1,0,0)  },
    { "ISS026-E-10425", "URUGUAY"  ,  -35.0,   -56.0,   20101216, Point_S2d(1,0,0)  },
    { "ISS026-E-10426", "URUGUAY"  ,  -35.0,   -56.0,   20101216, Point_S2d(1,0,0)  },
    { "ISS026-E-10433", "URUGUAY"  ,  -34.5,   -56.0,   20101216, Point_S2d(1,0,0)  },
    { "ISS023-E-42088", "URUGUAY"  ,  -34.9,   -56.1,   20100509, Point_S2d(1,0,0)  },
    { "ISS023-E-30385", "URUGUAY"  ,  -34.9,   -56.1,   20100501, Point_S2d(1,0,0)  },
    { "ISS023-E-30386", "URUGUAY"  ,  -34.9,   -56.2,   20100501, Point_S2d(1,0,0)  },
    { "ISS023-E-30387", "URUGUAY"  ,  -34.9,   -56.3,   20100501, Point_S2d(1,0,0)  }
};

int number_of_images()
{
    size_t sz = sizeof(images) / sizeof(Image);
    return sz;
}
