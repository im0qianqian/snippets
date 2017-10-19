# E. National Property

## **Description**

> You all know that the Library of Bookland is the largest library in the world. There are dozens of thousands of books in the library.
>
> Some long and uninteresting story was removed...
>
> The alphabet of Bookland is so large that its letters are denoted by positive integers. Each letter can be small or large, the large version of a letter x is denoted by x'. BSCII encoding, which is used everywhere in Bookland, is made in that way so that large letters are presented in the order of the numbers they are denoted by, and small letters are presented in the order of the numbers they are denoted by, but all large letters are before all small letters. For example, the following conditions hold: 2 < 3, 2' < 3', 3' < 2.
>
> A word x1, x2, ..., xa is not lexicographically greater than y1, y2, ..., yb if one of the two following conditions holds: a ≤ b and x1 = y1, ..., xa = ya, i.e. the first word is the prefix of the second word;there is a position 1 ≤ j ≤ min(a, b), such that x1 = y1, ..., xj - 1 = yj - 1 and xj < yj, i.e. at the first position where the words differ the first word has a smaller letter than the second word has.
>
> For example, the word "3' 7 5" is before the word "2 4' 6" in lexicographical order. It is said that sequence of words is in lexicographical order if each word is not lexicographically greater than the next word in the sequence.
>
> Denis has a sequence of words consisting of small letters only. He wants to change some letters to large (let's call this process a capitalization) in such a way that the sequence of words is in lexicographical order. However, he soon realized that for some reason he can't change a single letter in a single word. He only can choose a letter and change all of its occurrences in all words to large letters. He can perform this operation any number of times with arbitrary letters of Bookland's alphabet.
>
> Help Denis to choose which letters he needs to capitalize (make large) in order to make the sequence of words lexicographically ordered, or determine that it is impossible.
>
> Note that some words can be equal.



## **Input**

> The first line contains two integers n and m (2 ≤ n ≤ 100 000, 1 ≤ m ≤ 100 000) — the number of words and the number of letters in Bookland's alphabet, respectively. The letters of Bookland's alphabet are denoted by integers from 1 to m.
>
> Each of the next n lines contains a description of one word in format li, si, 1, si, 2, ..., si, li (1 ≤ li ≤ 100 000, 1 ≤ si, j ≤ m), where li is the length of the word, and si, j is the sequence of letters in the word. The words are given in the order Denis has them in the sequence.
>
> It is guaranteed that the total length of all words is not greater than 100 000.



## **Output**

> In the first line print "Yes" (without quotes), if it is possible to capitalize some set of letters in such a way that the sequence of words becomes lexicographically ordered. Otherwise, print "No" (without quotes).
>
> If the required is possible, in the second line print k — the number of letters Denis has to capitalize (make large), and in the third line print k distinct integers — these letters. Note that you don't need to minimize the value k.
>
> You can print the letters in any order. If there are multiple answers, print any of them.



## **Examples input**

    4 3
    1 2
    1 1
    3 1 3 2
    2 1 1



## **Examples output**

    Yes
    2
    2 3 



## **题意**

现在我们想要让所有行的字典序升序排列，且对于每一种数字，我们可以采用一种变换，比如 `x->x'` ，所有加 `'` 的都比不加小，问是否可以找到一种变换使得原序列升序。



## **思路**

只要相邻两行满足升序则原序列升序。

于是我们考虑相邻的两行 $a,b$ ，找到第一个 $a_i!=b_i$ ，则这两个序列之间的大小由这两个字母来决定，

既然要升序，假如 $a_i<b_i$ ，则此时已经满足升序的条件，选择 $a_i$ 则必须选择 $b_i$ ，选择 $b_i'$ 则必须选择 $a_i'$ ，连边 $a_i->b_i,b_i'->a_i'$ 。

假如 $a_i>b_i$ ，要使原序列升序则必须选择 $a_i',b_i$ ，连边 $a_i->a_i',b_i'->b_i$ 。

然后套用 2-SAT 模板即可。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);
#define inf 0x7f7f7f7f
using namespace std;
typedef __int64 LL;
const int maxn = 2e5+10;
const int maxm = 4e5+10;

class TwoSAT
{
public:
    struct node
    {
        int to;
        int next;
    } edge[maxm];

    int head[maxn],tot;
    int low[maxn],dfn[maxn],Stack[maxn],Belong[maxn],num[maxn],topo[maxn];
    int index,top,sum;
    int scc,n;
    bool instack[maxn];

    void init(int n)
    {
        memset(head,-1,sizeof(head));
        memset(dfn,0,sizeof(dfn));
        memset(instack,false,sizeof(instack));
        memset(num,0,sizeof(num));
        index = scc = top = tot = sum = 0;
        this->n = n;
    }

    void addedge(int u,int v)
    {
        edge[tot].to=v;
        edge[tot].next= head[u];
        head[u]=tot++;
    }

    void tarjan(int u)
    {
        int v;
        low[u] = dfn[u] = ++index;
        Stack[top++] = u;
        instack[u] = true;
        for(int i=head[u]; i!=-1; i=edge[i].next)
        {
            v = edge[i].to;
            if(!dfn[v])
            {
                tarjan(v);
                if(low[u]>low[v])
                    low[u] = low[v];
            }
            else if(instack[v]&&low[u]>dfn[v])
                low[u]=dfn[v];
        }
        if(low[u] == dfn[u])
        {
            scc++;
            do
            {
                v = Stack[--top];
                instack[v] = false;
                Belong[v] = scc;
                num[scc]++;
                topo[v] = ++sum;
            }
            while(u!=v);
        }
    }

    bool solve()
    {
        for(int i=0; i<n; i++)
            if(!dfn[i])
                tarjan(i);
        for(int i=0; i<n; i+=2)
            if(Belong[i] == Belong[i^1])
                return false;
        return true;
    }
} sat;

vector<int> cnt[maxn];
int n,m;

void solve()
{
    sat.init(2*m);
    bool result = true;
    for(int i=0; i<n-1; i++)
    {
        bool flag = false;
        int len = min(cnt[i].size(),cnt[i+1].size());
        for(int j=0; j<len; j++)
        {
            int u = cnt[i][j];
            int v = cnt[i+1][j];
            if(u!=v)
            {
                --u,--v;
                if(u<v)
                {
                    sat.addedge(u<<1|1,v<<1|1);
                    sat.addedge(v<<1,u<<1);
                }
                else
                {
                    sat.addedge(u<<1|1,u<<1);
                    sat.addedge(v<<1,v<<1|1);
                }
                flag = true;
                break;
            }
        }
        if(!flag&&cnt[i+1].size()<cnt[i].size())
        {
            result = false;
            break;
        }
    }
    if(!result || !sat.solve())
        cout<<"No"<<endl;
    else
    {
        cout<<"Yes"<<endl;
        vector<int> ans;
        for(int i=0; i<m<<1; i+=2)
            if(sat.topo[i] < sat.topo[i^1])
                ans.push_back((i>>1)+1);
        cout<<ans.size()<<endl;
        for(auto s:ans)
            cout<<s<<" ";
    }
}

int main()
{
    IO;
    cin>>n>>m;
    for(int i=0; i<n; i++)
    {
        int len;
        cin>>len;
        for(int j=0; j<len; j++)
        {
            int x;
            cin>>x;
            cnt[i].push_back(x);
        }
    }
    solve();
    return 0;
}
```

