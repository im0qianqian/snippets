# Problem B

## **Problem Description**

> 度熊面前有一个全是由1构成的字符串，被称为全1序列。你可以合并任意相邻的两个1，从而形成一个新的序列。对于给定的一个全1序列，请计算根据以上方法，可以构成多少种不同的序列。



## **Input**

> 这里包括多组测试数据，每组测试数据包含一个正整数N，代表全1序列的长度。
>
> 1≤N≤200



## **Output**

> 对于每组测试数据，输出一个整数，代表由题目中所给定的全1序列所能形成的新序列的数量。



## **Sample Input**

    1
    3
    5



## **Sample Output**

    1
    3
    8



## **思路**

题目说了那么多，终究没有说这就是一个斐波那契数列~ o(╯□╰)o

既然是斐波那契数列，接下来就很好做咯！不过要注意，斐波那契数列中的第 `200` 个可是很大的哦！

`C/C++` 用大数， `Java` 用 `Biginteger`



## **AC 代码**

```cpp
#include "stdio.h"
#include "stdlib.h"
#define N 22                //22位能表示第100个以内的斐波那契数列值
//大数加法函数
char * Add(char * x1, char * x2)
{
    char * y = (char *) malloc(sizeof(char *) * N);
    int i = 0;
    int t = 0;              //表示进位
    //实现大数加法，数组前面存的是数值的高位。如123在数组中是{'3','2','1','\0'}
    //处理相同长度的部分
    while(x1[i] != '\0' && x2[i] != '\0')
    {
        y[i] = (x1[i] - '0' + x2[i] - '0' + t) % 10 + '0';
        t = (x1[i] - '0' + x2[i] - '0' + t) / 10;
        i++;
    }
    //如果x1比x2长
    while(x1[i] != '\0')
    {
        y[i] = (x1[i] - '0' + t) % 10 + '0';
        t = (x1[i] - '0' + t) / 10;
        i++;
    }
    //如果x2比x1长
    while(x2[i] != '\0')
    {
        y[i] = (x2[i] - '0' + t) % 10 + '0';
        t = (x2[i] - '0' + t) / 10;
        i++;
    }
    //如果还有进位
    if (t == 1)y[i++] = '1';
    y[i] = '\0';
    return y;
}
//输出
void Output(char * y)
{
    //先找到\0的位置，然后逆序输出
    int i = 0;
    while(y[i] != '\0')i++;
    i--;
    while(i >= 0)
        printf("%d", y[i--] - '0');
}

int main()
{
    int b;
    while(~scanf("%d", &b))
    {
        if(b)
        {
            getchar();
            int count = b;
            int i;
            char * x1 = (char *)malloc(sizeof(char) * N);
            char * x2 = (char *)malloc(sizeof(char) * N);
            char * y = (char *)malloc(sizeof(char) * N);
            //初始化y, x1, x2
            for (i = 0; i < N; i++)
            {
                x1[i] = '\0';
                x2[i] = '\0';
                y[i] = '\0';
            }
            //给x1和x2赋初值
            x1[0] = '0';
            x1[1] = '\0';
            x2[0] = '1';
            x2[1] = '\0';
            //斐波那契数列，叠加
            for(i = 1; i <= count; i++)
            {
                y = Add(x1, x2);
                x1 = x2;
                x2 = y;
            }
            //输出结果
            Output(y);
            printf("\n");
        }
        else printf("\n");
    }
    return 0;
}
```



```java
import java.util.Scanner;
import java.math.BigInteger;
public class Main {
    public static BigInteger[]dp=new BigInteger[205];
    public static void main(String[] args) {
        // TODO Auto-generated method stub
        Scanner cin=new Scanner(System.in);
        //int n=cin.nextInt();
        Init();
        while(cin.hasNext())
        {
            int n=cin.nextInt();
            if(n>=1&&n<=200)
            {
                System.out.print(dp[n]);
            }
            System.out.println();
        }
    }
    public static void Init()
    {
        dp[1]=new BigInteger("1");
        dp[2]=new BigInteger("2");
        for(int i=3;i<=201;i++)
        {
            dp[i]=dp[i-1].add(dp[i-2]);
        }
    }
}
```

