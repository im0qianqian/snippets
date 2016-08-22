/*
POJ 2686 Traveling by Stagecoach
*/

#include <stdio.h>
#include<string.h>
#include<iostream>
#include<math.h>
#include<algorithm>
#define INF (1<<30)
#define MAX 35
using namespace std;
int n,m,p,a,b;
int t[MAX];
int mapp[MAX][MAX];
float dp[1<<8][MAX];
void solve()
{
    for(int i=0; i<(1<<n); i++)
        fill(dp[i],dp[i]+m,INF);
    dp[(1<<n)-1][a-1]=0;
    float res=INF;
    for(int s=(1<<n)-1; s>=0; s--)
    {
        res=min(res,dp[s][b-1]);
        for(int v=0; v<m; v++)
            for(int i=0; i<n; i++)
                if(s>>i&1)
                    for(int u=0; u<m; u++)
                        if(mapp[v][u]>=0)
                            dp[s&~(1<<i)][u]=min(dp[s&~(1<<i)][u],dp[s][v]+(float)mapp[v][u]/(float)t[i]);
    }
    if(res==INF)cout<<"Impossible"<<endl;
    else printf("%.3f\n",res);
}
int main()
{
    while(cin>>n>>m>>p>>a>>b&&(n||m||p||a||b))
    {
        for(int i=0; i<n; i++)
            cin>>t[i];
        memset(mapp,-1,sizeof(mapp));
        for(int i=0; i<p; i++)
        {
            int x,y,s;
            cin>>x>>y>>s;
            mapp[x-1][y-1]=mapp[y-1][x-1]=s;
        }
        solve();
    }
    return 0;
}
