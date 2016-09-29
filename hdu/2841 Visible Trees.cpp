/*
HDU 2841 Visible Trees

题意：给你一个n*m的点阵，问站在最左下角的点可以看到其他多少个点。

思路：我们发现如果A1/B1=A2/B2，那么就有一棵树看不到了，所以接下来就是找出Ai/Bi有多少种。
再可以发现A/B中，如果A,B有大于1的公约数，则A=A'*D B=B'*D，那么A/B=A'/B',也就是存在另外一组数和这种相等，则问题转换成有多少对互质的数，枚举i，从1-M中找与i互质的数，其中1<=i<=N。
对于不大于n并且与i互质的数，看起来不能用欧拉函数求解的样子，那我们只能换一种思路咯！(求解不大于n并且与i不互质的数的个数，然后n-num便是与i互质的个数)。

素因子表：num[i][0]代表i的素因子个数，num[i][j]代表i的一个素因子。

容斥原理：不大于16并且与6不互质的数的个数 = 16/2 + 16/3 -16/2/3（6有两个素因子2、3）。
*/

#include <iostream>
#include<stdio.h>
using namespace std;
typedef __int64 LL;
int Prim[100005],num[100005][20];
//求素因子
void init()
{
    int i,j;
    for(i=2; i<=100005; i++)
        if(Prim[i]==0)
        {
            num[i][1]=i;
            num[i][0]++;
            for(j=i*2; j<=100000; j+=i)
            {
                num[j][++num[j][0]]=i;  //num[i][0]代表i的素因子个数，num[i][j]代表i的一个素因子。
                Prim[j]=1;
            }
        }
}
LL dfs(int id,int b,int now)//求不大于b的数中,与now不互质的数的个数;
{
    LL ans=0;
    for(int i=id; i<=num[now][0]; i++)  //num[now][0]为now的素因子个数
        ans+=b/num[now][i]-dfs(i+1,b/num[now][i],now);  //+奇数层集合-dfs(...)为偶数层集合 比如 + 16/2 - 16/2/3 + 16/3
    return ans;
}

int main()
{
    int m,n,t;
    init();
    cin>>t;
    while(t--)
    {
        cin>>m>>n;
        LL sum=0;
        for(int i=2; i<=m; i++)
            sum+=n-dfs(1,n,i);
        printf("%I64d\n",sum+n);    //处理第一层
    }
    return 0;
}
