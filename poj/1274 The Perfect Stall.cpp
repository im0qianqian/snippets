/*
POJ 1274 The Perfect Stall

二分图匹配模版题目 匈牙利算法实现
*/

#include <iostream>
#include <vector>
#include<stdio.h>
#include<queue>
#include<string.h>
#define INF (1<<25)
#define MAXX 255
using namespace std;

//顶点编号从0开始的
const int MAXN=510;
int uN,vN;//u,v数目
int g[MAXN][MAXN];
int linker[MAXN];
bool used[MAXN];
bool dfs(int u)//从左边开始找增广路径
{
    int v;
    for(v=0; v<vN; v++) //这个顶点编号从0开始，若要从1开始需要修改
        if(g[u][v]&&!used[v])
        {
            used[v]=true;
            if(linker[v]==-1||dfs(linker[v]))
            {
                //找增广路，反向
                linker[v]=u;
                return true;
            }
        }
    return false;//这个不要忘了，经常忘记这句
}

int hungary()
{
    int res=0;
    int u;
    memset(linker,-1,sizeof(linker));
    for(u=0; u<uN; u++)
    {
        memset(used,0,sizeof(used));
        if(dfs(u))res++;
    }
    return res;
}

int main()
{
    while(~scanf("%d%d",&uN,&vN))
    {
        int s,n;
        memset(g,0,sizeof(g));
        for(int j=0; j<uN; j++)
        {
            scanf("%d",&s);
            for(int i=0; i<s; i++)
            {
                scanf("%d",&n);
                g[j][n-1]=1;
            }
        }
        printf("%d\n",hungary());
    }
    return 0;
}
