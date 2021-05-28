#ifndef __COLOR_BUFFER_H__
#define __COLOR_BUFFER_H__

#include "../graphic_conf.h"
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned short colorInfo;
typedef float colorDepth;
typedef unsigned int bufferSize;
typedef _Bool bufferState;

//记录双缓冲(单线程,无DMA，好像没啥用)
// typedef struct
// {
//     /* data */
//     color color;
//     colorDepth depth;
// }colorInfo;

typedef struct
{
    /* data */
    colorInfo * current;
    bufferState state;
}bufferHead;

typedef struct
{
    /* data */
    colorInfo * prior;
    colorInfo * next;
    bufferHead *head;
    bufferSize bufferSize;
}colorBuffer;

colorBuffer* colorBufferInit();


#ifdef __cplusplus
}
#endif

#endif //__COLOR_BUFFER_H__