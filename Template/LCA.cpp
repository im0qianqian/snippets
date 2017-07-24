// POJ 1130

#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

const int maxn=10001;
int fa[maxn];
int rank[maxn];
int indegree[maxn];     //入度
bool visit[maxn];
vector<int> tree[maxn],Qes[maxn];
int ancestor[maxn];

void init(int n)
{
    memset(rank,0,sizeof(rank));
    memset(visit,false,sizeof(visit));
    memset(indegree,0,sizeof(indegree));
    memset(ancestor,0,sizeof(ancestor));
    for(int i=1; i<=n; i++)
    {
        fa[i]=i;
        tree[i].clear();
        Qes[i].clear();
    }
}

int find_set(int x)     //并查集 查询+路径压缩
{
    if(x!=fa[x])
        fa[x]=find_set(fa[x]);
    return fa[x];
}

void union_set(int x,int y)     //并查集 合并
{
    x=find_set(x);
    y=find_set(y);
    if(rank[x]>rank[y])
        fa[y]=x;
    else
    {
        fa[x]=y;
        if(rank[x]==rank[y])
            rank[y]++;
    }
}


void LCA(int u)
{
    ancestor[u]=u;
    int len = tree[u].size();
    for(int i=0; i<len; i++)
    {
        LCA(tree[u][i]);
        union_set(u,tree[u][i]);
        ancestor[find_set(u)]=u;
    }
    visit[u]=true;
    len = Qes[u].size();
    for(int i=0; i<len; i++)
    {
        if(visit[Qes[u][i]])    //如果该点之前访问过，输出最近公共祖先
        {
            cout<<ancestor[find_set(Qes[u][i])]<<endl;
            return;
        }
    }
}


int main()
{
    int cnt;
    int n;
    cin>>cnt;
    while(cnt--)
    {
        cin>>n;;
        init(n);
        int s,t;
        for(int i=1; i<n; i++)
        {
            cin>>s>>t;
            tree[s].push_back(t);
            indegree[t]++;
        }
        cin>>s>>t;
        Qes[s].push_back(t);
        Qes[t].push_back(s);
        for(int i=1; i<=n; i++)
            if(!indegree[i])
            {
                LCA(i);
                break;
            }
    }
    return 0;
}