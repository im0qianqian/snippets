# C. From Y to Y

## **Description**

> From beginning till end, this message has been waiting to be conveyed.
>
> For a given unordered multiset of n lowercase English letters ("multi" means that a letter may appear more than once), we treat all letters as strings of length 1, and repeat the following operation n - 1 times:
>
> Remove any two elements s and t from the set, and add their concatenation s + t to the set.
>
> The cost of such operation is defined to be $\sum_{c \in \{'a','b',...,'z'\}}f(s,c)\times f(t,c)$ , where $f(s, c)$ denotes the number of times character c appears in string s.
>
> Given a non-negative integer k, construct any valid non-empty set of no more than 100 000 letters, such that the minimum accumulative cost of the whole process is exactly k. It can be shown that a solution always exists.



## **Input**

> The first and only line of input contains a non-negative integer k (0 ≤ k ≤ 100 000) — the required minimum cost.



## **Output**

> Output a non-empty string of no more than 100 000 lowercase English letters — any multiset satisfying the requirements, concatenated to be a string.
>
> Note that the printed string doesn't need to be the final concatenated string. It only needs to represent an unordered multiset of letters.



## **Examples input**

    12



## **Examples output**

    abababab



## **题意**

给定一个代价 $k$ ，输出一个字符串满足根据公式合并 $n-1$ 次所花费的代价和等于 $k$ 。



## **思路**

分析可知，不论我们挑选哪两个元素合并最终结果都是一样的。

且每一次合并的贡献只和相同字母的个数有关。

**例如：**

$aaaaaa$ ，我们挑选任意一种合并方式，其结果为 $1+2+3+4+5=15$ ，即 $cnt=len \times (len-1)/2$ 。

因此，最终的代价 $k$ 便由若干个 $cnt$ 组成，其中每一个代表一种字母。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+10;
int cnt[maxn];

void init()
{
    for(int i=1; i<=10000; i++)
        cnt[i]=i*(i-1)/2;
}

void solve(int n)
{
    if(!n)
        puts("ab");
    else
    {
        int tot=0;
        while(n)
        {
            int i=1;
            while(n>=cnt[i])++i;
            --i;
            n-=cnt[i];
            while(i--)
                printf("%c",tot+'a');
            tot++;
        }
        putchar('\n');
    }
}

int main()
{
    init();
    int n;
    while(cin>>n)
        solve(n);
}
```

