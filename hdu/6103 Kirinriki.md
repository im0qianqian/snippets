# Kirinriki

## **Description**

> We define the distance of two strings A and B with same length n is
>
> $dis_{A,B}=\sum_{i=0}^{n−1}|A_i−B_{n−1−i}|$
>
> The difference between the two characters is defined as the difference in ASCII.
>
> You should find the maximum length of two non-overlapping substrings in given string S, and the distance between them are less then or equal to m.



## **Input**

> The first line of the input gives the number of test cases T; T test cases follow.
>
> Each case begins with one line with one integers m : the limit distance of substring.
>
> Then a string S follow.
>
> Limits
>
> $T≤100, 0≤m≤5000$
>
> Each character in the string is lowercase letter, $2≤|S|≤5000$
>
> $\sum|S|≤20000$



## **Output**

> For each test case output one interge denotes the answer : the maximum length of the substring.



## **Sample Input**

    1
    5
    abcdefedcb



## **Sample Output**

    5



## **题意**

给出字符串 `s` ，寻找其两个长度相同且不重叠的子串，满足其每位的 `ascil` 差值之和不大于 `m` ，且长度最长。



## **思路**

因为字符串长度很小，故我们可以枚举其每一个前缀与每一个后缀，

然后在枚举的子串内利用尺取法将区间等分，

利用差值之和不大于 `m` 的条件双指针同时遍历两个区间，更新最大值即可。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=21000;
char str[maxn];
int m,len;

int solve()
{
    int ans=0;
    for(int i=len; i>=1; i--)
    {
        int cnt=i/2-1,d=0,t=0,p=0;
        for(int j=0; j<=cnt; j++)
        {
            d+=abs(str[1+j]-str[i-j]);
            if(d>m)
            {
                d-=abs(str[1+p]-str[i-p]);
                d-=abs(str[1+j]-str[i-j]);
                p++;
                t--;
                j--;
            }
            else
            {
                t++;
                ans=max(ans,t);
            }
        }
    }
    return ans;
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int ans=0;
        scanf("%d%s",&m,str+1);
        len=strlen(str+1);
        ans=max(ans,solve());
        reverse(str+1,str+len+1);
        ans=max(ans,solve());
        printf("%d\n",ans);
    }
    return 0;
}
```

