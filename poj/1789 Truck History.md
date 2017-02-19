# Truck History

## **Description**

> Advanced Cargo Movement, Ltd. uses trucks of different types. Some trucks are used for vegetable delivery, other for furniture, or for bricks. The company has its own code describing each type of a truck. The code is simply a string of exactly seven lowercase letters (each letter on each position has a very special meaning but that is unimportant for this task). At the beginning of company's history, just a single truck type was used but later other types were derived from it, then from the new types another types were derived, and so on.
>
> Today, ACM is rich enough to pay historians to study its history. One thing historians tried to find out is so called derivation plan -- i.e. how the truck types were derived. They defined the distance of truck types as the number of positions with different letters in truck type codes. They also assumed that each truck type was derived from exactly one other truck type (except for the first truck type which was not derived from any other type). The quality of a derivation plan was then defined as
>
> $$1/Σ(to,td)d(to,td)$$
>
> where the sum goes over all pairs of types in the derivation plan such that to is the original type and td the type derived from it and d(to,td) is the distance of the types.
>
> Since historians failed, you are to write a program to help them. Given the codes of truck types, your program should find the highest possible quality of a derivation plan.



## **Input**

> The input consists of several test cases. Each test case begins with a line containing the number of truck types, N, 2 <= N <= 2 000. Each of the following N lines of input contains one truck type code (a string of seven lowercase letters). You may assume that the codes uniquely describe the trucks, i.e., no two of these N lines are the same. The input is terminated with zero at the place of number of truck types.



## **Output**

> For each test case, your program should output the text "The highest possible quality is 1/Q.", where 1/Q is the quality of the best derivation plan.



## **Sample Input**

    4
    aaaaaaa
    baaaaaa
    abaaaaa
    aabaaaa
    0



## **Sample Output**

    The highest possible quality is 1/3.


## **题意**

用一个7位的string代表一个编号，两个编号之间的distance代表这两个编号之间不同字母的个数。一个编号只能由另一个编号衍生出来，代价是这两个编号之间相应的distance，现在要找出一个衍生方案，使得所有的编号之间都可以直接或者间接形成转换，并且总代价最小，也就是distance之和最小。



## **思路**

既然所有的编号之间都有一个转换权值，那么把它可以表示成一张完全图。

要求可以直接或者间接形成转换，即需要找一个子图必须连通。

权值最小，即最小生成树。



## **AC 代码**

```cpp
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<map>
#include<algorithm>
using namespace std;

char str[2005][10];
int parent[2005],n,etop;
struct eage     //边的结构体，u、v为两端点，w为边权值
{
    int u, v, w;
    eage() {};
    eage(int u,int v,int w)
    {
        this->u=u;
        this->v=v;
        this->w=w;
    }
} EG[2005*2005];
int jud(int a,int b)
{
    int ans=0;
    for(int i=0; i<7; i++)
        if(str[a][i]!=str[b][i])
            ans++;
    return ans;
}

bool cmp(eage a, eage b)    //排序调用
{
    return a.w < b.w;
}

int Find(int x)     //寻找根节点，判断是否在同一棵树中的依据
{
    if(parent[x] == -1) return x;
    return Find(parent[x]);
}

void Kruskal()      //Kruskal算法，parent能够还原一棵生成树，或者森林
{
    memset(parent, -1, sizeof(parent));
    int cnt = n,ans=0;        //初始时根节点数目为n个
    sort(EG, EG+etop, cmp);    //按权值将边从小到大排序
    for(int i = 0; i < etop; i++)     //按权值从小到大选择边
    {
        if(cnt == 1) break;     //当根节点只有1个时，跳出循环
        int t1 = Find(EG[i].u), t2 = Find(EG[i].v);
        if(t1 != t2)    //若不在同一棵树种则选择该边，
        {
            ans += EG[i].w;
            parent[t1] = t2;
            cnt--;      //每次合并，减少一个根节点
        }
    }
    printf("The highest possible quality is 1/%d.\n",ans);
}

int main()
{
    while(~scanf("%d%*c",&n)&&n)
    {
        etop=0;
        for(int i=0; i<n; i++)
            gets(str[i]);
        for(int i=0; i<n; i++)
            for(int j=i+1; j<n; j++)
            {
                int cnt=jud(i,j);
                EG[etop++]=eage(i,j,cnt);
                EG[etop++]=eage(j,i,cnt);
            }
        Kruskal();
    }
    return 0;
}
```

