/*
POJ 2769 Reduced ID Numbers

题意：找出一个最小的数m，使得所有数模m都不相同。

没想过这道题目直接暴力就会通过，用一个数组记录模m的值是否存在，如果第二次模出现该数，说明当前的m不合理，m++。
*/
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<iostream>
using namespace std;

int g[1100000];
bool vis[1100000];
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        scanf("%d",&n);
        for(int i=0; i<n; i++)
            scanf("%d",g+i);
        for(int i=n; i<1100000; i++)    //小于最大限度
        {
            bool flag=true;
            memset(vis,0,sizeof(int)*i);
            for(int j=0; j<n; j++)
            {
                int no=g[j]%i;
                if(!vis[no])vis[no]=true;   //如果第一次求得当前模
                else        //否则说明此时的模数不合理
                {
                    flag=false;
                    break;
                }
            }
            if(flag)    //所有数模i都不相同
            {
                printf("%d\n",i);
                break;
            }
        }
    }
    return 0;
}
