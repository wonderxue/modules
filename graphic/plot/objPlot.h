#ifndef __OBJ_PLOT_H__
#define __OBJ_PLOT_H__

#include "../base/objBase.h"
#include "../buffer/colorBuffer.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef float PixelDepth;
typedef unsigned char PixelLoc;
typedef struct
{
    /* data */
    PixelLoc x;
    PixelLoc y;
    color color;
    PixelDepth depth;
    Pixel *next;
}Pixel;
typedef struct
{
    /* data */
    objNodeLoc x1;
    objNodeLoc y1;
    objNodeLoc x2;
    objNodeLoc y2;
}plotArea;






#ifdef __cplusplus
}
#endif

#endif //__OBJ_PLOT_H__