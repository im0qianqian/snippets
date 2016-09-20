/*
POJ 2007 Scrambled Polygon

题意：给出一些点，将这些点进行极角排序后输出
*/

#include <iostream>
#include<stdio.h>
#include<algorithm>
using namespace std;
struct point
{
    int  x;
    int  y;
} p[10010];
bool camp(point a,point b)
{
    if((a.x*b.y-a.y*b.x)>0)
        return true;
    return false;
}
int main()
{
    int n=0,i;
    while(~scanf("%d %d",&p[n].x,&p[n].y))
    {
        n++;
    }
    sort(p+1,p+n,camp);
    for(i=0; i<n; i++)
        printf("(%d,%d)\n",p[i].x,p[i].y);
    return 0;
}
