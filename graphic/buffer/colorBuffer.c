#include "colorBuffer.h"

colorBuffer* colorBufferInit(colorInfo color)
{
    unsigned short i;
    static colorInfo colorBuff1[SCREEN_HOR_MAX*20];
    //static colorInfo colorBuff2[SCREEN_HOR_MAX*20];
    colorBuffer* Buffer=(colorBuffer*)malloc(sizeof(colorBuffer));
    Buffer->prior=&colorBuff1;
    Buffer->next=NULL;//&colorBuff2;
    Buffer->bufferSize=SCREEN_HOR_MAX*20;
    (Buffer->head)->current=Buffer->prior;
    (Buffer->head)->state=FALSE;
    for (i=0;i<SCREEN_HOR_MAX*20;i++)
    {
        colorBuff1[i]=color;
        //colorBuff2[i].color=color;
        //colorBuff1[i].depth=COLOR_DEPTH_MIN;
        //colorBuff2[i].depth=COLOR_DEPTH_MIN;
    }
    return Buffer;
}

