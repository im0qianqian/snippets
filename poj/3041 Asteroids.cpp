/*
POJ 3041 Asteroids

把光束看做顶点，小行星看做连接顶点的边，然后就转换成了一个求解最小顶点覆盖的问题
因为是二分图，最小顶点覆盖等于最大匹配
所以采用匈牙利算法实现
*/

#include <iostream>
#include<stdio.h>
#include<string.h>
using namespace std;

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
    int k;
    scanf("%d%d",&uN,&k);
    vN=uN;
    memset(g,0,sizeof(g));
    for(int i=0; i<k; i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        g[a-1][b-1]=1;
    }
    printf("%d\n",hungary());
    return 0;
}

