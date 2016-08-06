/*
HDU 1372 Knight Moves
*/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
int x2,y2;
int movee[8][2]= {-2,1, -1,2, 1,2, 2,1, 2,-1, 1,-2, -1,-2, -2,-1};
int mapp[10][10];
char a[5],b[5];
struct po
{
    int x;
    int y;
    int num;
    void init(int a,int b,int n)
    {
        x=a;
        y=b;
        num=n;
    }
} xy;
void bfs(po xa)
{
    queue<po>k;
    k.push(xa);
    while(!k.empty())
    {
        po t=k.front();
        mapp[xa.x][xa.y]=1;
        k.pop();
        if(t.x==x2&&t.y==y2)
        {
            printf("To get from %s to %s takes %d knight moves.\n",a,b,t.num);
            break;
        }
        else
        {
            for(int i=0; i<8; i++)
            {
                po xx;
                xx.init(t.x+movee[i][0],t.y+movee[i][1],t.num+1);
                if(xx.x<=8&&xx.x>0&&xx.y<=8&&xx.y>0&&mapp[xx.x][xx.y]==0)
                    k.push(xx);
            }
        }
    }
}
int main()
{
    while(~scanf("%s %s",a,b))
    {
        xy.init(a[0]-96,a[1]-48,0);
        x2=b[0]-96;
        y2=b[1]-48;
        memset(mapp,0,sizeof(mapp));
        bfs(xy);
    }
    return 0;
}
