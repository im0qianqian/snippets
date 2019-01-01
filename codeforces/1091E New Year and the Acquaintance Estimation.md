# E. New Year and the Acquaintance Estimation

## **Description**

> Bob is an active user of the social network Faithbug. On this network, people are able to engage in a mutual friendship. That is, if a is $a$ friend of $b$, then $b$ is also a friend of $a$. Each user thus has a non-negative amount of friends.
>
> This morning, somebody anonymously sent Bob the following link: graph realization problem and Bob wants to know who that was. In order to do that, he first needs to know how the social network looks like. He investigated the profile of every other person on the network and noted down the number of his friends. However, he neglected to note down the number of his friends. Help him find out how many friends he has. Since there may be many possible answers, print all of them.



## **Input**

> The first line contains one integer $n$ $(1≤n≤5⋅10^5)$, the number of people on the network excluding Bob.
>
> The second line contains $n$ numbers $a_1,a_2,…,a_n$ $(0≤a_i≤n)$, with $a_i$ being the number of people that person $i$ is a friend of.



## **Output**

> Print all possible values of $a_{n+1}$ — the amount of people that Bob can be friend of, in increasing order.
>
> If no solution exists, output $−1$.



## **Examples input**

    4
    1 1 1 1



## **Examples output**

    0 2 4 



## **题意**



## **思路**



## **AC 代码**

```cpp
#include <bits/stdc++.h>
#define IO                       \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);
using namespace std;
typedef long long LL;
const int maxn = 5e5 + 10;

int a[maxn];
int b[maxn];
int n, parity;

int judge(int mid) {
    memset(b, 0, sizeof(b));
    for (int i = 0; i < n; i++)
        ++b[a[i]];
    ++b[mid];
    LL left = 0, right = 0, les = 0;
    for (int i = 0, k = 0; k <= n; k++) {
        int now = (i == k && (i == n || a[i] < mid)) ? mid : a[i++];
        left += now;
        --b[now];
        les += b[k];
        right += n - k - les - min(now, k);
        if (left > right + 1LL * k * (k + 1))
            return i == k ? 1 : -1;
    }
    return 0;
}

bool solve() {
    sort(a, a + n, greater<int>());
    int low = 0, high = (n - parity) >> 1;
    int alow = -1, ahigh = -1;
    while (low <= high) {
        int mid = (low + high) >> 1;
        if (judge(mid * 2 + parity) == -1)
            low = mid + 1;
        else
            high = mid - 1, alow = mid;
    }
    low = alow, high = (n - parity) >> 1;
    while (low <= high) {
        int mid = (low + high) >> 1;
        if (judge(mid * 2 + parity) == 1)
            high = mid - 1;
        else
            low = mid + 1, ahigh = mid;
    }
    if (alow == -1 || ahigh == -1)
        return false;
    for (int i = alow; i <= ahigh; i++)
        cout << i * 2 + parity << " ";
    cout << endl;
    return true;
}

int main() {
#ifdef LOCAL_IM0QIANQIAN
    freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
#else
    IO;
#endif // LOCAL_IM0QIANQIAN

    while (cin >> n) {
        parity = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            parity ^= a[i];
        }
        parity &= 1;
        if (!solve())
            cout << "-1" << endl;
    }
    return 0;
}

```

