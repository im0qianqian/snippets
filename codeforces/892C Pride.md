# C. Pride

## **Description**

> You have an array a with length n, you can perform operations. Each operation is like this: choose two adjacent elements from a, say x and y, and replace one of them with gcd(x, y), where gcd denotes the greatest common divisor.
>
> What is the minimum number of operations you need to make all of the elements equal to 1?



## **Input**

> The first line of the input contains one integer n (1 ≤ n ≤ 2000) — the number of elements in the array.
>
> The second line contains n space separated integers a1, a2, ..., an (1 ≤ ai ≤ 10^9) — the elements of the array.



## **Output**

> Print -1, if it is impossible to turn all numbers to 1. Otherwise, print the minimum number of operations needed to make all numbers equal to 1.



## **Examples input**

    5
    2 2 3 4 6



## **Examples output**

    5



## **题意**

给定一个数列，我们定义一个操作是取相邻的两个数计算其 gcd ，然后替换掉其中的某一个数，问最少多少步可以将数列全部变为 1 。



## **思路**

显然，数列所有数的 gcd 如果不等于 1 答案一定是 -1 。

对于其他情况，我们枚举找出最短的 gcd 为 1 的区间，此时的操作即，先造出一个 1 ，然后用这一个 1 与相邻的数字进行 gcd 填充。

注意特判 n = 1 的情况与数列中存在 1 的情况。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);
using namespace std;
typedef __int64 LL;
const int maxn = 2e5+10;

LL a[maxn];
int n;
void solve()
{
    LL k = a[0],one = (a[0]==1);
    for(int i=1; i<n; i++)
    {
        k = __gcd(k,a[i]);
        if(a[i]==1)one++;
    }
    if(n==1&&a[0]==1)
    {
        cout<<0<<endl;
        return;
    }
    if(k!=1)
    {
        cout<<"-1"<<endl;
        return;
    }
    int lm = 0,ans = 3000;
    for(int i=0; i<n; i++)
    {
        LL k = a[i];
        for(int j=i+1; j<n; j++)
        {
            k = __gcd(k,a[j]);
            if(k==1)
            {
                lm = j-i+1;
                break;
            }
        }
        ans = min(ans,lm);
    }
    cout<<ans+n-2-one<<endl;
}

int main()
{
    IO;
    cin>>n;
    for(int i=0; i<n; i++)
        cin>>a[i];
    solve();
    return 0;
}
```

