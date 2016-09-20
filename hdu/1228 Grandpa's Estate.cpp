/*
POJ 1228 Grandpa's Estate

题意：判断一个凸包每个边是否至少有三个点，注意所有点都在同一条直线上的情况

解题思路：首先用给出的点构造凸包，然后对每一条边枚举所有的点，看是否有其他点在这条边上
*/

#include<iostream>
#include<algorithm>
#include<stack>
#include<stdio.h>
#include<cmath>
using namespace std;
#define PI acos(-1)
struct Point
{
    double x,y;
    double distance(Point a)    //计算两点距离
    {
        return hypot(x-a.x,y-a.y);
    }
} a[1005];
int crossLeft(Point p0,Point p1,Point p2)   //判断左转还是右转
{
    return (p1.x-p0.x)*(p2.y-p0.y)-(p1.y-p0.y)*(p2.x-p0.x);
}
bool cmp(Point b,Point c)                   //极角排序比较函数
{
    int tmp = crossLeft(a[0],b,c);
    if(tmp>0)return true;
    else if(tmp==0&&a[0].distance(b)<a[0].distance(c))return true;  //如果极角相同按距离从近到远
    return false;
}
void init(int n)
{
    Point p;
    int k=0;
    scanf("%lf%lf",&a[0].x,&a[0].y);
    p=a[0];                 //p为最左下角的点
    for(int i=1; i<n; i++)
    {
        scanf("%lf%lf",&a[i].x,&a[i].y);
        if(a[i].y<p.y||(a[i].y==p.y&&a[i].x<p.x))
        {
            p=a[i];
            k=i;
        }
    }
    a[k]=a[0];
    a[0]=p;
    sort(a+1,a+n,cmp);
}
bool pointinline(Point Pi,Point Pj,int n)
{
    for(int i=0; i<n; i++)
    {
        Point Q=a[i];
        if((!((Pi.x==Q.x&&Pi.y==Q.y)||(Pj.x==Q.x&&Pj.y==Q.y)))&&(Q.x - Pi.x) * (Pj.y - Pi.y) == (Pj.x - Pi.x) * (Q.y - Pi.y)    //若点在线段内部
                && min(Pi.x, Pj.x) <= Q.x && Q.x <= max(Pi.x, Pj.x)
                && min(Pi.y, Pj.y) <= Q.y && Q.y <= max(Pi.y, Pj.y))
            return false;
    }
    return true;
}
bool judge(Point *st,int top,int N)
{
    if(top<2)return false;          //如果所有的点在一条直线上
    for(int i=1; i<=top; i++)
        if(pointinline(st[i-1],st[i],N))return false;   //如果有边中没有第三个点存在
    if(pointinline(st[top],st[0],N))return false;
    return true;
}
int main()
{
    int N,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&N);
        init(N);
        if(N<6)             //稳定凸包最小构成的点为6
        {
            printf("NO\n");
            continue;
        }
        Point st[1005];
        int top =1;
        for(int i=0; i<2; i++)
            st[i]=a[i];
        for(int i=2; i<N; i++)
        {
            st[++top]=a[i];
            while(top>1&&crossLeft(st[top-2],st[top-1],st[top])<=0) //如果有凹存在
                st[top-1]=st[top],--top;                            //出栈
        }
        printf(judge(st,top,N)?"YES\n":"NO\n");
    }
}
