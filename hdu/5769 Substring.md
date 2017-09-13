# Substring

## **Description**

> ?? is practicing his program skill, and now he is given a string, he has to calculate the total number of its distinct substrings. 
>
> But ?? thinks that is too easy, he wants to make this problem more interesting. 
>
> ?? likes a character X very much, so he wants to know the number of distinct substrings which contains at least one X. 
>
> However, ?? is unable to solve it, please help him.



## **Input**

> The first line of the input gives the number of test cases T;T test cases follow. 
>
> Each test case is consist of 2 lines: 
>
> First line is a character X, and second line is a string S. 
>
> X is a lowercase letter, and S contains lowercase letters(‘a’-‘z’) only.
>
> T<=30 
>
> 1<=|S|<=10^5 
>
> The sum of |S| in all the test cases is no more than 700,000.



## **Output**

> For each test case, output one line containing “Case #x: y”(without quotes), where x is the test case number(starting from 1) and y is the answer you get for that case.



## **Sample Input**

    2 
    a 
    abc 
    b 
    bbb



## **Sample Output**

    Case #1: 3 
    Case #2: 3



## **题意**

给定一个字符串，求包含字母 `x` 的不相同子串数目。



## **思路**

这道题和之前我们所做的**求字符串不同子串数目**类似，唯一的不同便是限制了必须要包含字母 `x` 。

如果没有该限制，每一个后缀对结果的贡献为 $len-SA[i]+1-Height[i]$

我们记录第 $i$ 位以后第一个出现字母 `x` 的位置为 $last[i]$ ，保证不相同子串的情况下如果 $last[SA[i]]+1<=len-SA[i]+1-Height[i]$ ，则说明当前后缀所有贡献的子串都满足条件，否则只有 $len-last[SA[i]]$ 个满足。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
#define rank rankk
using namespace std;
typedef __int64 LL;
const int MAXN = 7e5+10;

char ch[MAXN], All[MAXN];
int SA[MAXN], rank[MAXN], Height[MAXN], tax[MAXN], tp[MAXN], a[MAXN], n, m;
char str[MAXN];
int last[MAXN];
//rank[i] 第i个后缀的排名; SA[i] 排名为i的后缀位置; Height[i] 排名为i的后缀与排名为(i-1)的后缀的LCP
//tax[i] 计数排序辅助数组; tp[i] rank的辅助数组(计数排序中的第二关键字),与SA意义一样。
//a为原串
void RSort()
{
    //rank第一关键字,tp第二关键字。
    for (int i = 0; i <= m; i ++) tax[i] = 0;
    for (int i = 1; i <= n; i ++) tax[rank[tp[i]]] ++;
    for (int i = 1; i <= m; i ++) tax[i] += tax[i-1];
    for (int i = n; i >= 1; i --) SA[tax[rank[tp[i]]] --] = tp[i]; //确保满足第一关键字的同时，再满足第二关键字的要求
} //计数排序,把新的二元组排序。

int cmp(int *f, int x, int y, int w)
{
    return f[x] == f[y] && f[x + w] == f[y + w];
}
//通过二元组两个下标的比较，确定两个子串是否相同

void Suffix()
{
    //SA
    for (int i = 1; i <= n; i ++) rank[i] = a[i], tp[i] = i;
    m = 127,RSort();  //一开始是以单个字符为单位，所以(m = 127)

    for (int w = 1, p = 1, i; p < n; w += w, m = p)   //把子串长度翻倍,更新rank
    {

        //w 当前一个子串的长度; m 当前离散后的排名种类数
        //当前的tp(第二关键字)可直接由上一次的SA的得到
        for (p = 0, i = n - w + 1; i <= n; i ++) tp[++ p] = i; //长度越界,第二关键字为0
        for (i = 1; i <= n; i ++) if (SA[i] > w) tp[++ p] = SA[i] - w;

        //更新SA值,并用tp暂时存下上一轮的rank(用于cmp比较)
        RSort(), swap(rank, tp), rank[SA[1]] = p = 1;

        //用已经完成的SA来更新与它互逆的rank,并离散rank
        for (i = 2; i <= n; i ++) rank[SA[i]] = cmp(tp, SA[i], SA[i - 1], w) ? p : ++ p;
    }
    //离散：把相等的字符串的rank设为相同。
    //LCP
    int j, k = 0;
    for(int i = 1; i <= n; Height[rank[i ++]] = k)
        for( k = k ? k - 1 : k, j = SA[rank[i] - 1]; a[i + k] == a[j + k]; ++ k);
    //这个知道原理后就比较好理解程序
}

LL solve(char c)
{
    n = strlen(str);
    int la = -1;
    for(int i=n-1; i>=0; i--)   //记录当前位置以后第一次出现 c 的坐标
    {
        if(str[i]==c)
            la = i;
        last[i+1]=la;
    }
    for(int i=0; i<n; i++)
        a[i+1]=str[i];
    Suffix();
    LL ans=0;
    for(int i=1; i<=n; i++)
        if(last[SA[i]]!=-1)
            ans+= n+1 - max(SA[i]+Height[i],last[SA[i]]+1);
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int T;
    cin>>T;
    for(int ti=1; ti<=T; ti++)
    {
        char c;
        cin>>c;
        cin>>str;
        cout<<"Case #"<<ti<<": "<<solve(c)<<endl;
    }
    return 0;
}
```

