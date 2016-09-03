/*
POJ 3255 Roadblocks
*/

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<vector>
#include<queue>
#define MAXN 5005
#define INF (1<<30)
using namespace std;

struct edge
{
    int to;
    int cost;
};

typedef pair<int,int>P;
vector<edge>G[MAXN];
int n,r;
int dist[MAXN],dist2[MAXN];

void solve()
{
    priority_queue<P,vector<P>,greater<P> >que; //小顶堆优化
    fill(dist,dist+n,INF);
    fill(dist2,dist2+n,INF);
    dist[0]=0;
    que.push(P(0,0));
    while(!que.empty())
    {
        P p=que.top();
        que.pop();
        int v=p.second,d=p.first;
        if(dist2[v]<d)continue;

        for(int i=0; i<(int)G[v].size(); i++)
        {
            edge e=G[v][i];
            int d2=d+e.cost;
            if(dist[e.to]>d2)
            {
                swap(dist[e.to],d2);
                que.push(P(dist[e.to],e.to));
            }
            if(dist2[e.to]>d2&&dist[e.to]<d2)
            {
                dist2[e.to]=d2;
                que.push(P(dist2[e.to],e.to));
            }
        }
    }
    printf("%d\n",dist2[n-1]);
}
int main()
{
    scanf("%d%d",&n,&r);
    for(int i=0; i<r; i++)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        G[a-1].push_back({b-1,c});      //图的邻接表存储
        G[b-1].push_back({a-1,c});
    }
    solve();
    return 0;
}
