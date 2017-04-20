# Astronomy

## **Description**

> There are n planets in the planetary system of star X. They orbit star X in circular orbits located in the same plane. Their tangent velocities are constant. Directions of orbiting of all planets are the same.
>
> Sometimes the event happens in this planetary system which is called planet parade. It is the moment when all planets and star X are located on the same straight line.
>
> ![img](http://poj.org/images/3101_1.gif)
>
> Your task is to find the length of the time interval between two consecutive planet parades.



## **Input**

> The first line of the input file contains n — the number of planets (2 ≤ n ≤ 1 000).
>
> Second line contains n integer numbers ti — the orbiting periods of planets (1 ≤ ti ≤ 10 000). Not all of ti are the same.



## **Output**

> Output the answer as a common irreducible fraction, separate numerator and denominator by a space.



## **Sample Input**

    3
    6 2 3



## **Sample Output**

    3 1



## **题意**

给出 `n` 个行星围绕恒星转动的周期，刚开始所有的行星都在恒星的一侧并且排成一条直线。问最少再经过多长时间所有的行星出现在同一条直线上。



## **思路**

我们先来看两个行星的情况，假设 `t` 时间之后这两个行星会出现在同一条直线上。

则 $\frac{2π}{T_0}t-\frac{2π}{T_1}t=πk$ 其中 $k$ 为一整数。

**化简得：** $\frac{2(T_1-T_0)t}{T_0T_1}=k$ ，为使 `k` 为最小正整数， $t=\frac{T_0T_1}{2(T_1-T_0)t}$ 。



对于两个行星以上的情况，可以两两计算得到的 `t` ，然后求出**最小公倍数**即可。

---

**分式的最小公倍数求法：** （分子分母约分到最简形式）

$$\frac{a}{b}~\frac{c}{d}:\frac{lcm(a,c)}{gcd(b,d)}$$



## **AC 代码**

```java
import java.util.Scanner;
import java.math.BigInteger;

public class Main {
	private static Scanner cin;

	public static void main(String[] args) {
		int N;
		BigInteger on, lcm = null, gc = null;
		cin = new Scanner(System.in);
		N = cin.nextInt();
		on = cin.nextBigInteger();
		lcm = on;
		for (int i = 1; i < N; i++) {
			BigInteger x;
			x = cin.nextBigInteger();
			if (i == 1) {
				lcm = lcm.multiply(x);
				gc = (x.subtract(on)).abs().multiply(new BigInteger("2"));
				BigInteger r = lcm.gcd(gc);
				lcm = lcm.divide(r);
				gc = gc.divide(r);
			} else {
				BigInteger n1 = on.multiply(x);
				BigInteger n2 = (x.subtract(on)).abs().multiply(new BigInteger("2"));
				BigInteger r = n1.gcd(n2);
				n1 = n1.divide(r);
				n2 = n2.divide(r);
				lcm = lcm.divide(lcm.gcd(n1)).multiply(n1);
				gc = gc.gcd(n2);
				r = lcm.gcd(gc);
				lcm = lcm.divide(r);
				gc = gc.divide(r);
			}
		}
		System.out.println(lcm + " " + gc);
	}
}
```

