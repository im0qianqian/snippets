/*
UVA 2678 Subsequence
*/

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<vector>
#include<string.h>
#include<map>
using namespace std;
int a[110000];
int main()
{
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        for(int i=0; i<n; i++)
            scanf("%d",a+i);
        int len=n,i=0,j=0;
        long long res=0;
        while(true)
        {
            if(res<m)
            {
                if(j>=n)break;
                res+=a[j++];
            }
            else
            {
                len=min(len,j-i);
                res-=a[i++];
            }
        }
        printf("%d\n",len==n?0:len);
    }
    return 0;
}
