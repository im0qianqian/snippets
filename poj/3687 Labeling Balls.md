

# Labeling Balls

## **Description**

> Windy has N balls of distinct weights from 1 unit to N units. Now he tries to label them with 1 to N in such a way that:
>
> No two balls share the same label.
>
> The labeling satisfies several constrains like "The ball labeled with a is lighter than the one labeled with b".
>
> Can you help windy to find a solution?



## **Input**

> The first line of input is the number of test case. The first line of each test case contains two integers, N (1 ≤ N ≤ 200) and M (0 ≤ M ≤ 40,000). The next M line each contain two integers a and b indicating the ball labeled with a must be lighter than the one labeled with b. (1 ≤ a, b ≤ N) There is a blank line before each test case.



## **Output**

> For each test case output on a single line the balls' weights from label 1 to label N. If several solutions exist, you should output the one with the smallest weight for label 1, then with the smallest weight for label 2, then with the smallest weight for label 3 and so on... If no solution exists, output -1 instead.



## **Sample Input**

    5
    4 0
    4 1
    1 1
    4 2
    1 2
    2 1
    4 1
    2 1
    4 1
    3 2



## **Sample Output**

    1 2 3 4
    -1
    -1
    2 1 3 4
    1 3 2 4


## **题意**

标号为 1~n 的 N 个球，满足给定的 M 个编号约束关系，输出最终满足关系的球的标号。



## **思路**

每一个标号都有可能被其他标号所约束，而对于这样的题目我们可以联想到拓扑排序。

但是题目要求使字典序尽可能的小，于是我们可以逆向建图，然后从最大的标号开始判断，因为这样保证了大一点的标号在右边，于是使得字典序也是最小的了。



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
#define M 210
int in[M],arr[M];
vector<int>G[M];

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        for(int i=1; i<=n; i++)
            G[i].clear();
        memset(in,0,sizeof(in));
        for(int i=0; i<m; i++)
        {
            int a,b;
            scanf("%d%d",&a,&b);
            G[b].push_back(a);      //反向建立邻接表
            in[a]++;                //点的入度
        }
        int w;
        for(w=n; w>0; w--)          //从最大点开始
        {
            int i;
            for(i=n; i>0; i--)      //寻找入度为0的点
                if(!in[i])break;
            if(i==0)break;          //没有找到
            arr[i]=w;
            in[i]=-1;               //删除该点
            for(int j=0; j<(int)G[i].size(); j++)
            {
                int v=G[i][j];      //临接点的入度-1
                if(in[v]>0)
                    in[v]--;
            }
        }
        if(w!=0)
            printf("-1\n");
        else
        {
            for(int i=1; i<=n; i++)
                printf(i!=n?"%d ":"%d\n",arr[i]);
        }
    }
    return 0;
}
```

