/*
HDU 1304 A Contesting Decision
*/

#include<iostream>
#include<string.h>
#include<algorithm>
#include<stdio.h>
using namespace std;
struct po
{
    string name;
    int count;
    int time;
    void init()
    {
        count=0;
        time=0;
    }
} a[10005];
bool cmp(po a,po b)
{
    if(a.count!=b.count)return a.count>b.count;
    else return a.time<b.time;
}
int main()
{
    int t;
    scanf("%d",&t);
    for(int i=0; i<t; i++)
    {
        cin>>a[i].name;
        int x,y;
        a[i].init();
        for(int j=0; j<4; j++)
        {
            scanf("%d%d",&x,&y);
            if(y!=0)
            {
                a[i].count++;
                a[i].time+=y+(x-1)*20;
            }
        }
    }
    sort(a,a+t,cmp);
    cout<<a[0].name<<" "<<a[0].count<<" "<<a[0].time<<endl;
    return 0;
}
