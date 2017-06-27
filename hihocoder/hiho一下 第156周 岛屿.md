# 岛屿

## **描述**

> 给你一张某一海域卫星照片，你需要统计：
>
> 1. 照片中海岛的数目
> 2. 照片中面积不同的海岛数目
> 3. 照片中形状不同的海岛数目
> 4. 其中海域的照片如下，"."表示海洋，"#"表示陆地。在"上下左右"四个方向上连在一起的一片陆地组成一座岛屿。
>
> ```
> .####..
> .....#.
> ####.#.
> .....#.
> ..##.#.
> ```
> 上图所示的照片中一共有4座岛屿；其中3座面积为4，一座面积为2，所以不同面积的岛屿数目是2；有两座形状都是"####"，所以形状不同的岛屿数目为3。



## **输入**

> 第一行包含两个整数：N 和 M，(1 ≤ N, M ≤ 50)，表示照片的行数和列数。
>
> 以下一个 N * M 的矩阵，表示表示海域的照片。



## **输出**

> 输出3个整数，依次是照片中海岛的数目、面积不同的海岛数目和形状不同的海岛数目。



## **样例输入**

    5 7
    .####..
    .....#.
    ####.#.
    .....#.
    ..##.#.



## **样例输出**

    4 2 3


## **思路**

用一个数组标记某个点是否被访问，然后 `dfs` 遍历整张地图，分别记录每个联通块的内容。

最后输出联通块的数量以及不同的联通块大小，比较某两个联通块形状是否相同可以先把它移动到原点（左上角），然后再比较内容。（毕竟数据很小）



## **AC 代码**

```cpp
#include <iostream>
#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f

const int N = 55;
char mapp[N][N];
bool isvis[N][N];
vector<int>G[N*N];
int minn[N*N];
int n,m;
int ind;
const int mv[4][2]= {{-1,0},{1,0},{0,-1},{0,1}};

void dfs(int x,int y)
{
    isvis[x][y]=true;               //标记已访问
    G[ind].push_back(x*n+y);        //记录当前联通块坐标
    minn[ind]=min(minn[ind],x*n+y); //当前联通块中的最小坐标
    for(int i=0; i<4; i++)          //四个方向
    {
        int xi=x+mv[i][0];
        int yi=y+mv[i][1];
        if(xi<0||xi>=n||yi<0||yi>=m||isvis[xi][yi])continue;    //不成立
        dfs(xi,yi);
    }
}

void solve()
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            if(!isvis[i][j])        //遇到一个联通块
            {
                G[ind].clear();
                dfs(i,j);
                ind++;
            }
        }
    }
    set<int> size;
    set<vector<int> > area;
    for(int i=0; i<ind; i++)    //图像移至原点
    {
        for(int j=0; j<(int)G[i].size(); j++)
            G[i][j]-=minn[i];
    }
    for(int i=0; i<ind; i++)
    {
        size.insert(G[i].size());   //块大小
        area.insert(G[i]);          //块内容
    }
    cout<<ind<<" "<<size.size()<<" "<<area.size()<<endl;
}

int main()
{
    while(scanf("%d%d%*c",&n,&m)!=EOF)
    {
        memset(isvis,false,sizeof(isvis));
        memset(minn,INF,sizeof(minn));
        ind=0;
        for(int i=0; i<n; i++)
        {
            gets(mapp[i]);
            for(int j=0; j<m; j++)
            {
                if(mapp[i][j]=='.')
                    isvis[i][j]=true;
            }
        }
        solve();
    }
    return 0;
}
```

