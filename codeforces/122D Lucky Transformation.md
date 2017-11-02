# D. Lucky Transformation

## **Description**

> Petya loves lucky numbers. Everybody knows that lucky numbers are positive integers whose decimal representation contains only the lucky digits 4 and 7. For example, numbers 47, 744, 4 are lucky and 5, 17, 467 are not.
>
> Petya has a number consisting of n digits without leading zeroes. He represented it as an array of digits without leading zeroes. Let's call it d. The numeration starts with 1, starting from the most significant digit. Petya wants to perform the following operation k times: find the minimum x (1 ≤ x < n) such that dx = 4 and dx + 1 = 7, if x is odd, then to assign dx = dx + 1 = 4, otherwise to assign dx = dx + 1 = 7. Note that if no x was found, then the operation counts as completed and the array doesn't change at all.
>
> You are given the initial number as an array of digits and the number k. Help Petya find the result of completing k operations.



## **Input**

> The first line contains two integers n and k (1 ≤ n ≤ 10^5, 0 ≤ k ≤ 10^9) — the number of digits in the number and the number of completed operations. The second line contains n digits without spaces representing the array of digits d, starting with d1. It is guaranteed that the first digit of the number does not equal zero.



## **Output**

> In the single line print the result without spaces — the number after the k operations are fulfilled.



## **Examples input**

    7 4
    4727447



## **Examples output**

    4427477



## **题意**

给定一个由 `4`, `7` 组成的字符串，每次从左到右找第一个 `47` ，然后判断其起始下标是偶数还是奇数，若为奇数，则替换为 `44` ，否则替换为 `77` ，最多操作 `k` 次，求最终结果。



## **思路**

显然我们把 `47` 替换为 `44` 只会对当前位置以后产生影响，而替换为 `77` 则会对当前位置以前产生影响。

若串中 $i-1$ 的位置也为 `4` ，则会发现 `447` 这部分会产生循环，此时可以直接得出结果，否则遍历一下原串照题意修改即可。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);

using namespace std;
typedef long long ll;
const int maxn = 1e5+10;

int n,k;
char a[maxn];
int main()
{
    cin>>n>>k;
    getchar();
    gets(a+1);
    for(int i=1; i<=n-1&&k; i++)
    {
        if(a[i]=='4'&&a[i+1]=='7')
        {
            if(i&1)a[i+1] = '4';
            else
            {
                if(a[i-1]=='4')
                {
                    if(k&1)a[i]='7';
                    else a[i]='4';
                    break;
                }
                else
                    a[i]='7';
            }
            --k;
        }
    }
    puts(a+1);
    return 0;
}
```

