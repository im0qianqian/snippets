/*
51node 1212 无向图最小生成树
*/

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<vector>
#include<string.h>
#include<map>
#define INF (1<<30)
using namespace std;
int cost[1005][1005];
int mincost[1005];
int n,m,used[1005];
void prim()
{
    fill(mincost,mincost+n,INF);
    mincost[0]=0;
    int res=0;
    while(true)
    {
        int v=-1;
        for(int i=0; i<n; i++)          //寻找距离当前集合最近的点
            if(!used[i]&&(v==-1||mincost[i]<mincost[v]))
                v=i;
        if(v==-1)break;
        used[v]=true;
        res+=mincost[v];                //添加一条边
        for(int i=0; i<n; i++)          //更新点到集合的距离
            mincost[i]=min(mincost[i],cost[v][i]);
    }
    printf("%d\n",res);
}
int main()
{
    int a,b,co;
    scanf("%d%d",&n,&m);
    for(int i=0; i<n; i++)
    {
        fill(cost[i],cost[i]+n,INF);
        cost[i][i]=0;
    }
    for(int i=0; i<m; i++)
    {
        scanf("%d%d%d",&a,&b,&co);
        cost[a-1][b-1]=cost[b-1][a-1]=co;
    }
    prim();
    return 0;
}
