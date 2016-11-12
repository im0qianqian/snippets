/*
HDU 1403 Longest Common Substring

题意：求两个串的最长公共子串

思路：可以考虑这样一种情形，假设两个串s,t首尾连接形成新的一个串str，那么最长公共子串便是str中至少出现两次的子串（前提是这两个子串分别属于s与t），
答案一定会在后缀数组中相邻两个后缀的公共前缀中，因为经过排序后的后缀相邻两个的字典序差最小，因此最长公共前缀也就是本题的答案。（注意：这两个前缀必须是分别属于s与t的）

sa[]:后缀数组
rk[]:名次数组
lcp[]:高度数组
*/

#include<stdio.h>
#include<math.h>
#include<string.h>
#include<iostream>
#include<algorithm>
#define MAXX 220000
using namespace std;

int k,n;
int sa[MAXX],rk[MAXX],temp[MAXX],lcp[MAXX];
char s[MAXX],t[MAXX];
bool cmp(int i,int j)   //倍增算法比较函数
{
    if(rk[i] != rk[j]) return rk[i] < rk[j];
    int ri = i+k<=n?rk[i+k]:-1;
    int rj = j+k<=n?rk[j+k]:-1;
    return ri < rj;
}
void construct_sa(char *a)
{
    for(int i=0; i<=n; i++)
    {
        sa[i]=i;
        rk[i]=i<n?a[i]:-1;
    }
    for(k=1; k<=n; k<<=1)    //*2倍增
    {
        sort(sa,sa+n+1,cmp);
        temp[sa[0]]=0;
        for(int i=1; i<=n; i++)
            temp[sa[i]]=temp[sa[i-1]]+cmp(sa[i-1],sa[i]);
        for(int i=0; i<=n; i++) //计算名次数组
            rk[i]=temp[i];
    }
}

void construct_lcp(char *s) //lcp
{
    for(int i=0; i<=n; i++)
        rk[sa[i]]=i;
    int h=0;
    lcp[0]=0;
    for(int i=0; i<n; i++)
    {
        int j=sa[rk[i]-1];
        if(h>0)h--;
        for(; j+h<n&&i+h<n; h++)
            if(s[j+h]!=s[i+h])
                break;
        lcp[rk[i]-1]=h;
    }
}

void solve()
{
    int s1=strlen(s);   //计算串s的长度
    strcat(s,t);    //连接s,t
    n=strlen(s);    //计算连接之后串的长度
    construct_sa(s);
    construct_lcp(s);
    int ans=0;
    for(int i=0; i<n; i++)
        if((sa[i]<s1)!=(sa[i+1]<s1))    //子串分属两个串
            ans=max(ans,lcp[i]);
    printf("%d\n",ans);
}
int main()
{
    while(gets(s))
    {
        gets(t);
        solve();
    }
    return 0;
}
