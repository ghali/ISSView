#ifndef DISPLAY_SIZES_H
#define DISPLAY_SIZES_H

// All the sizes below are 4:3.
// To be proper, we should avoid #define in favor of static const, but we
// avoid the additional compilation unit that would then be necessary.
#define Display_Size__QVGA     QSize(320,240);
#define Display_Size__VGA      QSize(640,480);
#define Display_Size__SVGA     QSize(800,600);
#define Display_Size__XGA      QSize(1024,768);
#define Display_Size__1280x960 QSize(1280,960);
#define Display_Size__UXGA     QSize(1600,1200);

#endif // DISPLAY_SIZES_H
