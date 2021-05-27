#include "colorBuffer.h"

colorBuffer* colorBufferInit()
{
    static color colorBuff1[SCREEN_HOR_MAX*20];
    static color colorBuff2[SCREEN_HOR_MAX*20];
    colorBuffer* Buffer=(colorBuffer*)malloc(sizeof(colorBuffer));
    Buffer->prior=&colorBuff1;
    Buffer->next=&colorBuff2;
    Buffer->bufferSize=SCREEN_HOR_MAX*20;
    (Buffer->head)->current=Buffer->prior;
    (Buffer->head)->state=FALSE;
    return Buffer;
}

