/*
hihocoder 1032 最长回文子串

算法：Manacher
*/

#include<stdio.h>
#include<math.h>
#include<string.h>
#include<iostream>
using namespace std;
#define MAXX 1100000
int N;
char c[MAXX];
char s[MAXX<<1];
int p[MAXX<<1];
void solve()
{
    //字符串中间插入'#'
    memset(p,0,sizeof(p));
    memset(s,0,sizeof(s));
    s[0]='$';
    s[1]='#';
    int len=strlen(c);
    for(int i=0,j=2; i<len; i++)
    {
        s[j++]=c[i];
        s[j++]='#';
    }
    //---start----
    int id=1,mx=1,max1=1;
    p[0]=1,p[1]=1;
    for(int i=2; s[i]!='\0'; i++)
    {
        if(i>mx)p[i]=1; //如果当前位置超过前一个最长回文喘所在区间 置1
        else p[i]=min(p[2*id-i],mx-i);  //否则与对称串比较
        while(s[p[i]+i]==s[i-p[i]]) //从当前位置向两边扩展到最大回文
            p[i]++;
        if(p[i]+i>mx)   //若新的端点大于mx
        {
            id=i;
            mx=p[i]+i;
        }
        if(p[i]>max1+1) //更新最大值
            max1=p[i]-1;
    }
    //---end----
    printf("%d\n",max1);
}
int main()
{
    scanf("%d%*c",&N);
    while(N--)
    {
        gets(c);
        solve();
    }
    return 0;
}
