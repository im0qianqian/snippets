/*
HDU 2444 The Accomodation of Students
*/

#include <stdio.h>
#include<string.h>
#include<iostream>
#include<math.h>
#include<algorithm>
#include<list>
#include<map>
#include<queue>
using namespace std;

int N,M;
bool mapp[205][205];
int vis[205];
int linker[205];

bool dfs()
{
    queue<int>q;
    memset(vis,0,sizeof(vis));
    q.push(0);
    vis[0]=1;                           //从0点开始，颜色为1
    while(!q.empty())
    {
        int p=q.front();
        q.pop();
        for(int i=0; i<N; i++)
            if(mapp[p][i])
            {
                if(vis[i]==0)           //若临接的点有没有访问过的
                {
                    vis[i]=-vis[p];     //涂色不同于当前点
                    q.push(i);          //新点加入
                }
                else if(vis[i]==vis[p]) //若相邻点颜色相同
                    return false;
            }
    }
    return true;
}

bool xyl(int i)
{
    for(int j=0; j<N; j++)
    {
        if(!vis[j]&&mapp[i][j])         //未访问并且临接
        {
            vis[j]=1;
            if(linker[j]==0||xyl(linker[j])) //找增广路，反向
            {
                linker[j]=i;
                return true;
            }
        }
    }
    return false;
}
int main()
{
    while(~scanf("%d%d",&N,&M))
    {
        int a,b,ans=0;
        memset(mapp,false,sizeof(mapp));
        for(int i=0; i<M; i++)
        {
            scanf("%d%d",&a,&b);
            mapp[a-1][b-1]=mapp[b-1][a-1]=true;     //邻接矩阵
        }
        if(dfs()&&N!=1)                             //判断是否是二分图
        {
            memset(linker,0,sizeof(linker));        //与集合B临接的点
            for(int i=0; i<N; i++)
            {
                memset(vis,0,sizeof(vis));
                if(xyl(i))ans++;
            }
            printf("%d\n",ans/2);                   //因为是无向图，有对称性
        }
        else printf("No\n");
    }
    return 0;
}
