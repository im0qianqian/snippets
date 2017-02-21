# Blue Jeans

## **Description**

> The Genographic Project is a research partnership between IBM and The National Geographic Society that is analyzing DNA from hundreds of thousands of contributors to map how the Earth was populated. 
>
> As an IBM researcher, you have been tasked with writing a program that will find commonalities amongst given snippets of DNA that can be correlated with individual survey information to identify new genetic markers. 
>
> A DNA base sequence is noted by listing the nitrogen bases in the order in which they are found in the molecule. There are four bases: adenine (A), thymine (T), guanine (G), and cytosine (C). A 6-base DNA sequence could be represented as TAGACC. 
>
> Given a set of DNA base sequences, determine the longest series of bases that occurs in all of the sequences.



## **Input**

> Input to this problem will begin with a line containing a single integer n indicating the number of datasets. Each dataset consists of the following components:
>
> A single positive integer m (2 <= m <= 10) indicating the number of base sequences in this dataset.
>
> m lines each containing a single base sequence consisting of 60 bases.



## **Output**

> For each dataset in the input, output the longest base subsequence common to all of the given base sequences. If the longest common subsequence is less than three bases in length, display the string "no significant commonalities" instead. If multiple subsequences of the same longest length exist, output only the subsequence that comes first in alphabetical order.



## **Sample Input**

    3
    2
    GATACCAGATACCAGATACCAGATACCAGATACCAGATACCAGATACCAGATACCAGATA
    AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
    3
    GATACCAGATACCAGATACCAGATACCAGATACCAGATACCAGATACCAGATACCAGATA
    GATACTAGATACTAGATACTAGATACTAAAGGAAAGGGAAAAGGGGAAAAAGGGGGAAAA
    GATACCAGATACCAGATACCAGATACCAAAGGAAAGGGAAAAGGGGAAAAAGGGGGAAAA
    3
    CATCATCATCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
    ACATCATCATAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
    AACATCATCATTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT



## **Sample Output**

    no significant commonalities
    AGATAC
    CATCATCAT


## **题意**

找出m个串中的最长公共子串，若存在多个的话输出最小的那一个。



## **思路**

本来想到AC自动机或者后缀数组，然后一看m的范围，最大只有10，所以单纯暴力也能过了。

子串最短长度为1，最长为60。

可以用二分的思想，检测第一个字符串的长为mid的子串是否被其他所包含，若是，增大low，否则减小high。

当然，一个字符串的子串中可能会有重复，并且题意要求若有相同长度的公共子串时，输出字典序最小的一个，于是考虑用set来存储所有子串，一方面保证了集合元素的不重复，另一方面便是已有的排序，所以我们可以直接对集合枚举，若找到，则必是字典序最小的一个。



## **AC 代码**

```cpp
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<algorithm>
#include<set>
using namespace std;
typedef int LL;

char a[15][65];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n;
        scanf("%d%*c",&n);
        for(int i=0; i<n; i++)
            gets(a[i]);
        int low=1,high=60;      //初始子串最大长度与最小长度
        string ans="";
        while(low<=high)
        {
            int mid=(low+high)/2;   //二分
            char str[mid+1];
            bool flag=false;
            set<string>sk;
            for(int i=0; i<=60-mid; i++)    //枚举所有长为mid的子串，加入集合
            {
                strncpy(str,a[0]+i,mid);
                str[mid]=0;
                sk.insert((string)str);
            }
            for(set<string>::iterator j=sk.begin(); j!=sk.end(); j++)   //因为set默认已经排好序了，所以从字典序最小开始枚举
            {
                flag=false;
                for(int i=1; i<n; i++)      //枚举其他字符串
                    if(!strstr(a[i],(*j).data()))   //若无这一个子串
                    {
                        flag=true;
                        break;
                    }
                if(!flag)                   //若其他串都包含该子串
                {
                    ans=*j;
                    break;
                }
            }
            if(flag)high=mid-1;
            else low=mid+1;
        }
        if(ans.size()<3)cout<<"no significant commonalities"<<endl;
        else cout<<ans<<endl;
    }
    return 0;
}
```

