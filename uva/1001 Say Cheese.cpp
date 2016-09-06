/*
UVA 1001 Say Cheese
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<math.h>
#define INF (1<<30)
using namespace std;

struct edge
{
    double x,y,z,r;
} point[105];

double mapp[105][105];
double getlin(edge a,edge b)        //求两个球之间的距离
{
    double line=sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z));
    if(a.r+b.r>=line)return 0;
    else return line-a.r-b.r;
}
int main()
{
    int n;
    for(int T=1;~scanf("%d",&n)&&n!=-1;T++)
    {
        for(int i=2; i<n+2; i++)
            scanf("%lf%lf%lf%lf",&point[i].x,&point[i].y,&point[i].z,&point[i].r);
        for(int i=0; i<2; i++)
            scanf("%lf%lf%lf",&point[i].x,&point[i].y,&point[i].z),point[i].r=0;
        for(int i=0; i<n+2; i++,mapp[i][i]=0)
            for(int j=0; j<i; j++)
                mapp[i][j]=mapp[j][i]=getlin(point[i],point[j]);    //建图
        for(int k=0; k<n+2; k++)                                    //Floyd
            for(int i=0; i<n+2; i++)
                for(int j=0; j<n+2; j++)
                    mapp[i][j]=min(mapp[i][j],mapp[i][k]+mapp[k][j]);
        printf("Cheese %d: Travel time = %.0lf sec\n",T,mapp[0][1]*10);
    }
    return 0;
}
