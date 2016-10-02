/*
HDU 5907 Find Q

题意：有一个小写字母组成的字符串S，输出S的所有仅包含字母'q'的连续子串的个数。

思路：只S中所有的仅包含q的段的长度，每一段能组成这种字串的个数都是一个等差数列的前n项和
    比如qqqaqq 长度3 2 子串个数 = 1+2+3 + 1+2 = 6 + 3 = 9
*/

#include <iostream>
#include<algorithm>
#include<string.h>
#include<stdio.h>
using namespace std;
char c[110000];
__int64 getsum(__int64 n)   //等差数列前n项和
{
    if(n%2==0)return n/2*(1+n);
    else return (1+n)/2*n;
}
int main()
{
    int n;
    scanf("%d%*c",&n);
    while(n--)
    {
        __int64 sum=0,s=0;
        gets(c);
        for(__int64 i=0; i<(__int64)strlen(c); i++)
        {
            if(c[i]=='q')s++;
            else
            {
                if(s)sum+=getsum(s);
                s=0;
            }
        }
        printf("%I64d\n",sum+getsum(s));
    }
    return 0;
}
