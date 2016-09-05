/*
UVA 11396 Claw Decomposition
*/

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<vector>
#include<string.h>
#include<queue>
#define MAXX 500
using namespace std;
int vis[MAXX],n;
bool dfs(vector<int> G[MAXX])
{
    queue<int>q;
    memset(vis,0,sizeof(vis));
    q.push(0);
    vis[0]=1;
    while(!q.empty())
    {
        int p=q.front();
        q.pop();
        for(int i=0; i<(int)G[p].size(); i++)
            if(!vis[G[p][i]])
            {
                vis[G[p][i]]=-vis[p];
                q.push(G[p][i]);
            }
            else if(vis[G[p][i]]==vis[p])
                return false;
    }
    return true;
}
int main()
{
    while(~scanf("%d",&n)&&n)
    {
        int a,b;
        vector<int>G[MAXX];
        while(~scanf("%d%d",&a,&b)&&(a||b))
        {
            G[a-1].push_back(b-1);
            G[b-1].push_back(a-1);
        }
        printf(dfs(G)?"YES\n":"NO\n");
    }
    return 0;
}
