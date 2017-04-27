# Stars

## **Problem Description**

> There are N (1 ≤ N ≤ 400) stars in the sky. And each of them has a unique coordinate (x, y) (1 ≤ x, y ≤ N). Please calculate the minimum area of the rectangle (the edges of the rectangle must be parallel to the X, Y axes) that can cover at least K (1 ≤ K ≤ N) stars. The stars on the borders of the rectangle should not be counted, and the length of each rectangle’s edge should be an integer.



## **Input**

> Input may contain several test cases. The first line is a positive integer T (T ≤ 10), indicating the number of test cases below.
>
> For each test cases, the first line contains two integers N, K, indicating the total number of the stars and the number of stars the rectangle should cover at least.
>
> Each of the following N lines contains two integers x, y, indicating the coordinate of the stars.



## **Output**

> For each test case, output the answer on a single line.



## **Example Input**

    2
    1 1
    1 1
    2 2
    1 1
    1 2



## **Example Output**

    1
    2



## **题意**

给出平面中 `n` 个整数点，求最小的至少可以覆盖 `k` 个点的矩形面积。



## **思路**

把这个平面看作一个矩阵，有整数点的位置为 `1` ，其他位置为 `0` 。

求出 $(1,1)$ 到任意点 $(n,m)$ 的矩阵和，然后枚举任意两行，我们可以根据这两行值的差求得当前判断的子矩阵的和，这里可以用尺取法，若满足条件，计算面积，取最小值。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define INF 0x3f3f3f

const int maxn  = 450;

int arr[maxn][maxn];
int v[maxn],n;

int cal(int *l,int *r,int k)
{
    int st,ed;
    st = ed = 0;
    for(int i=0; i<=n; i++)
        v[i] = r[i] - l[i];
    while(ed <= n && v[ed] < k)
        ed++;
    if(ed > n)return INF; // 无法满足条件
    int ret = ed;
    while(ed<=n)    // 尺取法
    {
        if(v[ed]-v[st] >= k)
            ret = min(ret,ed-st++);
        else ed++;
    }
    return ret;
}


int main()
{
    int T,k;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&k);
        memset(arr,0,sizeof(arr));
        for(int i=0; i<n; i++)
        {
            int x,y;
            scanf("%d %d",&x,&y);
            arr[x][y]=1;
        }
        for(int i=0; i<=n; i++)
            for(int j=0; j<=n; j++) // 向右推进
                arr[i][j] += arr[i][j-1];
        for(int i=0; i<=n; i++)
            for(int j=0; j<=n; j++) // 向下推进
                arr[i][j] += arr[i-1][j];
        int ans = n*n;
        for(int i=0; i<=n; i++) // 枚举两行
            for(int j=i+1; j<=n; j++)
                ans = min(ans,(j-i)*cal(arr[i],arr[j],k));
        printf("%d\n",ans);
    }
    return 0;
}
```
