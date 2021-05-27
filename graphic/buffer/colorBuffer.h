#ifndef __COLOR_BUFFER_H__
#define __COLOR_BUFFER_H__

#include "../graphic_conf.h"
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned short color;
typedef unsigned int bufferSize;
typedef _Bool bufferState;

//记录双缓冲(单线程,无DMA，好像没啥用)
typedef struct
{
    /* data */
    color * current;
    bufferState state;
}bufferHead;

typedef struct
{
    /* data */
    color * prior;
    color * next;
    bufferHead *head;
    bufferSize bufferSize;
}colorBuffer;

colorBuffer* colorBufferInit();


#ifdef __cplusplus
}
#endif

#endif //__COLOR_BUFFER_H__