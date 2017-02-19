# Sorting It All Out

## **Description**

> An ascending sorted sequence of distinct values is one in which some form of a less-than operator is used to order the elements from smallest to largest. For example, the sorted sequence A, B, C, D implies that A < B, B < C and C < D. in this problem, we will give you a set of relations of the form A < B and ask you to determine whether a sorted order has been specified or not.



## **Input**

> Input consists of multiple problem instances. Each instance starts with a line containing two positive integers n and m. the first value indicated the number of objects to sort, where 2 <= n <= 26. The objects to be sorted will be the first n characters of the uppercase alphabet. The second value m indicates the number of relations of the form A < B which will be given in this problem instance. Next will be m lines, each containing one such relation consisting of three characters: an uppercase letter, the character "<" and a second uppercase letter. No letter will be outside the range of the first n letters of the alphabet. Values of n = m = 0 indicate end of input.



## **Output**

> For each problem instance, output consists of one line. This line should be one of the following three: 
>
> Sorted sequence determined after xxx relations: yyy...y. 
>
> Sorted sequence cannot be determined. 
>
> Inconsistency found after xxx relations. 
>
> where xxx is the number of relations processed at the time either a sorted sequence is determined or an inconsistency is found, whichever comes first, and yyy...y is the sorted, ascending sequence. 



## **Sample Input**

    4 6
    A<B
    A<C
    B<C
    C<D
    B<D
    A<B
    3 2
    A<B
    B<A
    26 1
    A<Z
    0 0



## **Sample Output**

    Sorted sequence determined after 4 relations: ABCD.
    Inconsistency found after 2 relations.
    Sorted sequence cannot be determined.


## **题意**

依序给出一些字母之间的大小关系，判断并输出它能否唯一确定一个序列满足这一关系。



## **思路**

依旧是一道拓扑排序的题目。

无法唯一确定一个序列当且仅当在所有关系输入完毕之后，进行拓扑排序的时候存在一个以上入度为0的点。

序列不存在会在图中存在环的情况下出现。

于是，每输入一组关系，进行一次拓扑排序，对此次拓扑排序的结果判断并做出相应的选择。



## **AC 代码**

```cpp
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<vector>
#include<queue>
#include<set>
using namespace std;
#define M 30
vector<int>G[M];

int in[M],n,m;
char ans[M];

int solve()
{
    int res=1,h[M],top=0;
    memcpy(h,in,sizeof(h));     //copy 入度数组
    queue<int>sk;
    for(int i=0; i<n; i++)      //入度为0的点压入队列
        if(h[i]==0)
            sk.push(i);
    while(!sk.empty())
    {
        int p=sk.front();
        sk.pop();
        ans[top++]=p+'A';
        if(sk.size()>0)         //如果入度为0的点同时存在一个以上，说明无法唯一确定序列
            res=0;
        for(int i=0; i<(int)G[p].size(); i++)   //消除当前点，临界点入度-1
        {
            int j=G[p][i];
            if(--h[j]==0)
                sk.push(j);
        }
    }
    if(top<n)res=-1;            //图中存在环
    ans[top]=0;
    return res;
}
int main()
{
    while(~scanf("%d%d%*c",&n,&m)&&(n||m))
    {
        char a,b;
        int flag=0;
        memset(in,0,sizeof(in));
        for(int i=0; i<M; i++)
            G[i].clear();
        for(int i=0; i<m; i++)
        {
            scanf("%c%*c%c%*c",&a,&b);
            if(flag)continue;
            a-='A';
            b-='A';
            G[(int)a].push_back((int)b);
            ++in[(int)b];       //入度
            flag=solve();       //拓扑排序
            if(flag==1)
                printf("Sorted sequence determined after %d relations: %s.\n",i+1,ans);
            if(flag==-1)
                printf("Inconsistency found after %d relations.\n",i+1);
        }
        if(!flag)
            printf("Sorted sequence cannot be determined.\n");
    }
    return 0;
}
```

