/* **************************************************************************/
//二分图匹配（匈牙利算法的DFS实现）
//初始化：g[][]两边顶点的划分情况
//建立g[i][j]表示i->j的有向边就可以了，是左边向右边的匹配
//g没有边相连则初始化为0
//uN是匹配左边的顶点数，vN是匹配右边的顶点数
//调用：res=hungary();输出最大匹配数
//优点：适用于稠密图，DFS找增广路，实现简洁易于理解
//时间复杂度:O(VE)
//***************************************************************************/

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

//******************************************************************************/
