/*
HDU 2717 Catch That Cow
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
#define LL 1000000
int last;
struct po
{
    int x;
    int num;
};
bool mapp[1005000];
void bfs(int n)
{
    memset(mapp,0,sizeof(mapp));
    queue<po>k;
    k.push({n,0});
    while(!k.empty())
    {
        po t=k.front();
        k.pop();
        mapp[t.x]=1;
        if(t.x==last)
        {
            cout<<t.num<<endl;
            break;
        }
        else
        {
            if(t.x+1<=LL&&mapp[t.x+1]==0)
                k.push({t.x+1,t.num+1});
            if(t.x-1>=0&&mapp[t.x-1]==0)
                k.push({t.x-1,t.num+1});
            if(t.x*2<=LL&&mapp[t.x*2]==0)
                k.push({t.x*2,t.num+1});
        }
    }
}
int main()
{
    int n;
    while(cin>>n>>last)
        bfs(n);
    return 0;
}
