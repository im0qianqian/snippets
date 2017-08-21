# Friend-Graph

## **Description**

> It is well known that small groups are not conducive of the development of a team. Therefore, there shouldn’t be any small groups in a good team.
>
> In a team with n members,if there are three or more members are not friends with each other or there are three or more members who are friends with each other. The team meeting the above conditions can be called a bad team.Otherwise,the team is a good team.
>
> A company is going to make an assessment of each team in this company. We have known the team with n members and all the friend relationship among these n individuals. Please judge whether it is a good team.



## **Input**

> The first line of the input gives the number of test cases T; T test cases follow.（T<=15）
>
> The first line od each case should contain one integers n, representing the number of people of the team.(n≤3000)
>
> Then there are n-1 rows. The ith row should contain n-i numbers, in which number aij represents the relationship between member i and member j+i. 0 means these two individuals are not friends. 1 means these two individuals are friends.



## **Output**

> Please output ”Great Team!” if this team is a good team, otherwise please output “Bad Team!”.



## **Sample Input**

    1
    4
    1 1 0
    0 0
    1



## **Sample Output**

    Great Team!



## **题意**

给出 `n` 个人之间的关系，如果其中有三个人互相认识或者互相不认识，则输出 `Bad Team!` ，否则输出 `Great Team!` 。



## **思路**

显然，当人数大于等于 `6` 时其结果一定是 `Bad Team!` 。（拉姆齐定理，等同于使用两种颜色给 Kn 的边染色，当 `n >= 6` 时图中一定存在同色三角形）

而对于 `n < 6` 的情况，实际上需要求图的最大团点的个数是否大于 `3` ，暴力解出判断即可。



## **AC 代码**

```cpp
#include <iostream>
#include <memory.h>
#include <stdio.h>
using namespace std;

const int maxn=3010;
bool mapp[maxn][maxn];
bool flag,use[maxn];
int n;
int pre[maxn];
void dfs(int x,int fa,int now,int dep)
{
    pre[x]=fa;      // 记录前置节点
    if(dep>=2)
    {
        int no = x;
        flag = true;
        while(pre[no]!=-1)
        {
            flag&=(now==mapp[pre[no]][x]);  // 当前集合是否可以构成完全图
            no = pre[no];
        }
        return;
    }
    use[x]=true;
    for(int i=1; i<=n; i++)
    {
        if(!use[i]&&(now==-1||mapp[x][i]==now))
        {
            dfs(i,x,mapp[x][i],dep+1);
            if(flag)return;
        }
    }
    use[x]=false;
}

int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        memset(mapp,false,sizeof(mapp));
        cin>>n;
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n-i; j++)
            {
                int x;
                cin>>x;
                mapp[i][i+j]=x;
                mapp[i+j][i]=x;
            }
        if(n>=6)
        {
            cout<<"Bad Team!"<<endl;
            continue;
        }
        flag = false;
        for(int i=1; i<=n; i++)
        {
            memset(use,false,sizeof(use));
            dfs(i,-1,-1,0);
            if(flag)break;
        }
        cout<<(flag?"Bad Team!":"Great Team!")<<endl;
    }
    return 0;
}
```

