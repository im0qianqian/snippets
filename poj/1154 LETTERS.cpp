/*
POJ 1154 LETTERS

题意：从字符矩阵的左上角出发，可以向上下左右四个方向走，但是路线中不能有两个相同的字母，问这条路径最多有多长

简单DFS
*/

#include <iostream>
#include<cstdio>
using namespace std;
#include<algorithm>
#include<string.h>
#define maxn 40
int m,n,deep;
bool is[26],ism[maxn][maxn];
char str[maxn][maxn];
int mo[4][2]= {{0,-1},{0,1},{-1,0},{1,0}};
bool jud(int x,int y)
{
    if(x>=0&&x<m&&y>=0&&y<n&&!is[(int)str[x][y]-'A']&&!ism[x][y])return true;
    return false;
}
void DFS(int x,int y,int de)
{
    if(!jud(x,y))return;
    if(de>deep)deep=de;
    for(int i=0; i<4; i++)
    {
        is[str[x][y]-'A']=ism[x][y]=true;
        DFS(x+mo[i][0],y+mo[i][1],de+1);
        is[str[x][y]-'A']=ism[x][y]=false;
    }
}
int main()
{
    while(~scanf("%d%d%*c",&m,&n))
    {
        deep=0;
        for(int i=0; i<m; i++)
            gets(str[i]);
        DFS(0,0,1);
        printf("%d\n",deep);
    }
    return 0;
}
