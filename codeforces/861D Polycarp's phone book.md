# D. Polycarp's phone book

## **Description**

> There are n phone numbers in Polycarp's contacts on his phone. Each number is a 9-digit integer, starting with a digit different from 0. All the numbers are distinct.
>
> There is the latest version of Berdroid OS installed on Polycarp's phone. If some number is entered, is shows up all the numbers in the contacts for which there is a substring equal to the entered sequence of digits. For example, is there are three phone numbers in Polycarp's contacts: 123456789, 100000000 and 100123456, then:
>
> if he enters 00 two numbers will show up: 100000000 and 100123456,
>
> if he enters 123 two numbers will show up 123456789 and 100123456,
>
> if he enters 01 there will be only one number 100123456.
>
> For each of the phone numbers in Polycarp's contacts, find the minimum in length sequence of digits such that if Polycarp enters this sequence, Berdroid shows this only phone number.



## **Input**

> The first line contains single integer n (1 ≤ n ≤ 70000) — the total number of phone contacts in Polycarp's contacts.
>
> The phone numbers follow, one in each line. Each number is a positive 9-digit integer starting with a digit from 1 to 9. All the numbers are distinct.



## **Output**

> Print exactly n lines: the i-th of them should contain the shortest non-empty sequence of digits, such that if Polycarp enters it, the Berdroid OS shows up only the i-th number from the contacts. If there are several such sequences, print any of them.



## **Examples input**

    3
    123456789
    100000000
    100123456



## **Examples output**

    9
    000
    01



## **题意**

有 $n$ 个 9 位的手机号码，现在我们想用最短的子串来表示每一个号码，求解该问题。



## **思路**

既然每一个手机号码只有 9 位，那我们可以建立字典树存储其所有的后缀，

树中每一个节点记录访问过该节点串的标号集合，

然后通过一次 $bfs$ 找出标号集合大小为 $1$ 的部分，此时的这条路径即为集合中唯一的那个元素所代表的串的最小表示。

---

考虑逐一插入串的所有后缀复杂度为 $O(n^2)$ ，其中 $n=9$ ，最大有 $70000$ 次输入，因此总大小为 $70000 \times 9^2$ 。

另外一种类似的做法可以将字典树换为后缀自动机，每次插入时间复杂度为 $O(n)$ ，总大小为 $70000 \times 9$ 。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef __int64 LL;
const int maxn = 1e6+10;

int tot;

struct node
{
    int next[20];
    set<int> cnt;
    node()
    {
        memset(next,0,sizeof(next));
    }
} trie[maxn];

void init()
{
    memset(trie,0,sizeof(trie));
    trie[0].cnt = set<int>();
    tot=0;
}

char str[20];
void insert_str(char *s,int dep)
{
    int len = strlen(s);
    int tmp = 0;
    trie[tmp].cnt.insert(dep);
    for(int i=0; i<len; i++)
    {
        if(!trie[tmp].next[s[i]-'0'])
        {
            trie[tmp].next[s[i]-'0']=++tot;
            trie[trie[tmp].next[s[i]-'0']].cnt = set<int>();
        }
        tmp=trie[tmp].next[s[i]-'0'];
        trie[tmp].cnt.insert(dep);
    }
}

typedef pair<int,string> P;
map<int,string> ans;

void bfs()
{
    queue<P> sk;
    sk.push(P(0,""));
    while(!sk.empty())
    {
        P p = sk.front();
        sk.pop();
        int id = p.first;
        string path = p.second;
        if(id!=0&&trie[id].cnt.size()<=1)
        {
            if(trie[id].cnt.size()==1)
            {
                int sl = *trie[id].cnt.begin();
                if(ans[sl]==""||ans[sl].length()>path.length())
                    ans[sl] = path;
            }
        }
        for(int i=0; i<10; i++)
            if(trie[id].next[i])
                sk.push(P(trie[id].next[i],path + char('0'+i)));
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    init();
    int n;
    cin>>n;
    for(int i=0; i<n; i++)
    {
        cin>>str;
        int len = strlen(str);
        for(int j=0; j<len; j++)
            insert_str(str+j,i);
    }
    bfs();
    for(int i=0; i<n; i++)
        cout<<ans[i]<<endl;
    return 0;
}
```

