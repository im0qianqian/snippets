/*
51nod 1445 变色DNA
*/

#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<set>
#include<string.h>
#define INF (1<<25)
using namespace std;
int mapp[55][55];
int n;
void floyd()
{
    for(int k=0; k<n; k++)
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                mapp[i][j]=min(mapp[i][j],mapp[i][k]+mapp[k][j]);
    printf("%d\n",mapp[0][n-1]==INF?-1:mapp[0][n-1]);
}
int main()
{
    int T;
    char c;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%*c",&n);
        for(int i=0; i<n; i++)
            fill(mapp[i],mapp[i]+n,INF);
        for(int i=0; i<n; i++)
        {
            int s=0;
            for(int j=0; j<n; j++)
            {
                scanf("%c",&c);
                if(c=='Y')mapp[i][j]=s,s++;
            }
            getchar();
        }
        floyd();
    }
    return 0;
}
