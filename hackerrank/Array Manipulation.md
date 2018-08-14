# Array Manipulation

## **Description**

> Devendra 在 9 号云上看到了他的教练朝他微笑。 每次教授选出 Devendra 单独问他一个问题，Devendra 朦胧的头脑里全是他的教练和她的微笑，以至于他无法专注于其他事情。帮助他解决这个问题：
>
> 给你一个长度为 N 的列表，列表的初始值全是 0。对此列表，你要进行 M 次查询，输出列表最终 N 个值的最大值。对每次查询，给你的是 3 个整数—— a, b 和 k，你要对列表中从位置 a 到位置 b 范围内的（包含 a 和 b )的全部元素加上 k。



## **Input Format**

> 第一行包含两个整数 N 和 M
>
> 接下来 M 行，每行包含 3 个整数 a, b 和 k
>
> 列表中的数位置编号为从 1 到 N



## **Output Format**

> 单独的一行包含最终列表里的最大值



## **Constraints**

> $3 <= N <= 10^7$
>
> $1 <= M <= 2 \times 10^5$
>
> $1 <= a <= b <= N$
>
> $0 <= k <= 10^9$



## **Sample Input**

    5 3
    1 2 100
    2 5 100
    3 4 100



## **Sample Output**

    200



## **思路**

这是一类对区间操作先更新后查询的题目，对此，我们可以采用差分数组很方便的完成要求，时间复杂度 $O(n)$。

当然线段树之类的数据结构也是可行的，缺点就是代码太长，敲起来麻烦。



## **AC 代码**

```cpp
#include <bits/stdc++.h>
#define IO                       \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);
using namespace std;
typedef long long LL;
const int maxn = 2e7 + 10;

LL cnt[maxn];
int main() {
#ifdef LOCAL_IM0QIANQIAN
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
#else
    IO;
#endif // LOCAL_IM0QIANQIAN

    LL n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        LL a, b, k;
        cin >> a >> b >> k;
        cnt[a - 1] += k;
        cnt[b] -= k;
    }
    LL ans = 0;
    for (int i = 1; i < n; i++) {
        cnt[i] += cnt[i - 1];
        ans = max(ans, cnt[i]);
    }
    cout << ans << endl;
    return 0;
}
```

