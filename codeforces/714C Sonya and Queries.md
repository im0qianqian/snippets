# C. Sonya and Queries

## **Description**

> Today Sonya learned about long integers and invited all her friends to share the fun. Sonya has an initially empty multiset with integers. Friends give her t queries, each of one of the following type:
>
> 1. \+ ai — add non-negative integer ai to the multiset. Note, that she has a multiset, thus there may be many occurrences of the same integer.
> 2. \- ai — delete a single occurrence of non-negative integer ai from the multiset. It's guaranteed, that there is at least one ai in the multiset.
> 3. ? s — count the number of integers in the multiset (with repetitions) that match some pattern s consisting of 0 and 1. In the pattern, 0 stands for the even digits, while 1 stands for the odd. Integer x matches the pattern s, if the parity of the i-th from the right digit in decimal notation matches the i-th from the right digit of the pattern. If the pattern is shorter than this integer, it's supplemented with 0-s from the left. Similarly, if the integer is shorter than the pattern its decimal notation is supplemented with the 0-s from the left.
>
> For example, if the pattern is s = 010, than integers 92, 2212, 50 and 414 match the pattern, while integers 3, 110, 25 and 1030 do not.



## **Input**

> The first line of the input contains an integer t (1 ≤ t ≤ 100 000) — the number of operation Sonya has to perform.
>
> Next t lines provide the descriptions of the queries in order they appear in the input file. The i-th row starts with a character ci — the type of the corresponding operation. If ci is equal to '+' or '-' then it's followed by a space and an integer ai (0 ≤ ai < 10^18) given without leading zeroes (unless it's 0). If ci equals '?' then it's followed by a space and a sequence of zeroes and onse, giving the pattern of length no more than 18.
>
> It's guaranteed that there will be at least one query of type '?'.
>
> It's guaranteed that any time some integer is removed from the multiset, there will be at least one occurrence of this integer in it.



## **Output**

> For each query of the third type print the number of integers matching the given pattern. Each integer is counted as many times, as it appears in the multiset at this moment of time.



## **Examples input**

    12
    + 1
    + 241
    ? 1
    + 361
    - 241
    ? 0101
    + 101
    ? 101
    - 101
    ? 101
    + 4000
    ? 0



## **Examples output**

    2
    1
    2
    1
    1



## **题意**

有三种针对多重集的操作：

1. 向多重集中添加一个元素
2. 去除多重集中的一个元素
3. 给定模式串，询问多重集中有多少个元素与之匹配（奇偶性匹配）



## **思路**

因为询问匹配时与元素的具体内容无关，因此我们只考虑每个元素每一位的奇偶性。

我们将一个元素的各位奇偶信息存储为一个整数（用其二进制信息代表），然后便可以很轻易的利用桶的性质完成更新与查询。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);
using namespace std;
typedef long long LL;
const int maxn = 1e6+10;
char op;
string tmp;
int ans[maxn];

int get_binary()
{
    int x =  0;
    for(int i=0; i<(int)tmp.length(); i++)
    {
        x<<=1;
        x|=tmp[i]&1;
    }
    return x;
}

int main()
{
    IO;
    int T;
    cin>>T;
    while(T--)
    {
        cin>>op>>tmp;
        if(op=='?')
            cout<<ans[get_binary()]<<endl;
        else
            ans[get_binary()] += (op=='+')?1:-1;
    }
    return 0;
}
```

