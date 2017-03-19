# TIANKENG’s restaurant(Ⅱ)

## **Problem Description**

> After improving the marketing strategy, TIANKENG has made a fortune and he is going to step into the status of TuHao. Nevertheless, TIANKENG wants his restaurant to go international, so he decides to name his restaurant in English. For the lack of English skills, TIANKENG turns to CC, an English expert, to help him think of a property name. CC is a algorithm lover other than English, so he gives a long string S to TIANKENG. The string S only contains eight kinds of letters-------‘A’, ‘B’, ‘C’, ‘D’, ‘E’, ‘F’, ‘G’, ‘H’. TIANKENG wants his restaurant’s name to be out of ordinary, so the restaurant’s name is a string T which should satisfy the following conditions: The string T should be as short as possible, if there are more than one strings which have the same shortest length, you should choose the string which has the minimum lexicographic order. Could you help TIANKENG get the name as soon as possible?
>
> Meanwhile, T is different from all the substrings of S. Could you help TIANKENG get the name as soon as possible?



## **Input**

> The first line input file contains an integer T(T<=50) indicating the number of case.
>
> In each test case:
>
> Input a string S. the length of S is not large than 1000000.



## **Output**

> For each test case:
>
> Output the string t satisfying the condition.(T also only contains eight kinds of letters-------‘A’, ‘B’, ‘C’, ‘D’, ‘E’, ‘F’, ‘G’, ‘H’.)



## **Sample Input**

    3
    ABCDEFGH
    AAABAACADAEAFAGAH
    ACAC



## **Sample Output**

    AA
    BB
    B


## **题意**

我们假设从小到大定义这么一些字符串：

`A、B、C、D、E、F、G、H、AA、AB...AAA、...、HHH、...`

给你一个字符串，找出它里面没有出现过并且最小的子串。



## **思路**

我们可以先想一下，如果一个字符串中出现了从1位到6位的所有子串，那么它的长度会是多少， $6*6^8=10077696$ ，当然这只是最坏的情况，但是也超出了题目中的数据范围很多，所以我们只考虑六位以及六位以下的子串。

当长度为1时枚举所有子串存储其有没有出现。

长度为 $2、...、6$ 时也一样。

最后从小到大遍历数组，查找哪一个没有出现过，输出。



## **AC 代码**

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<iostream>
using namespace std;
#include<queue>
#include<stack>

bool hs[8000000];
char str[1001000];

bool jud(int n)
{
    while(n)
    {
        if(n%9==0)return false;
        n/=9;
    }
    return true;
}

int main()
{
    int n;
    scanf("%d%*c",&n);
    while(n--)
    {
        memset(hs,false,sizeof(hs));
        gets(str);
        int len=strlen(str);
        for(int i=1; i<7; i++)  //子串长度
        {
            for(int j=0; j<len-i+1; j++)    //遍历
            {
                int temp=0;
                for(int k=0; k<i; k++)  //求当前子串的哈希值
                    temp=temp*9+str[j+k]-'A'+1;
                hs[temp]=true;
            }
        }
        char ans[10];
        int top=0;
        for(int i=1;; i++)
            if(!hs[i]&&jud(i))
            {
                while(i)
                {
                    ans[top++]=i%9;
                    i/=9;
                }
                break;
            }
        for(int i=top-1; i>=0; i--)
            printf("%c",ans[i]+'A'-1);
        printf("\n");
    }
    return 0;
}
```

