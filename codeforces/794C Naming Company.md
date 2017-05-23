# C. Naming Company

## **Description**

> Oleg the client and Igor the analyst are good friends. However, sometimes they argue over little things. Recently, they started a new company, but they are having trouble finding a name for the company.
>
> To settle this problem, they've decided to play a game. The company name will consist of n letters. Oleg and Igor each have a set of n letters (which might contain multiple copies of the same letter, the sets can be different). Initially, the company name is denoted by n question marks. Oleg and Igor takes turns to play the game, Oleg moves first. In each turn, a player can choose one of the letters c in his set and replace any of the question marks with c. Then, a copy of the letter c is removed from his set. The game ends when all the question marks has been replaced by some letter.
>
> For example, suppose Oleg has the set of letters {i, o, i} and Igor has the set of letters {i, m, o}. One possible game is as follows :
>
> Initially, the company name is ???.
>
> Oleg replaces the second question mark with 'i'. The company name becomes ?i?. The set of letters Oleg have now is {i, o}.
>
> Igor replaces the third question mark with 'o'. The company name becomes ?io. The set of letters Igor have now is {i, m}.
>
> Finally, Oleg replaces the first question mark with 'o'. The company name becomes oio. The set of letters Oleg have now is {i}.
>
> In the end, the company name is oio.
>
> Oleg wants the company name to be as lexicographically small as possible while Igor wants the company name to be as lexicographically large as possible. What will be the company name if Oleg and Igor always play optimally?
>
> A string s = s1s2...sm is called lexicographically smaller than a string t = t1t2...tm (where s ≠ t) if si < ti where i is the smallest index such that si ≠ ti. (so sj = tj for all j < i)



## **Input**

> The first line of input contains a string s of length n (1 ≤ n ≤ 3·105). All characters of the string are lowercase English letters. This string denotes the set of letters Oleg has initially.
>
> The second line of input contains a string t of length n. All characters of the string are lowercase English letters. This string denotes the set of letters Igor has initially.



## **Output**

> The output should contain a string of n lowercase English letters, denoting the company name if Oleg and Igor plays optimally.



## **input**

    tinkoff
    zscoder



## **output**

    fzfsirk



## **题意**

`Oleg` 与 `Igor` 在玩一个游戏，他们两人每人手中都有一个字符集，需要轮流使用字符集中的字符来组成一个新的字符串， `Oleg` 总是希望该串的字典序最小，而 `Igor` 总想让它的字典序最大，假设两人足够聪明，求最终组成的字符串。



## **思路**

**有两种情况**

1. 假设 `Oleg` 手中拥有 `1 2 3 4` ， `Igor` 手中拥有 `5 6 7 8` ，此时不论游戏进行到哪种状态， `Oleg` 手中所有的棋子总是小于 `Igor` ，而他想要字典序尽可能小，则总会取最小的一个放置在新串中尽可能前的位置，同时， `Igor` 也总会取最大的一个放置在尽可能前的位置，最终得到的结果为 `1 8 2 7` 。
2. 假设游戏进行到某种状态， `Oleg` 手中拥有 `5 6 7 8` ， `Igor` 手中拥有 `1 2 3 4` ，因为 `Igor` 手中的字符小于 `Oleg` ，此时 `Oleg` 把自己的棋子放置在最前面显然是不理智的，所以他会选择把大一点的可能用到的棋子向后放，因为这样才能利用 `Igor` 得到更小的字典序，同样的， `Igor` 也是这么想的，他会把较小的可能用到的棋子尽可能向后放，最终得到的结果为 `4 5 3 6` 。

注意处理游戏过程中后手有可能首先进入第二种情况的情况。

**如：**

`Oleg`: `reddit`

`Igor`: `abcdef`

答案： `dfdeed`



## **AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;

char s1[310000];
char s2[310000];
char ans[310000];

bool cmp(char a,char b)
{
    return a>b;
}

int main()
{
    scanf("%s%s",s1,s2);
    int len=strlen(s1);
    sort(s1,s1+len);
    sort(s2,s2+len,cmp);
    int cnt=0,t1=0,t2=0,flag=1;
    while(true)
    {
        if(s2[t2]<=s1[t1])
        {
            int l=len-cnt;
            int o1=(l+flag)/2;
            int o2=l-o1;
            for(int i=len-1; i>=cnt; i--)
            {
                if(flag)ans[i]=s1[t1+--o1];
                else ans[i]=s2[t2+--o2];
                flag^=1;
            }
            break;
        }
        else
        {
            ans[cnt++]=s1[t1++];
            if(s1[t1]<s2[t2])
                ans[cnt++]=s2[t2++];
            else flag=0;
        }
        if(cnt>=len)break;
    }
    ans[len]=0;
    puts(ans);
    return 0;
}
```

