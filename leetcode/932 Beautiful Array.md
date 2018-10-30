# 932 漂亮数组

## **Description**

> 对于某些固定的 N，如果数组 A 是整数 1, 2, ..., N 组成的排列，使得：
>
> 对于每个 i < j，都不存在 k 满足 i < k < j 使得 A[k] * 2 = A[i] + A[j]。
>
> 那么数组 A 是漂亮数组。
>
> 给定 N，返回任意漂亮数组 A（保证存在一个）。



## **Input**

```
4
```



## **Output**

```
[2,1,4,3]
```



## **思路**

容易看出，假若数组左边为一个满足条件的奇数序列，右边为一个满足条件的偶数序列，则该数组也满足条件。

因为一定不存在一个数的二倍等于一个奇数。



再者，假若 $A[k] \times 2 \not= A[i] + A[j]$

那么 $(A[k]+x)\times2\not=(A[i]+x)+(A[j]+x)$ 与 $(A[k] \times x)\times2\not=(A[i]\times x)+(A[j]\times x)$ 也都成立。



综上，假若 $A$ 是一个从 $[1, N]$ 满足条件的数组

那么 $A\times 2-1$ 是一个从 $[1, 2N-1]$ 满足条件的奇数数组，同理 $A\times2$ 是一个从 $[2, 2N]$ 满足条件的偶数数组。

于是 $[A\times 2-1, A\times2]$ 是一个满足条件且从 $[1, 2N]$ 的漂亮数组。



令 $A=[1]$ ，则有 $[1]\rightarrow[1, 2]\rightarrow[1, 3, 2, 4]\rightarrow[1, 5, 3, 7, 2, 6, 4, 8]\dots$

显然删除大于 $N$ 的元素对最终结果没有影响。



## **AC 代码**

```cpp
class Solution {
public:
    vector<int> beautifulArray(int n) {
        vector<int> ans = {1};
        while (ans.size() < n) {
            vector<int> t2;
            for (auto s : ans) {
                if (s * 2 - 1 <= n)
                    t2.push_back(s * 2 - 1);
            }
            for (auto s : ans) {
                if (s * 2 <= n)
                    t2.push_back(s * 2);
            }
            ans = t2;
        }
        return ans;
    }
};
```

