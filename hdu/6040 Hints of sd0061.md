# Hints of sd0061

## **Description**

> sd0061, the legend of Beihang University ACM-ICPC Team, retired last year leaving a group of noobs. Noobs have no idea how to deal with m coming contests. sd0061 has left a set of hints for them.
>
> There are n noobs in the team, the i-th of which has a rating ai. sd0061 prepares one hint for each contest. The hint for the j-th contest is a number bj, which means that the noob with the (bj+1)-th lowest rating is ordained by sd0061 for the j-th contest.
>
> The coach asks constroy to make a list of contestants. constroy looks into these hints and finds out: bi+bj≤bk is satisfied if bi≠bj, bi<bk and bj<bk.
>
> Now, you are in charge of making the list for constroy.



## **Input**

> There are multiple test cases (about 10).
>
> For each test case:
>
> The first line contains five integers n,m,A,B,C. (1≤n≤10^7,1≤m≤100)
>
> The second line contains m integers, the i-th of which is the number bi of the i-th hint. (0≤bi<n)
>
> The n noobs' ratings are obtained by calling following function n times, the i-th result of which is ai.
>
> ```cpp
> unsigned x = A, y = B, z = C;
> unsigned rng61()
> {
>     unsigned t;
>     x ^= x << 16;
>     x ^= x >> 5;
>     x ^= x << 1;
>     t = x;
>     x = y;
>     y = z;
>     z = t ^ x ^ y;
>     return z;
> }
> ```



## **Output**

> For each test case, output "Case #x: y1 y2 ⋯ ym" in one line (without quotes), where x indicates the case number starting from 1 and yi (1≤i≤m) denotes the rating of noob for the i-th contest of corresponding case.



## **Sample Input**

    3 3 1 1 1
    0 1 2
    2 2 2 2 2
    1 1



## **Sample Output**

    Case #1: 1 1 202755
    Case #2: 405510 405510



## **题意**

用题中所给的函数生成 n 个数，然后有 m 次查询，查询数列 $a$ 中第 $b_i$ 大的数是多少。



## **思路**

​如果单纯想着排序以后直接输出的话会超时，因为 n 最大有 $10^7$ ，也就是数列的长度最大也是这些。

那么就应该想想其他线性的解法了， STL 库中实现了 `nth_element` 函数，其功能是使第 n 大元素处于第 n 个位置，并且比这个元素小的元素都排在它之前，比这个元素大的元素都排在它之后，但不能保证它们是有序的。

```cpp
template<class RandomAccessIterator>  
void nth_element(RandomAccessIterator first, RandomAccessIterator nth, RandomAccessIterator last);  
```

**时间复杂度：**平均为线性。

然后在使用过程中做一点点的优化就可以了，题中有说 $b_i+b_j≤b_k$ ，因此我们在查询时从大往小开始遍历，这样每次都可以减掉数组的一半长度。



## **AC 代码**

```cpp
#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;

unsigned x, y, z;

unsigned rng61()
{
    unsigned t;
    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;
    t = x;
    x = y;
    y = z;
    z = t ^ x ^ y;
    return z;
}

typedef pair<int,int> P;
const int manx = 1e7+10;
unsigned a[manx];
unsigned ans[manx];
P b[110];

int main()
{
    ios::sync_with_stdio(false);
    int n,m,kase=0;
    while(cin>>n>>m>>x>>y>>z)
    {
        for(int i=0; i<m; i++)
        {
            cin>>b[i].first;
            b[i].second=i;
        }
        for(int i=0; i<n; i++)
            a[i]=rng61();
        sort(b,b+m);
        b[m].first=n;
        for(int i=m-1; i>=0; i--)
        {
            nth_element(a,a+b[i].first,a+b[i+1].first);
            ans[b[i].second]=a[b[i].first];
        }
        cout<<"Case #"<<++kase<<":";
        for(int i=0; i<m; i++)
            cout<<" "<<ans[i];
        cout<<endl;
    }
    return 0;
}
```

