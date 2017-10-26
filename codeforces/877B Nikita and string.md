# B. Nikita and string

## **Description**

> One day Nikita found the string containing letters "a" and "b" only.
>
> Nikita thinks that string is beautiful if it can be cut into 3 strings (possibly empty) without changing the order of the letters, where the 1-st and the 3-rd one contain only letters "a" and the 2-nd contains only letters "b".
>
> Nikita wants to make the string beautiful by removing some (possibly none) of its characters, but without changing their order. What is the maximum length of the string he can get?



## **Input**

> The first line contains a non-empty string of length not greater than 5 000 containing only lowercase English letters "a" and "b".



## **Output**

> Print a single integer — the maximum possible size of beautiful string Nikita can get.



## **Examples input**

    abba



## **Examples output**

    4



## **题意**

我们想要在原串中找出一个子序列，这个子序列左半边与右半边全是 `a` ，中间部分全是 `b` （每部分可以为空），问序列的长度最长为多少。



## **思路**

我们考虑记录每一个前缀所出现 $a,b$ 的数量，其中 $prea[i]$ 代表前 $i$ 个元素中 $a$ 的数量，$preb[i]$ 代表前 $i$ 个元素中 $b$ 的数量。

然后构造双指针 $i,j$ 来做分割线，满足 $0≤i≤j≤n$ ，则此时得到序列的长度为 $n-(preb[i]+(preb[n]-preb[j])+(prea[j]-prea[i]))$ 。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);
#define inf 0x7f7f7f7f
using namespace std;
typedef __int64 LL;
const int maxn = 1e5+10;

char str[maxn];
int prea[maxn],preb[maxn];

void solve()
{
    int len = strlen(str+1);
    for(int i=1; i<=len; i++)
    {
        prea[i] = prea[i-1];
        preb[i] = preb[i-1];
        if(str[i]=='a')
            prea[i]++;
        else
            preb[i]++;
    }
    int ans = 0;
    for(int i=0; i<=len; i++)
    {
        for(int j=i; j<=len; j++)
        {
            int now = preb[i]+preb[len]-preb[j]+prea[j]-prea[i];
            ans = max(ans,len - now);
        }
    }
    printf("%d\n",ans);
}

int main()
{
    gets(str+1);
    solve();
    return 0;
}
```

