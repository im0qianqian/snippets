# Channel Allocation

## **Description**

> When a radio station is broadcasting over a very large area, repeaters are used to retransmit the signal so that every receiver has a strong signal. However, the channels used by each repeater must be carefully chosen so that nearby repeaters do not interfere with one another. This condition is satisfied if adjacent repeaters use different channels. 
>
> Since the radio frequency spectrum is a precious resource, the number of channels required by a given network of repeaters should be minimised. You have to write a program that reads in a description of a repeater network and determines the minimum number of channels required.



## **Input**

> The input consists of a number of maps of repeater networks. Each map begins with a line containing the number of repeaters. This is between 1 and 26, and the repeaters are referred to by consecutive upper-case letters of the alphabet starting with A. For example, ten repeaters would have the names A,B,C,...,I and J. A network with zero repeaters indicates the end of input. 
>
> Following the number of repeaters is a list of adjacency relationships. Each line has the form: 
>
> A:BCDH 
>
> which indicates that the repeaters B, C, D and H are adjacent to the repeater A. The first line describes those adjacent to repeater A, the second those adjacent to B, and so on for all of the repeaters. If a repeater is not adjacent to any other, its line has the form 
>
> A: 
>
> The repeaters are listed in alphabetical order. 
>
> Note that the adjacency is a symmetric relationship; if A is adjacent to B, then B is necessarily adjacent to A. Also, since the repeaters lie in a plane, the graph formed by connecting adjacent repeaters does not have any line segments that cross. 



## **Output**

> For each map (except the final one with no repeaters), print a line containing the minumum number of channels needed so that no adjacent channels interfere. The sample output shows the format of this line. Take care that channels is in the singular form when only one channel is required.



## **Sample Input**

    2
    A:
    B:
    4
    A:BC
    B:ACD
    C:ABD
    D:BC
    4
    A:BCD
    B:ACD
    C:ABD
    D:ABC
    0



## **Sample Output**

    1 channel needed.
    3 channels needed.
    4 channels needed. 


## **题意**

给出一张图，问至少需要几种颜色才能给这张图染色，其中相邻点不能有相同的颜色。



## **思路**

根据四色定理得出，答案最大是4。

首先对一点着色，然后把它相邻的点置为其他颜色（保证他们之间相邻的也是不同颜色）。

同理，对于其他没有进行染色的点也执行该种操作，在染色的过程中要保证颜色数尽可能少，具体看代码。



## **AC 代码**

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;
#include<vector>
vector<int>G[26];
int n,color[26];    //每个点的颜色
void solve()
{
    memset(color,0,sizeof(color));  //初始化无染色
    int ans=1;
    for(int ni=0; ni<n; ni++)       //枚举每一个点
    {
        if(color[ni]==0)            //如果当前点没有染色
        {
            bool isc[5]= {false};   //根据四色原理，最大有四种颜色
            for(int i=0; i<(int)G[ni].size(); i++)  //枚举临接的点并标记它的颜色
                isc[color[G[ni][i]]]=true;
            for(int i=1; i<=4; i++) //找出一个与相邻点不同的颜色
                if(isc[i]==false)
                {
                    color[ni]=i;        //着色
                    ans=max(ans,i);     //当前所使用的最大颜色种数
                    break;
                }
        }
    }
    printf(ans==1?"%d channel needed.\n":"%d channels needed.\n",ans);
}

int main()
{
    char c[105];
    while(~scanf("%d%*c",&n)&&n)
    {
        for(int ni=0; ni<n; ni++)
        {
            gets(c);
            G[ni].clear();  //一开始没加这个，WA过
            for(int i=2; i<(int)strlen(c); i++)
                G[ni].push_back(c[i]-'A');
        }
        solve();
    }
    return 0;
}
```

