# Necklace of Beads

## **Description**

> Beads of red, blue or green colors are connected together into a circular necklace of n beads ( n < 24 ). If the repetitions that are produced by rotation around the center of the circular necklace or reflection to the axis of symmetry are all neglected, how many different forms of the necklace are there?
>
> ![img](http://poj.org/images/1286_1.jpg)



## **Input**

> The input has several lines, and each line contains the input data n.
>
> -1 denotes the end of the input file.



## **Output**

> The output should contain the output data: Number of different forms, in each line correspondent to the input data.



## **Sample Input**

    4
    5
    -1



## **Sample Output**

    21
    39



## **题意**

用三种颜色的珠子连接成一个长度为N的圆形项链，项链通过旋转或者对称得到的情况算一种，问总共有多少种不同的形式。



## **思路**

[POJ 2409 Let it Bead （Polya）](https://www.dreamwings.cn/poj2409/4554.html) 的弱化版本，具体方法请戳左边链接。

需要注意的是，当输入为 `0` 的时候我们要进行特判，输出也为 `0` 。



## **AC 代码**

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<cmath>
#include<iostream>
using namespace std;
#include<queue>
#include<map>

int gcd(int a,int b)
{
    if(b%a==0)return a;
    return gcd(b%a,a);
}

int main()
{
    int n;
    while(cin>>n&&n!=-1)
    {
        if(n==0)
        {
            printf("0\n");
            continue;
        }
        long long ans=0;
        for(int i=1; i<=n; i++)
            ans+=pow(3,gcd(i,n));
        if(n&1)ans+=n*pow(3,n/2+1);
        else ans+=n/2*(pow(3,n/2+1)+pow(3,n/2));
        cout<<ans/n/2<<endl;
    }
    return 0;
}
```

