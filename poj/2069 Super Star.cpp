/*
POJ 2069 Super Star

题意：在三维空间内给出一些点的坐标，求出把所有点都包含在内的球的最小半径。

思想：模拟退火，首先找到一个步长平均的点，然后每次靠近距离该点最远的点，循环多次之后便到达中心
*/
#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<iostream>
using namespace std;
struct point
{
    double x,y,z;
    double ditence(point k)
    {
        return sqrt((x-k.x)*(x-k.x)+(z-k.z)*(z-k.z)+(y-k.y)*(y-k.y));
    }
    void operator/=(int n)
    {
        x/=n;
        y/=n;
        z/=n;
    }
    void operator+=(point k)
    {
        x+=k.x;
        y+=k.y;
        z+=k.z;
    }
    point operator-(point k)
    {
        return {x-k.x,y-k.y,z-k.z};
    }
    point operator*(double k)
    {
        return {x*k,y*k,z*k};
    }
};
int main()
{
    int n;
    while(cin>>n&&n)
    {
        point a[n],po;
        po.x=po.y=po.z=0;
        for(int i=0; i<n; i++)
        {
            cin>>a[i].x>>a[i].y>>a[i].z;
            po+=a[i];
        }
        po/=n;               //计算初始平均位置的点
        double step=0.1,s,t;
        for(int i=0; i<30000; i++)
        {
            int k=0;
            t=0;
            for(int j=0; j<n; j++)
            {
                s=po.ditence(a[j]); //求两点距离
                if(s>t)t=s,k=j;
            }
            po+=(a[k]-po)*step;     //靠近最远点
            step*=0.999;
        }
        printf("%.5f\n",t);
    }
    return 0;
}
