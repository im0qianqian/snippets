# A Secret

## **Description**

> Today is the birthday of SF,so VS gives two strings S1,S2 to SF as a present,which have a big secret.SF is interested in this secret and ask VS how to get it.There are the things that VS tell:
>
> Suffix(S2,i) = S2[i...len].Ni is the times that Suffix(S2,i) occurs in S1 and Li is the length of Suffix(S2,i).Then the secret is the sum of the product of Ni and Li.
>
> Now SF wants you to help him find the secret.The answer may be very large, so the answer should mod 1000000007.



## **Input**

> Input contains multiple cases.
>
> The first line contains an integer T,the number of cases.Then following T cases.
>
> Each test case contains two lines.The first line contains a string S1.The second line contains a string S2.
>
> 1<=T<=10.1<=|S1|,|S2|<=1e6.S1 and S2 only consist of lowercase ,uppercase letter.



## **Output**

> For each test case,output a single line containing a integer,the answer of test case.
>
> The answer may be very large, so the answer should mod 1e9+7.



## **Sample Input**

    2
    aaaaa
    aa
    abababab
    aba



## **Sample Output**

    13
    19


## **题意**

给出两个字符串 A 和 B ，求 B 的所有后缀在 A 中的出现次数与后缀长度的乘积和。



## **思路**

枚举所有后缀显然不是理想的方案，但是我们把两个串倒过来，问题就变成了求 B 的所有前缀在 A 中出现次数与后缀长度的乘积和。

于是便是 **扩展 KMP** 的基础题目啦。

对于 `extend[i]` 所保存的 `y[i..n-1]` 与 `x[0..m-1]` 的最长公共前缀。

我们可以枚举所有的 `i` ，对于每一个 `i` ，结果便是 $1+2+3+...+extend[i]$ ，即 $\frac{extend[i] \times (extend[i]+1)}{2}$ 。

累计求和即可。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6+10;
typedef __int64 LL;
const int mod = 1e9+7;

void pre_ekmp(char *x,int m,int next[])
{
    next[0]=m;
    int j=0;
    while(j+1<m&&x[j]==x[j+1])j++;
    next[1]=j;
    int k=1;
    for(int i=2; i<m; i++)

    {
        int p=next[k]+k-1;
        int L=next[i-k];
        if(i+L<p+1)next[i]=L;
        else
        {
            j=max(0,p-i+1);
            while(i+j<m&&x[i+j]==x[j])
                j++;
            next[i]=j;
            k=i;
        }
    }
}

void ekmp(char x[],int m,char y[],int n,int next[],int extend[])
{
    pre_ekmp(x,m,next);
    int j=0;
    while(j<n&&j<m&&x[j]==y[j])j++;
    extend[0]=j;
    int k=0;
    for(int i=1; i<n; i++)
    {
        int p=extend[k]+k-1;
        int L=next[i-k];
        if(i+L<p+1)extend[i]=L;
        else
        {
            j=max(0,p-i+1);
            while(i+j<n&&j<m&&y[i+j]==x[j])j++;
            extend[i]=j;
            k=i;
        }
    }
}

char str1[maxn],str2[maxn];
int nex[maxn],extend[maxn];
int main()
{
    ios::sync_with_stdio(false);
    int T;
    cin>>T;
    while(T--)
    {
        cin>>str1>>str2;
        int n=strlen(str1);
        int m=strlen(str2);
        reverse(str1,str1+n);
        reverse(str2,str2+m);
        ekmp(str2,m,str1,n,nex,extend);
        LL ans=0;
        for(int i=0; i<n; i++)
            ans=((1LL*extend[i]*(extend[i]+1)/2)%mod+ans)%mod;
        cout<<ans<<endl;
    }
    return 0;
}
```

