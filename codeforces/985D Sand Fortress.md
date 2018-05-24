# D. Sand Fortress

## **Description**

> You are going to the beach with the idea to build the greatest sand castle ever in your head! The beach is not as three-dimensional as you could have imagined, it can be decribed as a line of spots to pile up sand pillars. Spots are numbered 1 through infinity from left to right.
>
> Obviously, there is not enough sand on the beach, so you brought $n$ packs of sand with you. Let height $h_i$ of the sand pillar on some spot $i$ be the number of sand packs you spent on it. You can't split a sand pack to multiple pillars, all the sand from it should go to a single one. There is a fence of height equal to the height of pillar with $H$ sand packs to the left of the first spot and you should prevent sand from going over it.
>
> Finally you ended up with the following conditions to building the castle:
>
> - $h_1 ≤ H$: no sand from the leftmost spot should go over the fence;
> - For any $i\in[1,∞)]$ $|h_i - h_{i + 1}| ≤ 1$: large difference in heights of two neighboring pillars can lead sand to fall down from the higher one to the lower, you really don't want this to happen;
> - $\sum_{i=1}^{∞}h_i=n$: you want to spend all the sand you brought with you.
>
> As you have infinite spots to build, it is always possible to come up with some valid castle structure. Though you want the castle to be as compact as possible.
>
> Your task is to calculate the minimum number of spots you can occupy so that all the aforementioned conditions hold.



## **Input**

> The only line contains two integer numbers $n$ and $H~(1 ≤ n, H ≤ 10^{18})$ — the number of sand packs you have and the height of the fence, respectively.



## **Output**

> Print the minimum number of spots you can occupy so the all the castle building conditions hold.



## **Examples input**

    5 2



## **Examples output**

    3



## **题意**

有 $n$ 块沙包，左侧挡板的高度为 $H$ ，若某一格的沙包个数与相邻格的沙包个数之差大于 1，则该格内的沙包可能会发生滑落，因此这样的情况是不被允许的，现要你求出最少需要多少格才能完全放置所有的沙包。



## **思路**

显然最后放置好沙包以后的图形从左到右大体趋势要么一直递减，要么先上升后递减，于是我们二分求临界点即可。



## **AC 代码**

```python
def judge(mid, n, H):
    if mid <= H:  # 一直递减的情形
        return mid * (mid + 1) // 2

    # 左右两侧都是等差数列
    right = mid * (mid + 1) // 2
    left = (mid - H + 1) * H + (mid - H + 1) * ((mid - H + 1) - 1) // 2
    return left + right - mid


def solve(n, H):
    low = 1
    high = 1000000000000000000
    while True:
        mid = (low + high) >> 1
        now = judge(mid, n, H)
        if low == mid:
            if now >= n:
                return low + max(0, low - H)
            elif now + low >= n:  # 能否再加一列使其满足条件
                return low + max(0, low - H) + 1
            return high + max(0, high - H)
        if now == n:
            return mid + max(0, mid - H)
        elif now < n:
            low = mid
        elif now > n:
            high = mid
    pass


try:
    while True:
        n, H = input().split()
        n = int(n)
        H = int(H)
        print(solve(n, H))
except EOFError:
    pass
```

