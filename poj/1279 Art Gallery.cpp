/*
POJ 1279 Art Gallery

题意：给出一个n个点的多边形，求多边形核的面积；
多边形的核即为多边形内部的点集，使其中的点可以看到多边形的任意顶点和边；
*/
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cmath>
#define eps 1e-8
using namespace std;
struct point
{
    double x;
    double y;
    double distance(point k)    //求距离
    {
        return sqrt((x-k.x)*(x-k.x)+(y-k.y)*(y-k.y));
    }
} a[1505],tp[1505];
void getline(point x,point y,double &a,double &b,double &c) //求直线方程
{
    b=x.x-y.x;
    a=y.y-x.y;
    c=y.x*x.y-x.x*y.y;
}
double xmul(point p0,point p1,point p2)     //求叉积
{
    return (p1.x-p0.x)*(p2.y-p0.y)-(p1.y-p0.y)*(p2.x-p0.x);
}
double area(int n)              //求面积，正为顺时针，和叉积写法有关
{
    double s=0;
    for(int i=2; i<n; i++)
        s+=xmul(a[1],a[i],a[i+1]);
    return -s/2.0;
}
void dir(int n) //改变顺续
{
    for(int i=1; i<=n/2; i++)
        swap(a[i],a[n+1-i]);
}
//求交点
point Intersection(point p1,point p2,double a,double b,double c)
{
    double u=fabs(a*p1.x+b*p1.y+c);
    double v=fabs(a*p2.x+b*p2.y+c);
    point t;
    t.x=(p1.x*v+p2.x*u)/(u+v);
    t.y=(p1.y*v+p2.y*u)/(u+v);
    return t;
}
void cut(double aa,double b,double c,int &n)    //切割
{
    int tmp=0;
    for(int i=1; i<=n; i++)
    {
        //当前点在右侧
        if(aa*a[i].x+b*a[i].y+c>-eps)tp[++tmp]=a[i];
        else
        {
            //前一个点在右侧，产生交点
            if(aa*a[i-1].x+b*a[i-1].y+c>-eps)
                tp[++tmp]=Intersection(a[i-1],a[i],aa,b,c);
            if(aa*a[i+1].x+b*a[i+1].y+c>-eps)
                tp[++tmp]=Intersection(a[i],a[i+1],aa,b,c);
        }
    }
    for(int i=1; i<=tmp; i++)
        a[i]=tp[i];
    a[0]=a[tmp],a[tmp+1]=a[1];
    n=tmp;
}
void solve(int n)
{
    point sk[1505];
    if(area(n)<eps)dir(n);
    a[0]=a[n],a[n+1]=a[1];
    //记录原来点的坐标
    for(int i=0; i<=1+n; i++)sk[i]=a[i];
    int cnt=n;
    for(int i=1; i<=n; i++)
    {
        double aa,b,c;
        getline(sk[i],sk[i+1],aa,b,c);
        cut(aa,b,c,cnt);
    }
    printf("%.2f\n",fabs(area(cnt)));
}
int main()
{
    int N;
    scanf("%d",&N);
    while(N--)
    {
        int n;
        scanf("%d",&n);
        for(int i=1; i<=n; i++)
            scanf("%lf%lf",&a[i].x,&a[i].y);
        solve(n);
    }
}
