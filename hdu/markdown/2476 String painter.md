# HDU 2476 String painter #

<br/>

## **Problem Description** ##
>There are two strings A and B with equal length. Both strings are made up of lower case letters.

>Now you have a powerful string painter. With the help of the painter, you can change a segment of

>characters of a string to any other character you want. That is, after using the painter, the

>segment is made up of only one kind of character. Now your task is to change A to B using string

>painter. What’s the minimum number of operations?

<br/>

## **Input** ##
>Input contains multiple cases. Each case consists of two lines:

>The first line contains string A.

>The second line contains string B.

>The length of both strings will not be greater than 100.
 
<br/>

## **Output** ##
>A single line contains one integer representing the answer.
 
<br/>

## **Sample Input** ##
	zzzzzfzzzzz
	abcdefedcba
	abababababab
	cdcdcdcdcdcd
 
<br/>

## **Sample Output** ##
	6
	7

<br/>

## **题意** ##
给出两个字符串，每次我们可以把一个字符串的一个区间刷成同一个字母，问最少多少步可以把第一个字符串变为第二个字符串

<br/>

## **思路** ##
假设有一个字符串abcddcba，我们先考虑区间[0,7]也就是abcddcba，假如我们认为每次刷一位，不考虑优化的情况下的答案是8，也就是刷8次可以得到这个区间，但是，可以发现的是区间两个端点的值相等，所以我们可以在第一次用a来刷这个区间，假如用dp[0][7]来表示建立这个区间的最小次数,在端点相等的情况下我们可以假设去掉左端点，因为二者是等价的，然后区间变为bcddcba，如此便是一次优化，然后我们可以分解区间，然后分别优化求解两个区间

这样便可以得到单个字符串建立的最小次数，由串1变为串2，如果相同位置字符相同的话我们可以不刷这个位置。

<br/>

## **AC代码** ##

```cpp
#include <iostream>
#include<cstdio>
using namespace std;
#include<algorithm>
#include<string.h>
char s1[105],s2[105];
int dp[105][105],ans[105];
//dp[i][j]表示从i到j的最小次数
int main()
{
    while(gets(s1))
    {
        gets(s2);
        int len=strlen(s1);
        memset(dp,0,sizeof(dp));
        for(int j=0; j<len; j++)
            for(int i=j; i>=0; i--)
            {
                dp[i][j]=dp[i+1][j]+1;  //先假设无优化刷当前区间
                for(int k=i+1; k<=j; k++)   //用k来分割区间
                    if(s2[i]==s2[k])    //找到相等位置，更新最小次数
                        dp[i][j]=min(dp[i][j],dp[i+1][k]+dp[k+1][j]);
            }
        for(int i=0; i<len; i++)    //初始化ans
            ans[i]=dp[0][i];
        for(int i=0; i<len; i++)
        {
            if(s1[i]!=s2[i])    //分割区间找最优解
                for(int j=0; j<i; j++)
                    ans[i]=min(ans[i],ans[j]+dp[j+1][i]);
            else ans[i]=ans[i-1];   //如果相等，当前位置可以不刷
        }
        printf("%d\n",ans[len-1]);
    }
    return 0;
}
```