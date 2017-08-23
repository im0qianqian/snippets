# Two strings

## **Description**

> Giving two strings and you should judge if they are matched.
>
> The first string contains lowercase letters and uppercase letters.
>
> The second string contains lowercase letters, uppercase letters, and special symbols: “.” and “\*”.
>
> . can match any letter, and \* means the front character can appear any times. For example, “a.b” can match “acb” or “abb”, “a\*” can match “a”, “aa” and even empty string. ( “\*” will not appear in the front of the string, and there will not be two consecutive “\*”.



## **Input**

> The first line contains an integer T implying the number of test cases. (T≤15)
>
> For each test case, there are two lines implying the two strings (The length of the two strings is less than 2500).



## **Output**

> For each test case, print “yes” if the two strings are matched, otherwise print “no”.



## **Sample Input**

    3
    aa
    a*
    abb
    a.*
    abb
    aab



## **Sample Output**

    yes
    yes
    no


## **题意**

给出原串与匹配串，问能否匹配原串中所有的字符。



## **思路**

**如果这是一个标准的正则匹配，是不是可以直接用语言特性了呢？**

我们设原串为 `a` ，匹配串为 `b` ， `dp[i][j]` 代表 `b[1..i]` 与 `a[1..j]` 是否匹配成功。

显然 `dp[0][0] = true` ，

**对于其他情况：**

- 如果 `b[i] == '.'` ，则此时 `a[j]` 可以是任意字符， `dp[i][j]` 由 `dp[i-1][j-1]` 转移而来。

- 如果 `a[j] == b[i]` ，同样 `dp[i][j]` 由 `dp[i-1][j-1]` 转移而来。

- 如果 `b[i] == '*'` ，假设该 `*` 最终可以匹配 0 位，则 `dp[i][j]` 状态从 `dp[i-2][j]` 转移而来，假设最终匹配 1 位，则从 `dp[i-1][j]` 转移而来；

  假如 `a[1..j-1]` 与 `b[1..i-1]` 已成功匹配，并且 `a[j-1] == a[j]` ，显然当前的 `*` 可以继续匹配这一个字符，因此 `dp[i][j] = true` ；

  假如 `a[1..j-1]` 与 `b[1..i]` 已成功匹配（当前 `*` 已成功匹配若干位），且 `a[j-1] == a[j]` ，则可以继续匹配这一个字符，因此 `dp[i][j] = true` 。

- 特别的，如果 `b[2] == '*'` ，则 `dp[ALL][0] = true` 。



## **AC 代码**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=2600;

char a[maxn],b[maxn];
bool dp[maxn][maxn];
int lena,lenb;
int main()
{
    int T;
    scanf("%d%*c",&T);
    while(T--)
    {
        memset(dp,false,sizeof(dp));
        a[0]=b[0]=1;
        gets(a+1);
        gets(b+1);
        lena = strlen(a) - 1;
        lenb = strlen(b) - 1;
        dp[0][0]=true;
        for(int i=1; i<=lenb; i++)
        {
            if(i==2&&b[i]=='*')
                dp[i][0] = true;
            for(int j=1; j<=lena; j++)
            {
                if(b[i]=='.'||a[j]==b[i])
                    dp[i][j]=dp[i-1][j-1];
                else if(b[i]=='*')
                {
                    dp[i][j]=dp[i-2][j]|dp[i-1][j];
                    if((dp[i-1][j-1]||dp[i][j-1])&&a[j-1]==a[j])
                        dp[i][j] = true;
                }
            }
        }
        puts(dp[lenb][lena]?"yes":"no");
    }
    return 0;
}
```

