/*
POJ 3723 Conscription

要征兵n个男兵和m个女兵，每个花费10000元，但是如果已经征募的男士兵中有和将要征募的女士兵关系好的，那么可以减少花费，给出关系，求最小花费。
初始花费每人10000元，那么减去其中有关系的就是当前的花费。
为使得花费最少，那么减去最大的关系集合即可，而这个最大的关系集合也就是最大生成树。
*/
#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<set>
#include<string.h>
#define INF (1<<25)
using namespace std;

struct edge
{
    int u;
    int v;
    int cost;
} a[51000];
int p[51000],f[51000];

bool cmp(int _a,int _b)     //按边的权值排序
{
    return a[_a].cost>a[_b].cost;
}
int findd(int x)            //寻找代表元素并压缩路径
{
    if(f[x]==x)return x;
    return f[x]=findd(f[x]);
}
int kus(int n,int m)
{
    int ans=0;
    for(int i=0; i<m; i++)  //初始化并查集
        p[i]=i;
    for(int i=0; i<n; i++)
        f[i]=i;
    sort(p,p+m,cmp);
    for(int i=0; i<m; i++)
    {
        int e=p[i];
        int x=findd(a[e].u);    //权值最大边两点x,y
        int y=findd(a[e].v);
        if(x!=y)ans+=a[e].cost,f[x]=y;  //如果不会构成环，添加路径并标记集合
    }
    return ans;
}
int main()
{
    int T,n,m;
    scanf("%d",&T);
    while(T--)
    {
        int d,s;
        scanf("%d%d%d",&n,&m,&d);
        for(int i=0; i<d; i++)
        {
            scanf("%d%d%d",&a[i].u,&s,&a[i].cost);
            a[i].v=s+n;
        }
        printf("%d\n",(n+m)*10000-kus(m+n,d));
    }
    return 0;
}
