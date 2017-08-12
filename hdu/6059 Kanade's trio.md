# Kanade's trio

## **Description**

> Give you an array $A[1..n]$ ，you need to calculate how many tuples $(i,j,k)$ satisfy that $(i<j<k)$ and $((A[i]\ xor\ A[j])<(A[j]\ xor\ A[k]))$
>
> There are T test cases.
>
> $1≤T≤20$
>
> $1≤\sum n≤5×10^5$
>
> $0≤A[i]<2^{30}$



## **Input**

> There is only one integer T on first line.
>
> For each test case , the first line consists of one integer n ,and the second line consists of n integers which means the array $A[1..n]$



## **Output**

> For each test case , output an integer , which means the answer.



## **Sample Input**

    1
    5
    1 2 3 4 5



## **Sample Output**

    6



## **题意**

给定一个序列，寻找有多少个组合 $(i,j,k)$ ，满足 $i<j<k$ and $((A[i]\ xor\ A[j])<(A[j]\ xor\ A[k]))$ 。



## **思路**

之前一直在想如何处理这些二进制数，看过题解以后发现原来可以插进字典树（早该想到的）

---

从前往后遍历这个序列，用字典树来维护前 $k-1$ 个数，当前处理第 $k$ 个数。

对于每一个数，因为其大小不超过 $2^{30}$ ，所以我们可以用一个 `cnt` 数组来记录每一位某个数字（1 或 0）出现的次数。

`node.next` 为字典树中节点的后继， `node.cnt` 为当前节点被访问的次数。

对于 $k$ 与 $i$ 的最高不相同位 $k_p$ 与 $i_p$ ：

- 当 $k_p=1,i_p=0$ 时， $j_p$ 必须为 $0$ 才能使得 $(A_i \oplus A_j)<(A_j \oplus A_k)$ ，对于 $j$ 来说其他位随意。
- 当 $k_p=0,i_p=1$ 时， 同理 $j_p$ 必须为 $1$ ，其他位随意。


而对于 $A_j$ 来说，既然第 $p$ 位已经固定了，那其他位的变换我们也可以分情况讨论：

（设 $A_k[p]$ 对应节点为 `child` ，与其同父亲的另一个节点为 `xchild` ）

- 高位相同，低位随意，即 $i_{high}=j_{high},j_{high}=k_{high}$ ，因为前 $k-1$ 个数字已经被插入到了字典树，因此我们当前判断到第 $p$ 位时，需要在 `trie[xchild].cnt` 个数字中挑出两个作为 $i,j$ ，其结果为 $C_{trie[xchild].cnt}^{2}$ 。

- 高位不同，低位随意，即 $k_{high}!=j_{high},k_{high}=i_{high}$ ，此时 $A_i$ 共有 `trie[xchild].cnt` 种选择， $A_j$ 共有 `cnt[i][1-num[i]]-trie[xchild].cnt` 种选择，根据乘法原理，总贡献为 $(cnt[i][1-num[i]]-trie[xchild].cnt)×trie[xchild].cnt$ ，不过这部分会计算出一些不合法的结果，我们需要减掉它。（比如 $i>j,((A[i]\ xor\ A[j])<(A[j]\ xor\ A[k]))$ 的情况）

  统计 `node.ext` 的方式为在将第 $k$ 个数的贡献统计后，将其视作 $i$ ，则前 $k-1$ 个数有多少能与之在对应 $p$ 位相同，就能构成多少 $i>j$ 的方案。

分别计算这两部分的结果，其和便是最终答案。




## **AC 代码**

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef __int64 LL;
const int maxm = 32;
const int maxn = 5e5+10;

int n,num[maxm],a[maxn],cnt[maxm][2],tot;
LL ext,ans;

struct node
{
    int next[2];
    int cnt,ext;
} trie[maxn*maxm];

void call(int tmp,int i)
{
    ans+=trie[tmp].cnt*1LL*(trie[tmp].cnt-1)/2;         // 前面有 trie[tmp].cnt 个，从中挑选两个分别代表 i,j
    ext+=(cnt[i][1-num[i]]-trie[tmp].cnt)*1LL*trie[tmp].cnt-trie[tmp].ext;
}

void tree_insert(int index)
{
    int tmp=0;
    for(int i=0; i<30; i++)
    {
        if(!trie[tmp].next[num[i]])
            trie[tmp].next[num[i]]=++tot;
        if(trie[tmp].next[1-num[i]])
            call(trie[tmp].next[1-num[i]],i);
        tmp=trie[tmp].next[num[i]];
        trie[tmp].cnt++;
        trie[tmp].ext+=cnt[i][num[i]]-trie[tmp].cnt;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    int T;
    cin>>T;
    while(T--)
    {
        memset(trie,0,sizeof(trie));
        memset(cnt,0,sizeof(cnt));
        tot=ans=ext=0;
        int n;
        cin>>n;
        for(int i=1; i<=n; i++)
        {
            cin>>a[i];
            int tmp=a[i];
            for(int j=30-1; j>=0; j--)
            {
                num[j]=tmp%2;
                cnt[j][tmp%2]++;
                tmp>>=1;
            }
            tree_insert(i);
        }
        cout<<ans+ext<<endl;
    }
    return 0;
}
```

