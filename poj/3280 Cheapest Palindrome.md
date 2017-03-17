# Cheapest Palindrome

## **Description**

> Keeping track of all the cows can be a tricky task so Farmer John has installed a system to automate it. He has installed on each cow an electronic ID tag that the system will read as the cows pass by a scanner. Each ID tag's contents are currently a single string with length M (1 ≤ M ≤ 2,000) characters drawn from an alphabet of N (1 ≤ N ≤ 26) different symbols (namely, the lower-case roman alphabet).
>
> Cows, being the mischievous creatures they are, sometimes try to spoof the system by walking backwards. While a cow whose ID is "abcba" would read the same no matter which direction the she walks, a cow with the ID "abcb" can potentially register as two different IDs ("abcb" and "bcba").
>
> FJ would like to change the cows's ID tags so they read the same no matter which direction the cow walks by. For example, "abcb" can be changed by adding "a" at the end to form "abcba" so that the ID is palindromic (reads the same forwards and backwards). Some other ways to change the ID to be palindromic are include adding the three letters "bcb" to the begining to yield the ID "bcbabcb" or removing the letter "a" to yield the ID "bcb". One can add or remove characters at any location in the string yielding a string longer or shorter than the original string.
>
> Unfortunately as the ID tags are electronic, each character insertion or deletion has a cost (0 ≤ cost ≤ 10,000) which varies depending on exactly which character value to be added or deleted. Given the content of a cow's ID tag and the cost of inserting or deleting each of the alphabet's characters, find the minimum cost to change the ID tag so it satisfies FJ's requirements. An empty ID tag is considered to satisfy the requirements of reading the same forward and backward. Only letters with associated costs can be added to a string.



## **Input**

> Line 1: Two space-separated integers: N and M 
>
> Line 2: This line contains exactly M characters which constitute the initial ID string 
>
> Lines 3..N+2: Each line contains three space-separated entities: a character of the input alphabet and two integers which are respectively the cost of adding and deleting that character.



## **Output**

> Line 1: A single line with a single integer that is the minimum cost to change the given name tag.



## **Sample Input**

    3 4
    abcb
    a 1000 1100
    b 350 700
    c 200 800



## **Sample Output**

    900



## **题意**

给出一个由n种字母组成的长度为m的串，然后给出这n种字母的添加和删除的代价，问如何使用最小的代价通过添加字母与删除字母使得原串变成回文串。



## **思路**

定义 `dp[i][j]` 为区间 i 到 j 之间变成回文的最小代价。

**那么对于 `dp[i][j]` 有三种情况：**

- 如果 `s[i]==s[j]` ， `dp[i][j]=dp[i+1][j-1]` 
- 如果 `dp[i+1][j]` 是回文串，那么 `dp[i][j]=dp[i+1][j]+min(add[i],del[i])`
- 如果 `dp[i][j-1]` 是回文串，那么 `dp[i][j]=dp[i][j-1]+min(add[j],del[j])`

从上面推出的情况可以看到， i、j 之间跨度大的区间总是依赖于小的，于是我们可以从区间宽度为1的时候开始计算，然后计算宽度为2，...



## **AC 代码**

```cpp
#include <iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<stdio.h>
#include<algorithm>
#include<stack>
using namespace std;
#define INF (1<<25)

int ad[26],dp[2005][2005];
char str[2005];
int main()
{
    int n,m;
    while(~scanf("%d%d%*c",&n,&m))
    {
        gets(str);
        int add,del;
        char x;
        for(int i=0; i<n; i++)
        {
            scanf("%c%d%d%*c",&x,&add,&del);
            ad[x-'a']=min(del,add);
        }
        for(int k=1; k<m; k++)
            for(int i=0,j=k; j<m; i++,j++)
            {
                dp[i][j]=INF;
                if(str[i]==str[j])
                    dp[i][j]=dp[i+1][j-1];
                else
                    dp[i][j]=min(dp[i][j],min(dp[i+1][j]+ad[str[i]-'a'],dp[i][j-1]+ad[str[j]-'a']));
            }
        printf("%d\n",dp[0][m-1]);
    }
    return 0;
}
```

