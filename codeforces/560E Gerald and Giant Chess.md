# E. Gerald and Giant Chess

## **Description**

> Giant chess is quite common in Geraldion. We will not delve into the rules of the game, we'll just say that the game takes place on an h × w field, and it is painted in two colors, but not like in chess. Almost all cells of the field are white and only some of them are black. Currently Gerald is finishing a game of giant chess against his friend Pollard. Gerald has almost won, and the only thing he needs to win is to bring the pawn from the upper left corner of the board, where it is now standing, to the lower right corner. Gerald is so confident of victory that he became interested, in how many ways can he win?
>
> The pawn, which Gerald has got left can go in two ways: one cell down or one cell to the right. In addition, it can not go to the black cells, otherwise the Gerald still loses. There are no other pawns or pieces left on the field, so that, according to the rules of giant chess Gerald moves his pawn until the game is over, and Pollard is just watching this process.



## **Input**

> The first line of the input contains three integers: h, w, n — the sides of the board and the number of black cells (1 ≤ h, w ≤ 10^5, 1 ≤ n ≤ 2000).
>
> Next n lines contain the description of black cells. The i-th of these lines contains numbers ri, ci (1 ≤ ri ≤ h, 1 ≤ ci ≤ w) — the number of the row and column of the i-th cell.
>
> It is guaranteed that the upper left and lower right cell are white and all cells in the description are distinct.



## **Output**

> Print a single line — the remainder of the number of ways to move Gerald's pawn from the upper left to the lower right corner modulo 10^9 + 7.



## **Examples input**

    3 4 2
    2 2
    2 3



## **Examples output**

    2



## **题意**

在一个 $h \times w$ 的网格中，从左上角走到右下角，只能向右或者向下走，其中有一些点不能通过，求共有多少种走法。



## **思路**

首先对所有坏点按照 $x$ 作为第一键值， $y$ 作为第二键值进行排序。

$dp[i]$ 代表从 $(1,1)$ 走到第 $i$ 个坏点的方案数，其路径中不能包含其他坏点。

显然：

$$
dp[0]=\binom{x_0+y_0-2}{x_0-1}
$$

$$
dp[i]=\binom{x_i+y_i-2}{x_i-1}-\sum_{j=0}^{i-1}\binom{x_i-x_j+y_i-y_j}{x_i-x_j} \times dp[j]
$$

其中 $j$ 为我们枚举出现在 $i$ 之前同一路径上的第一个坏点，然后将这些从总方案数中减掉。

仔细想想我们还可以发现，将 $(h,w)$ 当作坏点那它一定是最后一个，此时的结果为 $dp[last]$ 。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<n;i++)
#define per(i,a,n) for(int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define inf 0x7f
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);
using namespace std;
typedef long long LL;
typedef pair<int,int> P;
const int maxn = 2e5+10;
const int mod = 1e9+7;
LL mul[maxn];
LL inv[maxn];
LL dp[maxn];
P p[maxn];
int h,w,n;

void init()
{
    mul[0]=1;
    for(int i=1; i<maxn; i++)
        mul[i]=(mul[i-1]*i)%mod;

    inv[0]=inv[1]=1;
    for(int i=2; i<maxn; i++)
        inv[i]=(LL)(mod-mod/i)*inv[mod%i]%mod;
    for(int i=1; i<maxn; i++)
        inv[i]=(inv[i-1]*inv[i])%mod;
}

LL C(int n,int m)
{
    return mul[n]*inv[m]%mod*inv[n-m]%mod;
}

void solve()
{
    dp[0] = C(p[0].fi+p[0].se-2,p[0].fi-1);
    for(int i=1; i<n; i++)
    {
        dp[i] = C(p[i].fi+p[i].se-2,p[i].fi-1);
        for(int j=0; j<i; j++)
        {
            if(p[j].fi<=p[i].fi&&p[j].se<=p[i].se)
            {
                dp[i] -= C(p[i].fi-p[j].fi+p[i].se-p[j].se,p[i].fi-p[j].fi) * dp[j] % mod;
                dp[i] = (dp[i]+mod)%mod;
            }
        }
    }
    cout<<dp[n-1]<<endl;
}

int main()
{
    IO;
    init();
    cin>>h>>w>>n;
    for(int i=0; i<n; i++)
        cin>>p[i].fi>>p[i].se;
    p[n++] = mp(h,w);
    sort(p,p+n);
    solve();
    return 0;
}
```

