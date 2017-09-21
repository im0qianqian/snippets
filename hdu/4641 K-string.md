# K-string

## **Description**

> Given a string S. K-string is the sub-string of S and it appear in the S at least K times.It means there are at least K different pairs (i,j) so that Si,Si+1... Sj equal to this K-string. Given m operator or query:1.add a letter to the end of S; 2.query how many different K-string currently.For each query ,count the number of different K-string currently.



## **Input**

> The input consists of multiple test cases. 
>
> Each test case begins with a line containing three integers n, m and K(1<=n,K<=50000,1<=m<=200000), denoting the length of string S, the number of operator or question and the least number of occurrences of K-string in the S.
>
> The second line consists string S,which only contains lowercase letters. 
>
> The next m lines describe the operator or query.The description of the operator looks as two space-separated integers t c (t = 1; c is lowercase letter).The description of the query looks as one integer t (t = 2).



## **Output**

> For each query print an integer — the number of different K-string currently.



## **Sample Input**

    3 5 2
    abc
    2
    1 a
    2
    1 a
    2



## **Sample Output**

    0
    1
    1



## **题意**

对于一个长度为 $n$ 的字符串有两种操作：

1. 向字符串的末尾增加一个字符 $c$
2. 查询串中至少出现 $m$ 次的子串有多少个



## **思路**

我们用原串建立后缀自动机，显然第一种操作即一次 `insert` 。

对于第二种操作，我们考虑每一次的 `insert` ，对新加入节点 $u->S$ 的状态路径 $num[np]+1$ ，若此时的 $num[np]>=m$ 则说明当前状态下所有子串的出现次数都已达到 $m$ ，因此 $ans+=step[np]-step[pre[np]]$ 。

最终的 $ans$ 即为结果。



## **AC 代码**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 5e5+10;
LL ans, K;

struct SAM
{
    int ch[maxn][26];
    int pre[maxn], step[maxn];
    int last, id;
    int num[maxn];
    void init()
    {
        last = id = 0;
        memset(ch[0], -1, sizeof(ch[0]));
        pre[0] = -1;
        step[0] = 0;
    }
    void insert(int c)
    {
        int p = last, np = ++id;
        step[np] = step[p] + 1;
        memset(ch[np], -1, sizeof(ch[np]));
        num[np] = 0;

        while (p != -1 && ch[p][c] == -1)
            ch[p][c] = np, p = pre[p];
        if (p == -1)
            pre[np] = 0;
        else
        {
            int q = ch[p][c];
            if (step[q] != step[p] + 1)
            {
                int nq = ++id;
                memcpy(ch[nq], ch[q], sizeof(ch[q]));
                num[nq] = num[q];
                step[nq] = step[p] + 1;
                pre[nq] = pre[q];
                pre[np] = pre[q] = nq;
                while (p != -1 && ch[p][c] == q)
                    ch[p][c] = nq, p = pre[p];
            }
            else
                pre[np] = q;
        }
        last = np;

        /* diy */
        while (np != -1 && num[np] < K)
        {
            num[np]++;
            if (num[np] >= K)
                ans += step[np] - step[pre[np]];
            np = pre[np];
        }
        /* end diy */
    }
} sam;

char str[maxn];
int main()
{
    int n, q;
    while (~scanf("%d%d%I64d%*c", &n, &q, &K))
    {
        sam.init();
        ans = 0;
        gets(str);
        for (int i = 0; i < n; i++)
            sam.insert(str[i] - 'a');
        for (int i = 0; i < q; i++)
        {
            int op;
            scanf("%d%*c", &op);
            if (op == 1)
            {
                char c;
                c = getchar();
                sam.insert(c - 'a');
            }
            else
                printf("%I64d\n", ans);
        }
    }
    return 0;
}
```

