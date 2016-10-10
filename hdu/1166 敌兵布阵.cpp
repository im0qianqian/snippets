/*
HDU 1166 敌兵布阵

思路：建立二叉索引树，add更新，sum求[1,sum]的和，题目中营地人数满足区间减法
*/
#include <iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
#define lowbit(x) (x&-x)
using namespace std;

int a[51000],c[51000],n;
char str[30];

void add(int i,int x)
{
    while(i<=n)
    {
        c[i]+=x;
        i+=lowbit(i);
    }
}

int sum(int x)
{
    int ans=0;
    while(x>0)
    {
        ans+=c[x];
        x-=lowbit(x);
    }
    return ans;
}

int main()
{
    int T;
    scanf("%d",&T);
    for(int si=1; si<=T; si++)
    {
        scanf("%d",&n);
        memset(c,0,sizeof(c));
        for(int i=1; i<=n; i++)
        {
            scanf("%d%*c",a+i);
            add(i,a[i]);
        }
        int start,en;
        printf("Case %d:\n",si);
        while(~scanf("%s",str))
        {
            if(str[0]=='E')break;
            scanf("%d%d%*c",&start,&en);
            if(str[0]=='Q')printf("%d\n",sum(en)-sum(start-1));
            else if(str[0]=='A')
                add(start,en);
            else if(str[0]=='S')
                add(start,-en);
        }
    }
    return 0;
}
