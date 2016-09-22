/*
POJ 3714 Raid
题意：给出两个集合，求第一个集合中的点到第二个集合中点的最近距离
*/

#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<algorithm>
#include<iostream>
#define INF 1e100
using namespace std;
struct point
{
    double x,y;
    bool flag;                  //判断是否在同一个集合
    double distance(point k)    //求距离
    {
        return sqrt((x-k.x)*(x-k.x)+(y-k.y)*(y-k.y));
    }
} a[220000];
int t[220000];                 //存储中心d范围内的点
bool cmp(point s,point t)
{
    return s.x<t.x;
}
bool cmpy(int s,int t)
{
    return a[s].y<a[t].y;
}
double findd(int left,int right)
{
    if(left==right)return INF;
    else if(left+1==right)
    {
        if(a[left].flag!=a[right].flag)
            return a[left].distance(a[right]);    //分割为刚好两个点的区域
        else return INF;
    }
    int mid=(left+right)>>1;
    double dl=findd(left,mid);
    double dr=findd(mid+1,right);
    dl=min(dl,dr);                      //左边和右边最近点对的最小值
    int k=0;
    for(int i=left; i<=right; i++)
        if(fabs(a[i].x-a[mid].x)<=dl)    //取出中间区域的点
            t[k++]=i;
    sort(t,t+k,cmpy);
    for(int i=0; i<k; i++)
        for(int j=i+1; j<k&&a[t[j]].y-a[t[i]].y<dl; j++)
            if(a[t[i]].flag!=a[t[j]].flag)
                dl=min(dl,a[t[i]].distance(a[t[j]]));
    return dl;
}
int main()
{
    int n;
    scanf("%d",&n);
    while(n--)
    {
        int T;
        scanf("%d",&T);
        T<<=1;
        for(int i=0; i<T; i++)
        {
            a[i].flag = (i>=T>>1);
            scanf("%lf%lf",&a[i].x,&a[i].y);
        }
        sort(a,a+T,cmp);
        double l = findd(0,T-1);
        printf("%.3f\n",l);
    }
    return 0;
}
