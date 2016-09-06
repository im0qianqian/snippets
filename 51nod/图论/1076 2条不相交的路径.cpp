/*
51nod 1076 2条不相交的路径
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include<vector>
using namespace std;
#define M 30000             //题目中可能的最大点数

int STACK[M],top;           //Tarjan算法中的栈
bool InStack[M];            //检查是否在栈中
int DFN[M];                 //深度优先搜索访问次序
int Low[M];                 //能追溯到的最早的次序
int ComponentNumber;        //有向图强连通分量个数
int Index=0;                //索引号
vector<int> Edge[M];        //邻接表表示
int InComponent[M];         //记录每个点在第几号强连通分量里

int n,m;
void Tarjan(int i,int fa)
{
    int j;
    DFN[i]=Low[i]=++Index;
    InStack[i]=true;
    STACK[++top]=i;
    for (int e=0; e<(int)Edge[i].size(); e++)
    {
        j=Edge[i][e];
        if (DFN[j]==-1)     //如果未访问
        {
            Tarjan(j,i);
            Low[i]=min(Low[i],Low[j]);
        }
        else if (InStack[j]&&j!=fa)
            Low[i]=min(Low[i],DFN[j]);
    }
    if (DFN[i]==Low[i])
    {
        ComponentNumber++;
        do
        {
            j=STACK[top--];
            InStack[j]=false;
            InComponent[j]=ComponentNumber;
        }
        while (j!=i);
    }
}
void solve()
{
    memset(DFN,-1,sizeof(DFN));
    for(int i=1; i<=m; i++)
        if(DFN[i]==-1)
            Tarjan(i,-1);
}
int main ()
{
    int a,b;
    scanf("%d%d",&m,&n);
    for(int i=0; i<n; i++)
    {
        scanf("%d%d",&a,&b);
        Edge[a].push_back(b);
        Edge[b].push_back(a);
    }
    solve();
    scanf("%d",&m);
    while(m--)
    {
        scanf("%d%d",&a,&b);
        printf(InComponent[a]==InComponent[b]?"Yes\n":"No\n");
    }
    return 0;
}
