# 3-idiots

## **Description**

> King OMeGa catched three men who had been streaking in the street. Looking as idiots though, the three men insisted that it was a kind of performance art, and begged the king to free them. Out of hatred to the real idiots, the king wanted to check if they were lying. The three men were sent to the king's forest, and each of them was asked to pick a branch one after another. If the three branches they bring back can form a triangle, their math ability would save them. Otherwise, they would be sent into jail.
>
> However, the three men were exactly idiots, and what they would do is only to pick the branches randomly. Certainly, they couldn't pick the same branch - but the one with the same length as another is available. Given the lengths of all branches in the forest, determine the probability that they would be saved.



## **Input**

> An integer T(T≤100) will exist in the first line of input, indicating the number of test cases.
>
> Each test case begins with the number of branches N(3≤N≤10^5).
>
> The following line contains N integers a_i (1≤a_i≤10^5), which denotes the length of each branch, respectively.



## **Output**

> Output the probability that their branches can form a triangle, in accuracy of 7 decimal places.



## **Sample Input**

    2
    4
    1 3 3 4
    4
    2 3 3 4



## **Sample Output**

    0.5000000
    1.0000000



## **题意**

给定一些数字表示线段的长度，求任意选取三个可以组成三角形的概率。



## **思路**

在所有数字中选取三个的总组合数为 $C_n^3$ ，所以问题就转化成了取三个数可以形成三角形的组合有多少种。

组成三角形需要找两条短边的长度之和大于一条长边，因此我们要先计算选取两条边所能组合成的长度有哪些。

而两条边组合后的长度本质上为其和，因此我们可以用 `num[i]` 来记录长度为 `i` 的边的个数。

然后求 `num` 数组自身对自身的卷积，其结果便是所有两两组合的情况了。



如对于 `{1,3,3,4}` 来说， `num = {0,1,0,2,1}` 。

`{0,1,0,2,1} * {0,1,0,2,1}` 卷积结果为 `{0,0,1,0,4,2,4,4,1}` 。

卷积的意义其实是**增幅**，**平移**再**相加**。（和乘法的原理一致）



**我们知道：时域卷积，频域乘积。**

因此我们可以采用 FFT(DFT) 先将 `num` 转换为另一种表示形式（求值），然后两两做（乘积）以后再使用 FFT(IDFT) 将其转换回来（插值）。

此时我们便求得了 `num` 自身对自身的卷积结果啦。



结果中的值代表着 `num` 自身的两两组合。

- 因为包含某个数本身与本身的组合，所以我们要先去除这样的情况。
- 第一个选取 `a1` ，第二个选取 `a2` 与第一个选取 `a2` ，第二个选取 `a1` 我们认为是一样的，因此 `num` 数组需要整体除以 `2` 。



对 `num` 数组求前缀和，原数组 `a` 进行排序，接下来我们需要找第三条边，满足另外两条边的和大于这条边且标号都小于这条边。

此时我们假设 `a[i]` 为三角形中最长的一条边，则长度大于 `a[i]` 的取法有 `sum[len]-sum[a[i]]` 种。

但是我们需要满足取到的这两条边的边长都小于 `a[i]` ，假设这两条边分别为 `x,y` ，则可能出现以下几种情况：

- `x,y` 中有一个值大于 `a[i]` ，另一个值小于 `a[i]` ，总共有 `(n-i-1)*i` 种情况
- `x,y` 的值都大于 `a[i]` ，总共有 `(n-i-1)*(n-i-2)/2` 种情况
- `x,y` 中有一点落在 `i` 这一位置，总共有 `n-1` 种情况

于是减掉这三种情况剩下的即为满足题意的组合咯，累加统计即可。



## **AC 代码**

```cpp
#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<iomanip>
#include<cmath>
#include<cstring>
#include<vector>
typedef __int64 LL;
#define pi acos(-1.0)
using namespace std;

const int maxn = 400005;
//复数结构体
struct complex
{
    double r,i;
    complex(double R=0,double I=0)
    {
        r=R;
        i=I;
    }
    complex operator+(const complex &a)
    {
        return complex(r+a.r,i+a.i);
    }
    complex operator-(const complex &a)
    {
        return complex(r-a.r,i-a.i);
    }
    complex operator*(const complex &a)
    {
        return complex(r*a.r-i*a.i,r*a.i+i*a.r);
    }
};
/*
 *进行FFT和IFFT前的反转变换
 *位置i和i的二进制反转后位置互换，(如001反转后就是100)
 *len必须去2的幂
 */
void change(complex x[],int len)
{
    int i,j,k;
    for(i = 1, j = len/2; i <len-1; i++)
    {
        if (i < j) swap(x[i],x[j]);
        //交换互为小标反转的元素，i<j保证交换一次
        //i做正常的+1,j做反转类型的+1，始终i和j是反转的
        k = len/2;
        while (j >= k)
        {
            j -= k;
            k /= 2;
        }
        if (j < k) j += k;
    }
}
/*
 *做FFT
 *len必须为2^n形式，不足则补0
 *on=1时是DFT，on=-1时是IDFT
 */
void fft (complex x[],int len,int on)
{
    change(x,len);
    for (int i=2; i<=len; i<<=1)
    {
        complex wn(cos(-on*2*pi/i),sin(-on*2*pi/i));  //单位复根e^(2*PI/m)用欧拉公式展开
        for (int j=0; j<len; j+=i)
        {
            complex w(1,0);
            for (int k=j; k<j+i/2; k++)
            {
                complex u = x[k];
                complex t = w*x[k+i/2];
                x[k] = u+t;
                x[k+i/2] = u-t;
                w = w*wn;
            }
        }
    }
    if (on == -1)
        for (int i=0; i<len; i++)
            x[i].r /= len;
}

complex x[maxn];
int a[maxn];
LL num[maxn],sum[maxn];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n;
        scanf("%d",&n);
        memset(num,0,sizeof(num));
        for(int i=0; i<n; i++)
        {
            scanf("%d",a+i);
            num[a[i]]++;
        }
        sort(a,a+n);
        int len1 = a[n-1]+1;
        int len=1;
        while(len<2*len1)len<<=1;
        for(int i=0; i<len1; i++)
            x[i]=complex(num[i],0);
        for(int i=len1; i<len; i++)     // 补零
            x[i]=complex(0,0);
        fft(x,len,1);                   // 求值
        for(int i=0; i<len; i++)        // 乘法
            x[i]=x[i]*x[i];
        fft(x,len,-1);                  // 插值
        for(int i=0; i<len; i++)
            num[i]=(x[i].r+0.5);        // 四舍五入
        for(int i=0; i<n; i++)          // 去除挑选相同数字的情况
            num[a[i]+a[i]]--;
        for(int i=1; i<len; i++)        // 选取与顺序无关
            num[i]/=2;
        for(int i=1; i<=len; i++)
            sum[i]=sum[i-1]+num[i];
        LL ans=0;
        for(int i=0; i<n; i++)
        {
            ans+=sum[len]-sum[a[i]];
            ans-=LL(n-i-1)*i;           // 一大一小
            ans-=LL(n-i-1)*(n-i-2)/2;   // 两大
            ans-=n-1;                   // 其中有一点在当前位
        }
        LL tot=1LL*n*(n-1)*(n-2)/6;     // 所有组合
        printf("%.7lf\n",(double)ans/tot);
    }
    return 0;
}
```

