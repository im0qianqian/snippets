# C. Mahmoud and Ehab and the xor

## **Description**

> Mahmoud and Ehab are on the third stage of their adventures now. As you know, Dr. Evil likes sets. This time he won't show them any set from his large collection, but will ask them to create a new set to replenish his beautiful collection of sets.
>
> Dr. Evil has his favorite evil integer x. He asks Mahmoud and Ehab to find a set of n distinct non-negative integers such the bitwise-xor sum of the integers in it is exactly x. Dr. Evil doesn't like big numbers, so any number in the set shouldn't be greater than 10^6.



## **Input**

> The only line contains two integers n and x (1 ≤ n ≤ 10^5, 0 ≤ x ≤ 10^5) — the number of elements in the set and the desired bitwise-xor, respectively.



## **Output**

> If there is no such set, print "NO" (without quotes).
>
> Otherwise, on the first line print "YES" (without quotes) and on the second line print n distinct integers, denoting the elements in the set is any order. If there are multiple solutions you can print any of them.



## **Examples input**

    5 5



## **Examples output**

    YES
    1 2 4 5 7



## **题意**

寻找 $n$ 个不同的数，且这些数的异或值等于 $x$ 。



## **思路**

开个脑洞就可以想到

除了 $n=2,x=0$ 时找不到结果，其他情况下都可以找到一组解。

当 $n=1$ 时显然直接输出 $x$ 即可， $n=2$ 时解为 $0,x$ 。

对于其他情况下，保留三个数，其中两个可以中和掉相应位，而另一个数对最终结果做出贡献。

我们令 $pr=1<<17$ ，代表一个大于 $n$ 的数，最终结果中我们假设包含 $1,2,3...n-3$ ，且这些数的异或值为 $y$ 。

如果 $x=y$ ，则说明这 $n-3$ 个数已经保证了答案，那剩下的三个数只要异或值等于 $0$ 即可，于是很方便找到 $pr \oplus (pr \times 2) \oplus (pr \oplus (pr \times 2))=0$ 。

对于 $x!=y$ 时，剩下的三个数 $0 \oplus pr \oplus (pr \oplus x \oplus y)$ 可以保证它与之前的 $y$ 异或等于 $x$ 。



## **AC 代码**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define IO                       \
    ios::sync_with_stdio(false); \
    cin.tie(0);
typedef __int64 LL;
const int maxn = 1e5 + 10;
const int pr = 1 << 17;
int n, k;

void solve()
{
    if (n < 3)
    {
        if (n == 1)
        {
            cout << k << endl;
        }
        else
        {
            cout << 0 << " " << k << endl;
        }
        return;
    }
    vector<int> ans;
    LL cnt = 0;
    for (int i = 1; i <= n - 3; i++)
    {
        cnt ^= i;
        ans.push_back(i);
    }
    if (cnt == k)
    {
        ans.push_back(pr);
        ans.push_back(pr << 1);
        ans.push_back(pr ^ (pr << 1));
    }
    else
    {
        ans.push_back(0);
        ans.push_back(pr);
        ans.push_back(pr ^ k ^ cnt);
    }
    sort(ans.begin(), ans.end());
    int len = ans.size();
    for (int i = 0; i < len; i++)
    {
        cout << ans[i] << (i != len - 1 ? " " : "\n");
    }
}

int main()
{
    IO;
    cin >> n >> k;
    if (n == 2 && k == 0)
        cout << "NO" << endl;
    else
    {
        cout << "YES" << endl;
        solve();
    }
    return 0;
}
```



