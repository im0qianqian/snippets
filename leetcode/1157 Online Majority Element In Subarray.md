# 1157 Online Majority Element In Subarray

## **Description**

> 实现一个 `MajorityChecker` 的类，它应该具有下述几个 API：
>
> - `MajorityChecker(int[] arr)` 会用给定的数组 `arr` 来构造一个 `MajorityChecker` 的实例。
> - `int query(int left, int right, int threshold)` 有这么几个参数：
>   - `0 <= left <= right < arr.length` 表示数组 `arr` 的子数组的长度。
>   - `2 * threshold > right - left + 1`，也就是说阀值 `threshold` 始终比子序列长度的一半还要大。
> 
> 每次查询 `query(...)` 会返回在 `arr[left], arr[left+1], ..., arr[right]` 中至少出现阀值次数 `threshold` 的元素，如果不存在这样的元素，就返回 `-1`。



## **Constraints**

> - `1 <= arr.length <= 20000`
> - `1 <= arr[i] <= 20000`
> - 对于每次查询，`0 <= left <= right < len(arr)`
> - 对于每次查询，`2 * threshold > right - left + 1`
> - 查询次数最多为 `10000`



## **思路**

既然要查询的元素满足 `2 * threshold > right - left + 1`（该元素个数在子区间一半以上），那么给子区间排序以后若存在这样的元素则它一定出现在最中央的位置。

而根据数据范围我们可以得出每一次查询的时间最好要保证在 $O(n)$ 以内，显然直接排序再求中间元素的方法是不可行的。

既然为的是求静态区间排序后最中间的元素，那它等同于求第 $k$ 小的一个数（这里的 $k$ 为最中间的索引），套用划分树或者主席树等便可以解决了。

直接查找得到该元素后我们无法得知它的个数的确大于等于 `threshold`，因此稍加验证即可。



## **AC 代码**

```cpp
const int maxn = 1e5 + 10;
const int mod = 1e9 + 7;
const double eps = 1e-8;

int tree[20][maxn];   // 每层每个位置的值
int sorted[maxn];     // 已经排序好的数
int toleft[20][maxn]; // 第 i 层从 1-j 有多少个数被划分到了左边
int n;
void build(int l, int r, int dep) {
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    int same = mid - l + 1; // 等于中间值且被划分到左边数的个数
    for (int i = l; i <= r; i++) {
        if (tree[dep][i] < sorted[mid])
            same--;
    }
    int lpos = l;
    int rpos = mid + 1;
    for (int i = l; i <= r; i++) {
        if (tree[dep][i] < sorted[mid])
            tree[dep + 1][lpos++] = tree[dep][i];
        else if (tree[dep][i] == sorted[mid] && same > 0)
            tree[dep + 1][lpos++] = tree[dep][i], same--;
        else
            tree[dep + 1][rpos++] = tree[dep][i];
        toleft[dep][i] = toleft[dep][l - 1] + lpos - l;
    }
    build(l, mid, dep + 1);
    build(mid + 1, r, dep + 1);
}

int query2(int L, int R, int l, int r, int dep, int k) {
    if (l == r)
        return tree[dep][l];
    int mid = (L + R) >> 1;
    int cnt = toleft[dep][r] - toleft[dep][l - 1];
    if (cnt >= k) {
        int newl = L + toleft[dep][l - 1] - toleft[dep][L - 1];
        int newr = newl + cnt - 1;
        return query2(L, mid, newl, newr, dep + 1, k);
    } else {
        int newr = r + toleft[dep][R] - toleft[dep][r];
        int newl = newr - (r - l - cnt);
        return query2(mid + 1, R, newl, newr, dep + 1, k - cnt);
    }
}

class MajorityChecker {
public:
    vector<int> arr;
    MajorityChecker(vector<int> &arr) {
        this->arr = arr;
        memset(tree, 0, sizeof(tree));
        n = arr.size();
        for (int i = 1; i <= n; i++) {
            tree[0][i] = arr[i - 1];
            sorted[i] = tree[0][i];
        }
        sort(sorted + 1, sorted + n + 1);
        build(1, n, 0);
    }

    int query(int left, int right, int threshold) {
        int value =
            query2(1, n, left + 1, right + 1, 0, (right - left + 1) / 2 + 1);
        int count = 0;
        for (int i = left; i <= right; i++) {
            if (arr[i] == value)
                ++count;
            if (count >= threshold)
                return value;
        }
        return -1;
    }
};
```

