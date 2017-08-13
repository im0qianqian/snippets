# B. Game of the Rows

## **Description**

> Daenerys Targaryen has an army consisting of k groups of soldiers, the i-th group contains ai soldiers. She wants to bring her army to the other side of the sea to get the Iron Throne. She has recently bought an airplane to carry her army through the sea. The airplane has n rows, each of them has 8 seats. We call two seats neighbor, if they are in the same row and in seats {1, 2}, {3, 4}, {4, 5}, {5, 6} or {7, 8}.
>
> ![img](https://www.dreamwings.cn/wp-content/uploads/2017/08/20a11448a0afaf3655320120c369fcbc0e46769d.png)
>
> Daenerys Targaryen wants to place her army in the plane so that there are no two soldiers from different groups sitting on neighboring seats.
>
> Your task is to determine if there is a possible arranging of her army in the airplane such that the condition above is satisfied.



## **Input**

> The first line contains two integers n and k (1 ≤ n ≤ 10000, 1 ≤ k ≤ 100) — the number of rows and the number of groups of soldiers, respectively.
>
> The second line contains k integers a1, a2, a3, ..., ak (1 ≤ ai ≤ 10000), where ai denotes the number of soldiers in the i-th group.
>
> It is guaranteed that a1 + a2 + ... + ak ≤ 8·n.



## **Output**

> If we can place the soldiers in the airplane print "YES" (without quotes). Otherwise print "NO" (without quotes).
>
> You can choose the case (lower or upper) for each letter arbitrary.



## **Example input**

    2 2
    5 8



## **Example output**

    YES


## **题意**

有 $k$ 个不同的团体，每个团体有 $a_i$ 人，现有 $n$ 排 8 座的飞机，要为这些团体分配座位且不同团体的人不能坐在相邻位置，问能否分配成功。



## **思路**

既然中间位置比较特殊，因此我们贪心从团体人数最高开始往下枚举，为每一个团体的人优先分配中间的位置，标记当前所剩余的单人座，双人座，以及四人座的个数。

假设中间有一个 `A` ，那么还可以坐两个 `B` ；中间有两个 `A` ，那么还可以坐一个 `B` 。

最终如果对于某个人数没有座位可分则输出 `NO` ，否则输出 `YES` 。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int a[11000];
int sk[5];
int maxx;
bool solve()
{
    for(int i=maxx,j; i>0; i--)
    {
        while(a[i]--)   // 枚举每一个大小为 i 的集团
        {
            for(j=4; j>0; j--)  // 枚举座位剩余空间
            {
                if(sk[j])
                {
                    sk[j]--;
                    int t=min(i,j);
                    a[i-t]++;
                    if(j-t-1>0) // 如果中间位置坐 1 人，可空出一个双人座，如果坐 2 人，可空出单人座
                        sk[j-t-1]++;
                    break;
                }
            }
            if(!j)
                return false;
        }
    }
    return true;
}

int main()
{
    while(cin>>n>>k)
    {
        memset(sk,0,sizeof(sk));
        memset(a,0,sizeof(a));
        sk[2]=n*2,sk[4]=n;
        maxx=0;
        for(int i=0,x; i<k; i++)
        {
            cin>>x;
            a[x]++;
            maxx=max(maxx,x);
        }
        cout<<(solve()?"YES":"NO")<<endl;
    }
    return 0;
}
```

