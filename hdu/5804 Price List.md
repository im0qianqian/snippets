# Price List

## **Problem Description**

> There are  shops numbered with successive integers from  to  in Byteland. Every shop sells only one kind of goods, and the price of the -th shop's goods is .Every day, Byteasar will purchase some goods. He will buy at most one piece of goods from each shop. Of course, he can also choose to buy nothing. Back home, Byteasar will calculate the total amount of money he has costed that day and write it down on his account book.
>
> However, due to Byteasar's poor math, he may calculate a wrong number. Byteasar would not mind if he wrote down a smaller number, because it seems that he hadn't used too much money.
>
> Please write a program to help Byteasar judge whether each number is sure to be strictly larger than the actual value.



## **Input**

> The first line of the input contains an integer  , denoting the number of test cases.In each test case, the first line of the input contains two integers, denoting the number of shops and the number of records on Byteasar's account book.
>
> The second line of the input contains  integers  , denoting the price of the -th shop's goods.
>
> Each of the next  lines contains an integer  , denoting each number on Byteasar's account book.



## **Output**

> For each test case, print a line with  characters. If the -th number is sure to be strictly larger than the actual value, then the -th character should be '1'. Otherwise, it should be '0'.



## **Sample Input**

    1
    3 3
    2 5 4
    1
    7
    10000



## **Sample Output**

    001



## **思路**

第三行所输入的数，代表购买的实际价格，然后接下来所输入的是账本上所记录的数据，如果这个数据大于购买总额，输出 `1` ，否则输出 `0` 。注意数据范围哦！

因为数据范围的问题，我被Hack过了……[伤心]



## **AC 代码**

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
__int64 a[100005],b[100005];
int main()
{
    __int64 T;
    scanf("%I64d",&T);
    while(T--)
    {
        __int64 n,m,t,s=0;
        scanf("%I64d%I64d",&n,&m);
        for(__int64 i=1; i<=n; i++)
        {
            scanf("%I64d",a+i);
            s+=a[i];
        }
        for(__int64 i=1; i<=m; i++)
        {
            scanf("%I64d",&t);
            if(t>s)printf("1");
            else printf("0");
        }
        puts("");
    }
    return 0;
}
```

