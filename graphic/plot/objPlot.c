#include "objPlot.h"
/*
^y
|
|
|
|
|------->x
*/
static void (*plotBaseFun)(PixelLoc,PixelLoc,PixelLoc,PixelLoc,colorInfo*);
Pixel *linePixel(objNode *node1, objNode *node2, colorInfo color)
{
    objNodeLoc x, y, dx, dy, p, temp, z, dz;
    _Bool s1, s2, interchange;
    short i;
    Pixel *root, *pixel;
    x = node1->x;
    y = node1->y;
    dx = node2->x;
    dy = node2->y;
    z = node1->z;
    dz = node2->z - z;
    //z=(dz-z)/sqrt((dx-x)^2+(dy-y)^2)*i+dz
    //dz=(dz-z)/sqrt(pow((dx-x),2)+pow((dy-y),2));
    //y=temp*x+p
    if (y == dy)
    {
        if (y > SCREEN_VER_MAX || y < 0)
            return NULL;
        //约束x
        x = (x > SCREEN_HOR_MAX) ? SCREEN_HOR_MAX : x;
        x = (x < 0) ? 0 : x;
        dx = (dx > SCREEN_HOR_MAX) ? SCREEN_HOR_MAX : dx;
        dx = (dx < 0) ? 0 : dx;
    }
    else
    {
        temp = (dy - y) / (dx - x);
        p = y - temp * x;
        //约束x
        x = (x > SCREEN_HOR_MAX) ? SCREEN_HOR_MAX : x;
        x = (x < 0) ? 0 : x;
        dx = (dx > SCREEN_HOR_MAX) ? SCREEN_HOR_MAX : dx;
        dx = (dx < 0) ? 0 : dx;
        //计算y
        y = temp * x + p;
        dy = temp * dx + p;
        if(y>SCREEN_VER_MAX&&dy>SCREEN_VER_MAX)
        return NULL;
        if(y<0&&dy<0)
        return NULL;
        if(y>SCREEN_VER_MAX)
            x=(SCREEN_VER_MAX-p)/temp;
        if(y<0)
            x=-p/temp;
        if(dy>SCREEN_VER_MAX)
            dx=(SCREEN_VER_MAX-p)/temp;
        if(dy<0)
            dx=-p/temp;
    }
    if (dx > x)
        s1 = 1;
    else
        s1 = -1;

    if (dy > y)
        s2 = 1;
    else
        s2 = -1;
    dx = dx - x;
    dx = (dx > 0) ? dx : -dx;
    dy = dy - y;
    dy = (dy > 0) ? dy : -dy;
    if (dy > dx)
    {
        temp = dx;
        dx = dy;
        dy = temp;
        interchange = 1;
    }
    else
        interchange = 0;
    p = 2 * dy - dx;
    pixel = (Pixel *)malloc(sizeof(Pixel));
    root = pixel;
    for (i = 1; i <= (short)(dx + 0.5); i++)
    {
        //putpixel(x, y, color);
        pixel->x = (PixelLoc)(x + 0.5);
        pixel->y = (PixelLoc)(y + 0.5);
        pixel->depth = dz / ((short)(dx + 0.5))*(i-1) + z;
        pixel->color = color;
        pixel->next = (Pixel *)malloc(sizeof(Pixel));
        pixel = pixel->next;
        if (p >= 0)
        {
            if (interchange == 0)
                y = y + s2;
            else
                x = x + s1;
            p = p - 2 * dx;
        }
        if (interchange == 0)
            x = x + s1;
        else
            y = y + s2;
        p = p + 2 * dy;
    }
    pixel->x = (PixelLoc)(x + 0.5);
    pixel->y = (PixelLoc)(y + 0.5);
    pixel->depth = dz / ((short)(dx + 0.5))*(i-1) + z;
    pixel->color = color;
    pixel->next = NULL;
    return root;
}
void plotFunReg(void (*fun)(PixelLoc,PixelLoc,PixelLoc,PixelLoc,colorInfo*))
{
    plotBaseFun=fun;
}
PixelSets* plotObj(objRoot *root,colorInfo color)
{
    Pixel *pixel;
    objShape i,k,shape=root->shape;
    objNode *node=root->next;
    PixelSets *pixelSets,*proot;
    if(shape==1)
    {
        objNodeLoc x,y;
        x=node->x;
        y=node->y;
        if(0<=x&&x<=SCREEN_HOR_MAX&&0<=y&&y<=SCREEN_VER_MAX)
        {
            pixel=(Pixel *)malloc(sizeof(Pixel));
            pixelSets=(PixelSets *)malloc(sizeof(PixelSets));
            pixel->x=x+0.5;
            pixel->y=y+0.5;
            pixel->color=color;
            pixel->depth=node->z;
            pixel->next=NULL;
            pixelSets->root=pixel;
            pixelSets->next=NULL;
            return pixelSets;
        }
        return NULL;
    }
    if(shape==2)
    {
        pixel=linePixel(node,node->next,color);
        if(pixel!=NULL)
        {
        pixelSets=(PixelSets *)malloc(sizeof(PixelSets));
        pixelSets->root=pixel;
        pixelSets->next=NULL;
        return pixelSets;
        }
        return NULL;
    }
    pixelSets=(PixelSets *)malloc(sizeof(PixelSets));
    proot=pixelSets;
    k=0;
    for(i=1;i<shape;i++)
    {
        pixel=linePixel(node,node->next,color);
        if(pixel!=NULL)
        {
            pixelSets->root=pixel;
            pixelSets->next=(PixelSets *)malloc(sizeof(PixelSets));
            pixelSets=pixelSets->next;
            k++;
        }
        node=node->next;
    }
    //首尾相连
    pixel=linePixel(node,root->next,color);
    if(pixel!=NULL)
    {
        pixelSets->root=pixel;
        pixelSets->next=NULL;
    }
    else
    {
        free(pixelSets);
        pixelSets=proot;
        while (k--)
        {
            /* code */
            pixelSets=pixelSets->next;
        }
        
    }
    

}
plotArea detectPlotArea(objRoot *root)
{
    objNode *node=root->next;
    PixelSets pixelSet 
    do
    {
        /* code */
        lineCut()
    } while ();
    






    objNodeLoc tempx, tempy, x1, y1, x2, y2;
    plotArea area;
    objNode *node = root->next;
    if (root->shape == 1)
    {
        area.x1 = node->x;
        area.x2 = node->x;
        area.y1 = node->y;
        area.y2 = node->y;
        return area;
    }
    x1 = MAX;
    y1 = MAX;
    x2 = MIN;
    y2 = MIN;
    do
    {
        /* code */
        tempx = node->x;
        tempy = node->y;
        x1 = min(tempx, x1);
        y1 = min(tempy, y1);
        x2 = max(tempx, x1);
        y2 = max(tempy, y1);
        node = node->next;
    } while (node != NULL);
    area.x1 = x1;
    area.y1 = y1;
    area.x2 = x2;
    area.y2 = y2;
    return area;
}
