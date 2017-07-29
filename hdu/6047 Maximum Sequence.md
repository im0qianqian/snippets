# Maximum Sequence

## **Description**

> Steph is extremely obsessed with “sequence problems” that are usually seen on magazines: Given the sequence 11, 23, 30, 35, what is the next number? Steph always finds them too easy for such a genius like himself until one day Klay comes up with a problem and ask him about it.
>
> Given two integer sequences {ai} and {bi} with the same length n, you are to find the next n numbers of {ai}: an+1…a2n. Just like always, there are some restrictions on $a_{n+1}…a_{2n}$ : for each number ai, you must choose a number bk from {bi}, and it must satisfy $a_i≤\max(a_j-j)~(b_k≤j<i)$ , and any bk can’t be chosen more than once. Apparently, there are a great many possibilities, so you are required to find $\max(\sum^{2n}_{n+1}a_i)$ modulo $10^9+7$ .
>
> Now Steph finds it too hard to solve the problem, please help him.



## **Input**

> The input contains no more than 20 test cases.
>
> For each test case, the first line consists of one integer n. The next line consists of n integers representing {ai}. And the third line consists of n integers representing {bi}.
>
> $1≤n≤250000, n≤a_i≤1500000, 1≤b_i≤n$



## **Output**

> For each test case, print the answer on one line: $\max(\sum^{2n}_{n+1}a_i)$ modulo $10^9+7$ 。



## **Sample Input**

    4
    8 11 8 5
    3 1 4 2



## **Sample Output**

    27



## **题意**

给出数列 $A$ 和 $B$ ，我们可以从 $B$ 数列中取出一个编号来查找 $A$ 数列中该编号及以后的位置中 $A_i-i$ 的最大值并将其加入末尾，求 $A_{n+1}..A_{2n}$ 的和。



## **思路**

题目很简单，但是题意好难懂。（可能是英语差的原因）

贪心思想，既然这样我们每次取 $B$ 中当前编号最小的数字即可，因为这样才有机会让较大的数被加入到较前的位置，然后 $A_i-i$ 作差后的值仍然较大。

具体可以用两个优先队列来实现。



## **AC 代码**

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include<queue>
#include<iostream>
using namespace std ;

typedef __int64 LL;
typedef pair<LL,int> P;

const int mod = 1e9+7;
int main()
{
    ios::sync_with_stdio(false);
    int n;
    while(cin>>n)
    {
        priority_queue<P>sk;
        priority_queue<int,vector<int>,greater<int> >b;
        LL ans=0;
        for(int i=1; i<=n; i++)
        {
            LL x;
            cin>>x;
            sk.push(P(x-i,i));
        }
        for(int i=1; i<=n; i++)
        {
            int x;
            cin>>x;
            b.push(x);
        }
        for(int ti=n+1; !b.empty(); ti++)
        {
            int i=b.top();
            b.pop();
            while(sk.top().second<i)
                sk.pop();
            P p=sk.top();
            sk.push(P(p.first-ti,ti));
            ans=(ans+p.first)%mod;
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

