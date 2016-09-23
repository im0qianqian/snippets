/*
POJ 2187 Beauty Contest

题意：给出一些点，求平面最远点对距离的平方

思想：我们知道，平面中最远点对一定是存在于这些点所围成的凸包中，那么，我们首先用Graham's Scan算法求出凸包中的所有点，然后枚举这些点就可以了
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
} ;
point a[55000];
struct stack
{
    point data[55000];
    int top;
} st;
point minn;
int crossLeft(point p0,point p1,point p2)   //判读左转还是右转
{
    return (p1.x-p0.x)*(p2.y-p0.y)-(p1.y-p0.y)*(p2.x-p0.x);
}
bool cmp(point p1,point p2)
{
    int tmp=crossLeft(a[0],p1,p2);
    if(tmp>0) return true;
    else if(tmp==0&&a[0].distance(p1)<a[0].distance(p2))return true;
    else return false;
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
            st.data[i]=a[i];            //前两个点入栈
        st.top=1;
        for(int i=2; i<N; i++)
        {
            st.data[++st.top]=a[i];     //新点进栈
            while(st.top>1&&crossLeft(st.data[st.top-2],st.data[st.top-1],st.data[st.top])<=0)  //向后遍历判断是否存在凹的区域
                st.data[st.top-1]=st.data[st.top],st.top--;                                     //存在，出栈一个点
        }
        double maxx=0.0;
        for(int i=0; i<=st.top; i++)
            for(int j=i+1; j<=st.top; j++)
                maxx=max(maxx,st.data[i].distance(st.data[j]));
        printf("%.0f\n",maxx);
    }
}
