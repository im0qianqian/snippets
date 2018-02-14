## D. Interactive LowerBound

## **Description**

> This is an interactive problem.
>
> You are given a sorted in increasing order singly linked list. You should find the minimum integer in the list which is greater than or equal to x.
>
> More formally, there is a singly liked list built on an array of n elements. Element with index i contains two integers: valuei is the integer value in this element, and nexti that is the index of the next element of the singly linked list (or -1, if the current element is the last). The list is sorted, i.e. if nexti ≠  - 1, then valuenexti > valuei.
>
> You are given the number of elements in the list n, the index of the first element start, and the integer x.
>
> You can make up to 2000 queries of the following two types:
>
> ? i (1 ≤ i ≤ n) — ask the values valuei and nexti,
>
> ! ans — give the answer for the problem: the minimum integer, greater than or equal to x, or ! -1, if there are no such integers. Your program should terminate after this query.
>
> Write a program that solves this problem.



## **Input**

> The first line contains three integers n, start, x (1 ≤ n ≤ 50000, 1 ≤ start ≤ n, 0 ≤ x ≤ 10^9) — the number of elements in the list, the index of the first element and the integer x.



## **Output**

> To print the answer for the problem, print ! ans, where ans is the minimum integer in the list greater than or equal to x, or -1, if there is no such integer.



## **Example input**

    5 3 80
    97 -1
    58 5
    16 2
    81 1
    79 4



## **Example output**

    ? 1
    ? 2
    ? 3
    ? 4
    ? 5
    ! 81



## **题意**

交互题，对于第一次接触它的人一定很难搞懂题意吧~

在这里我来介绍一下这种题型，千千也是之前经过一位高人指点才懂得这类题目的做法的。

所谓交互，也就是我们与系统的互动，我们通过程序的输出作为系统的输入，然后系统会根据你所给定的数据决定它将要输出什么，随后我们再进行处理系统给出的数据，如此进行下去便是一次又一次的交互。

这类题目与平常我们所做的题目有一个非常关键的不同：强制在线

因为系统甚至可能会根据你的输出改变它的想法，此时你可以把它想象成另一个编码手，而现在便是你们之间较量。（它尽可能的想让你 WA ，而你尽可能的想让自己 AC ）

---

存在一个有序的单链表，给定长度，给定头节点的索引，给定一个整数 $x$ ，然后你需要在不超过 1999 次询问之中找到大于等于 x 的最小的那一个数是多少。



## **思路**

考虑 $n$ 的最大值只有 5w ，因此我们可以花费 1000 次的查询拆分整个索引块，然后在已知的数值小于 $x$ 的最大索引开始遍历，一般情况下剩余的 999 次查询足够找到我们想要的结果了。（关于如何拆分比较合理，随机或者等分都可以啦~ 代码中是用随机查询的）

PS：记得每次输出结束以后都要 `fflush(stdout);`



## **AC 代码**

```cpp
#include<bits/stdc++.h>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);
using namespace std;
typedef __int64 LL;
const int maxn = 2e5+10;

int n,head,x;
int ans = -1;
int main()
{
    srand(time(0));
    scanf("%d%d%d",&n,&head,&x);
    for(int i=0; i<1000; i++)
    {
        printf("? %d\n",(rand()%n*rand()%n)%n+1);
        fflush(stdout);
        int a,b;
        scanf("%d%d",&a,&b);
        if(a<x&&ans<a)
        {
            ans = a;
            head = b;
        }
    }
    for(int i=0; i<999; i++)
    {
        if(head==-1)
            break;
        printf("? %d\n",head);
        fflush(stdout);
        int a,b;
        scanf("%d%d",&a,&b);
        head = b;
        if(a>=x)
        {
            printf("! %d\n",a);
            return 0;
        }
    }
    printf("! -1\n");
    return 0;
}
```

