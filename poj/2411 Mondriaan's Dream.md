# Mondriaan's Dream

## **Description**

> Squares and rectangles fascinated the famous Dutch painter Piet Mondriaan. One night, after producing the drawings in his 'toilet series' (where he had to use his toilet paper to draw on, for all of his paper was filled with squares and rectangles), he dreamt of filling a large rectangle with small rectangles of width 2 and height 1 in varying ways.
>
> ![img](https://www.dreamwings.cn/wp-content/uploads/2017/04/2411_1.gif)
>
> Expert as he was in this material, he saw at a glance that he'll need a computer to calculate the number of ways to fill the large rectangle whose dimensions were integer values, as well. Help him, so that his dream won't turn into a nightmare!



## **Input**

> The input contains several test cases. Each test case is made up of two integer numbers: the height h and the width w of the large rectangle. Input is terminated by h=w=0. Otherwise, 1<=h,w<=11.



## **Output**

> For each test case, output the number of different ways the given rectangle can be filled with small rectangles of size 2 times 1. Assume the given large rectangle is oriented, i.e. count symmetrical tilings multiple times.
>
> ![img](https://www.dreamwings.cn/wp-content/uploads/2017/04/2411_2.gif)



## **Sample Input**

    1 2
    1 3
    1 4
    2 2
    2 3
    2 4
    2 11
    4 11
    0 0



## **Sample Output**

    1
    0
    1
    2
    3
    5
    144
    51205



## **题意**

给出一个 `n×m` 的方格，问用 `1×2` 的小方格来填充总共有多少种方法。



## **思路**

我们定义 `dp[i][j]` 代表第 `i-1` 行已经放满，第 `i` 行状态为 `j` 时候的方案数。

其中每一行的状态我们可以用一个二进制来表示， `0` 代表未填充， `1` 代表已填充。



**因为方块有两种摆放形式：竖放、横放**

所以当第 `i` 行第 `j` 列竖放一个方块时，第 `i-1` 行第 `j` 列需要留空；而当第 `i` 行第 `j` 列与第 `j+1` 列横放一个方块时，第 `i-1` 行第 `j` 列与第 `j+1` 列则需已填充，因为我们定义的 `dp` 需要把第 `i-1` 行全部放满。

**状态转移方程：** $dp[i][s]=sum(dp[i-1][si])$ 其中状态 `s` 与状态 `si` 必须兼容，也就是状态 `s` 中竖放的块能够填满状态 `si` 中的空。



这里有一个优化，也就是当 $n×m$ 结果为奇数的时候，无论怎样都不可能成功放置，因为每一个块的面积是偶数。



## **AC 代码**

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;

#define MAX ((1<<11)+10)
typedef __int64 LL;
int n,m;

LL dp[15][MAX];
LL ans[15][15];

bool jud(int x) // 判断 x 二进制中是否存在独立的1
{
    bool is1=false;
    for(int i=0; i<m; i++)
    {
        if(x&(1<<i))
            is1=!is1;
        else if(is1)return false;
    }
    return true;
}

bool ok(int s, int ss)  //判断状态s与状态ss是否兼容
{
    for(int j=0; j<m; )
        if(s & (1<<j)) //第i行第j列为1
        {
            if( ss & (1<<j)) //第i-1行第j列也为1，那么第i行必然是横放
            {
                //第i行和第i-1行的第j+1都必须是1，否则是非法的
                if( j==m-1 || !(s&1<<(j+1)) || !(ss&(1<<(j+1))) ) return false;
                else  j+=2;
            }
            else j++; //第i-1行第j列为0，说明第i行第j列是竖放
        }
        else //第i行第j列为0，那么第i-1行的第j列应该是已经填充了的
        {
            if(ss&(1<<j)) j++;//已经填充
            else return false;
        }
    return true;
}

void solve()
{
    int maxs;
    if(n<m)swap(n,m);   // 交换之后可以得到更小的状态数
    maxs=(1<<m)-1;      // 状态全1的情况
    memset(dp,0,sizeof(dp));
    for(int i=0; i<=maxs; i++)  // 初始化第一行
        dp[1][i]=jud(i);
    for(int c=2; c<=n; c++)     // 枚举 [2,n] 行
        for(int i=0; i<=maxs; i++)  // 第i行的状态
            for(int si=0; si<=maxs; si++)   //第i-1行的状态
                if(ok(i,si))
                    dp[c][i]+=dp[c-1][si];
    ans[n][m]=ans[m][n]=dp[n][maxs];
    printf("%I64d\n",dp[n][maxs]);
}

int main()
{
    memset(ans,0,sizeof(ans));
    while(cin>>n>>m&&(n||m))
    {
        if(ans[n][m])   //如果之前计算过，则直接给出结果
        {
            printf("%I64d\n",ans[n][m]);
            continue;
        }
        if(n&1&&m&1)    // 如果两边长都为奇数，则其面积也是奇数，无法放置
        {
            printf("0\n");
            continue;
        }
        solve();
    }
    return 0;
}
```

