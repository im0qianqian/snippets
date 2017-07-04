# Number Sequence

## **Description**

> A single positive integer i is given. Write a program to find the digit located in the position i in the sequence of number groups S1S2...Sk. Each group Sk consists of a sequence of positive integer numbers ranging from 1 to k, written one after another. 
>
> For example, the first 80 digits of the sequence are as follows: 
>
> 11212312341234512345612345671234567812345678912345678910123456789101112345678910



## **Input**

> The first line of the input file contains a single integer t (1 ≤ t ≤ 10), the number of test cases, followed by one line for each test case. The line for a test case contains the single integer i (1 ≤ i ≤ 2147483647)



## **Output**

> There should be one output line per test case containing the digit located in the position i.



## **Sample Input**

    2
    8
    3



## **Sample Output**

    2
    2



## **题意**

这道题目的题意很简单，就是给你一个有规律的序列 `1 12 123 1234 12345 …` 然后给出一个整数 `N` ，问第 `N` 位是什么数字。



## **思路**

题目中有说明 `N<=2147483647` ，也就相当于这个字符串的长度是这些，显然我们不能直接使用暴力的方法去枚举它的每一位，因为，恩~因为我试过…… 爆栈了 233



既然是一道找规律的题目，那就要好好看一看题目了。

我们知道，对于每一个数 `x` ，它的位数等于 $\log10(x)+1$ 。

然后对于每一个数它所组成序列*（比如3组成的序列是123）*等于它前面那个数的序列加本身。

每一个数的序列都可以作为后一个数序列的前缀，既然有这种规律，我们可以创建一个数组保存每一个数所产生序列的位数，然后用另一个数组保存当前数以及它前面所有序列的位数和。



`a` 保存当前序列位数，则 `a[i]=a[i-1]+log10(i)+1` ;

`s` 保存前多少个序列总位数，则 `s[i]=s[i-1]+a[i]` ;



对于给定的整数 `N` ，我们可以根据 `s` 先计算出这个整数所在的序列是第多少个，然后 `N-s[i-1]` 便是 `N` 在第 `i` 这个序列的位置，至于序列嘛！当然就是 `1234567891011121314` 这样的咯~



然后我们知道 `N` 的位置，这个时候可以模拟创建整个序列了，不过感觉会有点慢，应该不会卡到 `TLE` 的。其他更快的算法呢！看代码 咯！



## **AC 代码**

```cpp
#include<iostream>
#include<math.h>
using namespace std;
#define SIZE 31269              //这个数字是计算出来的，差不多刚好满足题目位数
unsigned a[SIZE],s[SIZE];
void init()
{
    a[1]=s[1]=1;
    for(int i=2; i<SIZE; i++)
    {
        a[i]=a[i-1]+log10(i)+1; //保存当前序列总位数
        s[i]=s[i-1]+a[i];       //保存前i的序列位数和
    }
}
int solve(unsigned n)
{
    int i=1,len=0;;
    while(s[i]<n)i++;           //根据s计算整数在第几个序列
    int st=n-s[i-1];            //求出它在这个序列中的位置
    for(i=1; len<st; i++)       //i代表当前位置的数字
        len+=log10(i)+1;
    return (i-1)/(int)pow(10,len-st)%10;    //返回结果
}
int main(void)
{
    int N;
    init();             //打表a s
    cin>>N;
    while(N--)
    {
        unsigned n;
        cin>>n;
        cout<<solve(n)<<endl;
    }
    return 0;
}
```

