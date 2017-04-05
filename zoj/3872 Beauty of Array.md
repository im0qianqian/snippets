# Beauty of Array

> Edward has an array A with N integers. He defines the beauty of an array as the summation of all distinct integers in the array. Now Edward wants to know the summation of the beauty of all contiguous subarray of the array A.



## **Input**

> There are multiple test cases. The first line of input contains an integer T indicating the number of test cases. For each test case:
>
> The first line contains an integer N (1 <= N <= 100000), which indicates the size of the array. The next line contains N positive integers separated by spaces. Every integer is no larger than 1000000.



## **Output**

> For each case, print the answer in one line.



## **Sample Input**

    3
    5
    1 2 3 4 5
    3
    2 3 3
    4
    2 3 3 2



## **Sample Output**

    105
    21
    38



## **题意**

我们定义一个序列的贡献是它里面所有不相同的数字之和，然后给出一个数字序列，求其所有连续子序列的贡献和。



## **思路**

**假设当前给出序列为：** `2 3 3 2`

1. 以第一个 `2` 结尾的子串有一个，当前贡献为 `1*2=2`
2. 以第一个 `3` 结尾的子串有两个，当前贡献为 `2+2*3=8`
3. 以第二个 `3` 结尾的子串有三个，因为 `3` 已经在第二个位置出现过，因此对于包含前一个 `3` 的所有子串的贡献都已经计算过了，当前贡献为 `8+(3-2)*3=11`
4. 以第二个 `2` 结尾的子串有四个，因为 `2` 已经在第一个位置出现过，因此对于包含前一个 `2` 的所有子串的贡献也计算过了，当前贡献为 `11+(4-1)*2=17`

最终的结果是所有计算的数值之和。



## **AC 代码**

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<map>
#include<cstring>
#include<algorithm>
#include<set>
using namespace std;
#define eps (1e-7)
typedef long long LL;

LL mapp[1100000],ans,sum;
int a[110000];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n;
        scanf("%d",&n);
        sum=0;
        memset(mapp,-1,sizeof(mapp));
        for(int i=0; i<n; i++)
        {
            scanf("%d",a+i);
            if(i==0)ans=a[i];
            else ans+=(i-mapp[a[i]])*a[i];
            mapp[a[i]]=i;
            sum += ans;
        }
        printf("%lld\n",sum);
    }
    return 0;
}
```

