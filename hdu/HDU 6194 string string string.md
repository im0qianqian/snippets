# string string string

## **Description**

> Uncle Mao is a wonderful ACMER. One day he met an easy problem, but Uncle Mao was so lazy that he left the problem to you. I hope you can give him a solution.
>
> Given a string s, we define a substring that happens exactly k times as an important string, and you need to find out how many substrings which are important strings.



## **Input**

> The first line contains an integer T (T≤100) implying the number of test cases.
>
> For each test case, there are two lines:
>
> the first line contains an integer k (k≥1) which is described above;
>
> the second line contain a string s (length(s)≤10^5).



## **Output**

> For each test case, print the number of the important substrings in a line.



## **Sample Input**

    2
    2
    abcabc
    3
    abcabcabcabc



## **Sample Output**

    6
    9



## **题意**

询问字符串 $s$ 中恰好出现 $k$ 次的子串有多少个。



## **思路**

和 [HDU 4641](https://www.dreamwings.cn/hdu4641/5005.html) 一样的思路。

区间减法计算 [至少出现 $k$ 次的结果] 减去 [至少出现 $k+1$ 次的结果] 即为 [恰好出现 $k$ 次的结果]



## **AC 代码**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef __int64 LL;
const int maxn = 2e5 + 10;
LL ans;
int K;

struct SAM
{
    int next[maxn][26];
    int pre[maxn], step[maxn];
    int last, id;
    int num1[maxn], num2[maxn];
    void init()
    {
        last = id = 0;
        memset(next[0], -1, sizeof(next[0]));
        pre[0] = -1;
        step[0] = 0;
    }
    void insert(int c)
    {
        int p = last, np = ++id;
        step[np] = step[p] + 1;
        memset(next[np], -1, sizeof(next[np]));
        num1[np] = num2[np] = 0;

        while (p != -1 && next[p][c] == -1)
            next[p][c] = np, p = pre[p];
        if (p == -1)
            pre[np] = 0;
        else
        {
            int q = next[p][c];
            if (step[q] != step[p] + 1)
            {
                int nq = ++id;
                memcpy(next[nq], next[q], sizeof(next[q]));
                num1[nq] = num1[q];
                num2[nq] = num2[q];
                step[nq] = step[p] + 1;
                pre[nq] = pre[q];
                pre[np] = pre[q] = nq;
                while (p != -1 && next[p][c] == q)
                    next[p][c] = nq, p = pre[p];
            }
            else
                pre[np] = q;
        }
        last = np;

        /* diy */
        bool f1 = false, f2 = false;
        while (np != -1 && (!f1 || !f2))
        {
            if (!f1 && num1[np] < K)
            {
                num1[np]++;
                if (num1[np] == K)
                {
                    ans += step[np] - step[pre[np]];
                    f1 = true;
                }
            }
            if (!f2 && num2[np] < K + 1)
            {
                num2[np]++;
                if (num2[np] == K + 1)
                {
                    ans -= step[np] - step[pre[np]];
                    f2 = true;
                }
            }
            np = pre[np];
        }
        /* end diy */
    }
} sam;

char str[maxn];
LL get_ans()
{
    sam.init();
    ans = 0;
    int len = strlen(str);
    for (int i = 0; i < len; i++)
        sam.insert(str[i] - 'a');
    return ans;
}

template <class T>
inline void scan_d(T &ret)
{
    char c;
    ret = 0;
    while ((c = getchar()) < '0' || c > '9')
        ;
    while (c >= '0' && c <= '9')
    {
        ret = ret * 10 + (c - '0'), c = getchar();
    }
}
template <class T>
inline void print_d(T x)
{
    if (x > 9)
    {
        print_d(x / 10);
    }
    putchar(x % 10 + '0');
}

int main()
{
    int T;
    scan_d(T);
    while (T--)
    {
        scan_d(K);
        gets(str);
        print_d(get_ans());
        putchar('\n');
    }
    return 0;
}
```

