# C. Memory and De-Evolution

## **Description**

> Memory is now interested in the de-evolution of objects, specifically triangles. He starts with an equilateral triangle of side length x, and he wishes to perform operations to obtain an equilateral triangle of side length y.
>
> In a single second, he can modify the length of a single side of the current triangle such that it remains a non-degenerate triangle (triangle of positive area). At any moment of time, the length of each side should be integer.
>
> What is the minimum number of seconds required for Memory to obtain the equilateral triangle of side length y?



## **Input**

> The first and only line contains two integers x and y (3 ≤ y < x ≤ 100 000) — the starting and ending equilateral triangle side lengths respectively.



## **Output**

> Print a single integer — the minimum number of seconds required for Memory to obtain the equilateral triangle of side length y if he starts with the equilateral triangle of side length x.



## **Examples input**

    6 3



## **Examples output**

    4



## **题意**

一开始有一个边长为 $x$ 的等边三角形，我们每一次可以把它其中一条边减掉任意长度，但是每一次减完以后必须要保证三边依然可以组成三角形，问至少需要多少次才可以将原图形变为边长为 $y$ 的等边三角形。



## **思路**

正着不好想我们可以反过来看，将边长为 $y$ 的等边三角形变为边长为 $x$ 的等边三角形至少需要操作多少次。

假设三角形三边长分别为 $a,b,c$ ，且此时 $a≤b≤c$ ，那么显然我们可以将最短边 $a$ 增大到 $b+c-1$ 的长度，如此反复，直到最短边大于等于 $x$ 即可。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);
using namespace std;
typedef long long LL;
const int maxn = 1e6+10;

int x,y;
int a[3];
int ans;
int main()
{
    IO;
    cin>>x>>y;
    a[0] = a[1] = a[2] = y;
    while(a[0]<=x)
    {
        a[0] = a[1] + a[2] -1;
        sort(a,a+3);
        ++ans;
    }
    cout<<ans<<endl;
    return 0;
}
```

