/*
POJ 3669 Meteor Shower
*/

#include <iostream>
#include<stdio.h>
#include<string.h>
#include<vector>
#include<queue>
using namespace std;
#define MAXX 512

int mapp[MAXX][MAXX];
int mo[5][2]= {{0,-1},{0,1},{-1,0},{1,0},{0,0}};

struct edge
{
    int x,y,t;
    edge(int x,int y,int t) //构造函数
    {
        this->x=x;
        this->y=y;
        this->t=t;
    }
};

void insert(int x,int y,int t)  //更新陨石坠落地点以及周边的时间
{
    for(int i=0; i<5; i++)
    {
        int sx=x+mo[i][0],sy=y+mo[i][1];
        if(sx<0||sy<0)continue;
        if(mapp[sx][sy]==-1)mapp[sx][sy]=t;
        else if(mapp[sx][sy]>t)mapp[sx][sy]=t;
    }
}

int bfs()
{
    if(mapp[0][0]==0)return -1;
    queue<edge>k;
    k.push(edge(0,0,0));
    while(!k.empty())
    {
        edge t=k.front();
        k.pop();
        for(int i=0; i<4; i++)
        {
            int x=t.x+mo[i][0];
            int y=t.y+mo[i][1];
            if(x<0||y<0)continue;
            if(mapp[x][y]==-1)return t.t+1;
            else if(mapp[x][y]>t.t+1)   //如果到达此地点不会被陨石击中
            {
                k.push(edge(x,y,t.t+1));
                mapp[x][y]=0;           //防止重复回到某一点
            }
        }
    }
    return -1;
}

int main()
{
    int t,x,y,T;
    scanf("%d",&T);
    memset(mapp,-1,sizeof(mapp));
    while(T--)
    {
        scanf("%d%d%d",&x,&y,&t);
        insert(x,y,t);
    }
    printf("%d\n",bfs());
    return 0;
}