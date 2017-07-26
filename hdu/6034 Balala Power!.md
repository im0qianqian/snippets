# Balala Power!

## **Description**

> ![img](http://acm.hdu.edu.cn/data/images/C642-1002-1.jpg)
>
> Talented Mr.Tang has n strings consisting of only lower case characters. He wants to charge them with Balala Power (he could change each character ranged from a to z into each number ranged from 0 to 25, but each two different characters should not be changed into the same number) so that he could calculate the sum of these strings as integers in base 26 hilariously.
>
> Mr.Tang wants you to maximize the summation. Notice that no string in this problem could have leading zeros except for string "0". It is guaranteed that at least one character does not appear at the beginning of any string.
>
> The summation may be quite large, so you should output it in modulo 109+7.



## **Input**

> The input contains multiple test cases.
>
> For each test case, the first line contains one positive integers n, the number of strings. (1≤n≤100000)
>
> Each of the next n lines contains a string si consisting of only lower case letters. (1≤|si|≤100000,∑|si|≤106)



## **Output**

> For each test case, output "Case #x: y" in one line (without quotes), where x indicates the case number starting from 1 and y denotes the answer of corresponding case.



## **Sample Input**

    1
    a
    2
    aa
    bb
    3
    a
    ba
    abc



## **Sample Output**

    Case #1: 25
    Case #2: 1323
    Case #3: 18221


## **题意**

有 `n` 个字符串，我们可以把串中任意一个字母替换成 `0-25` 这些数字中的一个，要求不同的字母不可以替换为相同的数字，问最终组成的所有 26 进制数的最大和。



## **思路**

**贪心思想**，既然每一个字母都可以替换为一个 26 进制数，那么首先想到的当然是高位替换为较大值，因为这样才可以使得整个数的大小变大。

于是，我们可以先统计所有字母在每一位中出现的次数，满 26 进 1 （因为是 26 进制咯，为了方便比较），每一个字母的出现可以表示为一个 26 进制数，然后根据这一权值排序。

**题目中要求长度大于 1 的字符串中不可以替换为存在前导 0 的数，比如 [0 13 25]。**

所以对于权值比较小，但是在某些字符串的首位出现过的字母，我们要特殊处理，这里要用一个权值较小并且没有在首位中出现的字母替换之！

一定会存在一个字母不出现在长度大于 1 的字符串首位的！

> It is guaranteed that at least one character does not appear at the beginning of any string.

因此该方法成立~



## **AC 代码**

```cpp
#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cstdio>
using namespace std;

typedef __int64 LL;
const int maxs=26;
const int maxn = 1e5+10;
const int mod = 1e9+7;

struct node
{
    int data;
    int num[maxn];      //所有字符串中该字母在第i位中出现过多少次
} ks[maxs];
bool vis[maxs];         //该字母是否在长度大于1的字符串首位出现过
char str[maxn];

bool cmp(const node &a,const node &b)   //比较两个26进制数的大小
{
    for(int i=maxn-1; i>=0; i--)
        if(a.num[i]!=b.num[i])
            return a.num[i]<b.num[i];
    return false;
}

void init()
{
    for(int i=0; i<maxs; i++)
    {
        ks[i].data=i;
        memset(ks[i].num,0,sizeof(ks[i].num));
    }
    memset(vis,false,sizeof(vis));
}

int main()
{
    ios::sync_with_stdio(false);
    int n;
    for(int ti=1; cin>>n; ti++)
    {
        init();
        for(int i=0; i<n; i++)
        {
            cin>>str;
            int len=strlen(str);
            if(len>1)vis[str[0]-'a']=true;
            for(int j=0; j<len; j++)
            {
                int cr=str[j]-'a';
                int rk=len-j-1;
                ks[cr].num[rk]++;
                while(ks[cr].num[rk]==maxs) //进位
                {
                    ks[cr].num[rk++]=0;
                    ks[cr].num[rk]++;
                }
            }
        }
        sort(ks,ks+maxs,cmp);
        int op=-1;
        for(int i=0; i<maxs; i++)           //寻找一个没有在首位出现过的字母
            if(vis[ks[i].data]==false)
            {
                op=i;
                break;
            }
        LL ans=0;
        for(int i=maxs-1; i>=0; i--)
        {
            LL cnt=0;
            for(int j=maxn-1; j>=0; j--)
                cnt=((cnt*maxs)%mod+ks[i].num[j])%mod;
            ans=(ans+(cnt*(i==op?0:i<op?i+1:i))%mod)%mod;   //若权值比较小的字母在首位出现过，则用其他代替
        }
        cout<<"Case #"<<ti<<": "<<ans<<endl;
    }
    return 0;
}
```

