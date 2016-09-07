/*
POJ 1007 DNA Sorting
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include<string.h>
#include<math.h>
using namespace std;
struct DNA
{
    char c[55];
    int data;
} d[105];
int nixu(char *c)
{
    int k=0;
    int n=strlen(c);
    for(int i=0; i<n; i++)
        for(int j=i+1; j<n; j++)
            if(c[i]>c[j])k++;
    return k;
}
bool cmp(DNA a,DNA b)   //重写比较函数
{
    return a.data<b.data;
}
int main()
{
    int n,m;
    while(cin>>n>>m)
    {
        getchar();
        for(int i=0; i<m; i++)
        {
            scanf("%s",d[i].c);
            d[i].data=nixu(d[i].c);
        }
        sort(d,d+m,cmp);
        for(int i=0; i<m; i++)
            puts(d[i].c);
    }
    return 0;
}
