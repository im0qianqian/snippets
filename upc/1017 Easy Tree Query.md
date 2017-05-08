# 1017 Easy Tree Query

## **题目描述**

> You are given a binary search tree with depth k, whose nodes are valued from 1 to (2k − 1) and then Q queries.
>
> For each query, you are given p nodes. Find the root of a smallest subtree which contains all p nodes and print its value.



## **输入**

> The ﬁrst line of input contains an integer T (T ≤ 100), the number of test cases. The ﬁrst line of each test case contains two integers k (1 ≤ k ≤ 60) and Q (1 ≤ Q ≤ 10 4 ). In next Q lines, each line contains an integer p and then p integers — the values of nodes in this query. It is guaranteed that the total number of nodes given in each test case will not exceed 105.



## **输出**

> For each query, print a line contains the answer of that query.



## **样例输入**

    1
    4 1
    3 10 15 13



## **样例输出**

    12



## **题意**

在深度为 `k` 的二叉搜索树中，给出 `q` 次查询，输出每次查询节点的最近共同祖先。



## **思路**

二叉搜索树有这样一个性质，即把树上所有节点从左到右依次输出其值刚好是排序的。

我们可以先对所要查询的点排序，设定 `root` 为当前判断的根节点。

1. 若 `a[0]<=root&&a[n-1]>=root` ，说明这些点遍布在 `root` 的两棵子树中，此时最近公共祖先便是 `root` 咯！
2. 若 `a[0]>root` ，说明所有节点都在 `root` 的右子树中，更新 `root` 为其右孩子节点，返回第一步。
3. 若 `a[n-1]<root` ，说明所有节点都在 `root` 的左子树中，更新 `root` 为其左孩子节点，返回第一步。



## **AC 代码**

```cpp
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <cstdio>
#include <set>
#include <math.h>
#include <algorithm>
#include <queue>
#include <iomanip>
#include <ctime>
#define INF 0x3f3f3f3f
#define MAXN 1000005
#define Mod 1000000007
using namespace std;

typedef unsigned long long LL;

LL a[MAXN];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int k,q;
        scanf("%d%d",&k,&q);
        while(q--)
        {
            int n;
            scanf("%d",&n);
            for(int i=0; i<n; i++)
                scanf("%llu",a+i);
            sort(a,a+n);
            int t=k;
            LL root=(LL)1<<t;
            while(true)
            {
                if(a[0]<=root&&a[n-1]>=root)
                {
                    printf("%llu\n",root);
                    break;
                }
                if(a[n-1]<root)
                {
                    t--;
                    root-=(LL)1<<t;
                }
                else if(a[0]>root)
                {
                    t--;
                    root+=(LL)1<<t;
                }
            }
        }
    }
    return 0;
}
```

