#include "stdio.h"
#include "math.h"

typedef unsigned short color;
typedef float colorDepth;
typedef unsigned int bufferSize;
typedef _Bool bufferState;

//记录双缓冲(单线程,无DMA，好像没啥用)
typedef struct
{
    /* data */
    color color;
    colorDepth depth;
}colorInfo;

void main()
{
    colorInfo a[128*20];
    printf("%d",sizeof(a));
}