# The Grid Search

## **Description**

> Given a 2D array of digits or *grid*, try to find the occurrence of a given 2D pattern of digits. For example, consider the following grid:
>
> ```
> 1234567890
> 0987654321
> 1111111111
> 1111111111
> 2222222222
> ```
>
> Assume we need to look for the following 2D pattern array:
>
> ```
> 876543
> 111111
> 111111
> ```
>
> The 2D pattern begins at the second row and the third column of the grid. The pattern is said to be *present* in the grid.



## **Input Format**

> The first line contains an integer $t$, the number of test cases.
>
> Each of the $t$ test cases is represented as follows:
>
> The first line contains two space-separated integers $R$ and $C$, indicating the number of rows and columns in the grid $G$.
>
> This is followed by $R$ lines, each with a string of $C$ digits representing the grid $G$.
>
> The following line contains two space-separated integers, $r$ and $c$, indicating the number of rows and columns in the pattern grid $P$.
>
> This is followed by $r$ lines, each with a string of $c$ digits representing the pattern $P$.



## **Constraints**

> $1≤T≤5$
>
> $1≤R, r, C, c≤1000$
>
> $1≤r≤R$
>
> $1≤c≤C$



## **Output Format**

> Display 'YES' or 'NO', depending on whether $p$ is present in $G$.



## **Sample Input**

    2
    10 10
    7283455864
    6731158619
    8988242643
    3830589324
    2229505813
    5633845374
    6473530293
    7053106601
    0834282956
    4607924137
    3 4
    9505
    3845
    3530
    15 15
    400453592126560
    114213133098692
    474386082879648
    522356951189169
    887109450487496
    252802633388782
    502771484966748
    075975207693780
    511799789562806
    404007454272504
    549043809916080
    962410809534811
    445893523733475
    768705303214174
    650629270887160
    2 2
    99
    99



## **Sample Output**

    YES
    NO



## **题意**

判断一个 $R \times C$ 的数字矩阵中是否存在给定 $r \times c$ 的子矩阵。



## **思路**

今天无意看见了官方题解发现居然是纯暴力的解法…… 复杂度 $500^4 \times 5$ 也能过？

---

对于这样的题目，一般可以随机判点水数据，不过如果矩阵比较大的话这样的解法显然不可取了。

我们采用类似于奇偶校验的解法，将大矩阵中每一个 $r \times c$ 的区域压成一个 `long long` 的数字，然后 $O(n^2)$ 判断即可。

具体做法可以先统计出每一个 $r \times c$ 的子矩阵中各类数字出现的次数，我们知道 $64/10=6$，于是我们可以用每 $6$ 位二进制来存取一种数字的状态，假设数字 $0$ 出现了 $x$ 次，我们可以给 `long long` 标记数字的低 $6$ 位赋值 $x \% mod$ ，这里的 $mod$ 可以取 $2^6$ 以内较大的质数（有点哈希的思路，代码中 $mod$ 我取了 $2^6$ ，不过依然通过了所有的数据，不深究了）

最后用 $O(n^2)$ 的复杂度枚举判断，若标记数字与期望数字不同，则当前位置不满足条件，若相同，再用 $O(n^2)$ 的时间验证一下即可（多次验证的几率非常小，可以忽略不计）。



## **AC 代码**

```cpp
#include <bits/stdc++.h>
#define IO                       \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);
using namespace std;
typedef long long LL;
const int maxn = 1e3 + 10;

int r, c;
int r2, c2;
char str[maxn][maxn];
char str2[maxn][maxn];
int rl[maxn][maxn][10];
LL bj[maxn][maxn];

bool judge(int x, int y, LL test) {
    if (bj[x][y] != test) {
        return false;
    }
    for (int i = 0; i < r2; i++) {
        for (int j = 0; j < c2; j++) {
            if (str2[i][j] != str[x - r2 + i][y - c2 + j]) {
                return false;
            }
        }
    }
    return true;
}

bool solve() {
    memset(rl, 0, sizeof(rl));
    memset(bj, 0, sizeof(bj));
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            for (int k = 0; k < 10; k++) {
                rl[i][j][k] =
                    rl[i - 1][j][k] + rl[i][j - 1][k] - rl[i - 1][j - 1][k];
            }
            ++rl[i][j][str[i - 1][j - 1] - '0'];
        }
    }
    for (int i = r2; i <= r; i++) {
        for (int j = c2; j <= c; j++) {
            int sm[10] = {0};
            LL flag = 0;
            for (int k = 0; k < 10; k++) {
                sm[k] = rl[i][j][k] - rl[i - r2][j][k] - rl[i][j - c2][k] +
                        rl[i - r2][j - c2][k];
                flag <<= 6;
                flag |= sm[k] & ((1 << 6) - 1);
            }
            bj[i][j] = flag;
        }
    }
    LL test = 0;
    int sm[10] = {0};
    for (int i = 0; i < r2; i++) {
        for (int j = 0; j < c2; j++) {
            ++sm[str2[i][j] - '0'];
        }
    }
    for (int i = 0; i < 10; i++) {
        test <<= 6;
        test |= sm[i] & ((1 << 6) - 1);
    }
    for (int i = r2; i <= r; i++) {
        for (int j = c2; j <= c; j++) {
            if (judge(i, j, test)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
#ifdef LOCAL_IM0QIANQIAN
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
#else
    // IO;
#endif // LOCAL_IM0QIANQIAN

    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &r, &c);
        for (int i = 0; i < r; i++) {
            cin >> str[i];
        }
        scanf("%d%d", &r2, &c2);
        for (int i = 0; i < r2; i++) {
            cin >> str2[i];
        }
        cout << (solve() ? "YES" : "NO") << endl;
    }
    return 0;
}
```

