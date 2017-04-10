# Grandpa's Estate

## **Description**

> Being the only living descendant of his grandfather, Kamran the Believer inherited all of the grandpa's belongings. The most valuable one was a piece of convex polygon shaped farm in the grandpa's birth village. The farm was originally separated from the neighboring farms by a thick rope hooked to some spikes (big nails) placed on the boundary of the polygon. But, when Kamran went to visit his farm, he noticed that the rope and some spikes are missing. Your task is to write a program to help Kamran decide whether the boundary of his farm can be exactly determined only by the remaining spikes.



## **Input**

> The first line of the input file contains a single integer t (1 <= t <= 10), the number of test cases, followed by the input data for each test case. The first line of each test case contains an integer n (1 <= n <= 1000) which is the number of remaining spikes. Next, there are n lines, one line per spike, each containing a pair of integers which are x and y coordinates of the spike.



## **Output**

> There should be one output line per test case containing YES or NO depending on whether the boundary of the farm can be uniquely determined from the input.



## **Sample Input**

    1
    6 
    0 0
    1 2
    3 4
    2 0
    2 4 
    5 0



## **Sample Output**

    NO



## **题意**

判断一个凸包每个边是否至少有三个点。



## **思路**

首先用给出的点构造凸包，然后对每一条边枚举所有的点，看是否有其他点在这条边上。（注意所有点都在同一条直线上的情况）



## **AC 代码**

```cpp
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
```

