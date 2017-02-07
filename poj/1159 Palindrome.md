# Palindrome

## **Description**

> A palindrome is a symmetrical string, that is, a string read identically from left to right as well as from right to left. You are to write a program which, given a string, determines the minimal number of characters to be inserted into the string in order to obtain a palindrome. 
>
> As an example, by inserting 2 characters, the string "Ab3bd" can be transformed into a palindrome ("dAb3bAd" or "Adb3bdA"). However, inserting fewer than 2 characters does not produce a palindrome. 



## **Input**

> Your program is to read from standard input. The first line contains one integer: the length of the input string N, 3 <= N <= 5000. The second line contains one string with length N. The string is formed from uppercase letters from 'A' to 'Z', lowercase letters from 'a' to 'z' and digits from '0' to '9'. Uppercase and lowercase letters are to be considered distinct.



## **Output**

> Your program is to write to standard output. The first line contains one integer, which is the desired minimal number.



## **Sample Input**

    5
    Ab3bd



## **Sample Output**

    2



## **题意**

给出一个字符串，问最少添加几个字符才能构成一个回文串。



## **思路**

对于这种类型的题目是有一个公式的啦！

添加的最少字符个数 = 字符串长度 - （字符串正序与逆序的最长公共子序列长度）



**但是，对于这道题，仅仅知道这个公式可不行哦~**

题目中有说明字符串长度最大为5000，但是dp数组开到 $5000*5000$ 的话会内存超限。

**有两种解决方案：**

- 使用short类型
- 滚动数组



## **AC 代码**

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<iostream>
using namespace std;
#include<vector>
#include<queue>
#include<map>
#define MAXX 5100
char c[MAXX],d[MAXX];
int dp[2][MAXX],n;

void lcs()
{
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
        {
            if(c[i-1]==d[j-1])
                dp[i%2][j]=dp[(i-1)%2][(j-1)]+1;
            else dp[i%2][j]=max(dp[(i-1)%2][j],dp[i%2][(j-1)]);
        }
    cout<<n-dp[n%2][n]<<endl;     //字符串长度-最长公共子序列
}

int main()
{
    while(cin>>n>>c)
    {
        memset(dp,0,sizeof(dp));
        for(int i=n-1; i>=0; i--)
            d[n-i-1]=c[i];
        lcs();
    }
    return 0;
}
```

