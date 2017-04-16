# Anniversary party

## **Problem Description**

> There is going to be a party to celebrate the 80-th Anniversary of the Ural State University. The University has a hierarchical structure of employees. It means that the supervisor relation forms a tree rooted at the rector V. E. Tretyakov. In order to make the party funny for every one, the rector does not want both an employee and his or her immediate supervisor to be present. The personnel office has evaluated conviviality of each employee, so everyone has some number (rating) attached to him or her. Your task is to make a list of guests with the maximal possible sum of guests' conviviality ratings.



## **Input**

> Employees are numbered from 1 to N. A first line of input contains a number N. 1 <= N <= 6 000. Each of the subsequent N lines contains the conviviality rating of the corresponding employee. Conviviality rating is an integer number in a range from -128 to 127. After that go T lines that describe a supervisor relation tree. Each line of the tree specification has the form: 
>
> L K 
>
> It means that the K-th employee is an immediate supervisor of the L-th employee. Input is ended with the line 
>
> 0 0



## **Output**

> Output should contain the maximal sum of guests' ratings.



## **Sample Input**

    7
    1
    1
    1
    1
    1
    1
    1
    1 3
    2 3
    6 4
    7 4
    4 5
    3 5
    0 0



## **Sample Output**

    5



## **题意**

输入 `n` 个节点以及这些节点的活跃值，然后输入 `a b` ，代表 `b` 是 `a` 的上司，有直接关系的上司和下属不能同时参加Patty，求Patty的最大活跃值。



## **思路**

可以先按照给出的关系建树。

每一个节点有两种状态，参加与不参加， `0` 代表不参加， `1` 代表参加。

我们定义 `dp[i][0]` 为以 `i` 为根的子树且 `i` 不参加所能得到的最大活跃值， `dp[i][1]` 为 `i` 参加所能得到的最大活跃值。



**状态转移方程：** 

`dp[i][0]+=max(dp[j][1],dp[j][0]);`

`dp[i][1]+=dp[j][0];`

其中 `j` 是 `i` 的所有下属。



## **AC 代码**

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<iostream>
using namespace std;
#include<queue>
#include<stack>

int N;
int GS[6100][2];
int a[6100];
vector<int>G[6100];
bool vis[6100];

void dfs(int x)
{
    int len=G[x].size();
    GS[x][0]=0;
    GS[x][1]=a[x];
    for(int i=0; i<len; i++)
    {
        dfs(G[x][i]);
        GS[x][0]+=max(GS[G[x][i]][1],GS[G[x][i]][0]);
        GS[x][1]+=GS[G[x][i]][0];
    }
}

int main()
{
    while(~scanf("%d",&N)&&N)
    {
        int aa,bb;
        for(int i=1; i<=N; i++)
        {
            scanf("%d",a+i);
            G[i].clear();
        }
        memset(vis,false,sizeof(vis));
        while(~scanf("%d%d",&aa,&bb)&&(aa||bb))
        {
            G[bb].push_back(aa);
            vis[aa]=true;
        }
        int ans=0;
        for(int i=1; i<=N; i++)
        {
            if(!vis[i])
            {
                dfs(i);
                ans+=max(GS[i][0],GS[i][1]);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
```

