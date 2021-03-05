# LCP 19 秋叶收藏集

## Description

> 小扣出去秋游，途中收集了一些红叶和黄叶，他利用这些叶子初步整理了一份秋叶收藏集 leaves， 字符串 leaves 仅包含小写字符 r 和 y， 其中字符 r 表示一片红叶，字符 y 表示一片黄叶。
>
> 出于美观整齐的考虑，小扣想要将收藏集中树叶的排列调整成「红、黄、红」三部分。每部分树叶数量可以不相等，但均需大于等于 1。每次调整操作，小扣可以将一片红叶替换成黄叶或者将一片黄叶替换成红叶。请问小扣最少需要多少次调整操作才能将秋叶收藏集调整完毕。



## Example Input

    leaves = "rrryyyrryyyrr"



## Example Output

    2



## 思路

考虑满足题意的形如 `rrryyrrr` 的字符串是由形如 `rrry` 以及 `yrrr` 两个字符串拼接而来。

那假如我们分别知道了构造形如 `rrry` 以及 `yrrr` 的最小花费，也便可以轻易的计算出构造形如 `rrryyrrr` 的最小花费。

由于这两种情况是类似的，因此我们专门讨论有关构造 `rrry` 的具体思路：

- 定义 `dp1_pre[i]` 代表第 $[0, i]$ 的子串满足形如 `rrry` 时的最小花费
- 定义 `dp2_pre[i]` 代表第 $[0,i]$ 全为 `r` 时的最小花费
- 那么便有，`dp1_pre[i] = min(dp1_pre[i - 1], dp2_pre[i - 1]) + (leaves[i] != 'y')`，即当前状态确保第 $i$ 位为 `y`，且可以从 $[0, i-1]$ 全为 `r` 或者 $[0, i-1]$ 满足 `rrry` 的情况转移而来，新状态从之前两种状态花费最小的那个转移而来的花费也最小

同理，计算 `dp1_lst[i]` 代表第 $[i, len-1]$ 满足形如 `yrrr` 时的最小花费。

再遍历 $i\in[1, len-2]$，`dp1_pre[i] + dp1_lst[i] - (leaves[i] != 'y')` 即为第 $i$ 个空位为 `y` 时的最小花费。这里假如第 $i$ 个空位本来为 `r`，则花费会被重复计算两次，因此要减掉一次。



## AC 代码

```cpp
const int maxn = 1e5 + 10;
const int mod = 1e9 + 7;
const double eps = 1e-8;

class Solution {
public:
    int minimumOperations(string leaves) {
        int dp1_pre[maxn], dp1_lst[maxn], dp2_pre[maxn], dp2_lst[maxn];
        int len = leaves.length();
        dp1_pre[0] = (leaves[0] != 'r'); // 第 0-i 符合形如 rrry 的最小花费
        dp2_pre[0] = (leaves[0] == 'y'); // 第 0-i 全为 r 的最小花费
        for (int i = 1; i < len; i++) {
            // 要么让 0-(i-1) 满足 rrry，要么 0-(i-1) 都为 r，取最小花费
            dp1_pre[i] =
                min(dp1_pre[i - 1], dp2_pre[i - 1]) + (leaves[i] != 'y');
            dp2_pre[i] = dp2_pre[i - 1] + (leaves[i] == 'y');
        }
        dp1_lst[len - 1] =
            (leaves[len - 1] != 'r'); // 第 i-(len-1) 符合形如 yrrr 的最小花费
        dp2_lst[len - 1] =
            (leaves[len - 1] == 'y'); // 第 i-(len-1) 全为 r 的最小花费
        for (int i = len - 2; i >= 0; i--) {
            dp1_lst[i] =
                min(dp1_lst[i + 1], dp2_lst[i + 1]) + (leaves[i] != 'y');
            dp2_lst[i] = dp2_lst[i + 1] + (leaves[i] == 'y');
        }
        int ans = INT_MAX;
        for (int i = 1; i < len - 1; i++) {
            // 因为 dp1_pre, dp1_lst 共用 i，所以如果在第 i
            // 位上做了消耗是会有双份的，因此要减掉一份
            ans = min({ans, dp1_pre[i] + dp1_lst[i] - (leaves[i] != 'y')});
        }
        return ans;
    }
};
```
