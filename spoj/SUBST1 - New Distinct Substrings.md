# SUBST1 - New Distinct Substrings

## **Description**

> Given a string, we need to find the total number of its distinct substrings.



## **Input**

> T - number of test cases. T<=20; Each test case consists of one string, whose length is <= 50000



## **Output**

> For each test case output one number saying the number of distinct substrings. 



## **Example Input**

    2
    CCCCC
    ABABA



## **Example Output**

    5
    9



## **题意**

给定一个字符串，求其不相同的子串数目。



## **思路**

每个子串一定是某个后缀的前缀，那么原问题便等价于求所有后缀之间有多少个不相同的前缀，可以发现，每增加一个后缀贡献 $len-SA[i]+1$ 个前缀，但这些子串中有重复计算，重复的个数为 $Height[i]$ 个与前面相同的前缀，减掉这部分就可以了。

即，每一个后缀对答案的贡献为 $len-SA[i]+1-Height[i]$



## **AC 代码**

```cpp
#include<bits/stdc++.h>
#define rank rankk
using namespace std;

const int MAXN = 2e5+10;

char ch[MAXN], All[MAXN];
int SA[MAXN], rank[MAXN], Height[MAXN], tax[MAXN], tp[MAXN], a[MAXN], n, m;
char str[MAXN];
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

void solve()
{
    n = strlen(str);
    for(int i=0; i<n; i++)
        a[i+1]=str[i];
    Suffix();
    int ans=0;
    for(int i=1; i<=n; i++)
        ans+=n-SA[i]+1-Height[i];
    cout<<ans<<endl;
}

int main()
{
    ios::sync_with_stdio(false);
    int T;
    cin>>T;
    while(T--)
    {
        cin>>str;
        solve();
    }
    return 0;
}
```

