# Build a tree

## **Description**

> HazelFan wants to build a rooted tree. The tree has $n$ nodes labeled $0$ to $n−1$ , and the father of the node labeled $i$ is the node labeled $\lfloor\frac{i-1}{k}\rfloor$. HazelFan wonders the size of every subtree, and you just need to tell him the XOR value of these answers.



## **Input**

> The first line contains a positive integer $T(1≤T≤5)$ , denoting the number of test cases.
>
> For each test case:
>
> A single line contains two positive integers $n,k(1≤n,k≤10^{18})$ .



## **Output**

> For each test case:
>
> A single line contains a nonnegative integer, denoting the answer.



## **Sample Input**

    2
    5 2
    5 3



## **Sample Output**

    7
    6


## **题意**

有一棵 $n$ 个节点的 $k$ 叉树，求所有子树大小的异或值。



## **思路**

考虑任意一个高度为 $h$ 的完全 $k$ 叉树

对于根节点的 $k$ 个孩子构成的 $k$ 个子树

一定有一部分构成了高度为 $h-1$ 的完全 $k$ 叉树，另一部分构成了高度为 $h-2$ 的完全 $k$ 叉树。

---

**通过递推我们可以得出：**

- $cnt[i]$ ，第 $i$ 层的节点个数
- $sum[i]$ ，高为 $i$ 的满 $k$ 叉树节点个数
- $xor[i]$ ，高为 $i$ 的满 $k$ 叉树所有子树异或和

我们知道， $x\oplus x=0$ ，一个数自身的偶数次异或值为 $0$ ，奇数次异或值等于它本身。

因此我们设 $F(x,y)$ 为将 $x$ 连续异或 $y$ 次，显然其结果与 $y$ 的奇偶性有关。

在满 $k$ 叉树阶段， $xor[dep]=sum[dep]\oplus F(xor[dep-1],k)$ ，而在其他阶段，我们只需要递归将这颗树分解为若干个满 $k$ 叉子树同样处理即可。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
typedef __int64 LL;
using namespace std;
const int maxn =105;
LL cnt[maxn];       // 第 i 层的节点个数
LL sum[maxn];       // 高为 i 的满 k 叉树节点个数
LL xxor[maxn];      // 高为 i 的满 k 叉树所有子树异或和
LL n,k;

inline LL F(LL a,LL b)
{
    return b&1?a:0;
}

LL dfs(LL dep,LL add)
{
    if(dep==0)return 0;
    return (sum[dep] + add)^F(sum[dep],add/cnt[dep])^F(sum[dep-1],k-1-add/cnt[dep])^dfs(dep-1,add%cnt[dep]);
}

LL solve()
{
    if(k==1)        // 对 1 特判
    {
        int mo = n%4;
        if(mo==0)
            return n;
        else if(mo==1)
            return 1;
        else if(mo==2)
            return n+1;
        else
            return 0;
    }
    int dep=1;
    sum[dep]=cnt[dep]=xxor[dep]=1;
    while((n-sum[dep])/k>=cnt[dep])     // 枚举深度（所有满节点的层）
    {
        dep++;
        cnt[dep] = cnt[dep-1]*k;
        sum[dep] = sum[dep-1] + cnt[dep];
        xxor[dep] = sum[dep]^F(xxor[dep-1],k);
    }
    return dfs(dep,n-sum[dep]);
}

int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        LL ans;
        cin>>n>>k;
        ans=solve();
        cout<<ans<<endl;
    }
    return 0;
}
```

