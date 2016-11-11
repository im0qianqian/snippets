/*
POJ 3581 Sequence

题意：给一个整数序列，要求划分成三个连续的子序列，同时将子序列反序，使得最后得到的序列的子典序最小。

思路：首先，我们确定第一段是比较简单的，因为题目中有说明A1比其他任何数都要大，所以我们只需要选择反转之后字典序最小的后缀，便可以得出第一段的结果（切除该后缀要保证剩下的部分可以分为两组）。
剩余的两段，也就是把此时的序列分为两段再分别反转得到的序列，可以看做是把两个原序列拼接得到新序列中某个子串反转所得到的序列（如串$1$2拼接得到$1$2$1$2），然后计算其后缀数组，从中选出字典序最小且合适的后缀便是另一组答案。
*/

#include<stdio.h>
#include<math.h>
#include<string.h>
#include<iostream>
#include<algorithm>
#define MAXX 200100
using namespace std;

int data[MAXX],k,n;
int rev[MAXX],sa[MAXX],rk[MAXX],temp[MAXX];

bool cmp(int i,int j)   //倍增算法比较函数
{
    if(rk[i] != rk[j]) return rk[i] < rk[j];
    else
    {
        int ri = i+k<=n?rk[i+k]:-1;
        int rj = j+k<=n?rk[j+k]:-1;
        return ri < rj;
    }
}
void construct_sa(int *a,int n,int *sa)
{
    for(int i=0; i<=n; i++)
    {
        sa[i]=i;
        rk[i]=i<n?a[i]:-1;
    }
    for(k=1; k<=n; k*=2)    //*2倍增
    {
        sort(sa,sa+n+1,cmp);
        temp[sa[0]]=0;
        for(int i=1; i<=n; i++)
            temp[sa[i]]=temp[sa[i-1]]+(cmp(sa[i-1],sa[i])?1:0);
        for(int i=0; i<=n; i++) //计算名次数组
            rk[i]=temp[i];
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=0; i<n; i++)
        scanf("%d",data+i);
    reverse_copy(data,data+n,rev);  //反转原数组
    construct_sa(rev,n,sa);     //计算sa后缀数组
    int p1;
    for(int i=0; i<=n; i++)
    {
        p1=n-sa[i];
        if(p1>=1&&n-p1>=2)break;
    }
    int m=n-p1;
    reverse_copy(data+p1,data+n,rev);
    reverse_copy(data+p1,data+n,rev+m);
    construct_sa(rev,2*m,sa);
    int p2;
    for(int i=0; i<=2*m; i++)
    {
        p2=p1+m-sa[i];
        if(p2-p1>=1&&n-p2>=1)break;
    }
    reverse(data,data+p1);
    reverse(data+p1,data+p2);
    reverse(data+p2,data+n);
    for(int i=0; i<n; i++)
        printf("%d\n",data[i]);
    return 0;
}
