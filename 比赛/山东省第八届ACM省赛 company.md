# company

## **Problem Description**

> There are n kinds of goods in the company, with each of them has a inventory of cnti and direct unit benefit vali. Now you find due to price changes, for any goods sold on day i, if its direct benefit is val, the total benefit would be i⋅val.
>
> Beginning from the first day, you can and must sell only one good per day until you can't or don't want to do so. If you are allowed to leave some goods unsold, what's the max total benefit you can get in the end?



## **Input**

> The first line contains an integers n(1≤n≤1000).
>
> The second line contains n integers val1,val2,..,valn(−100≤vali≤100).
>
> The third line contains n integers cnt1,cnt2,..,cntn(1≤cnti≤100).



## **Output**

> Output an integer in a single line, indicating the max total benefit.



## **Example Input**

    4
    -1 -100 5 6
    1 1 1 2



## **Example Output**

    51



## **题意**

有 `n` 种商品以及这些商品的价值与数量，每天只能购买一件商品，且 `ans` 为 $sum(t_i×val_i)$ ，其中 $t_i$ 为第几天，求最终所能得到的最大 `ans` 。



## **思路**

我们可以先把所有商品的价值存在数组中（包括数量大于一的），排序并顺便求出当前的 `ans` 。

然后从数组最左边开始枚举，判断是否需要去除当前商品，若去除，则 `ans-=a[i]-sum[top-1]+sum[i]` ，因为总天数减少了一天，所以后面的所有商品价值和也应该减少。

判断如果当前得到新的 `ans` 变小了，跳出，输出最大的 `ans` 。



## **AC 代码**

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<iostream>
using namespace std;
#include<queue>
#include<map>
#define eps (1e-8)
typedef long long LL;
const int mod = 1e9+7;
const int maxn = 100000;
int a[maxn],sum[maxn],d[maxn];
int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        int top=n;
        for(int i=0; i<n; i++)
            scanf("%d",a+i);
        for(int i=0; i<n; i++)
        {
            scanf("%d",d+i);
            for(int j=1; j<d[i]; j++)
                a[top++]=a[i];
        }
        sort(a,a+top);
        sum[0]=a[0];
        LL ans=a[0];
        for(int i=1; i<top; i++)
        {
            sum[i]=sum[i-1]+a[i];
            ans+=(i+1)*a[i];
        }
        for(int i=0; i<top; i++)
        {
            LL s=ans-a[i]-sum[top-1]+sum[i];
            if(s>ans)
                ans=s;
            else break;
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

