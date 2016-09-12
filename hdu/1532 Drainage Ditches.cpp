/*
HDU 1532 Drainage Ditches
*/

#include <iostream>
#include <vector>
#include<stdio.h>
#include<string.h>
#define INF (1<<25)
#define MAXX 1100
using namespace std;

struct node
{
    int to;
    int cap;    //容量
    int rev;    //反向边
};

vector<node>v[MAXX];
bool used[MAXX];

int dfs(int s,int t,int f)
{
    if(s==t)return f;
    used[s]=true;
    for(int i=0; i<v[s].size(); i++)
    {
        node &tmp=v[s][i];
        if(!used[tmp.to]&&tmp.cap>0)
        {
            int d=dfs(tmp.to,t,min(f,tmp.cap));
            if(d>0)
            {
                tmp.cap-=d;
                v[tmp.to][tmp.rev].cap+=d;
                return d;
            }
        }
    }
    return 0;
}
int maxxflow(int s,int t)
{
    int flow=0;
    while(true)
    {
        memset(used,false,sizeof(used));
        int f=dfs(s,t,INF);     //寻找增广路
        if(!f)return flow;
        flow+=f;
    }
    return 0;
}
int main()
{
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        memset(v,0,sizeof(v));
        for(int i=0; i<n; i++)
        {
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            v[x].push_back({y,z,v[y].size()});      //有重边
            v[y].push_back({x,0,v[x].size()-1});
        }
        printf("%d\n",maxxflow(1,m));
    }
    return 0;
}
