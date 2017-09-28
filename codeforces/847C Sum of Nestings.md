# C. Sum of Nestings

## **Description**

> Recall that the bracket sequence is considered regular if it is possible to insert symbols '+' and '1' into it so that the result is a correct arithmetic expression. For example, a sequence "(()())" is regular, because we can get correct arithmetic expression insering symbols '+' and '1': "((1+1)+(1+1))". Also the following sequences are regular: "()()()", "(())" and "()". The following sequences are not regular bracket sequences: ")(", "(()" and "())(()".
>
> In this problem you are given two integers n and k. Your task is to construct a regular bracket sequence consisting of round brackets with length 2·n with total sum of nesting of all opening brackets equals to exactly k. The nesting of a single opening bracket equals to the number of pairs of brackets in which current opening bracket is embedded.
>
> For example, in the sequence "()(())" the nesting of first opening bracket equals to 0, the nesting of the second opening bracket equals to 0 and the nesting of the third opening bracket equal to 1. So the total sum of nestings equals to 1.



## **Input**

> The first line contains two integers n and k (1 ≤ n ≤ 3·10^5, 0 ≤ k ≤ 10^18) — the number of opening brackets and needed total nesting.



## **Output**

> Print the required regular bracket sequence consisting of round brackets.
>
> If there is no solution print "Impossible" (without quotes).



## **Examples input**

    3 1



## **Examples output**

    ()(())



## **题意**

给定 $n$ 与 $k$ ，代表括号的数目与嵌套之和，输出一种嵌套序列满足这种情况。



## **思路**

我们考虑一种嵌套最大和的情况： `((((()))))` ，此时 $n=5,k=1+2+3+4=10$ 。

显然，对于 $k \in (1+2+3,1+2+3+4]$ 中的任意一个数，我们可以将原本在第四层的括号安置在合适的层中，当然， $k$ 在其他范围时也是一样的思路。

此时这部分的序列类似于 `(((())()))` 这样的结果，假如括号没有用完，我们在最后补单独的 `()` 即可。

而对于 $k>n \times (n-1)/2$ ，则应输出 `Impossible` ，因为在最极端的情况下都无法找到解，因此其一定不成立。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+10;
typedef __int64 LL;

LL n,k;
int main()
{
    cin>>n>>k;
    if(k>n*(n-1)/2)
        puts("Impossible");
    else
    {
        string ans;
        int base = 0;
        LL num = 0;
        while(num+base<=k)
        {
            num+=base++;
            ans+="(";
        }
        LL cnt = k-num;
        num = 0;
        while(base--)
        {
            ans+=")";
            if(base && base == cnt)ans+="()",num++;
            num++;
        }
        for(int i=0; i<n-num; i++)
            ans+="()";
        cout<<ans<<endl;
    }
    return 0;
}
```

