# D. Huge Strings

## **Description**

> You are given n strings s1, s2, ..., sn consisting of characters 0 and 1. m operations are performed, on each of them you concatenate two existing strings into a new one. On the i-th operation the concatenation saisbi is saved into a new string sn + i (the operations are numbered starting from 1). After each operation you need to find the maximum positive integer k such that all possible strings consisting of 0 and 1 of length k (there are 2k such strings) are substrings of the new string. If there is no such k, print 0.



## **Input**

> The first line contains single integer n (1 ≤ n ≤ 100) — the number of strings. The next n lines contain strings s1, s2, ..., sn (1 ≤ |si| ≤ 100), one per line. The total length of strings is not greater than 100.
>
> The next line contains single integer m (1 ≤ m ≤ 100) — the number of operations. m lines follow, each of them contains two integers ai abd bi (1 ≤ ai, bi ≤ n + i - 1) — the number of strings that are concatenated to form sn + i.



## **Output**

> Print m lines, each should contain one integer — the answer to the question after the corresponding operation.



## **Example input**

    5
    01
    10
    101
    11111
    0
    3
    1 2
    6 5
    4 4



## **Example output**

    1
    2
    0



## **题意**

一个字符串最多可以包含几位二进制数的所有组合。



## **思路**

以下做法属于旁门左道，二分 + 随机 + SAM 成功水过数据。

首先利用这个字符串建立后缀自动机，然后二分答案 $k$ ，对于每一个 $k$ 我们最多测试 $1000$ 种组合，其中每一种组合都是随机生成的，然后在自动机中查找是否包含该子串。

因为初始的字符串可能是由某两个子串连接得到的，如果不做限制的话该串最长可以到达 $2^{100} \times 100$ 位。

我们假设当前字符串为 $s$ ，它是由 $a,b$ 连接得到的，假如 $len(s)>1000$ ， $s = s.substr(0,500)+s.substr(len(s)-500,500)$ ，因为概率。。。

最终的结果为 $\max(test(a),test(b),test(s))$ 。



## **AC 代码**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+10;
const int maxm = 210;
typedef long long LL;
LL ans, K;

struct SAM
{
    int ch[maxn][2];
    int pre[maxn], step[maxn];
    int last, id;
    int nu[maxn];
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
    }
} sam;

unordered_map<string,bool> sk;
bitset<64> ss;

bool judge(const int &mid)
{
    sk.clear();
    LL maxx = min(1LL<<(mid+5),1000LL);
    for(int i=0; i<maxx; i++)
    {
        ss = rand();
        string now = ss.to_string();
        if(sk[now])continue;
        sk[now] = true;
        int id = 0;
        for(int j=0; j<mid; j++)
        {
            if(sam.ch[id][ss[j]]==-1)
                return false;
            id = sam.ch[id][ss[j]];
        }
    }
    return true;
}

string s[maxm];
int n,m;
int dp[maxm];

int solve(int id)
{
    sam.init();
    int len = s[id].length();
    for(int i=0; i<len; i++)
        sam.insert(s[id][i]-'0');
    int low = 0,high = 20;
    while(true)
    {
        int mid = (low+high)>>1;
        if(mid==low)
        {
            if(judge(high))
                low = high;
            break;
        }
        if(judge(mid))
            low = mid;
        else
            high = mid-1;
    }
    return low;
}

int main()
{
    srand((unsigned)time(NULL));
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    for(int i=1; i<=n; i++)
        cin>>s[i];
    cin>>m;
    for(int i=n+1; i<=n+m; i++)
    {
        int a,b;
        cin>>a>>b;
        s[i] = s[a]+s[b];
        if(s[i].length()>1000)
            s[i] = s[i].substr(0,500) + s[i].substr(s[i].length()-500,500);
        dp[i] = max({dp[a],dp[b],solve(i)});
        cout<<dp[i]<<endl;
    }
    return 0;
}
```

