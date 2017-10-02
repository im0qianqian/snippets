/*
51nod 1091 线段的重叠
*/

#include<stdio.h>
#include<string.h>
#include<iostream>
#include<algorithm>
using namespace std;
struct po
{
    int start;
    int end;
} a[50005];
bool cmp(po a,po b)
{
    if(a.start==b.start)return a.end>b.end;
    return a.start<b.start;
}
int main()
{
    int n;
    cin>>n;
    for(int i=0; i<n; i++)
        cin>>a[i].start>>a[i].end;
    sort(a,a+n,cmp);
    int res=0;
    po s=a[0];
    for(int i=1; i<n; i++)
    {
        if(a[i].end<=s.end) //线段i在线段i-1内
            res=max(res,a[i].end-a[i].start);
        else if(a[i].start<=s.end&&a[i].end>s.end)
        {
            res=max(res,s.end-a[i].start);
            s=a[i];//选择最靠后的线段
        }
    }
    cout<<res<<endl;
}