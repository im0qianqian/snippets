/*
UVA 10397 Connect the Campus
*/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<math.h>
#define INF (1<<30)
using namespace std;
struct point
{
    double x,y;
} po[10005];
int T;
double mapp[1005][1005];
double mincost[10005];
int used[10005];
double getmul(point a,point b)  //求距离
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
void prim()                     //prim模版
{
    fill(mincost,mincost+T,INF);
    memset(used,0,sizeof(used));
    mincost[0]=0;
    double res=0;
    while(true)
    {
        int v=-1;
        for(int i=0; i<T; i++)
            if(!used[i]&&(v==-1||mincost[i]<mincost[v]))
                v=i;
        if(v==-1)break;
        used[v]=true;
        res+=mincost[v];
        for(int i=0; i<T; i++)
            mincost[i]=min(mincost[i],mapp[v][i]);
    }
    printf("%.2lf\n",res);
}
int main()
{
    while(~scanf("%d",&T))
    {
        memset(mapp,0,sizeof(mapp));
        for(int i=0; i<T; i++)
            scanf("%lf%lf",&po[i].x,&po[i].y);
        for(int i=0; i<T; i++)
            for(int j=0; j<i; j++)
                mapp[i][j]=mapp[j][i]=getmul(po[i],po[j]);  //建图
        int n,s,t;
        scanf("%d",&n);
        while(n--)
        {
            scanf("%d%d",&s,&t);
            mapp[s-1][t-1]=mapp[t-1][s-1]=0;                //已有的路线为0
        }
        prim();
    }
    return 0;
}
