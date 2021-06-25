#include "stdio.h"

void main()
{
    unsigned int c=0x01020304;
    signed char a=0x4a;
    unsigned short b=(((1<<6)+a)<<8)+(c>>24);
    printf("%d",1+(a<<1));
}