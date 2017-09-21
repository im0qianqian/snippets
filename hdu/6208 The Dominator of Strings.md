# The Dominator of Strings

## **Description**

> Here you have a set of strings. A dominator is a string of the set dominating all strings else. The string S is dominated by T if S is a substring of T.



## **Input**

> The input contains several test cases and the first line provides the total number of cases.
>
> For each test case, the first line contains an integer N indicating the size of the set.
>
> Each of the following N lines describes a string of the set in lowercase.
>
> The total length of strings in each case has the limit of 100000.
>
> The limit is 30MB for the input file.



## **Output**

> For each test case, output a dominator if exist, or No if not.



## **Sample Input**

    3
    10
    you
    better
    worse
    richer
    poorer
    sickness
    health
    death
    faithfulness
    youbemyweddedwifebetterworsericherpoorersicknesshealthtilldeathdouspartandpledgeyoumyfaithfulness
    5
    abc
    cde
    abcde
    abcde
    bcde
    3
    aaaaa
    aaaab
    aaaac



## **Sample Output**

    youbemyweddedwifebetterworsericherpoorersicknesshealthtilldeathdouspartandpledgeyoumyfaithfulness
    abcde
    No



## **题意**

给定一些串，问其中是否可以找到一个串满足其他串都是这个串的子串。



## **思路**

显然，去重后我们所要找的这个串一定是所有串中最长的一个，且最长是唯一的。

我们建立最长串的后缀自动机，然后其他串用来匹配即可，若所有都可以匹配成功，则说明当前串即为结果，否则输出 `No` 。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int CHAR = 26;
const int MAXN = 1e5+10;

struct sam_node
{
    sam_node *fa,*next[CHAR];
    int len;
    LL cnt;
    void clear()
    {
        fa = NULL;
        cnt = 0;
        memset(next,0,sizeof(next));
    }
} pool[MAXN<<1],*root,*tail;

sam_node *newnode(int len)
{
    sam_node *cur = tail++;
    cur->clear();
    cur->len=len;
    return cur;
}

void sam_init()
{
    tail = pool;
    root = newnode(0);
}

sam_node *extend(sam_node *last,int x)
{
    sam_node *p=last,*np = newnode(p->len+1);
    while(p&&!p->next[x])
        p->next[x]=np,p=p->fa;
    if(!p)np->fa=root;
    else
    {
        sam_node *q=p->next[x];
        if(q->len==p->len+1)np->fa=q;
        else
        {
            sam_node *nq=newnode(p->len+1);
            memcpy(nq->next,q->next,sizeof(q->next));
            nq->fa = q->fa;
            q->fa = np->fa = nq;
            while(p&&p->next[x]==q)
                p->next[x]=nq,p=p->fa;
        }
    }
    return np;
}

char str[MAXN];

set<string> sk;
int maxlen;

bool start()
{
    for(auto s:sk)
    {
        int len=s.length();
        if(len!=maxlen)
        {
            sam_node *t=root;
            for(int i=0; i<len; i++)
            {
                int w = s[i] - 'a';
                if (t->next[w])
                    t = t->next[w];
                else
                    return false;
            }
        }
    }
    return true;
}

void init()
{
    maxlen=0;
    sk.clear();
}

template <class T>
inline void scan_d(T &ret)
{
    char c;
    ret = 0;
    while ((c = getchar()) < '0' || c > '9');
    while (c >= '0' && c <= '9')
    {
        ret = ret * 10 + (c - '0'), c = getchar();
    }
}

char tt[MAXN];
int main()
{
    int T;
    scan_d(T);
    while(T--)
    {
        init();
        int n;
        scan_d(n);
        for(int i=0; i<n; i++)
        {
            gets(str);
            sk.insert((string)str);
            maxlen = max((int)strlen(str),maxlen);
        }
        int toal = 0;
        for(auto s:sk)
        {
            if((int)s.length()==maxlen)
            {
                toal++;
                if(toal>1)
                {
                    puts("No");
                    break;
                }
                strcpy(tt,s.data());
            }
        }
        if(toal<=1)
        {
            sam_init();
            sam_node *now = root;
            for(int i=0; i<maxlen; i++)
                now = extend(now,tt[i]-'a');
            if(start())
                puts(tt);
            else puts("No");
        }
    }
    return 0;
}
```
