# To my boyfriend

## **Description**

> Dear Liao
>
> I never forget the moment I met with you. You carefully asked me: "I have a very difficult problem. Can you teach me?". I replied with a smile, "of course". You replied:"Given a matrix, I randomly choose a sub-matrix, what is the expectation of the number of **different numbers** it contains?"
>
> Sincerely yours,
>
> Guo



## **Input**

> The first line of input contains an integer T(T≤8) indicating the number of test cases.
>
> Each case contains two integers, n and m (1≤n, m≤100), the number of rows and the number of columns in the grid, respectively.
>
> The next n lines each contain m integers. In particular, the j-th integer in the i-th of these rows contains g_i,j (0≤ g_i,j < n*m).



## **Output**

> Each case outputs a number that holds 9 decimal places.



## **Sample Input**

    1
    2 3
    1 2 1
    2 1 2



## **Sample Output**

    1.666666667



## **题意**

给出一个 $N × M$ 的数字矩阵，求其所有子矩阵不同数字个数的期望值。



## **思路**

直接枚举子矩阵的时间复杂度为 $O(n^4)$ ，显然不能达到预期的效果。

于是我们考虑每种数字对结果的贡献，**计算至少包含某一数字的子矩阵有多少个**，但因为如此一定会产生重复计数，所以我们要为其限定条件。

- 假设相对的两点 $(x_1,y_1),(x_2,y_2)$ 可以唯一确定一个矩形，且 $x_1<=x_2,y_1<=y_2$
- 对于当前所判断的数字 $a$ ，其坐标为 $(x,y)$
- 此时， $(x_1,y_1)$ 的位置只可以在 $(x,y)$ 的左上方， $(x_2,y_2)$ 的位置只可以在 $(x,y)$ 的右下方（包含当前行）
- 且最终 $(x,y)$ 以上以左部分无第二个数字 $a$

这样便不会产生重复计数啦~

接下来的工作便是找寻当前位置 $(x,y)$ 以上以左的空间中存在多少个可选择点，然后配合其以下以右的空间大小得出结果。



## **AC 代码**

```cpp
#include<iostream>
#include<cstdio>
#include<ctime>
#include<cstdlib>
#include<cstring>
#include<set>
#include<algorithm>
#define N
#define M
using namespace std;
typedef long long LL;

const int maxn = 101;
int col[maxn*maxn][maxn];
int n,m;
int l[maxn],r[maxn];
LL ans;

void solve(int x,int y,int c)
{
    for(int i=1; i<=x; i++)     // 初始化
    {
        l[i]=0;
        r[i]=m+1;
    }
    for(int i=1; i<y; i++)      // 找寻 c 出现在某行最大的列下标 (i<y)
        l[col[c][i]]=i;
    for(int i=m; i>y; i--)      // 找寻 c 出现在某行最小的列下标 (i>y)
        r[col[c][i]]=i;
    int h=col[c][y];            // c 所在列同种数字上一次出现位置
    for(int i=x-1; i>h; i--)    // 空间压缩至入口大小
    {
        l[i]=max(l[i],l[i+1]);
        r[i]=min(r[i],r[i+1]);
    }
    for(int i=x; i>h; i--)      // 枚举当前列 [h+1,x] 区间内所有情况
        ans+=LL(r[i]-y)*(y-l[i])*(n-x+1);
}

int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        memset(col,0,sizeof(col));
        ans=0;
        cin>>n>>m;
        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=m; j++)
            {
                int x;
                cin>>x;
                solve(i,j,x);
                col[x][j]=i;    // 当前列 x 上一次在哪行出现
            }
        }
        LL di=n*(n+1)*m*(m+1)/4;    // 所有情况
        cout<<di<<" "<<ans<<endl;
        printf("%.9lf\n",ans*1.0/di);
    }
    return 0;
}
```

