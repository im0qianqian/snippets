# Peaceful Commission

## **Description**

> The Public Peace Commission should be legislated in Parliament of The Democratic Republic of Byteland according to The Very Important Law. Unfortunately one of the obstacles is the fact that some deputies do not get on with some others. 
>
> The Commission has to fulfill the following conditions: 
>
> 1. Each party has exactly one representative in the Commission, 
> 2. If two deputies do not like each other, they cannot both belong to the Commission. 
>
> Each party has exactly two deputies in the Parliament. All of them are numbered from 1 to 2n. Deputies with numbers 2i-1 and 2i belong to the i-th party . 
>
> Task 
>
> Write a program, which: 
>
> 1. reads from the text file SPO.IN the number of parties and the pairs of deputies that are not on friendly terms, 
> 2. decides whether it is possible to establish the Commission, and if so, proposes the list of members, 
> 3. writes the result in the text file SPO.OUT. 



## **Input**

> In the first line of the text file SPO.IN there are two non-negative integers n and m. They denote respectively: the number of parties, 1 <= n <= 8000, and the number of pairs of deputies, who do not like each other, 0 <= m <=2 0000. In each of the following m lines there is written one pair of integers a and b, 1 <= a < b <= 2n, separated by a single space. It means that the deputies a and b do not like each other. 
>
> There are multiple test cases. Process to end of file. 



## **Output**

> The text file SPO.OUT should contain one word NIE (means NO in Polish), if the setting up of the Commission is impossible. In case when setting up of the Commission is possible the file SPO.OUT should contain n integers from the interval from 1 to 2n, written in the ascending order, indicating numbers of deputies who can form the Commission. Each of these numbers should be written in a separate line. If the Commission can be formed in various ways, your program may write mininum number sequence. 



## **Sample Input**

    3 2
    1 3
    2 4



## **Sample Output**

    1
    4
    5



## **题意**

某国有 $n$ 个党派，每个党派恰有两名议员，不过不同党派之间可能有一些议员不和，现在我们想在每个党派中找出一名议员参加会议，求解该问题，若问题无解，输出 `NIE` 。



## **思路**

假设 $x$ 与 $y$ 不和，且他们分别属于不同的两个党派，此时这两个党派中另外两个成员分别为 $x',y'$ 。

在选取中，假如我们在第一个党派中选择 $x$ ，那么第二个党派中必须选择 $y'$ ；同理，选择 $y$ ，必选 $x'$ 。

因此我们可以在图中加入 $x->y',y->x'$ 这两条边，然后利用染色法假设每一个节点是否被选取找出正确结果。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef __int64 LL;

const int maxn = 1e5+10;

class TwoSAT
{
public:
    struct node
    {
        int to;
        int next;
    } edge[maxn];
    int head[maxn],tot,n;
    bool vis[maxn];         // 染色标记 true 表示选择
    int S[maxn],top;        // 栈

    void init(int n)
    {
        memset(head,-1,sizeof(head));
        tot = 0;
        this->n = n;
    }

    void addedge(int u,int v)
    {
        edge[tot].to = v;
        edge[tot].next = head[u];
        head[u] = tot++;
    }

    bool dfs(int x)
    {
        if(vis[x^1])return false;
        if(vis[x])return true;
        vis[x] = true;
        S[top++] = x;
        for(int i=head[x]; i!=-1; i=edge[i].next)
            if(!dfs(edge[i].to))
                return false;
        return true;
    }

    bool solve()
    {
        memset(vis,false,sizeof(vis));
        for(int i=0; i<n; i+=2)
        {
            if(vis[i]||vis[i^1])continue;
            top = 0;
            if(!dfs(i))
            {
                while(top)
                    vis[S[--top]] = false;
                if(!dfs(i^1))return false;
            }
        }
        return true;
    }
} twoSAT;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    while(cin>>n>>m)
    {
        twoSAT.init(2*n);
        for(int i=0; i<m; i++)
        {
            int u,v;
            cin>>u>>v;
            --u,--v;
            cout<<u<<" "<<(v^1)<<" "<<v<<" "<<(u^1)<<endl;
            twoSAT.addedge(u,v^1);
            twoSAT.addedge(v,u^1);
        }
        if(twoSAT.solve())
        {
            for(int i=0; i<2*n; i++)
                if(twoSAT.vis[i])
                    cout<<i+1<<endl;
        }
        else
            cout<<"NIE"<<endl;
    }
    return 0;
}
```

