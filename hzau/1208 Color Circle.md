# Color Circle

## **Description**

> There are colorful flowers in the parterre in front of the door of college and form many beautiful patterns. Now, you want to find a circle consist of flowers with same color. What should be done ?
>
> Assuming the flowers arranged as matrix in parterre, indicated by a N*M matrix. Every point in the matrix indicates the color of a flower. We use the same uppercase letter to represent the same kind of color. We think a sequence of points d1, d2, … dk makes up a circle while:
>
> 1. Every point is different.
>
> 2. k >= 4
>
> 3. All points belong to the same color.
>
> 4. For 1 <= i <= k-1, di is adjacent to di+1 and dk is adjacent to d1. ( Point x is adjacent to Point y while they have the common edge).
>
>
> N, M <= 50. Judge if there is a circle in the given matrix. 



## **Input**

> There are multiply test cases.
>
> In each case, the first line are two integers n and m, the 2nd ~ n+1th lines is the given n*m matrix. Input m characters in per line. 



## **Output**

> Output your answer as “Yes” or ”No” in one line for each case. 



## **Sample Input**

    3 3
    AAA
    ABA
    AAA



## **Sample Output**

    Yes



## **题意**

对于一个点，找长度大于4，相同字母，并且回到原点。



## **思路**

找图中的一个环，可以从某个点进入开始 $dfs$ ，标记已经访问过的点，如果遍历过程中遇到它们，则找到一个环，输出 `Yes` ，否则输出 `No` 。

**时间复杂度：** $O(n)$



## **AC 代码**

```cpp
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
#define MAXX 110000

int n,m;
int mapp[55][55];
bool vis[55][55];
int mv[4][2]= {{-1,0},{1,0},{0,-1},{0,1}};
bool flag;

void dfs(int x,int y,int xa,int ya) // (x,y) 为当前点坐标， (xa,ya) 为它从哪个点来
{
    for(int i=0; i<4; i++)  // 四个方向
    {
        int xi=x+mv[i][0];
        int yi=y+mv[i][1];
        if(xi<0||xi>=n||yi<0||yi>=m||mapp[xi][yi]!=mapp[x][y])continue; // 要求搜索的点相同
        if(!vis[xi][yi])
        {
            vis[xi][yi]=true;
            dfs(xi,yi,x,y);
            if(flag)return;
        }
        else
        {
            if(xi==xa&&yi==ya)continue; // 忽略来的那一点，如果还遇到一个已经访问的点，则是一个环
            flag=true;
            return;
        }
    }
}

void solve()
{
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            if(!vis[i][j])
            {
                vis[i][j]=true;
                dfs(i,j,-1,-1);
                if(flag)
                {
                    cout<<"Yes"<<endl;
                    return;
                }
            }
    cout<<"No"<<endl;
}

int main()
{
    while(cin>>n>>m)
    {
        string c;
        memset(vis,false,sizeof(vis));
        flag=false;
        for(int i=0; i<n; i++)
        {
            cin>>c;
            for(int j=0; j<m; j++)
                mapp[i][j]=c[j];
        }
        solve();
    }
    return 0;
}
```

