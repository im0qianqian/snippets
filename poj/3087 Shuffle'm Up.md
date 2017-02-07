# Shuffle'm Up

## **Description**

> A common pastime for poker players at a poker table is to shuffle stacks of chips. Shuffling chips is performed by starting with two stacks of poker chips, S1 and S2, each stack containing C chips. Each stack may contain chips of several different colors.
>
> The actual shuffle operation is performed by interleaving a chip from S1 with a chip from S2 as shown below for C = 5:
>
> ![img](http://poj.org/images/3087_1.png)
>
> The single resultant stack, S12, contains 2 * C chips. The bottommost chip of S12 is the bottommost chip from S2. On top of that chip, is the bottommost chip from S1. The interleaving process continues taking the 2nd chip from the bottom of S2 and placing that on S12, followed by the 2nd chip from the bottom of S1 and so on until the topmost chip from S1 is placed on top of S12.
>
> After the shuffle operation, S12 is split into 2 new stacks by taking the bottommost C chips from S12 to form a new S1 and the topmost C chips from S12 to form a new S2. The shuffle operation may then be repeated to form a new S12.
>
> For this problem, you will write a program to determine if a particular resultant stack S12 can be formed by shuffling two stacks some number of times.



## **Input**

> The first line of input contains a single integer N, (1 ≤ N ≤ 1000) which is the number of datasets that follow.
>
> Each dataset consists of four lines of input. The first line of a dataset specifies an integer C, (1 ≤ C ≤ 100) which is the number of chips in each initial stack (S1 and S2). The second line of each dataset specifies the colors of each of the C chips in stack S1, starting with the bottommost chip. The third line of each dataset specifies the colors of each of the C chips in stack S2 starting with the bottommost chip. Colors are expressed as a single uppercase letter (A through H). There are no blanks or separators between the chip colors. The fourth line of each dataset contains 2 * C uppercase letters (A through H), representing the colors of the desired result of the shuffling of S1 and S2 zero or more times. The bottommost chip’s color is specified first.



## **Output**

> Output for each dataset consists of a single line that displays the dataset number (1 though N), a space, and an integer value which is the minimum number of shuffle operations required to get the desired resultant stack. If the desired result can not be reached using the input for the dataset, display the value negative 1 (−1) for the number of shuffle operations.



## **Sample Input**

    2
    4
    AHAH
    HAHA
    HHAAAAHH
    3
    CDE
    CDE
    EEDDCC



## **Sample Output**

    1 2
    2 -1


## **题意**

已知两堆牌数均为n的纸牌堆a和b的初始状态， 按给定规则能将他们相互交叉组合成一堆牌str，再将str的最底下的n张牌归为a，最顶的n张牌归为b，依此循环下去。

现在输入a和b的初始状态 以及 预想的最终状态c，问a, b经过多少次洗牌之后，最终能达到状态c，若永远不可能相同，则输出”-1”。



## **思路**

STL中的map是一个很好用的数据结构，想学的话可以去看看哦！

照着题目的意思，模拟，若产生一个环，说明永远不可能相同。

否则输出洗牌次数。



## **AC 代码**

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<iostream>
using namespace std;
#include<vector>
#include<queue>
#include<map>

string a,b,c;
int n;
void solve(int ki)
{
    int ans=0;
    bool flag=false;
    map<string,bool>sk;
    while(true)
    {
        string tmp="";
        for(int i=0; i<n; i++)  //重新洗牌
        {
            tmp+=b[i];
            tmp+=a[i];
        }
        a=b="";
        for(int i=0; i<n; i++)  //上下分为两叠
            a+=tmp[i];
        for(int i=n; i<2*n; i++)
            b+=tmp[i];
//        cout<<tmp<<endl;
        ans++;                  //洗牌次数+1
        if(tmp==c)              //找到答案
        {
            flag=true;
            break;
        }
        else if(sk[tmp]==true)break;    //返回到之前的某一步
        sk[tmp]=true;           //标记当前状态
    }
    if(flag)
        printf("%d %d\n",ki,ans);
    else printf("%d -1\n",ki);
}
int main()
{
    int N;
    scanf("%d",&N);
    for(int i=1; i<=N; i++)
    {
        cin>>n>>a>>b>>c;
        solve(i);
    }
    return 0;
}
```

