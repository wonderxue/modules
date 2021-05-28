#ifndef __OBJ_PLOT_H__
#define __OBJ_PLOT_H__

#include "../base/objBase.h"
#include "../buffer/colorBuffer.h"
#include <math.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef float PixelDepth;
typedef unsigned short PixelLoc;
typedef struct
{
    /* data */
    PixelLoc x;
    PixelLoc y;
    colorInfo color;
    PixelDepth depth;
    Pixel *next;
}Pixel;
typedef struct
{
    /* data */
    Pixel *root;
    PixelSets *next;
}PixelSets;

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