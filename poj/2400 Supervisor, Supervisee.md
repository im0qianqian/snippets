# Supervisor, Supervisee

## **Description**

> Suppose some supervisors each get to hire a new person for their department. There are N people to be placed in these N departments. Each supervisor interviews all N people, and ranks them according to how much she wants each of them in her department (1 being "really want" and N being "really don't want"). In turn, each of the N candidates ranks each of the supervisors as to how much that person would like to work for that supervisor (again, 1 is "really want to work for him/her" and N is "really don't want to work for him/her"). Given the scores that each supervisor has for each candidate, and the scores each candidate has for each manager, write a computer program to determine the "best match" of candidates to supervisors. The "best match" is determined by finding the distribution that leads to the highest overall (i.e. sum of) satisfaction for all people. The closer a person is to her number one choice, the better. If everyone gets their number one choice, the average difference will be 0.



## **Input**

> The first line of the input will contain a single integer greater than 0 specifying the number of test cases.
>
> The next line will contain a single integer value N, 0 < N < 15, representing the number of supervisors (and the number of employees - there are N supervisors and N employees). The next N lines will be the preferences of each of the N supervisors. Each line will contain N integer entries (1 through N for employees 1 through N), each separated by a space character, that represents the preferences of that supervisor from most preferred to least preferred. More specifically, the first entry on the line will represent that supervisor's first choice, the second entry her second, and so on. The next N lines will be the preferences of the N employees, in the same format as the supervisors.
>
> All lines of data in the input file will end with an empty line.



## **Output**

> For each test case, write the test case number (starting with 1) followed by the best average difference written to six digits of precision to the right of the decimal point. On the next line, show which best match it was (starting with 1). On the next N lines, show each supervisor (starting with 1) followed by the employee with which she was matched (1 per line). NOTE: if there is more than one best match, matches should be listed in ascending permuted order (see sample output).
>
> Separate each data set with an empty line.



## **Sample Input**

    2
    7
    1 2 3 4 5 6 7
    2 1 3 4 5 6 7
    3 1 2 4 5 6 7
    4 1 2 3 5 6 7
    5 1 2 3 4 6 7
    6 1 2 3 4 5 7
    7 1 2 3 4 5 6
    1 2 3 4 5 6 7
    2 1 3 4 5 6 7
    3 1 2 4 5 6 7
    4 1 2 3 5 6 7
    5 1 2 3 4 6 7
    6 1 2 3 4 5 7
    7 1 2 3 4 5 6
    
    2
    1 2
    2 1
    1 2
    1 2



## **Sample Output**

    Data Set 1, Best average difference: 0.000000
    Best Pairing 1
    Supervisor 1 with Employee 1
    Supervisor 2 with Employee 2
    Supervisor 3 with Employee 3
    Supervisor 4 with Employee 4
    Supervisor 5 with Employee 5
    Supervisor 6 with Employee 6
    Supervisor 7 with Employee 7
    
    Data Set 2, Best average difference: 0.250000
    Best Pairing 1
    Supervisor 1 with Employee 1
    Supervisor 2 with Employee 2



## **题意**

有 `n` 个老板和 `n` 个员工，他们对彼此有一个排名，现在要求选出最好的对应关系使他们平均分值最少。



## **思路**

老板和员工可以看作两个不同的集合，然后他们彼此的排名我们可以给其赋一个权值，求二分图的最大权匹配即可。

**最少平均分值：** $\frac{km}{2×n}$ 

根据结果和全排列来寻找老板与员工的匹配，输出~

**注意：** 题目中输入的两个矩阵好像刚好是颠倒的，反过来输入就对了



## **AC 代码**

```cpp
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
#include<iostream>
using namespace std;
#define LL long long
#define INF 0x3f3f3f

const int maxn = 20;
int g[maxn][maxn];
int nx,ny;
int linker[maxn],lx[maxn],ly[maxn];
int slack[maxn];
bool visx[maxn],visy[maxn];
int cost,sum;
bool mark[maxn];

bool DFS(int x)
{
    visx[x]=true;
    for(int y=0; y<ny; y++)
    {
        if(visy[y])continue;
        int tmp=lx[x]+ly[y]-g[x][y];
        if(tmp==0)
        {
            visy[y]=true;
            if(linker[y]==-1||DFS(linker[y]))
            {
                linker[y]=x;
                return true;
            }
        }
        else if(slack[y]>tmp)
            slack[y]=tmp;
    }
    return false;
}

int km()
{
    memset(linker,-1,sizeof(linker));
    memset(ly,0,sizeof(ly));
    for(int i=0; i<nx; i++)
    {
        lx[i]=-INF;
        for(int j=0; j<ny; j++)
            if(g[i][j]>lx[i])
                lx[i]=g[i][j];
    }
    for(int x=0; x<nx; x++)
    {
        for(int i=0; i<ny; i++)
            slack[i]=INF;
        while(true)
        {
            memset(visx,false,sizeof(visx));
            memset(visy,false,sizeof(visy));
            if(DFS(x))break;
            int d=INF;
            for(int i=0; i<ny; i++)
                if(!visy[i]&&d>slack[i])
                    d=slack[i];
            for(int i=0; i<nx; i++)
                if(visx[i])
                    lx[i]-=d;
            for(int i=0; i<ny; i++)
                if(visy[i])ly[i]+=d;
                else slack[i]-=d;
        }
    }
    cost=0;
    for(int i=0; i<ny; i++)
        if(linker[i]!=-1)
            cost+=g[linker[i]][i];
    return -cost;
}

void dfs(int cap,int x)         //全排列搜索找出所有答案
{
    if(x<cost)return;
    if(cap>=nx)
    {
        printf("Best Pairing %d\n",++sum);
        for(int i=0; i<nx; i++)
            printf("Supervisor %d with Employee %d\n",i+1,linker[i]+1);
    }
    else
    {
        for(int i=0; i<nx; i++)
        {
            if(!mark[i])
            {
                mark[i]=true;
                linker[cap]=i;
                dfs(cap+1,x+g[cap][i]);
                mark[i]=false;
            }
        }
    }
}

int main()
{
    int T;
    scanf("%d",&T);
    for(int ti=1; ti<=T; ti++)
    {
        scanf("%d",&nx);
        ny=nx;
        sum=0;
        memset(g,0,sizeof(g));
        memset(mark,false,sizeof(mark));
        for(int i=0; i<nx; i++)
            for(int j=0; j<ny; j++)
            {
                int x;
                scanf("%d",&x);
                g[x-1][i]-=j;
            }
        for(int i=0; i<nx; i++)
            for(int j=0; j<ny; j++)
            {
                int x;
                scanf("%d",&x);
                g[i][x-1]-=j;
            }
        printf("Data Set %d, Best average difference: %.6f\n",ti,0.5*km()/nx);
        dfs(0,0);
        printf("\n");
    }
    return 0;
}
```

