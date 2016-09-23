/*
POJ 2187 Beauty Contest

题意：给出一些点，求平面最远点对距离的平方

思想：我们知道，平面中最远点对一定是存在于这些点所围成的凸包中，那么，我们首先用Graham's Scan算法求出凸包中的所有点，然后可以用O(n)的旋转卡壳来解决剩下的问题(当然暴力枚举也可以啦)。

*/
#include<iostream>
#include<algorithm>
#include<cmath>
#include<stdio.h>
using namespace std;
#define max(a,b) (a>b?a:b)
#define PI acos(-1)
struct point
{
    double x;
    double y;
    double distance(const point &b)const    //计算距离
    {
        return (x-b.x)*(x-b.x)+(y-b.y)*(y-b.y);
    }
    point operator-(point s)
    {
        return {x-s.x,y-s.y};
    }
} ;
point a[55000],data[55000];

int crossLeft(point p0,point p1,point p2)   //判读左转还是右转
{
    return (p1.x-p0.x)*(p2.y-p0.y)-(p1.y-p0.y)*(p2.x-p0.x);
}
bool cmp(point p1,point p2)         //极角序
{
    int tmp=crossLeft(a[0],p1,p2);
    if(tmp>0) return true;
    else if(tmp==0&&a[0].distance(p1)<a[0].distance(p2))return true;
    else return false;
}
bool cmp_x(point p1,point p2)       //坐标序
{
    if(p1.x!=p2.x)return p1.x<p2.x;
    return p1.y<p2.y;
}
void init(int n)
{
    int i,k=0;
    point p;
    scanf("%lf%lf",&a[0].x,&a[0].y);
    p=a[0];
    for(i=1; i<n; i++)
    {
        scanf("%lf%lf",&a[i].x,&a[i].y);
        if( (p.y>a[i].y) || ((p.y==a[i].y)&&(p.x>a[i].x)) )
        {
            p=a[i];
            k=i;
        }
    }
    a[k]=a[0];
    a[0]=p;
    sort(a+1,a+n,cmp);
}

int main()
{
    int N;
    while(~scanf("%d",&N))
    {
        init(N);
        for(int i=0; i<2; i++)
            data[i]=a[i];         //前两个点入栈
        int top=1;
        for(int i=2; i<N; i++)
        {
            data[++top]=a[i];     //新点进栈
            while(top>1&&crossLeft(data[top-2],data[top-1],data[top])<=0)  //向后遍历判断是否存在凹的区域
                data[top-1]=data[top],top--;                               //存在，出栈一个点
        }
        ++top;
        /* 旋转卡壳部分 */
        if(top==2)printf("%.0f\n",data[0].distance(data[1]));               //凸包退化的情况
        else
        {
            double maxx=0.0;
            int i=0,j=0;                        //某方向上的对踵点对
            for(int k=0; k<top; k++)
            {
                if(!cmp_x(data[i],data[k]))i=k;
                if(cmp_x(data[j],data[k]))j=k;
            }
            int si=i,sj=j;
            while(i!=sj||j!=si)                 //旋转180°
            {
                maxx=max(maxx,data[i].distance(data[j]));
                if(crossLeft({0,0},data[(i+1)%top]-data[i],data[(j+1)%top]-data[j])<0)
                    i=(i+1)%top;
                else j=(j+1)%top;
            }
            printf("%.0f\n",maxx);
        }
        /* END */
    }
}
