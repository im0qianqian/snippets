# Human Gene Functions

## **Description**

> It is well known that a human gene can be considered as a sequence, consisting of four nucleotides, which are simply denoted by four letters, A, C, G, and T. Biologists have been interested in identifying human genes and determining their functions, because these can be used to diagnose human diseases and to design new drugs for them. 
>
> A human gene can be identified through a series of time-consuming biological experiments, often with the help of computer programs. Once a sequence of a gene is obtained, the next job is to determine its function. 
>
> One of the methods for biologists to use in determining the function of a new gene sequence that they have just identified is to search a database with the new gene as a query. The database to be searched stores many gene sequences and their functions – many researchers have been submitting their genes and functions to the database and the database is freely accessible through the Internet. 
>
> A database search will return a list of gene sequences from the database that are similar to the query gene. 
>
> Biologists assume that sequence similarity often implies functional similarity. So, the function of the new gene might be one of the functions that the genes from the list have. To exactly determine which one is the right one another series of biological experiments will be needed. 
>
> Your job is to make a program that compares two genes and determines their similarity as explained below. Your program may be used as a part of the database search if you can provide an efficient one. 
>
> Given two genes AGTGATG and GTTAG, how similar are they? One of the methods to measure the similarity of two genes is called alignment. In an alignment, spaces are inserted, if necessary, in appropriate positions of the genes to make them equally long and score the resulting genes according to a scoring matrix. 
>
> For example, one space is inserted into AGTGATG to result in AGTGAT-G, and three spaces are inserted into GTTAG to result in –GT--TAG. A space is denoted by a minus sign (-). The two genes are now of equal length. These two strings are aligned: 
>
> ```
> AGTGAT-G 
> -GT--TAG 
> ```
>
> In this alignment, there are four matches, namely, G in the second position, T in the third, T in the sixth, and G in the eighth. Each pair of aligned characters is assigned a score according to the following scoring matrix. 
>
> ![img](http://poj.org/images/1080/1080_1.gif)
>
> denotes that a space-space match is not allowed. The score of the alignment above is (-3)+5+5+(-2)+(-3)+5+(-3)+5=9. 
>
> Of course, many other alignments are possible. One is shown below (a different number of spaces are inserted into different positions): 
>
> ```
> AGTGATG 
> -GTTA-G 
> ```
>
> This alignment gives a score of (-3)+5+5+(-2)+5+(-1) +5=14. So, this one is better than the previous one. As a matter of fact, this one is optimal since no other alignment can have a higher score. So, it is said that the 
>
> similarity of the two genes is 14.



## **Input**

> The input consists of T test cases. The number of test cases ) (T is given in the first line of the input file. Each test case consists of two lines: each line contains an integer, the length of a gene, followed by a gene sequence. The length of each gene sequence is at least one and does not exceed 100.



## **Output**

> The output should print the similarity of each test case, one per line.



## **Sample Input**

    2 
    7 AGTGATG 
    5 GTTAG 
    7 AGCTATT 
    9 AGCTTTAAA 



## **Sample Output**

    14
    21 


## **题意**

给定两个基因字符串，用A，C，G，T表示其组成成分。

若两个基因的长度不一样，可以通过在两个串中分别添加空格使其长度一致，当其长度一样后，分别计算对应位置上的两个字母的分数，并将所有的分数相加便得到两个串的相似度分数，求最高分数。



## **思路**

分析可知，在匹配过程中有以下几种情况。

- $c[i-1]=d[j-1]$ ，分数为 $dp[i-1][j-1]+sorce[c[i-1]][d[j-1]]$
- $c[i-1]!=d[j-1]$
  - 给i处补空格，分数 $dp[i][j-1]+sorce['-'][d[j-1]]$
  - 给j处补空格，分数 $dp[i-1][j]+sorce[c[i-1]]['-']$
  - 直接匹配，分数 $dp[i-1][j-1]+sorce[c[i-1]][d[j-1]]$

在两字母不同下的直接匹配和相同下的匹配分数是一样的，因此可以合并。

$dp[i][j]$ 取这三者最大值便可。



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

int sorce[125][125];
void init()
{
    sorce['A']['A']=5;
    sorce['C']['C']=5;
    sorce['G']['G']=5;
    sorce['T']['T']=5;
    sorce['A']['C']=sorce['C']['A']=-1;
    sorce['A']['G']=sorce['G']['A']=-2;
    sorce['A']['T']=sorce['T']['A']=-1;
    sorce['A']['-']=sorce['-']['A']=-3;
    sorce['C']['G']=sorce['G']['C']=-3;
    sorce['C']['T']=sorce['T']['C']=-2;
    sorce['C']['-']=sorce['-']['C']=-4;
    sorce['G']['T']=sorce['T']['G']=-2;
    sorce['G']['-']=sorce['-']['G']=-2;
    sorce['T']['-']=sorce['-']['T']=-1;
    sorce['-']['-']=0;
}
char c[115],d[115];
int dp[115][115];
void lcs(int lc,int ld)
{
    memset(dp,0,sizeof(dp));
    for(int i=1; i<=lc; i++)
        dp[i][0]=dp[i-1][0]+sorce['-'][c[i-1]];
    for(int i=1; i<=ld; i++)
        dp[0][i]=dp[0][i-1]+sorce['-'][d[i-1]];
    for(int i=1; i<=lc; i++)
        for(int j=1; j<=ld; j++)
            dp[i][j]=max(dp[i-1][j-1]+sorce[c[i-1]][d[j-1]],max(dp[i-1][j]+sorce[c[i-1]]['-'],dp[i][j-1]+sorce['-'][d[j-1]]));
    printf("%d\n",dp[lc][ld]);
}
int main()
{
    init();
    int n;
    scanf("%d",&n);
    while(n--)
    {
        int lc,ld;
        cin>>lc>>c>>ld>>d;
        lcs(lc,ld);
    }
    return 0;
}
```

