#include "objPlot.h"
/*
^y
|
|
|
|
|_________>x
*/
Pixel* lineCut(objNode *node1,objNode *node2,color color)
{
    PixelLoc xstart,ystart,xend,yend,temp,k;
    PixelDepth i,j;
    k=0;
    if(node1->x==node2->x)
    {
        temp=node1->x;
        xstart=(temp>0)?temp+0.5:0;
        if(xstart>SCREEN_VER_MAX)
        return NULL;
        xend=xstart;
        temp=min(node1->y,node2->y);
        ystart=(temp>0)?temp+0.5:0;
        temp=max(node1->y,node2->y);
        yend=(temp>SCREEN_HOR_MAX)?temp+0.5:SCREEN_HOR_MAX;
        i=node1->z;
        j=node2->z;
        j=(j-i)/(yend-ystart);
        Pixel * root,*pixel;
        pixel=(Pixel *)malloc(sizeof(Pixel));
        root=pixel;
        pixel->x=xstart;
        pixel->y=ystart;
        pixel->depth=k*j+i;
        pixel->color=color;
        k++;
        for(temp=ystart+1;temp<=yend;temp++)
        {
            pixel->next=(Pixel*)mallco(sizeof(Pixel));
            pixel=pixel->next;
            pixel->x=xstart;
            pixel->y=temp;
            pixel->depth=k*j+i;
            pixel->color=color;
            k++;
        }
        pixel->next=NULL;
        return root;
    }
    if(node1->y==node2->y)
    {
        temp=node1->y;
        ystart=(temp>0)?temp+0.5:0;
        if(ystart>SCREEN_VER_MAX)
        return NULL;
        yend=ystart;
        temp=min(node1->x,node2->x);
        xstart=(temp>0)?temp+0.5:0;
        temp=max(node1->y,node2->y);
        yend=(temp>SCREEN_HOR_MAX)?temp+0.5:SCREEN_HOR_MAX;
        i=node1->z;
        j=node2->z;
        j=(j-i)/(yend-ystart);
        Pixel * root,*pixel;
        pixel=(Pixel *)malloc(sizeof(Pixel));
        root=pixel;
        pixel->x=xstart;
        pixel->y=ystart;
        pixel->depth=k*j+i;
        pixel->color=color;
        k++;
        for(temp=ystart+1;temp<=yend;temp++)
        {
            pixel->next=(Pixel*)mallco(sizeof(Pixel));
            pixel=pixel->next;
            pixel->x=xstart;
            pixel->y=temp;
            pixel->depth=k*j+i;
            pixel->color=color;
            k++;
        }
        pixel->next=NULL;
        return root;
    }
    objNodeLoc k=node1->x
}
plotArea detectPlotArea(objRoot* root)
{
    objNodeLoc tempx,tempy,x1,y1,x2,y2;
    plotArea area;
    objNode *node=root->next;
    if(root->shape==1)
    {
        area.x1=node->x;
        area.x2=node->x;
        area.y1=node->y;
        area.y2=node->y;
        return area;
    }
    x1=MAX;
    y1=MAX;
    x2=MIN;
    y2=MIN;
    do
    {
        /* code */
        tempx=node->x;
        tempy=node->y;
        x1=min(tempx,x1);
        y1=min(tempy,y1);
        x2=max(tempx,x1);
        y2=max(tempy,y1);
        node=node->next;
    } while (node!=NULL);
    area.x1=x1;
    area.y1=y1;
    area.x2=x2;
    area.y2=y2;
    return area;
}

