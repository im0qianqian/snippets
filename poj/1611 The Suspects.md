# The Suspects

## **Description**

> Severe acute respiratory syndrome (SARS), an atypical pneumonia of unknown aetiology, was recognized as a global threat in mid-March 2003. To minimize transmission to others, the best strategy is to separate the suspects from others. 
>
> In the Not-Spreading-Your-Sickness University (NSYSU), there are many student groups. Students in the same group intercommunicate with each other frequently, and a student may join several groups. To prevent the possible transmissions of SARS, the NSYSU collects the member lists of all student groups, and makes the following rule in their standard operation procedure (SOP). 
>
> Once a member in a group is a suspect, all members in the group are suspects. 
>
> However, they find that it is not easy to identify all the suspects when a student is recognized as a suspect. Your job is to write a program which finds all the suspects.



## **Input**

> The input file contains several cases. Each test case begins with two integers n and m in a line, where n is the number of students, and m is the number of groups. You may assume that 0 < n <= 30000 and 0 <= m <= 500. Every student is numbered by a unique integer between 0 and n−1, and initially student 0 is recognized as a suspect in all the cases. This line is followed by m member lists of the groups, one line per group. Each line begins with an integer k by itself representing the number of members in the group. Following the number of members, there are k integers representing the students in this group. All the integers in a line are separated by at least one space. 
>
> A case with n = 0 and m = 0 indicates the end of the input, and need not be processed.



## **Output**

> For each case, output the number of suspects in one line.



## **Sample Input**

    100 4
    2 1 2
    5 10 13 11 12 14
    2 0 1
    2 99 2
    200 2
    1 5
    5 1 2 3 4 5
    1 0
    0 0



## **Sample Output**

    4
    1
    1


## **题意**

有很多组，同一个组中的学生会经常接触，现在学生0感染了SARS，如果他和其他学生是一组的，那么认为这个组的所有人都受到了感染，问至少有多少人感染了SARS。



## **思路**

并查集，同一个组内的所有学生合并到同一个集合中，最后检测0所在的集合，看有多少人和他属于同一个集合即可。



## **AC 代码**

```cpp
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<map>
#include<set>
#include<algorithm>
using namespace std;

const int MAXN = 31000; /*结点数目上线*/
int pa[MAXN];    /*p[x]表示x的父节点*/
int rank[MAXN];    /*rank[x]是x的高度的一个上界*/

void make_set(int x)
{
    /*创建一个单元集*/
    pa[x] = x;
    rank[x] = 0;
}

int find_set(int x)
{
    /*带路径压缩的查找*/
    if(x != pa[x])
        pa[x] = find_set(pa[x]);
    return pa[x];
}

/*按秩合并x，y所在的集合*/
void union_set(int x, int y)
{
    x = find_set(x);
    y = find_set(y);
    if(rank[x] > rank[y])/*让rank比较高的作为父结点*/
        pa[y] = x;
    else
    {
        pa[x] = y;
        if(rank[x] == rank[y])
            rank[y]++;
    }
}

int main()
{
    int n,m;
    while(~scanf("%d%d",&n,&m)&&(n||m))
    {
        for(int i=0; i<n; i++)  //初始化每一个学生单独属于一个集合
            make_set(i);
        for(int i=0; i<m; i++)
        {
            int cou,one,tw;
            scanf("%d",&cou);
            for(int j=0; j<cou; j++)
            {
                scanf("%d",&tw);
                if(j==0)one=tw;
                else union_set(one,tw); //和组的第一个成员合并
            }
        }
        int pa0=find_set(0),ans=1;  //查找0所在的集合
        for(int i=1; i<n; i++)
            if(pa0==find_set(i))
                ans++;
        printf("%d\n",ans);
    }
    return 0;
}
```

