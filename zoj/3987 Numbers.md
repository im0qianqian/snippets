# **Numbers**

## **Description**

> DreamGrid has a nonnegative integer $n$. He would like to divide $n$ into $m$ nonnegative integers $a_1, a_2, \dots, a_m$ and minimizes their bitwise or (i.e. $n=a_1 + a_2 + \dots + a_m$ and $a_1 \text{ OR } a_2 \text{ OR } \dots \text{ OR } a_m$ should be as small as possible).



## **Input**

> There are multiple test cases. The first line of input contains an integer $T$ , indicating the number of test cases. For each test case:
>
> The first line contains two integers $n$ and $m$ ( $0 \le n < 10^{1000}, 1 \le m < 10^{100}$ ).
>
> It is guaranteed that the sum of the length of  does not exceed $20000$ .



## **Output**

> For each test case, output an integer denoting the minimum value of their bitwise or.



## **Sample Input**

    5
    3 1
    3 2
    3 3
    10000 5
    1244 10



## **Sample Output**

    3
    3
    1
    2000
    125



## **题意**

将整数 $n$ 拆分为 $m$ 个数的和，输出这 $m$ 个数 $or$ 的最小值。



## **思路**

考虑贪心，我们知道，$m$ 个数的二进制中某一位有一个为 $1$ ，最终的结果这一位一定是 $1$ ，因此尽可能多的让这 $m$ 个数充满二进制的这一位则为最优。

记录 $n$ 的二进制位数，从高位向低位开始枚举，对于当前位 $i$ ，首先判断 $n$ 是否可以充满 $m$ 行 $i$ 位以下的部分。

- 若可以，则说明溢出部分会被放置在当前位，于是尽可能多的填充当前第 $i$ 位共 $m$ 个二进制位。
- 若不可以，则说明剩余的数字可以被安置在低位，当前位为 $0$ 。





## **AC 代码**

```java
import java.math.BigInteger;
import java.util.Scanner;

public class Main {

	private static Scanner cin;
	static BigInteger n, m;

	public static void solve() {
		int len = 0;
		BigInteger tmp = n;
		while (tmp.compareTo(BigInteger.ZERO) != 0) {
			tmp = tmp.shiftRight(1);
			len++;
		}
		BigInteger ans = BigInteger.ZERO;
		for (int i = len - 1; i >= 0 && n.compareTo(BigInteger.ZERO) > 0; i--) {
			BigInteger cnt = BigInteger.ONE.shiftLeft(i);
			tmp = cnt.subtract(BigInteger.ONE).multiply(m); // 检验n是否可以填满m个低位
			if (tmp.compareTo(n) < 0) { // 若不可以填满则说明当前位一定被占用
				n = n.subtract(cnt.multiply(m.min(n.shiftRight(i)))); // 尽可能多的填充当前位
				ans = ans.or(cnt);
			}
		}
		System.out.println(ans);
	}

	public static void main(String[] args) {
		cin = new Scanner(System.in);
		int T;
		T = cin.nextInt();
		while ((T--) > 0) {
			n = cin.nextBigInteger();
			m = cin.nextBigInteger();
			solve();
		}
	}
}
```

