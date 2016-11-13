/*
sa[]:后缀数组
rk[]:名次数组
lcp[]:高度数组
*/

#include<stdio.h>
#include<math.h>
#include<string.h>
#include<iostream>
#include<algorithm>
using namespace std;

int k,sa[MAXX],rk[MAXX],temp[MAXX],lcp[MAXX];
bool cmp(int i,int j)   //倍增算法比较函数
{
    if(rk[i] != rk[j]) return rk[i] < rk[j];
    int ri = i+k<=n?rk[i+k]:-1;
    int rj = j+k<=n?rk[j+k]:-1;
    return ri < rj;
}
void construct_sa(char *a)
{
    int n=strlen(a);
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
    int n=strlen(s);
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