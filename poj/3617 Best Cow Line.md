# Best Cow Line

## **Description**

> FJ is about to take his N (1 ≤ N ≤ 2,000) cows to the annual"Farmer of the Year" competition. In this contest every farmer arranges his cows in a line and herds them past the judges.
>
> The contest organizers adopted a new registration scheme this year: simply register the initial letter of every cow in the order they will appear (i.e., If FJ takes Bessie, Sylvia, and Dora in that order he just registers BSD). After the registration phase ends, every group is judged in increasing lexicographic order according to the string of the initials of the cows' names.
>
> FJ is very busy this year and has to hurry back to his farm, so he wants to be judged as early as possible. He decides to rearrange his cows, who have already lined up, before registering them.
>
> FJ marks a location for a new line of the competing cows. He then proceeds to marshal the cows from the old line to the new one by repeatedly sending either the first or last cow in the (remainder of the) original line to the end of the new line. When he's finished, FJ takes his cows for registration in this new order.
>
> Given the initial order of his cows, determine the least lexicographic string of initials he can make this way.



## **Input**

> Line 1: A single integer: N
>
> Lines 2..N+1: Line i+1 contains a single initial ('A'..'Z') of the cow in the ith position in the original line



## **Output**

> The least lexicographic string he can make. Every line (except perhaps the last one) contains the initials of 80 cows ('A'..'Z') in the new line.



## **Sample Input**

    6
    A
    C
    D
    B
    C
    B



## **Sample Output**

    ABCBCD


## **题意**

给定一个长度为 `n` 的字符串 `s` ，要构造一个新的字符串 `t` ，刚开始 `t` 是一个空串，我们只能从 `s` 的头部或者尾部取得字符添加到 `t` 中，并且要保证 `t` 的字典序尽可能小。



## **思路**

就算是一道贪心问题吧！

我们可以对字符串 `s` 进行操作，比较首尾两个字符的大小，优先将小的字符放入 `t` 中，如果 `s` 中首尾字符此时相同，则两个指针向中间靠拢，继续比较，如果哪边比较小，则把这边的字符放入 `t` 中，既然这样的贪心策略建立好了，实现就不麻烦啦~



## **AC 代码**

```cpp
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
void solve(char *c,int n)
{
    int left=0,right=n-1,s=0;
    while(left<=right)
    {
        bool f=false;
        for(int i=0; left+i<=right; i++)
            if(c[left+i]<c[right-i])
            {
                f=true;
                break;
            }
            else if(c[left+i]>c[right-i])
            {
                f=false;
                break;
            }
        if(f)putchar(c[left++]);
        else putchar(c[right--]);
        s++;
        if(s%80==0)cout<<endl;
    }
}

int main()
{
    int n;
    char c[10005];
    cin>>n;
    getchar();
    for(int i=0; i<n; i++)
        scanf("%c%*c",c+i);
    solve(c,n);
    return 0;
}
```

