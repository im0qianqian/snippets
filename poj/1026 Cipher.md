# Cipher

## **Description**

> Bob and Alice started to use a brand-new encoding scheme. Surprisingly it is not a Public Key Cryptosystem, but their encoding and decoding is based on secret keys. They chose the secret key at their last meeting in Philadelphia on February 16th, 1996. They chose as a secret key a sequence of n distinct integers, a1 ; . . .; an, greater than zero and less or equal to n. The encoding is based on the following principle. The message is written down below the key, so that characters in the message and numbers in the key are correspondingly aligned. Character in the message at the position i is written in the encoded message at the position ai, where ai is the corresponding number in the key. And then the encoded message is encoded in the same way. This process is repeated k times. After kth encoding they exchange their message.
>
> The length of the message is always less or equal than n. If the message is shorter than n, then spaces are added to the end of the message to get the message with the length n.
>
> Help Alice and Bob and write program which reads the key and then a sequence of pairs consisting of k and message to be encoded k times and produces a list of encoded messages.



## **Input**

> The input file consists of several blocks. Each block has a number 0 < n <= 200 in the first line. The next line contains a sequence of n numbers pairwise distinct and each greater than zero and less or equal than n. Next lines contain integer number k and one message of ascii characters separated by one space. The lines are ended with eol, this eol does not belong to the message. The block ends with the separate line with the number 0. After the last block there is in separate line the number 0.



## **Output**

> Output is divided into blocks corresponding to the input blocks. Each block contains the encoded input messages in the same order as in input file. Each encoded message in the output file has the lenght n. After each block there is one empty line.



## **Sample Input**

    10
    4 5 3 7 2 8 1 6 10 9
    1 Hello Bob
    1995 CERC
    0
    0



## **Sample Output**

    BolHeol  b
    C RCE



## **题意**

给出一个 `n` 个数的置换，按照置换的规则将一个字符串置换 `k` 次，如果字符串长度不足 `n` ，则在末尾补空格，求置换 `k` 次之后的字符串是什么。



## **思路**

本来打算模拟出一个置换的前 100000 种情况，然后把所有的结果存储在一个数组中。

只是这道题目只给了 `10M` 的内存限制，提交了好几次都是内存超限，再小一点又是运行错误了。



最后改成 【置换 + 轮换 + 模】 的方法之后就可以过了。

把给出的 `key` 写成置换的形式，然后对其分解求出每部分的轮换以及轮换的长度，因为在变换过程中每一个轮换中的元素所占有的位置不会改变，所以只是这些局部的数字会循环变化，循环的长度也就是轮换的长度。



## **AC 代码**

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<cmath>
#include<iostream>
using namespace std;
#include<queue>
#include<map>
#define INF (1<<25)

char str[210];  // 输入的字符串
int a[210];     // key
int G[210][210];    // 存储群的每一个轮换
int cut[210];   // 存储每个轮换的长度
int ds[210];    // key 与下标之间的映射
int top;        // 轮换的个数
int n;

void solve()    // 求所有轮换以及轮换的长度
{
    bool vis[210]= {false};
    top=0;
    for(int i=1; i<=n; i++)
    {
        int p=a[i];
        if(!vis[p])
        {
            cut[top]=0;
            while(!vis[p])
            {
                vis[p]=true;
                G[top][cut[top]++]=p;
                p=ds[p];
            }
            top++;
        }
    }
}

void get(int x) // 获取第x次加密后得到的密文
{
    int ans[210];
    for(int i=0; i<top; i++)    // 遍历所有轮换
        for(int j=0; j<cut[i]; j++) // 对轮换中的每个元素求出它在第x次变换之后的位置
            ans[ds[G[i][j]]]=G[i][(j+x+1)%cut[i]];
    for(int i=1; i<=n; i++)     //输出
        printf("%c",str[ans[i]-1]);
    printf("\n");
}

int main()
{
    while(~scanf("%d",&n)&&n)
    {
        int x;
        for(int i=1; i<=n; i++)
        {
            scanf("%d",a+i);
            ds[a[i]]=i;
        }
        solve();
        while(~scanf("%d%*c",&x)&&x)
        {
            gets(str);
            for(int i=strlen(str); i<n; i++)    // 字符串长度不够补空格
                str[i]=' ';
            str[n]=0;
            get(x);
        }
        printf("\n");
    }
    return 0;
}
```

