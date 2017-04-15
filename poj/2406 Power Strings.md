# Power Strings

## **Description**

> Given two strings a and b we define a*b to be their concatenation. For example, if a = "abc" and b = "def" then a*b = "abcdef". If we think of concatenation as multiplication, exponentiation by a non-negative integer is defined in the normal way: a^0 = "" (the empty string) and a^(n+1) = a*(a^n).



## **Input**

> Each test case is a line of input representing s, a string of printable characters. The length of s will be at least 1 and will not exceed 1 million characters. A line containing a period follows the last test case.



## **Output**

> For each s you should print the largest n such that s = a^n for some string a.



## **Sample Input**

    abcd
    aaaa
    ababab
    .



## **Sample Output**

    1
    4
    3



## **题意**

给出的一个字符串是某个字串连接N次得出的，求最大N的。



## **思路**

KMP匹配算法之 `next[]` ;

模式串结尾指针回溯最小移动次数即最小字串长度 `N=s.length%(s.length-next[s.length]);`



## **AC 代码**

```cpp
#include <stdio.h>
#include <string.h>
char s[1000005];
int num[1000005];
int main()
{
    while(scanf("%s",s),s[0]!='.')
    {
        int j=-1;
        num[0]=-1;
        int n=strlen(s);
        for(int i=0; i<n;)
        {
            if(j==-1||s[i]==s[j])num[++i]=++j;
            else j=num[j];
        }
        if(n%(n-num[n])==0)
            printf("%d\n",n/(n-num[n]));
        else printf("1\n");
    }
    return 0;
}
```

