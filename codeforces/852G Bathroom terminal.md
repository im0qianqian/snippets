# G. Bathroom terminal

## **Description**

> Smith wakes up at the side of a dirty, disused bathroom, his ankle chained to pipes. Next to him is tape-player with a hand-written message "Play Me". He finds a tape in his own back pocket. After putting the tape in the tape-player, he sees a key hanging from a ceiling, chained to some kind of a machine, which is connected to the terminal next to him. After pressing a Play button a rough voice starts playing from the tape:
>
> "Listen up Smith. As you can see, you are in pretty tough situation and in order to escape, you have to solve a puzzle.
>
> You are given N strings which represent words. Each word is of the maximum length L and consists of characters 'a'-'e'. You are also given M strings which represent patterns. Pattern is a string of length  ≤  L and consists of characters 'a'-'e' as well as the maximum 3 characters '?'. Character '?' is an unknown character, meaning it can be equal to any character 'a'-'e', or even an empty character. For each pattern find the number of words that matches with the given pattern. After solving it and typing the result in the terminal, the key will drop from the ceiling and you may escape. Let the game begin."
>
> Help Smith escape.



## **Input**

> The first line of input contains two integers N and M (1 ≤ N ≤  100 000, 1 ≤ M ≤  5000), representing the number of words and patterns respectively.
>
> The next N lines represent each word, and after those N lines, following M lines represent each pattern. Each word and each pattern has a maximum length L (1 ≤ L ≤ 50). Each pattern has no more that three characters '?'. All other characters in words and patters are lowercase English letters from 'a' to 'e'.



## **Output**

> Output contains M lines and each line consists of one integer, representing the number of words that match the corresponding pattern.



## **Example input**

    3 1
    abc
    aec
    ac
    a?c



## **Example output**

    3



## **题意**

有 n 个字符串与 m 个匹配规则，在规则中每一个 `?` 可以代表 a-e 中的任意一个字符，也可以代表一个空字符，问每一个规则可以匹配多少个字符串。



## **思路**

将所有的字符串插入到一棵字典树中，然后，然后...

然后暴搜就可以啦 [小纠结]



## **AC 代码**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000*50;

struct node
{
    node()
    {
        cnt=0;
        memset(next,0,sizeof(next));
    }
    int cnt;
    node *next[5];
}*root;

int ind,now;
int nex[maxn];
int vis[maxn];
char str[105];

void insert(node *&p,char *s)
{
    if(!p)p=new node();
    if(!*s)
    {
        nex[ind]=p->cnt;
        p->cnt=ind;
        return;
    }
    insert(p->next[*s-'a'],s+1);
}

int findd(char *s,node *p)
{
    if(!p)return 0;
    if(*s=='?')
    {
        int res=0;
        for(int i=0; i<5; i++)
            res+=findd(s+1,p->next[i]);
        res+=findd(s+1,p);
        return res;
    }
    if(!*s)
    {
        int res=0;
        for(int i=p->cnt; i!=0; i=nex[i])
            if(vis[i]!=now)
            {
                res++;
                vis[i]=now;
            }
        return res;
    }
    else return findd(s+1,p->next[*s-'a']);
}

int main()
{
    ios::sync_with_stdio(false);
    root=new node();
    int n,m;
    cin>>n>>m;
    for(int i=0; i<n; i++)
    {
        ++ind;
        cin>>str;
        insert(root,str);
    }
    for(int i=0; i<m; i++)
    {
        ++now;
        cin>>str;
        cout<<findd(str,root)<<endl;
    }
    return 0;
}
```

