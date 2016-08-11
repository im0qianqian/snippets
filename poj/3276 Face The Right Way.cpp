/*
POJ 3276 Face The Right Way
*/

#include <stdio.h>
#include<iostream>
#include<algorithm>
#include<string.h>
#define max(a,b) (a>b?a:b)
using namespace std;
int df[5100];       //'F':0 'B':1
int f[5100];        //当前位是否被反转过
int solve(int k,int N)
{
    memset(f,0,sizeof(f));
    int ans=0,sum=0;
    for(int i=0; i+k<=N; i++)
    {
        if((sum+df[i])&1)ans++,f[i]=1;  //需要反转当前位
        sum+=f[i];                      //以后每位被反转的总次数
        if(i-k+1>=0)sum-=f[i-k+1];      //取消第i-k+1的状态
    }
    for(int i=N-k+1; i<N; i++)
    {
        if((sum+df[i])&1)return -1;     //无法完成
        if(i-k+1>=0)sum-=f[i-k+1];
    }
    return ans;
}
int main()
{
    int N;
    char c;
    scanf("%d%*c",&N);
    for(int i=0; i<N; i++)
    {
        scanf("%c%*c",&c);
        if(c=='B')df[i]=1;
    }
    int k=1,count=N;
    for(int i=1; i<=N; i++)
    {
        int cou=solve(i,N);
        if(cou>=0&&cou<count)
        {
            k=i;
            count=cou;
        }
    }
    printf("%d %d\n",k,count);
    return 0;
}
