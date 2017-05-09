# Problem D

## **Problem Description**

> 度熊所居住的 D 国，是一个完全尊重人权的国度。以至于这个国家的所有人命名自己的名字都非常奇怪。一个人的名字由若干个字符组成，同样的，这些字符的全排列的结果中的每一个字符串，也都是这个人的名字。例如，如果一个人名字是 ACM，那么 AMC， CAM， MAC， MCA， 等也都是这个人的名字。在这个国家中，没有两个名字相同的人。
>
> 度熊想统计这个国家的人口数量，请帮助度熊设计一个程序，用来统计每一个人在之前被统计过多少次。



## **Input**

> 这里包括一组测试数据，第一行包含一个正整数N，接下来的N 行代表了 N 个名字。N 不会超过100,000，他们的名字不会超过40位.



## **Output**

> 对于每输入的一个人名，输出一个整数，代表这个人之前被统计了多少次。



## **Sample Input**

    5
    ACM
    MAC
    BBA
    ACM
    BAB



## **Sample Output**

    0
    1
    0
    2
    1



## **思路**

这也是一道很水的题哎！对每一个输入的字符串排序，然后就可以用 `map` 做啦~

如果单纯的用 `cin` 输入会超时，默认情况，`cin` 与 `stdin` 总是保持同步的，也就是说这两种方法可以混用，而不必担心文件指针混乱，同时 `cout` 和 `stdout` 也一样，两者混用不会输 出顺序错乱。正因为这个兼容性的特性，导致 `cin` 有许多额外的开销，如何禁用这个特性呢？只需一个语句 `std::ios::sync_with_stdio(false);` ，这样就可以取消 `cin` 于 `stdin` 的同步了，此时的 `cin` 就与 `scanf` 差不多 了。



## **AC 代码**

```cpp
#include <stdio.h>
#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;
#include<map>
map<string,int>k;
int main()
{
    int N;
    char c[40];
    cin>>N;
    getchar();
    while(N--)
    {
        memset(c,0,sizeof(c));
        gets(c);
        sort(c,c+strlen(c));
        printf("%d\n",k[string(c)]);
        k[string(c)]++;
    }
    return 0;
}
```

