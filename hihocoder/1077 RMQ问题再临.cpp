/*
hihocoder 1077 RMQ问题再临
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
#define MAXX (1<<20)
#define INF 32767
int data[2*MAXX],n,s=1;
void init() //一棵完美二叉树初始化
{
    while(s<n)s<<=1;
    for(int i=0; i<=2*s; i++)
        data[i]=INF;
}
void update(int k,int a)    //从底向上更新数据
{
    k+=s;
    data[k]=a;
    while(k>1)
    {
        k/=2;
        data[k]=min(data[k*2],data[k*2+1]);
    }
}

int query(int a,int b,int k,int l,int r)    //查询[a,b]最小值，[l,r]为当前查询区间，k为当前所在节点
{
    if(r<a||b<l)return INF;                 //如果当前查询区间与[a,b]交集为空，返回INF
    if(a<=l&&r<=b)return data[k];           //如果[a,b]包含[l,r]返回当前节点的值
    else
    {
        int v1=query(a,b,k<<1,l,(l+r)>>1);  //左子树
        int v2=query(a,b,(k<<1)+1,1+((l+r)>>1),r);  //右子树
        return min(v1,v2);
    }
}

int main()
{
    int k;
    scanf("%d",&n);
    init();
    for(int i=0; i<n; i++)
    {
        scanf("%d",&k);
        update(i,k);
    }
    scanf("%d",&n);
    while(n--)
    {
        int a,b;
        scanf("%d%d%d",&k,&a,&b);
        if(k)update(a-1,b);
        else printf("%d\n",query(a-1,b-1,1,0,s-1));
    }
    return 0;
}
