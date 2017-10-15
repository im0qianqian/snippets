# Regular Number

## **Description**

> Using regular expression to define a numeric string is a very common thing. Generally, use the shape as follows:
>
> (0|9|7) (5|6) (2) (4|5)
>
> Above regular expression matches 4 digits:The first is one of 0,9 and 7. The second is one of 5 and 6. The third is 2. And the fourth is one of 4 and 5. The above regular expression can be successfully matched to 0525, but it cannot be matched to 9634.
>
> Now,giving you a regular expression like the above formula,and a long string of numbers,please find out all the substrings of this long string that can be matched to the regular expression.



## **Input**

> It contains a set of test data.The first line is a positive integer N (1 ≤ N ≤ 1000),on behalf of the regular representation of the N bit string.In the next N lines,the first integer of the i-th line is ai(1≤ai≤10),representing that the i-th position of regular expression has ai numbers to be selected.Next there are ai numeric characters. In the last line,there is a numeric string.The length of the string is not more than 5 * 10^6.



## **Output**

> Output all substrings that can be matched by the regular expression. Each substring occupies one line



## **Sample Input**

    4
    3 0 9 7
    2 5 7
    2 2 5
    2 4 5
    09755420524



## **Sample Output**

    9755
    7554
    0524



## **题意**

有 $n$ 组数，每组数中包含一些一位数，输出所有按顺序从每个组中取出一个数并且这些数组合形成的串是给定串的子串。



## **思路**

一开始想到把所有组的数压进一个 $bitset$ 中，其中每个组占 $10$ 位，随后用给定串构造一个类似的 $bitset$ ，然后移动相与求结果，无奈复杂度过高放弃了。

---

一个更优雅的做法是：我们用一个 $bitset$ 数组记录 $[0,9]$ 它们出现的组号，然后设定一个 $ans$ ，遍历给定串，对于每一位字符 $s$ ，首先左移 $ans$ 并置 $ans[0]=1$ ，它标记了当前所有连续组的长度，显然 $ans\&=a[s-'0']$ 这一步决定了是否可以扩充一位字符到之前的结果中，如果扩充到长度为 $n$ ，则 $ans[n-1]=1$ ，输出这部分即可。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);
using namespace std;
const int maxn = 1e3+10;
const int maxm = 5e6+10;
bitset<maxn>a[10],ans;
char str[maxm];

void init()
{
    for(int i=0; i<10; i++)
        a[i].reset();
    ans.reset();
}

int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        init();
        for(int i=0; i<n; i++)
        {
            int ai;
            scanf("%d",&ai);
            for(int j=0; j<ai; j++)
            {
                int x;
                scanf("%d%*c",&x);
                a[x].set(i);
            }
        }
        gets(str);
        int len = strlen(str);
        for(int i=0; i<len; i++)
        {
            ans<<=1;
            ans[0]=1;
            ans&=a[str[i]-'0'];
            if(ans[n-1]==1)
            {
                char tmp = str[i+1];
                str[i+1] = 0;
                puts(str+i-n+1);
                str[i+1] = tmp;
            }
        }
    }
    return 0;
}
```

