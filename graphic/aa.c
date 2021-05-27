#include "stdio.h"
#include "math.h"
void main()
{
    float a = -3.9415926535898;
    char b=a+0.5;//(8*sizeof(float)-1));
    printf("%d",b);
}