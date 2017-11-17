# D. Restoration of string

## **Description**

> A substring of some string is called the most frequent, if the number of its occurrences is not less than number of occurrences of any other substring.
>
> You are given a set of strings. A string (not necessarily from this set) is called good if all elements of the set are the most frequent substrings of this string. Restore the non-empty good string with minimum length. If several such strings exist, restore lexicographically minimum string. If there are no good strings, print "NO" (without quotes).
>
> A substring of a string is a contiguous subsequence of letters in the string. For example, "ab", "c", "abc" are substrings of string "abc", while "ac" is not a substring of that string.
>
> The number of occurrences of a substring in a string is the number of starting positions in the string where the substring occurs. These occurrences could overlap.
>
> String a is lexicographically smaller than string b, if a is a prefix of b, or a has a smaller letter at the first position where a and b differ.



## **Input**

> The first line contains integer n (1 ≤ n ≤ 10^5) — the number of strings in the set.
>
> Each of the next n lines contains a non-empty string consisting of lowercase English letters. It is guaranteed that the strings are distinct.
>
> The total length of the strings doesn't exceed 10^5.



## **Output**

> Print the non-empty good string with minimum length. If several good strings exist, print lexicographically minimum among them. Print "NO" (without quotes) if there are no good strings.



## **Examples input**

    4
    mail
    ai
    lru
    cf



## **Examples output**

    cfmailru



## **题意**

构造一个字典序最小的字符串，满足给定的所有串都是它的子串且这些串的出现频率最高。



## **思路**

显然，给定的一个串中如果出现两个相同的字母结果一定是 `NO` 。

对于 `mail` 与 `ai` ， `mail` 与 `ailkk` ， `mail` 与 `kkmai` 这三种类型的子串我们采取合并措施，若出现比如 `abc` 与 `abxc` 这种部分不连续的匹配或匹配错误则一定输出 `NO` 。

暴力枚举即可，因为相同字母已经把每个串的长度限制在了 26 以内，再加上部分不连续匹配的限制条件，最后能对答案做出贡献的串很少很少，想必测试数据中 n 在某个值以上的结果都是 `NO` 。

合并完的串之间是没有任何关联的，我们可以对这些串排序输出即字典序最小解。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);
typedef long long LL;
using namespace std;
const int maxn = 2e6+10;

string s[maxn];
int vis[26];
int n;

bool solve2(int s1,int s2)
{
    int len1 = s[s1].length();
    int len2 = s[s2].length();
    memset(vis,0,sizeof(vis));
    for(int i=0; i<len1; i++)
        vis[s[s1][i]-'a']=i+1;
    for(int i=0; i<len2; i++)
        if(vis[s[s2][i]-'a'])   //找的第一个相同位
        {
            int yi = vis[s[s2][i]-'a']-1;
            int ni = i;
            string cnt;
            for(int j=-26; j<26; j++)   //合并两个串
            {
                if(yi+j>=0&&yi+j<len1&&ni+j>=0&&ni+j<len2)
                {
                    if(s[s1][yi+j]!=s[s2][ni+j])
                        return false;
                    cnt+=s[s1][yi+j];
                }
                else if(yi+j>=0&&yi+j<len1)
                    cnt+=s[s1][yi+j];
                else if(ni+j>=0&&ni+j<len2)
                    cnt+=s[s2][ni+j];
            }
            memset(vis,false,sizeof(vis));  //合并完以后检查是否合法
            for(int j=0; j<(int)cnt.length(); j++)
                if(++vis[cnt[j]-'a']>1)
                    return false;
            s[n++] = cnt;
            s[s1] = "";
            s[s2] = "";
            return true;
        }
    return true;
}

void solve()
{
    for(int i=0; i<n; i++)
    {
        memset(vis,0,sizeof(vis));
        for(auto j:s[i])
            if(++vis[j-'a']>1)
            {
                cout<<"NO"<<endl;
                return;
            }
    }
    for(int i=0; i<n; i++)
        for(int j=i+1; j<n; j++)
            if(s[i]!=""&&s[j]!=""&&!solve2(i,j))
            {
                cout<<"NO"<<endl;
                return;
            }
    sort(s,s+n);
    for(int i=0; i<n; i++)
        cout<<s[i];
}

int main()
{
    IO;
    cin>>n;
    for(int i=0; i<n; i++)
        cin>>s[i];
    solve();
    return 0;
}
```

