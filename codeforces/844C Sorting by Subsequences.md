# C. Sorting by Subsequences

## **Description**

> You are given a sequence a1, a2, ..., an consisting of different integers. It is required to split this sequence into the maximum number of subsequences such that after sorting integers in each of them in increasing order, the total sequence also will be sorted in increasing order.
>
> Sorting integers in a subsequence is a process such that the numbers included in a subsequence are ordered in increasing order, and the numbers which are not included in a subsequence don't change their places.
>
> Every element of the sequence must appear in exactly one subsequence.



## **Input**

> The first line of input data contains integer n (1 ≤ n ≤ 10^5) — the length of the sequence.
>
> The second line of input data contains n different integers a1, a2, ..., an ( - 10^9 ≤ ai ≤ 10^9) — the elements of the sequence. It is guaranteed that all elements of the sequence are distinct.



## **Output**

> In the first line print the maximum number of subsequences k, which the original sequence can be split into while fulfilling the requirements.
>
> In the next k lines print the description of subsequences in the following format: the number of elements in subsequence ci (0 < ci ≤ n), then ci integers l1, l2, ..., lci (1 ≤ lj ≤ n) — indices of these elements in the original sequence.
>
> Indices could be printed in any order. Every index from 1 to n must appear in output exactly once.
>
> If there are several possible answers, print any of them.



## **Examples input**

    6
    3 2 1 6 5 4



## **Examples output**

    4
    2 1 3
    1 2
    2 4 6
    1 5



## **题意**

找出原序列的最大子序列个数，满足每个子序列内部排序以后可以使得原序列有序。



## **思路**

对原序列每个数字编号，寻找排序以后置换的循环节即可。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);
using namespace std;
const int maxn = 1e5+10;
typedef __int64 LL;

struct node
{
    int id;
    int num;
} a[maxn];

int n,tot;
bool vis[maxn];
vector<int> ans[maxn];

void solve()
{
    for(int i=0; i<n; i++)
    {
        if(vis[i])
            continue;
        vis[i] = true;
        ans[tot].push_back(i);
        int now = a[i].id;
        while(!vis[now])
        {
            ans[tot].push_back(now);
            vis[now] = true;
            now = a[now].id;
        }
        tot++;
    }
    cout<<tot<<endl;
    for(int i=0; i<tot; i++)
    {
        cout<<ans[i].size()<<" ";
        sort(ans[i].begin(),ans[i].end());
        for(auto s:ans[i])
            cout<<s+1<<" ";
        cout<<endl;
    }
}

int main()
{
    IO;
    cin>>n;
    for(int i=0; i<n; i++)
    {
        cin>>a[i].num;
        a[i].id = i;
    }
    sort(a,a+n,[](const node &x,const node &y)
    {
        return x.num<y.num;
    });
    solve();
    return 0;
}
```

