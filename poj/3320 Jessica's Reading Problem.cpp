/*
POJ 3320 Jessica's Reading Problem
*/

#include <stdio.h>
#include<iostream>
#include<algorithm>
#include<string.h>
#include<set>
#include<map>
#define INF 0xfffffff
using namespace std;
int a[1100000];
int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        set<int>cou;
        map<int,int>k;
        k.clear();
        cou.clear();
        for(int i=0; i<n; i++)
        {
            scanf("%d",a+i);
            cou.insert(a[i]);
        }
        int N=cou.size();
        int i=0,j=0,minn=INF,count=0;
        while(true)
        {
            while(i<n&&count<N)
                if(k[a[i++]]++==0)
                    ++count;
            if(count<N)break;
            minn=min(minn,i-j);
            if(--k[a[j++]]==0)
                --count;
        }
        printf("%d\n",minn);
    }
    return 0;
}
